#ifndef Z21FUNCTIONS_H
#define Z21FUNCTIONS_H

#include "global.h"

class Z21_EXPORT Z21Functions
{
public:
    Z21Functions() = default;

    enum class Number { F0, Lights = F0, F1, F2, F3, F4, F5, F6, F7, F8, F9,
                        F10, F11, F12, F13, F14, F15, F16, F17, F18, F19,
                        F20, F21, F22, F23, F24, F25, F26, F27, F28, F29,
                        F30, F31, F_OVERFLOW };
    /**
     * @brief IsEnabled
     * @param number
     * @return true if function is switched on
     */
    bool IsEnabled(Number number) const;
    /**
     * @brief Enable
     * @param number
     * @param enable
     */
    void Enable(Number number, bool enable);

    /**
     * @brief IsLights
     * @return true if ligths are switched on
     */
    bool IsLights() const;
    /**
     * @brief SetLights
     * @param on
     */
    void SetLights(bool on);


private:
    quint32 flags = 0;
};

Z21Functions::Number& operator ++ (Z21Functions::Number& n);

#endif // Z21FUNCTIONS_H
