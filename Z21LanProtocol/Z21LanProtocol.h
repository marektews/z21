#ifndef Z21LANPROTOCOL_H
#define Z21LANPROTOCOL_H

#include <QObject>
#include <QHostAddress>
#include <QThread>
#include <QThreadPool>
#include "global.h"
#include "Z21SystemState.h"

class Z21_EXPORT Z21LanProtocol : public QObject
{
    Q_OBJECT

public:
    Z21LanProtocol();
    ~Z21LanProtocol();

    bool Configure(const QHostAddress& address = QHostAddress("192.168.0.111"), quint16 port = 21105);

// SYSTEM, STATUS, VERSION
public:
    bool GetSerialNumber();                 // LAN_GET_SERIAL_NUMBER request
    bool Logoff();                          // LAN_LOGOFF request

    bool GetBroadcastFlags();               // LAN_GET_BROADCASTFLAGS request
    bool SetBroadcastFlags(quint32 flags, quint32 mask);  // LAN_SET_BROADCASTFLAGS request

signals:
    void lan_SerialNumber(quint32 serial, const QString& str);  // LAN_GET_SERIAL_NUMBER responce
    void lan_BroadcastFlags(quint32 flags);                     // LAN_GET_BROADCASTFLAGS responce
    void lan_SystemState(const Z21SystemState& systemState);    // LAN_SYSTEMSTATE_DATACHANGED broadcast message

// X-BUS
public:
    bool XBus_GetVersion();          // LAN_X_GET_VERSION request

signals:
    void xbus_Version(quint8 version, quint8 centralID);      // LAN_X_GET_VERSION responce

// LocoNet
public:

signals:

private:
    bool AddRequest(const QByteArray& data);

private:
    QHostAddress    address = QHostAddress("192.168.0.111");
    quint16         port = 21105;
    QThread         receiver;
    QThreadPool     transmitter;

    quint32         broadcastFlags = 0;

signals:
    void startReceiver(const QHostAddress& address, quint16 port);

private slots:
    void on_receiver_serialnumber(quint32 serial);
    void on_receiver_broadcastFlags(quint32 flags);
};

#endif // Z21LANPROTOCOL_H
