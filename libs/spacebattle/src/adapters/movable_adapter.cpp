
#include "uobject.h"
#include <adapters/movable_adapter.h>
#include <interfaces/movable.h>

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
        return obj.getProperty<math::vectorInt2D>(PROPERTY::VELOCITY_VECTOR);
    }

} // namespace spacebattle