#-------------------------------------------------
#
# Project created by QtCreator 2015-11-22T17:07:27
#
#-------------------------------------------------

QT       += core gui network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


DESTDIR = ../../
TARGET = Test1
TEMPLATE = app

INCLUDEPATH += ../../Z21LanProtocol

CONFIG(debug, debug|release) {
    LIBS += ../../Z21LanProtocol/debug/Z21LanProtocol.lib
}
else {
    LIBS += ../../Z21LanProtocol/release/Z21LanProtocol.lib
}

SOURCES += main.cpp\
        Dialog.cpp

HEADERS  += Dialog.h

FORMS    += Dialog.ui
