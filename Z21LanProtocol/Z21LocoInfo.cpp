#include "Z21LocoInfo.h"

Z21LocoInfo::Z21LocoInfo(QDataStream &stream, Z21Crc &crc)
{
    // DB0 & DB1
    quint8 db0, db1;
    stream >> db0; crc.Calculate(db0);
    stream >> db1; crc.Calculate(db1);
    address = Z21LocoAddress(db0, db1);

    // DB2 & DB3
    quint8 db2, db3;
    stream >> db2; crc.Calculate(db2);
    stream >> db3; crc.Calculate(db3);
    busy = db2 & (1<<3) ? true : false;
    speed = Z21Speed::fromXLocoInfo(db2, db3);
    direction.SetValue((db3 & 0x80) ? Z21Direction::Direction::Forward : Z21Direction::Direction::Backward);

    // DB4
    quint8 dbn;
    stream >> dbn; crc.Calculate(dbn);
    doubleTraction = (dbn & (1<<6)) ? true : false;
    smartSearch = (dbn & (1<<5)) ? true : false;
    functions.SetLights((dbn & (1<<4)) ? true : false);
    functions.Enable(Z21Functions::Number::F1, (dbn & (1<<0)) ? true : false);
    functions.Enable(Z21Functions::Number::F2, (dbn & (1<<1)) ? true : false);
    functions.Enable(Z21Functions::Number::F3, (dbn & (1<<2)) ? true : false);
    functions.Enable(Z21Functions::Number::F4, (dbn & (1<<3)) ? true : false);

    // DB5
    stream >> dbn; crc.Calculate(dbn);
    Z21Functions::Number n = Z21Functions::Number::F5;
    for(int bit=0; bit<8; ++bit, ++n)
        functions.Enable(n, (dbn & (1<<bit)) ? true : false);

    // DB6
    stream >> dbn; crc.Calculate(dbn);
    n = Z21Functions::Number::F13;
    for(int bit=0; bit<8; ++bit, ++n)
        functions.Enable(n, (dbn & (1<<bit)) ? true : false);

    // DB7
    stream >> dbn; crc.Calculate(dbn);
    n = Z21Functions::Number::F21;
    for(int bit=0; bit<8; ++bit, ++n)
        functions.Enable(n, (dbn & (1<<bit)) ? true : false);
}

bool Z21LocoInfo::IsBusy() const
{
    return busy;
}

bool Z21LocoInfo::IsDoubleTraction() const
{
    return doubleTraction;
}

bool Z21LocoInfo::IsSmartSearch() const
{
    return smartSearch;
}
