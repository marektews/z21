#ifndef Z21SYSTEMSTATE_H
#define Z21SYSTEMSTATE_H

#include "global.h"

class Z21_EXPORT Z21SystemState
{
public:
    Z21SystemState();

public:
    qint16  MainCurrent;            // Current on the main track (mA)
    qint16  ProgCurrent;            // (mA)
    qint16  FilteredMainCurrent;    // (mA)
    qint16  Temperature;            // Celesius
    quint16 SupplyVoltage;          // (mV)
    quint16 VCCVoltage;             // (mV)
    quint8  CentralState;           // bitmask
    quint8  CentralStateEx;         // bitmask
    quint16 reserved;
};

#endif // Z21SYSTEMSTATE_H
