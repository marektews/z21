#ifndef Z21CRC_H
#define Z21CRC_H

#include <QtCore>

class Z21Crc
{
public:
    Z21Crc() = default;
    void Calculate(quint8 v, bool start = false);
    quint8 Value() const;
    bool Check(quint8 crc);

private:
    quint8 crc = 0;
};

#endif // Z21CRC_H
