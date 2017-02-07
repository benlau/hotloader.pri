INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

CONFIG += c++11

QT += concurrent

HOT_LOADER_HOST_BINS = $$[QT_HOST_BINS]
DEFINES += HOT_LOADER_HOST_BINS=\\\"$$HOT_LOADER_HOST_BINS\\\"

HEADERS += \
    $$PWD/hotloader.h \
    $$PWD/HotLoader

SOURCES += \
    $$PWD/hotloader.cpp
