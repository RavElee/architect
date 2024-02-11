
#include "uobject.h"
#include <cmath>
#include <iostream>
#include <movable_adapter.h>

namespace engine
{
    movable_adapter::movable_adapter(uobject &obj) : obj(obj)
    {
    }

    math::vector2D<std::int32_t> movable_adapter::getPosition() const
    {
        return obj.getProperty<math::vectorInt2D>(PROPERTY::POSITION);
    }

    void movable_adapter::setPosition(math::vector2D<std::int32_t> position)
    {
        obj.setProperty(PROPERTY::POSITION, position);
    }

    math::vectorInt2D movable_adapter::getVelocity() const
    {
        // int d = obj.getProperty<int>(PROPERTY::DIRECTION);
        // int n = obj.getProperty<int>(PROPERTY::DIRECTIONS_COUNT);
        // int v = obj.getProperty<int>(PROPERTY::VELOCITY_ABS);
        // return math::vectorInt2D( v * std::cos(static_cast<double>((double)d * 2 * M_PI / (double) n)),
        //                           v * std::sin(static_cast<double>((double)d * 2 * M_PI / (double) n)));

        return obj.getProperty<math::vectorInt2D>(PROPERTY::VELOCITY_VECTOR);
    }

} // namespace spacebattle
