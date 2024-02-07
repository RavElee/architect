
#include <rotate.h>
#include <iostream>

namespace spacebattle
{
    rotate::rotate(rotatable &obj) : obj(obj)
    {
    }

    void rotate::execute()
    {
        obj.setDirection(obj.getDirection().next(obj.getAngularVelocity()));
    }

} // namespace spacebattle
