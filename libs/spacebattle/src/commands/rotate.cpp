
#include <commands/rotate.h>
#include <interfaces/rotatable.h>

namespace engine
{
    rotate::rotate(rotatable &obj) : obj(obj)
    {
    }

    void rotate::execute()
    {
        obj.setDirection(obj.getDirection().next(obj.getAngularVelocity()));
    }

} // namespace spacebattle
