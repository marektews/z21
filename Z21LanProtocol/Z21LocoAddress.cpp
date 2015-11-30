#include "Z21LocoAddress.h"

Z21LocoAddress::Z21LocoAddress(quint8 msb, quint8 lsb)
    : address((((quint16)msb & 0x3F)<<8) + lsb)
{}

quint16 Z21LocoAddress::Value() const
{
    return address;
}

void Z21LocoAddress::SetValue(quint16 address)
{
    this->address = address;
}

quint8 Z21LocoAddress::MSB() const
{
    return (address >> 8) & 0x3F;
}

quint8 Z21LocoAddress::LSB() const
{
    return address & 0xFF;
}
