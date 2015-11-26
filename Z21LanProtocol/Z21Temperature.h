#ifndef Z21TEMPERATURE_H
#define Z21TEMPERATURE_H

#include "global.h"
#include <QString>

class Z21_EXPORT Z21Temperature
{
public:
    Z21Temperature() = default;
    explicit Z21Temperature(quint16 v);

    quint16 value() const;
    QString unit(bool longName = false) const;
    QString toString(bool withUnit = false, bool unitLongName = false) const;

    Z21Temperature operator =(quint16 v);

private:
    quint16 val = 0;
};

#endif // Z21TEMPERATURE_H
