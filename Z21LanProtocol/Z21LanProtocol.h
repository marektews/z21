#ifndef Z21LANPROTOCOL_H
#define Z21LANPROTOCOL_H

#include <QObject>
#include <QHostAddress>
#include <QThread>
#include <QThreadPool>
#include "global.h"
#include "Z21SystemState.h"
#include "Z21LocoInfo.h"

class Z21_EXPORT Z21LanProtocol : public QObject
{
    Q_OBJECT

public:
    Z21LanProtocol();
    ~Z21LanProtocol();

    /**
     * @brief Configure and initialize internal threads and sockets
     * @param address Z21 host address, default is 192.168.0.111
     * @param port Z21 host port number, default is 21105
     * @return true if success
     */
    bool Configure(const QHostAddress& address = QHostAddress("192.168.0.111"), quint16 port = 21105);

// SYSTEM, STATUS, VERSION
public:
    /**
     * @brief Send_GetSerialNumber Read serial number
     * Sending request to z21. This routine is non-blocking.
     * The lan_SerialNumber signal is broadcasting after receiving the response from z21.
     * @return true if success
     */
    bool Send_GetSerialNumber();                                // LAN_GET_SERIAL_NUMBER request
    /**
     * @brief Send_Logoff
     * Sending request to z21. This routine is non-blocking.
     * After that Z21 no longer sends any response.
     * @return true if success
     */
    bool Send_Logoff();                                         // LAN_LOGOFF request
    /**
     * @brief Send_GetBroadcastFlags
     * Sending request to z21. This routine is non-blocking.
     * The lan_BroadcastFlags signal is broadcasting after receiving the response from z21.
     * @return true if success
     */
    bool Send_GetBroadcastFlags();                              // LAN_GET_BROADCASTFLAGS request
    /**
     * @brief Send_SetBroadcastFlags
     * Sending request to z21. This routine is non-blocking.
     * @param flags
     * @param mask
     * @return true if success
     */
    bool Send_SetBroadcastFlags(quint32 flags, quint32 mask);   // LAN_SET_BROADCASTFLAGS request
    /**
     * @brief Send_GetSystemStateData
     * @return true if success
     */
    bool Send_GetSystemStateData();                             // LAN_SYSTEMSTATE_GETDATA request
    /**
     * @brief Send_GetHardwareInfo
     * @return true if success
     */
    bool Send_GetHardwareInfo();                                // LAN_GET_HWINFO

signals:
    void lan_SerialNumber(quint32 serial, const QString& str);  // LAN_GET_SERIAL_NUMBER response
    void lan_BroadcastFlags(quint32 flags);                     // LAN_GET_BROADCASTFLAGS response
    void lan_SystemState(const Z21SystemState& systemState);    // LAN_SYSTEMSTATE_DATACHANGED broadcast message
    void lan_HardwareInfo(quint32 hardwareType, quint32 firmwareVersion);

// X-BUS
public:
    /**
     * @brief Send_XBus_GetVersion
     * @return true if success
     */
    bool Send_XBus_GetVersion();                                // LAN_X_GET_VERSION request
    /**
     * @brief Send_XBus_GetStatus
     * @return true if success
     */
    bool Send_XBus_GetStatus();                                 // LAN_X_GET_STATUS request
    /**
     * @brief Send_XBus_SetTrackPowerOff
     * @return true if success
     */
    bool Send_XBus_SetTrackPowerOff();                          // LAN_X_SET_TRACK_POWER_OFF request
    /**
     * @brief Send_XBus_SetTrackPowerOn
     * @return true if success
     */
    bool Send_XBus_SetTrackPowerOn();                           // LAN_X_SET_TRACK_POWER_ON request
    /**
     * @brief Send_XBus_SetStop
     * With this command the emergency stop is activated, the locomotives are stopped but the track power remains switched on.
     * @return true if success
     */
    bool Send_XBus_SetStop();                                   // LAN_X_SET_STOP
    /**
     * @brief Send_XBus_GetFirmwareVersion
     * With this command, the firmware version of the Z21 can be read.
     * @return true if success
     */
    bool Send_XBus_GetFirmwareVersion();                        // LAN_X_GET_FIRMWARE_VERSION

    /** DRIVE **/

    /**
     * @brief Send_XBus_GetLocoInfo
     * @param locoAddress
     * @return true if success
     */
    bool Send_XBus_GetLocoInfo(const Z21LocoAddress& la);            // LAN_X_GET_LOCO_INFO

    bool Send_XBus_SetLocoDrive(const Z21LocoInfo& li);

    bool Send_XBus_SetLocoFunction();

signals:
    void xbus_Version(quint8 version, quint8 centralID);                    // LAN_X_GET_VERSION response
    void xbus_BcTrackPower(bool off);                                       // LAN_X_BC_TRACK_POWER_OFF and LAN_X_BC_TRACK_POWER_ON responses
    void xbus_BcProgrammingMode();                                          // LAN_X_BC_PROGRAMMING_MODE response
    void xbus_BcTrackShortCircuit();                                        // LAN_X_BC_TRACK_SHORT_CIRCUIT response
    void xbus_BcStopped();                                                  // LAN_X_BC_STOPPED response
    void xbus_UnknownCommand();                                             // LAN_X_UNKNOWN_COMMAND response
    void xbus_StatusChanged(const Z21CentralState& state);                  // LAN_X_STATUS_CHANGED response
    void xbus_FirmwareVersion(quint8 msb, quint8 lsb, const QString& fv);   // LAN_X_GET_FIRMWARE_VERSION response
    void xbus_LocoInfo(const Z21LocoInfo& locoInfo);                        // LAN_X_LOCO_INFO response

// LocoNet
public:

signals:

private:
    bool AddRequest(const QByteArray& data);

private:
    QHostAddress    address = QHostAddress("192.168.0.111");
    quint16         port = 21105;
    QThread         receiver;
    QThreadPool     transmitter;

    quint32         broadcastFlags = 0;

signals:
    void startReceiver(const QHostAddress& address, quint16 port);

private slots:
    void on_receiver_serialnumber(quint32 serial);
    void on_receiver_broadcastFlags(quint32 flags);
};

#endif // Z21LANPROTOCOL_H
