
#include <direction.h>

namespace math
{
    direction::direction(const std::uint32_t direction, const std::uint32_t directionCount)
        : currDirection(direction), directionsCount(directionCount)
    {
    }

    direction &direction::next(const std::int32_t angularVelocity)
    {
        currDirection = (currDirection + angularVelocity) % directionsCount;
        return *this;
    }

    std::int32_t direction::getDirection() const
    {
        return currDirection;
    }

    std::uint32_t direction::getDirectionCount() const
    {
        return directionsCount;
    }
} // namespace math
