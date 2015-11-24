#ifndef TRANSMITTERTASK_H
#define TRANSMITTERTASK_H

#include <QRunnable>
#include <QHostAddress>

class TransmitterTask : public QRunnable
{
public:
    TransmitterTask(const QHostAddress& address, quint16 port, const QByteArray& data);

private:
    QHostAddress address;
    quint16 port;
    QByteArray data;

    virtual void run();
};

#endif // TRANSMITTERTASK_H
