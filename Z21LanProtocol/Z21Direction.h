#ifndef Z21DIRECTION_H
#define Z21DIRECTION_H

#include "global.h"

class Z21_EXPORT Z21Direction
{
public:
    Z21Direction() = default;

    enum class Direction { Forward, Backward };
    /**
     * @brief SetValue
     * @param d
     */
    void SetValue(Direction d);
    /**
     * @brief Value
     * @return
     */
    Direction Value() const;

    /**
     * @brief IsForward
     * @return true if direction is forward
     */
    bool IsForward() const;
    /**
     * @brief IsBackward
     * @return true if direction is backward
     */
    bool IsBackward() const;

private:
    Direction direction = Direction::Forward;
};

#endif // Z21DIRECTION_H
