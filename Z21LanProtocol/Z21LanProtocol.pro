#-------------------------------------------------
#
# Project created by QtCreator 2015-11-22T10:01:39
#
#-------------------------------------------------

QT       += network
QT       -= gui

TARGET = Z21LanProtocol
TEMPLATE = lib

DEFINES += Z21LANPROTOCOL_LIBRARY

SOURCES += Z21LanProtocol.cpp

HEADERS += Z21LanProtocol.h \
    global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
