#ifndef RECEIVER_H
#define RECEIVER_H

#include <QObject>
#include <QHostAddress>
#include <QUdpSocket>
#include "Z21SystemState.h"

class Receiver : public QObject
{
    Q_OBJECT
public:
    explicit Receiver(QObject *parent = 0);

signals:
    void lan_SerialNumber(quint32 serial);
    void lan_BroadcastFlags(quint32 flags);
    void lan_SystemState(const Z21SystemState& systemState);

    void xbus_Version(quint8 version, quint8 centralID);

public slots:
    void StartWork(const QHostAddress& address, quint16 port);

private slots:
    void ReadPendingDatagrams();

private:
    QUdpSocket* socket;

private:
    quint8 crc;
    void CRC(quint8 v, bool start = false);
    bool CheckCRC(quint8 crc);
};

#endif // RECEIVER_H
