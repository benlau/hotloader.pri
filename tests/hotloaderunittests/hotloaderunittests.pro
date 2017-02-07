#-------------------------------------------------
#
# Project created by QtCreator 2016-02-25T18:56:34
#
#-------------------------------------------------

QT       += testlib qml

TARGET = hotloaderunittests
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES +=     main.cpp     tests.cpp

DEFINES += SRCDIR=\\\"$$PWD/\\\" QUICK_TEST_SOURCE_DIR=\\\"$$PWD/qmltests\\\"

include(vendor/vendor.pri)
include(../../hotloader.pri)

DISTFILES +=     qpm.json \
     qmltests/tst_QmlTests.qml \
    sample/sample.qrc

HEADERS +=     tests.h

message($$[QT_HOST_BINS])
