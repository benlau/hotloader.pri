#pragma once
#include <QObject>

class Tests : public QObject
{
    Q_OBJECT
public:
    explicit Tests(QObject *parent = 0);

private slots:

    void test_HotLoader_run();

    void test_HotLoader_mappedUrl();

};

