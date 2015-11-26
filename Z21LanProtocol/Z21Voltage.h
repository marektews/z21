#ifndef Z21VOLTAGE_H
#define Z21VOLTAGE_H

#include "global.h"
#include <QString>

class Z21_EXPORT Z21Voltage
{
public:
    Z21Voltage() = default;
    explicit Z21Voltage(quint16 v);

    quint16 value() const;
    QString unit() const;
    QString toString(bool withUnit = false) const;

    Z21Voltage operator =(quint16 v);

private:
    quint16 val = 0;
};

#endif // Z21VOLTAGE_H
