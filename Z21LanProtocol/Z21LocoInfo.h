#ifndef Z21LOCOINFO_H
#define Z21LOCOINFO_H

#include "global.h"
#include "Z21Direction.h"
#include "Z21LocoAddress.h"
#include "Z21Speed.h"
#include "Z21Functions.h"
#include "Z21Crc.h"

class Z21_EXPORT Z21LocoInfo
{
public:
    Z21LocoInfo() = default;
    /**
     * @brief Z21LocoInfo
     * @param stream
     * @param crc
     */
    explicit Z21LocoInfo(QDataStream& stream, Z21Crc& crc);

    /**
     * @brief IsBusy
     * @return true if the locomotive is controlled by another X-BUS manual control
     */
    bool IsBusy() const;
    bool IsDoubleTraction() const;
    bool IsSmartSearch() const;

private:
    bool           busy = false;            // true if the locomotive is controlled by another X-BUS manual control
    bool           doubleTraction = false;  // true if the locomotive contained in double traction
    bool           smartSearch = false;     // true if smart search mode

public:
    Z21LocoAddress address;
    Z21Speed       speed;
    Z21Direction   direction;
    Z21Functions   functions;
};

#endif // Z21LOCOINFO_H
