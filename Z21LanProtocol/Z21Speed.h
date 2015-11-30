#ifndef Z21SPEED_H
#define Z21SPEED_H

#include "global.h"

class Z21_EXPORT Z21Speed
{
public:
    Z21Speed() = default;

    enum class Steps { SS14, SS28, SS128 };
    Steps GetSteps() const;
    void SetSteps(Steps value);

    quint8 Value() const;
    void SetValue(quint8 v);

    static Z21Speed fromXLocoInfo(quint8 db2, quint8 db3);

private:
    Steps steps = Steps::SS14;
    quint8 speed = 0;
};

#endif // Z21SPEEDSTEPS_H
