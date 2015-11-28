#include "Z21Crc.h"

/**
 * @brief Z21Crc::CRC
 * @param v
 * @param start
 */
void Z21Crc::Calculate(quint8 v, bool start)
{
    if(start)
        crc = v;
    else
        crc ^= v;
}

/**
 * @brief Z21Crc::Value
 * @return
 */
quint8 Z21Crc::Value() const
{
    return crc;
}

/**
 * @brief Z21Crc::CheckCRC
 * @param crc
 * @return
 */
bool Z21Crc::Check(quint8 crc)
{
    return this->crc == crc;
}
