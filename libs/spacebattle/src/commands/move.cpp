
#include <commands/move.h>
#include <interfaces/movable.h>

namespace engine
{
    move::move(movable &obj) : obj(obj)
    {
    }

    void move::execute()
    {
        obj.setPosition(obj.getPosition() + obj.getVelocity());
    }
} // namespace spacebattle
