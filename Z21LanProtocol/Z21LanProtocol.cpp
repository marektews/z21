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
 * @param address
 * @param port
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

    GetBroadcastFlags();
    return true;
}

/**
 * @brief Z21LanProtocol::GetSerialNumber
 * @return Look return value of AddRequest routine
 */
bool Z21LanProtocol::GetSerialNumber()
{
    QByteArray arr;
    QDataStream stream(&arr, QIODevice::WriteOnly);
    stream.setByteOrder(QDataStream::LittleEndian);
    stream << (quint16)0x0004 << (quint16)0x0010;
    return AddRequest(arr);
}

/**
 * @brief Z21LanProtocol::Logoff
 * @return
 */
bool Z21LanProtocol::Logoff()
{
    QByteArray arr;
    QDataStream stream(&arr, QIODevice::WriteOnly);
    stream.setByteOrder(QDataStream::LittleEndian);
    stream << (quint16)0x04 << (quint16)0x30;
    return AddRequest(arr);
}

/**
 * @brief Z21LanProtocol::SetBroadcastFlags
 * @param flags
 * @return
 */
bool Z21LanProtocol::SetBroadcastFlags(quint32 flags, quint32 mask)
{
    QByteArray arr;
    QDataStream stream(&arr, QIODevice::WriteOnly);
    stream.setByteOrder(QDataStream::LittleEndian);
    quint32 f = broadcastFlags | (flags & mask);     // setting bits
    f &= ~(~flags & mask);    // erased bits
    stream << (quint16)0x08 << (quint16)0x50 << f ;
    return AddRequest(arr);
}

/**
 * @brief Z21LanProtocol::GetBroadcastFlags
 * @return
 */
bool Z21LanProtocol::GetBroadcastFlags()
{
    QByteArray arr;
    QDataStream stream(&arr, QIODevice::WriteOnly);
    stream.setByteOrder(QDataStream::LittleEndian);
    stream << (quint16)0x04 << (quint16)0x51;
    return AddRequest(arr);
}

/**
 * @brief Z21LanProtocol::XBus_GetVersion
 * @return
 */
bool Z21LanProtocol::XBus_GetVersion()
{
    return false;
}

/**
 * @brief Z21LanProtocol::AddRequest
 * @param data Data to be send to the Z21 central
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
