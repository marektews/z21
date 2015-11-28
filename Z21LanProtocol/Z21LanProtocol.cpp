#include <QDataStream>
#include "Z21LanProtocol.h"
#include "TransmitterTask.h"
#include "Receiver.h"

/**
 * @brief Z21LanProtocol::Z21LanProtocol
 */
Z21LanProtocol::Z21LanProtocol()
{
    qRegisterMetaType<QHostAddress>("QHostAddress");
    qRegisterMetaType<Z21SystemState>("Z21SystemState");
    qRegisterMetaType<Z21CentralState>("Z21CentralState");
}

/**
 * @brief Z21LanProtocol::~Z21LanProtocol
 */
Z21LanProtocol::~Z21LanProtocol()
{
    receiver.quit();
    receiver.wait();
    transmitter.waitForDone();
}

/**
 * @brief Z21LanProtocol::Configure
 * @param address Z21 host address, default is 192.168.0.111
 * @param port Z21 host port number, default is 21105
 * @return true if success
 */
bool Z21LanProtocol::Configure(const QHostAddress &address, quint16 port)
{
    this->address = address;
    this->port = port;

    // create receiver
    Receiver* worker = new Receiver(this);
    if(worker == nullptr) return false;
    worker->moveToThread(&receiver);
    connect(&receiver, &QThread::finished, worker, &QObject::deleteLater);
    connect(this, &Z21LanProtocol::startReceiver, worker, &Receiver::StartWork);

    connect(worker, &Receiver::lan_SerialNumber, this, &Z21LanProtocol::on_receiver_serialnumber);
    connect(worker, &Receiver::lan_BroadcastFlags, this, &Z21LanProtocol::on_receiver_broadcastFlags);

    receiver.start();
    emit startReceiver(QHostAddress::Any, port);

    // create transmitter
    transmitter.setMaxThreadCount(5);

    Send_GetBroadcastFlags();
    return true;
}

/**
 * @brief Z21LanProtocol::Send_GetSerialNumber
 * @return true if success
 */
bool Z21LanProtocol::Send_GetSerialNumber()
{
    QByteArray arr;
    QDataStream stream(&arr, QIODevice::WriteOnly);
    stream.setByteOrder(QDataStream::LittleEndian);
    stream << (quint16)0x0004 << (quint16)0x0010;
    return AddRequest(arr);
}

/**
 * @brief Z21LanProtocol::Send_Logoff
 * @return true if success
 */
bool Z21LanProtocol::Send_Logoff()
{
    QByteArray arr;
    QDataStream stream(&arr, QIODevice::WriteOnly);
    stream.setByteOrder(QDataStream::LittleEndian);
    stream << (quint16)0x04 << (quint16)0x30;
    return AddRequest(arr);
}

/**
 * @brief Z21LanProtocol::Send_SetBroadcastFlags
 * @param flags
 * @return true if success
 */
bool Z21LanProtocol::Send_SetBroadcastFlags(quint32 flags, quint32 mask)
{
    QByteArray arr;
    QDataStream stream(&arr, QIODevice::WriteOnly);
    stream.setByteOrder(QDataStream::LittleEndian);
    quint32 f = broadcastFlags | (flags & mask);    // setting bits
    f &= ~(~flags & mask);                          // erased bits
    stream << (quint16)0x08 << (quint16)0x50 << f;
    return AddRequest(arr);
}

/**
 * @brief Z21LanProtocol::Send_GetSystemStateData
 * @return
 */
bool Z21LanProtocol::Send_GetSystemStateData()
{
    QByteArray arr;
    QDataStream stream(&arr, QIODevice::WriteOnly);
    stream.setByteOrder(QDataStream::LittleEndian);
    stream << (quint16)0x04 << (quint16)0x85;
    return AddRequest(arr);
}

/**
 * @brief Z21LanProtocol::Send_GetHardwareInfo
 * @return
 */
bool Z21LanProtocol::Send_GetHardwareInfo()
{
    QByteArray arr;
    QDataStream stream(&arr, QIODevice::WriteOnly);
    stream.setByteOrder(QDataStream::LittleEndian);
    stream << (quint16)0x04 << (quint16)0x1A;
    return AddRequest(arr);
}

/**
 * @brief Z21LanProtocol::Send_GetBroadcastFlags
 * @return true if success
 */
