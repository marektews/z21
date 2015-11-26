#ifndef Z21SYSTEMSTATE_H
#define Z21SYSTEMSTATE_H

#include "global.h"
#include "Z21Current.h"
#include "Z21Voltage.h"
#include "Z21Temperature.h"
#include "Z21CentralState.h"
#include <QDataStream>

class Z21_EXPORT Z21SystemState
{
public:
    Z21SystemState() = default;
    explicit Z21SystemState(QDataStream& stream);

public:
    Z21Current MainCurrent;            // Current on the main track (mA)
    Z21Current ProgCurrent;            // (mA)
    Z21Current FilteredMainCurrent;    // (mA)
    Z21Temperature Temperature;        // Celesius
    Z21Voltage SupplyVoltage;          // (mV)
    Z21Voltage VCCVoltage;             // (mV)
    Z21CentralState CentralState;      // bitmask
    quint16 reserved;
};

#endif // Z21SYSTEMSTATE_H
