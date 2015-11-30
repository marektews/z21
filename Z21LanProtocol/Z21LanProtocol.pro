#-------------------------------------------------
#
# Project created by QtCreator 2015-11-22T10:01:39
#
#-------------------------------------------------

QT       += network
QT       -= gui

DLLDESTDIR = ../

TARGET = Z21LanProtocol
TEMPLATE = lib

DEFINES += Z21LANPROTOCOL_LIBRARY

SOURCES += Z21LanProtocol.cpp \
    Receiver.cpp \
    TransmitterTask.cpp \
    Z21SystemState.cpp \
    Z21Current.cpp \
    Z21Voltage.cpp \
    Z21Temperature.cpp \
    Z21CentralState.cpp \
    Z21Crc.cpp \
    Z21LocoInfo.cpp \
    Z21LocoAddress.cpp \
    Z21Direction.cpp \
    Z21Functions.cpp \
    Z21Speed.cpp

HEADERS += Z21LanProtocol.h \
    global.h \
    Receiver.h \
    TransmitterTask.h \
    Z21SystemState.h \
    Z21Current.h \
    Z21Voltage.h \
    Z21Temperature.h \
    Z21CentralState.h \
    Z21Crc.h \
    Z21LocoInfo.h \
    Z21LocoAddress.h \
    Z21Direction.h \
    Z21Functions.h \
    Z21Speed.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
