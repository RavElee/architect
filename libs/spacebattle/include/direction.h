#ifndef DIRECTION_H
#define DIRECTION_H

#include <cstdint>

namespace math
{
    class direction
    {
        std::int32_t currDirection;
        std::uint32_t directionsCount;
    public:
        direction(const std::uint32_t direction, const std::uint32_t directionCount);
        direction& next(const std::int32_t angularVelocity);

        std::int32_t getDirection() const;
        std::uint32_t getDirectionCount() const;

        operator decltype(currDirection)() const
        {
            return this->currDirection;
        }
    };
} // namespace math

#endif // DIRECTION_H
