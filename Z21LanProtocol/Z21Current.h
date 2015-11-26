#ifndef Z21CURRENT_H
#define Z21CURRENT_H

#include "global.h"
#include <QString>

class Z21_EXPORT Z21Current
{
public:
    Z21Current() = default;
    explicit Z21Current(quint16 v);

    quint16 value() const;
    QString unit() const;
    QString toString(bool withUnit = false) const;

    Z21Current& operator = (quint16 v);

private:
    quint16 val = 0;
};

#endif // Z21CURRENT_H
