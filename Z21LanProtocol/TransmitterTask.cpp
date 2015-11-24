#include <QUdpSocket>
#include "TransmitterTask.h"

/**
 * @brief TransmitterTask::TransmitterTask
 * @param address
 * @param port
 * @param data
 */
TransmitterTask::TransmitterTask(const QHostAddress &address, quint16 port, const QByteArray &data)
    : address(address), port(port), data(data)
{}

/**
 * @brief TransmitterTask::run
 */
void TransmitterTask::run()
{
    QUdpSocket socket;
    socket.bind(port, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint);
    socket.writeDatagram(data, address, port);
    socket.waitForBytesWritten();
    socket.close();
    qDebug() << "Task:" << address << ':' << port << "<-" << data;
}

