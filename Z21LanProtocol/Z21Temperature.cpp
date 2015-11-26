#include "Z21Temperature.h"

Z21Temperature::Z21Temperature(quint16 v) : val(v)
{}

quint16 Z21Temperature::value() const
{
    return val;
}

QString Z21Temperature::unit(bool longName) const
{
    return longName ? QString("Celsius") : QString(L'\x2103');
}

QString Z21Temperature::toString(bool withUnit, bool unitLongName) const
{
    QString s(val);
    if(withUnit) { s += ' '; s += unit(unitLongName); }
    return s;
}

Z21Temperature &Z21Temperature::operator =(quint16 v)
{
    val = v;
    return *this;
}
