#include "Z21SystemState.h"

Z21SystemState::Z21SystemState(QDataStream &stream)
{
    quint16 v;
    stream >> v; MainCurrent = v;
    stream >> v; ProgCurrent = v;
    stream >> v; FilteredMainCurrent = v;
    stream >> v; Temperature = v;
    stream >> v; SupplyVoltage = v;
    stream >> v; VCCVoltage = v;
    stream >> v; CentralState = v;
    stream >> reserved;
}

