#ifndef Z21CENTRALSTATE_H
#define Z21CENTRALSTATE_H

#include "global.h"
#include <QDataStream>

class Z21_EXPORT Z21CentralState
{
public:
    Z21CentralState() = default;
    explicit Z21CentralState(quint16 bitmask);
    explicit Z21CentralState(QDataStream& stream);
    Z21CentralState operator=(quint16 bitmask);

    /**
     * @brief IsEmergencyStop
     * @return If true the emergency stop is switched on
     */
    bool IsEmergencyStop() const;
    /**
     * @brief IsTrackVoltageOff
     * @return If true the track power is switched off
     */
    bool IsTrackVoltageOff() const;
    /**
     * @brief IsShortCircuit
     * @return If true short circuit is on tracks
     */
    bool IsShortCircuit() const;
    /**
     * @brief IsProgrammingModeActive
     * @return If true the programming mode is active
     */
    bool IsProgrammingModeActive() const;
    /**
     * @brief IsHighTemperature
     * @return If true a internal temperature is too high
     */
    bool IsHighTemperature() const;
    /**
     * @brief IsPowerLost
     * @return If true an input voltage is too low
     */
    bool IsPowerLost() const;
    /**
     * @brief IsShortCircuitExternal
     * @return If true short circuit at the external booster output
     */
    bool IsShortCircuitExternal() const;
    /**
     * @brief IsShortCircuitInternal
     * @return If true short circuit on the main track or the programming track
     */
    bool IsShortCircuitInternal() const;

    QString toString() const;

private:
    quint16 bitmask = 0;
};

#endif // Z21CENTRALSTATE_H
