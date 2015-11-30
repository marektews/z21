#include "Z21Speed.h"


Z21Speed::Steps Z21Speed::GetSteps() const
{
    return steps;
}

void Z21Speed::SetSteps(Steps value)
{
    steps = value;
}

quint8 Z21Speed::Value() const
{
    return speed;
}

void Z21Speed::SetValue(quint8 v)
{
    speed = v;
}

Z21Speed Z21Speed::fromXLocoInfo(quint8 db2, quint8 db3)
{
    Z21Speed ss;
    switch(db2 & 0x07)
    {
    default: Q_ASSERT(0); break;    // catch undefined values or errors
    case 0: ss.SetSteps(Z21Speed::Steps::SS14); break;
    case 2: ss.SetSteps(Z21Speed::Steps::SS28); break;
    case 4: ss.SetSteps(Z21Speed::Steps::SS128); break;
    }
    ss.SetValue(db3 & 0x7F);
    return ss;
}
