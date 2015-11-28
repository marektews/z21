#include "Z21CentralState.h"

/**
 * @brief Z21CentralState::Z21CentralState
 * @param bitmask
 */
Z21CentralState::Z21CentralState(quint16 bitmask) : bitmask(bitmask)
{}

/**
 * @brief Z21CentralState::Z21CentralState
 * @param stream
 */
Z21CentralState::Z21CentralState(QDataStream &stream)
{
    stream >> bitmask;
}

/**
 * @brief Z21CentralState::operator =
 * @param bitmask
 * @return
 */
Z21CentralState Z21CentralState::operator=(quint16 bitmask)
{
    this->bitmask = bitmask;
    return *this;
}

/**
 * @brief Z21CentralState::IsEmergencyStop
 * @return If true the emergency stop is switched on
 */
bool Z21CentralState::IsEmergencyStop() const { return bitmask & 0x01 ? true : false; }

/**
 * @brief Z21CentralState::IsTrackVoltageOff
 * @return If true the track power is switched off
 */
bool Z21CentralState::IsTrackVoltageOff() const { return bitmask & 0x02 ? true : false; }

/**
 * @brief Z21CentralState::IsShortCircuit
 * @return If true short circuit is on tracks
 */
bool Z21CentralState::IsShortCircuit() const { return bitmask & 0x04 ? true : false; }

/**
 * @brief Z21CentralState::IsProgrammingModeActive
 * @return If true the programming mode is active
 */
bool Z21CentralState::IsProgrammingModeActive() const { return bitmask & 0x20 ? true : false; }

/**
 * @brief Z21CentralState::IsHighTemperature
 * @return If true a internal temperature is too high
 */
bool Z21CentralState::IsHighTemperature() const { return bitmask & 0x0100 ? true : false; }

/**
 * @brief Z21CentralState::IsPowerLost
 * @return If true an input voltage is too low
 */
bool Z21CentralState::IsPowerLost() const { return bitmask & 0x0200 ? true : false; }

/**
 * @brief Z21CentralState::IsShortCircuitExternal
 * @return If true short circuit at the external booster output
 */
bool Z21CentralState::IsShortCircuitExternal() const { return bitmask & 0x0400 ? true : false; }

/**
 * @brief Z21CentralState::IsShortCircuitInternal
 * @return If true short circuit on the main track or the programming track
 */
bool Z21CentralState::IsShortCircuitInternal() const { return bitmask & 0x0800 ? true : false; }

/**
 * @brief Z21CentralState::toString
 * @return
 */
QString Z21CentralState::toString() const
{
    QString s;
    if(IsEmergencyStop()) s += "EmergencyStop ";
    if(IsTrackVoltageOff()) s += "TrackVoltageOff ";
    if(IsShortCircuit()) s += "ShortCircuit ";
    if(IsProgrammingModeActive()) s += "ProgrammingModeActive ";
    if(IsHighTemperature()) s += "HighTemperature ";
    if(IsPowerLost()) s += "PowerLost ";
    if(IsShortCircuitExternal()) s += "ShortCircuitExternal ";
    if(IsShortCircuitInternal()) s += "ShortCircuitInternal ";
    return s.trimmed();
}

