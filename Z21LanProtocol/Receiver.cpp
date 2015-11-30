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

            case 0x1A:  // LAN_GET_HWINFO
                {
                    quint32 hwType, fwVersion;
                    stream >> hwType >> fwVersion;
                    emit z21->lan_HardwareInfo(hwType, fwVersion);
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
                    qDebug() << "X-Bus" << xHdr;
                    CRC.Calculate(xHdr, true);
                    switch(xHdr)
                    {
                    case 0x61:  // LAN_X_BC_TRACK_POWER_OFF, LAN_X_BC_TRACK_POWER_ON, LAN_X_BC_PROGRAMMING_MODE, LAN_X_BC_TRACK_SHORT_CIRCUIT, LAN_X_UNKNOWN_COMMAND
                        {
                            quint8 db0, crc;
                            stream >> db0;
                            CRC.Calculate(db0);
                            stream >> crc;
                            if(CRC.Check(crc))
                            {
                                switch(db0)
                                {
                                case 0x00: emit z21->xbus_BcTrackPower(false); break;
                                case 0x01: emit z21->xbus_BcTrackPower(true); break;
                                case 0x02: emit z21->xbus_BcProgrammingMode(); break;
                                case 0x08: emit z21->xbus_BcTrackShortCircuit(); break;
                                case 0x82: emit z21->xbus_UnknownCommand(); break;
                                }
                            }
                            break;
                        }

                    case 0x62:  // LAN_X_STATUS_CHANGED
                        {
                            quint8 db[2], crc;
                            for(int i=0; i<2; ++i)
                            {
                                stream >> db[i];
                                CRC.Calculate(db[i]);
                            }
                            stream >> crc;
                            if(CRC.Check(crc))
                                emit z21->xbus_StatusChanged(Z21CentralState(db[1]));
                            break;
                        }

                    case 0x63:  // LAN_X_GET_VERSION
                        {
                            quint8 db[3], crc;
                            for(int i=0; i<3; ++i)
                            {
                                stream >> db[i];
                                CRC.Calculate(db[i]);
                            }
                            stream >> crc;
                            if(CRC.Check(crc))
                                emit z21->xbus_Version(db[1], db[2]);
                            break;
                        }

                    case 0x81:  // LAN_X_BC_STOPPED
                        {
                            quint8 db0, crc;
                            stream >> db0;
                            CRC.Calculate(db0);
                            stream >> crc;
                            if(CRC.Check(crc))
                                emit z21->xbus_BcStopped(); break;
                            break;
                        }

                    case 0xEF:  // LAN_X_LOCO_INFO
                        {
                            Z21LocoInfo li(stream, CRC);
                            while(!stream.atEnd())
                            {
                                quint8 v;
                                stream >> v;
                                if(stream.atEnd())
                                {
                                    if(CRC.Check(v))
                                        emit z21->xbus_LocoInfo(li);
                                }
                                else
                                    CRC.Calculate(v);
                            }
                            break;
                        }

                    case 0xF3:  // LAN_X_GET_FIRMWARE_VERSION
                        {
                            quint8 db[3], crc;
                            for(int i=0; i<3; ++i)
                            {
                                stream >> db[i];
                                CRC.Calculate(db[i]);
                            }
                            stream >> crc;
                            if(CRC.Check(crc))
                            {
                                QString fv;
                                fv.sprintf("%x.%x", db[1], db[2]);
                                emit z21->xbus_FirmwareVersion(db[1], db[2], fv);
                            }
                            break;
                        }
                    }
                }
            }
        }
    }
}