bool Z21LanProtocol::Send_GetBroadcastFlags()
{
    QByteArray arr;
    QDataStream stream(&arr, QIODevice::WriteOnly);
    stream.setByteOrder(QDataStream::LittleEndian);
    stream << (quint16)0x04 << (quint16)0x51;
    return AddRequest(arr);
}

/**
 * @brief Z21LanProtocol::Send_XBus_GetVersion
 * @return true if success
 */
bool Z21LanProtocol::Send_XBus_GetVersion()
{
    QByteArray arr;
    QDataStream stream(&arr, QIODevice::WriteOnly);
    stream.setByteOrder(QDataStream::LittleEndian);
    stream << (quint16)0x07 << (quint16)0x40 << (quint8)0x21 << (quint8)0x21 << (quint8)0x00;
    return AddRequest(arr);
}

/**
 * @brief Z21LanProtocol::Send_XBus_GetStatus
 * @return true if success
 */
bool Z21LanProtocol::Send_XBus_GetStatus()
{
    QByteArray arr;
    QDataStream stream(&arr, QIODevice::WriteOnly);
    stream.setByteOrder(QDataStream::LittleEndian);
    stream << (quint16)0x07 << (quint16)0x40 << (quint8)0x21 << (quint8)0x24 << (quint8)0x05;
    return AddRequest(arr);
}

/**
 * @brief Z21LanProtocol::Send_XBus_SetTrackPowerOff
 * @return true if success
 */
bool Z21LanProtocol::Send_XBus_SetTrackPowerOff()
{
    QByteArray arr;
    QDataStream stream(&arr, QIODevice::WriteOnly);
    stream.setByteOrder(QDataStream::LittleEndian);
    stream << (quint16)0x07 << (quint16)0x40 << (quint8)0x21 << (quint8)0x80 << (quint8)0xA1;
    return AddRequest(arr);
}

/**
 * @brief Z21LanProtocol::Send_XBus_SetTrackPowerOn
 * @return true if success
 */
bool Z21LanProtocol::Send_XBus_SetTrackPowerOn()
{
    QByteArray arr;
    QDataStream stream(&arr, QIODevice::WriteOnly);
    stream.setByteOrder(QDataStream::LittleEndian);
    stream << (quint16)0x07 << (quint16)0x40 << (quint8)0x21 << (quint8)0x81 << (quint8)0xA0;
    return AddRequest(arr);
}

/**
 * @brief Z21LanProtocol::Send_XBus_SetStop
 * @return true if success
 */
bool Z21LanProtocol::Send_XBus_SetStop()
{
    QByteArray arr;
    QDataStream stream(&arr, QIODevice::WriteOnly);
    stream.setByteOrder(QDataStream::LittleEndian);
    stream << (quint16)0x06 << (quint16)0x40 << (quint8)0x80 << (quint8)0x80;
    return AddRequest(arr);
}

/**
 * @brief Z21LanProtocol::Send_XBus_GetFirmwareVersion
 * @return true if success
 */
bool Z21LanProtocol::Send_XBus_GetFirmwareVersion()
{
    QByteArray arr;
    QDataStream stream(&arr, QIODevice::WriteOnly);
    stream.setByteOrder(QDataStream::LittleEndian);
    stream << (quint16)0x07 << (quint16)0x40 << (quint8)0xF1 << (quint8)0x0A << (quint8)0xFB;
    return AddRequest(arr);
}

/**
 * @brief Z21LanProtocol::AddRequest
 * @param data Data to be send to the Z21 central
 * @return Always true
 */
bool Z21LanProtocol::AddRequest(const QByteArray &data)
{
    transmitter.start(new TransmitterTask(address, port, data));
    return true;
}

/**
 * @brief Z21LanProtocol::on_receiver_serialnumber
 * @param serial
 */
void Z21LanProtocol::on_receiver_serialnumber(quint32 serial)
{
    QString s(QByteArray::fromRawData((const char*)&serial, sizeof(quint32)).toHex());
    emit lan_SerialNumber(serial, s);
}

/**
 * @brief Z21LanProtocol::on_receiver_broadcastFlags
 * @param flags
 */
void Z21LanProtocol::on_receiver_broadcastFlags(quint32 flags)
{
    broadcastFlags = flags;
    emit lan_BroadcastFlags(flags);
}
