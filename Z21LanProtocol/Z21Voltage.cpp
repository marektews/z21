#include "Z21Voltage.h"

Z21Voltage::Z21Voltage(quint16 v) : val(v)
{}

quint16 Z21Voltage::value() const
{
    return val;
}

QString Z21Voltage::unit() const
{
    return "mV";
}

QString Z21Voltage::toString(bool withUnit) const
{
    QString s(val);
    if(withUnit) { s += ' '; s += unit(); }
    return s;
}

Z21Voltage Z21Voltage::operator =(quint16 v)
{
    val = v;
    return *this;
}
