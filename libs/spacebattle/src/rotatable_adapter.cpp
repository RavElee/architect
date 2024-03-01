
#include <rotatable_adapter.h>
#include <uobject.h>
#include <rotatable.h>


namespace engine
{
    rotatable_adapter::rotatable_adapter(uobject& obj):obj(obj)
    {}

    math::direction rotatable_adapter::getDirection() const
    {
        auto d = obj.getProperty<std::int32_t>(PROPERTY::DIRECTION);
        auto c = obj.getProperty<std::uint32_t>(PROPERTY::DIRECTIONS_COUNT);
        return math::direction(d, c);
    }

    void rotatable_adapter::setDirection(math::direction direction)
    {
        obj.setProperty(PROPERTY::DIRECTION, direction.getDirection());
        obj.setProperty(PROPERTY::DIRECTIONS_COUNT, direction.getDirectionCount());
    }

    std::int32_t rotatable_adapter::getAngularVelocity() const
    {
        return obj.getProperty<std::int32_t>(PROPERTY::ANGULAR_VELOCITY);
    }
} // namespace spacebattle
