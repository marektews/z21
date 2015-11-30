#ifndef Z21LOCOADDRESS_H
#define Z21LOCOADDRESS_H

#include "global.h"

class Z21_EXPORT Z21LocoAddress
{
public:
    Z21LocoAddress() = default;
    /**
     * @brief Z21LocoAddress
     * @param msb
     * @param lsb
     */
    explicit Z21LocoAddress(quint8 msb, quint8 lsb);

    /**
     * @brief Value
     * @return
     */
    quint16 Value() const;
    /**
     * @brief SetValue
     * @param address
     */
    void SetValue(quint16 address);

    /**
     * @brief MSB
     * @return
     */
    quint8 MSB() const;
    /**
     * @brief LSB
     * @return
     */
    quint8 LSB() const;

private:
    quint16 address = 0;
};

#endif // Z21LOCOADDRESS_H
