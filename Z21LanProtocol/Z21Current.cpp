#include "Z21Current.h"
#include <QVariant>

Z21Current::Z21Current(quint16 v) : val(v)
{}

quint16 Z21Current::value() const
{
    return val;
}

QString Z21Current::unit() const
{
    return "mA";
}

QString Z21Current::toString(bool withUnit) const
{
    QString s = QVariant(val).toString();
    if(withUnit) { s += ' '; s += unit(); }
    return s;
}

Z21Current Z21Current::operator =(quint16 v)
{
    val = v;
    return *this;
}

