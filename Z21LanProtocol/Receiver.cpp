#include <QDataStream>
#include "Z21LanProtocol.h"
#include "Receiver.h"

Receiver::Receiver(Z21LanProtocol *z21, QObject *parent) : QObject(parent), z21(z21)
{}

/**
 * @brief Receiver::StartWork
 * @param address
 * @param port
 */
void Receiver::StartWork(const QHostAddress &address, quint16 port)
{
    socket = new QUdpSocket(this);
    if(socket)
    {
        socket->bind(address, port, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint);
        connect(socket, &QUdpSocket::readyRead, this, &Receiver::ReadPendingDatagrams);
    }
}

/**
 * @brief Receiver::ReadPendingDatagrams
 */
void Receiver::ReadPendingDatagrams()
{
    QByteArray datagram;
    QHostAddress sender;
    quint16 senderPort;
    while(socket->hasPendingDatagrams())
    {
        datagram.resize(socket->pendingDatagramSize());
        socket->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);

        QDataStream stream(datagram);
        stream.setByteOrder(QDataStream::LittleEndian);

        quint16 length, header;
        while(!stream.atEnd())
        {
            stream >> length;
            stream >> header;
            qDebug() << "Z21: lenght:" << length << "header id:" << header;
            switch(header)
            {
            default:
                {
                    Q_ASSERT(0);    // debug cather for unknown commands
                    stream.skipRawData(length-2*sizeof(quint16));
                    break;
                }

            case 0x10:  // LAN_GET_SERIAL_NUMBER
                {
                    quint32 serial;
                    stream >> serial;
                    emit lan_SerialNumber(serial);
                    break;
                }

            case 0x51:  // LAN_GET_BROADCAST_FLAGS
                {
                    quint32 flags;
                    stream >> flags;
                    emit lan_BroadcastFlags(flags);
                    break;
                }

            case 0x84:  // LAN_SYSTEMSTATE_DATACHANGED
                {
                    Z21SystemState ss(stream);
                    emit z21->lan_SystemState(ss);
                    break;
                }

            case 0x40:  // X-Bus
                {
                    quint8 xHdr;
                    stream >> xHdr;
                    CRC(xHdr, true);
                    switch(xHdr)
                    {
                    case 0x63:  // LAN_X_GET_VERSION
                        {
                            quint8 db[3], crc;
                            for(int i=0; i<3; ++i)
                            {
                                stream >> db[i];
                                CRC(db[i]);
                            }
                            stream >> crc;
                            if(CheckCRC(crc))
                                emit z21->xbus_Version(db[1], db[2]);
                            break;
                        }
                    }
                }
            }
        }
    }
}

/**
 * @brief Receiver::CRC
 * @param v
 * @param start
 */
void Receiver::CRC(quint8 v, bool start)
{
    if(start)
        crc = v;
    else
        crc ^= v;
}

/**
 * @brief Receiver::CheckCRC
 * @param crc
 * @return
 */
bool Receiver::CheckCRC(quint8 crc)
{
    return this->crc == crc;
}

