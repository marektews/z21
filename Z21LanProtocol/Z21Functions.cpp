#include "Z21Functions.h"

/**
 * @brief Z21Functions::IsEnabled
 * @param functionNumber
 * @return
 */
bool Z21Functions::IsEnabled(Number number) const
{
    return flags & (1<<static_cast<int>(number)) ? true : false;
}

/**
 * @brief Z21Functions::Enable
 * @param number
 */
void Z21Functions::Enable(Number number, bool enable)
{
    if(enable)
        flags |= 1<<static_cast<int>(number);
    else
        flags &= ~(1<<static_cast<int>(number));
}

/**
 * @brief Z21Functions::IsLights
 * @return true if ligths are switched on
 */
bool Z21Functions::IsLights() const
{
    return IsEnabled(Number::Lights);
}

/**
 * @brief Z21Functions::SetLights
 * @param on
 */
void Z21Functions::SetLights(bool on)
{
    Enable(Number::Lights, on);
}


/**
 * @brief unary operator ++ for Z21Functions::Number enum class
 * @param n Previous value
 * @return Incremented value
 */
Z21Functions::Number &operator ++(Z21Functions::Number &n)
{
    n = static_cast<Z21Functions::Number>( static_cast<int>(n) + 1 );
    if( n == Z21Functions::Number::F_OVERFLOW )
        n = Z21Functions::Number::F0;
    return n;
}
