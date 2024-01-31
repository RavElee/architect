#include <iostream>
#include <move.h>

namespace spacebattle
{
    move::move(movable &obj) : obj(obj)
    {
    }

    void move::execute()
    {
        obj.setPosition(obj.getPosition() + obj.getVelocity());
    }
} // namespace spacebattle
