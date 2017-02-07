#ifndef HOTLOADER_H
#define HOTLOADER_H

#include <QStringList>
#include <functional>

class HotLoader
{
public:
    HotLoader();

    bool hotReloadEnabled() const;

    void setHotReloadEnabled(bool hotReloadEnabled);

    void addResourceFile(const QString& file);

    int run(std::function<int (void)> func);

    QString mapRoot() const;
    void setMapRoot(const QString &mapRoot);

private:
    void compile();

    bool m_hotReloadEnabled;
    QString m_mapRoot;

    QStringList m_resourceFiles;
    QStringList m_compiledResourceFiles;
};

#endif // HOTLOADER_H
