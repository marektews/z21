#include "Z21Direction.h"

void Z21Direction::SetValue(Direction d)
{
    direction = d;
}

Z21Direction::Direction Z21Direction::Value() const
{
    return direction;
}

bool Z21Direction::IsForward() const
{
    return direction == Direction::Forward ? true : false;
}

bool Z21Direction::IsBackward() const
{
    return direction == Direction::Backward ? true : false;
}
