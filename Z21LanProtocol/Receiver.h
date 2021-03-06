﻿#ifndef RECEIVER_H
#define RECEIVER_H

#include <QObject>
#include <QHostAddress>
#include <QUdpSocket>
#include "Z21SystemState.h"
#include "Z21Crc.h"

class Z21LanProtocol;

class Receiver : public QObject
{
    Q_OBJECT
public:
    explicit Receiver(Z21LanProtocol* z21, QObject *parent = 0);

signals:
    void lan_SerialNumber(quint32 serial);
    void lan_BroadcastFlags(quint32 flags);

    void xbus_Version(quint8 version, quint8 centralID);

public slots:
    void StartWork(const QHostAddress& address, quint16 port);

private slots:
    void ReadPendingDatagrams();

private:
    QUdpSocket* socket = nullptr;
    Z21LanProtocol* z21 = nullptr;

private:
    Z21Crc CRC;
};

#endif // RECEIVER_H
