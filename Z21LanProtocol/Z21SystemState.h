#ifndef Z21SYSTEMSTATE_H
#define Z21SYSTEMSTATE_H

#include "global.h"
#include "Z21Current.h"
#include "Z21Voltage.h"
#include "Z21Temperature.h"

class Z21_EXPORT Z21SystemState
{
public:
    Z21SystemState();

public:
    Z21Current MainCurrent;            // Current on the main track (mA)
    Z21Current ProgCurrent;            // (mA)
    Z21Current FilteredMainCurrent;    // (mA)
    Z21Temperature  Temperature;       // Celesius
    Z21Voltage SupplyVoltage;          // (mV)
    Z21Voltage VCCVoltage;             // (mV)
    quint8  CentralState;           // bitmask
    quint8  CentralStateEx;         // bitmask
    quint16 reserved;
};

#endif // Z21SYSTEMSTATE_H
