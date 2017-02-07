#include <QtConcurrent>
#include <QtShell>
#include <QResource>
#include "hotloader.h"

template <typename T, typename F, typename I>
QList<T> blockingMapped(QList<I> input, F f) {
    QList<QFuture<T> > futures;
    QList<T> res;

    for (int i = 0 ; i < input.size(); i++) {
        futures << QtConcurrent::run(f, input[i]);
    }

    for (int i = 0 ; i < input.size(); i++) {
        futures[i].waitForFinished();
        res << futures[i].result();
    }

    return res;
}

HotLoader::HotLoader() : m_hotReloadEnabled(false), m_resourceMapRoot("/hot-loader-dynamic-resource")
{

}

bool HotLoader::hotReloadEnabled() const
{
    return m_hotReloadEnabled;
}

void HotLoader::setHotReloadEnabled(bool hotReloadEnabled)
{
    m_hotReloadEnabled = hotReloadEnabled;
}

void HotLoader::addResourceFile(const QString &file)
{
    m_resourceFiles << file;
}

int HotLoader::run(std::function<int (void)> func)
{
    if (m_hotReloadEnabled) {
        compile();
    }

    int ret = func();

    foreach (QString rccFile, m_compiledResourceFiles) {
        QResource::unregisterResource(rccFile, m_resourceMapRoot);
    }

    return ret;
}

QUrl HotLoader::mappedUrl(const QString &source) const
{
    QUrl input(source);
    if (!input.isValid()) {
        if (source.indexOf(":") == 0) {
            input = QUrl();
            input.setPath(source.mid(1,-1));
            input.setScheme("qrc");
        } else {
            input = QUrl::fromLocalFile(source);
        }
    }

    if (!m_hotReloadEnabled) {
        return input;
    }

    QString path = input.path();
    input.setPath(m_resourceMapRoot + path);
    return input;
}

void HotLoader::compile()
{
    //@TODO - handle Windows
    //@TODO - Return promise

    auto func = [&](const QString& file) -> QString {
        QString rcc = QString(HOT_LOADER_HOST_BINS) + "/rcc";
        QString output = QtShell::basename(file).replace(".qrc","") + ".rcc";
        QProcess process;
        QStringList arguments;

        arguments << "--binary" << file << "-o" << output;
        process.start(rcc, arguments);
        process.setProcessChannelMode(QProcess::MergedChannels);
        process.waitForFinished();

        if (process.exitCode() != 0) {
            qWarning() << process.errorString();
        } else {
            qDebug().noquote() << "Compiled" << file;
        }

        return output;
    };

    m_compiledResourceFiles = blockingMapped<QString>(m_resourceFiles, func);

    foreach (QString rccFile, m_compiledResourceFiles) {
        QResource::unregisterResource(rccFile, m_resourceMapRoot);
        QResource::registerResource(rccFile, m_resourceMapRoot);
    }
}

QString HotLoader::resourceMapRoot() const
{
    return m_resourceMapRoot;
}

void HotLoader::setResourceMapRoot(const QString &mapRoot)
{
    m_resourceMapRoot = mapRoot;
}
