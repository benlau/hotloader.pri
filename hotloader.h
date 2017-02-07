#ifndef HOTLOADER_H
#define HOTLOADER_H

#include <QStringList>
#include <QUrl>
#include <functional>

class HotLoader
{
public:
    HotLoader();

    bool hotReloadEnabled() const;

    void setHotReloadEnabled(bool hotReloadEnabled);

    void addResourceFile(const QString& file);

    int run(std::function<int (void)> func);

    QUrl mappedUrl(const QString& source) const;

    QString resourceMapRoot() const;
    void setResourceMapRoot(const QString &resourceMapRoot);

private:
    void compile();

    bool m_hotReloadEnabled;

    QString m_resourceMapRoot;
    QStringList m_resourceFiles;
    QStringList m_compiledResourceFiles;
};

#endif // HOTLOADER_H
