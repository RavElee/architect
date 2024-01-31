#ifndef MOVABLE_H
#define MOVABLE_H

#include <cstdint>
#include <vector.h>

namespace spacebattle
{
    class movable
    {
    public:
        virtual ~movable() = default;
        virtual math::vector2D<std::int32_t> getPosition() const = 0;
        virtual math::vector2D<std::int32_t> getVelocity() const = 0;
        virtual void setPosition(math::vector2D<std::int32_t> position) = 0;
    };

} // namespace spacebattle

#endif // MOVABLE_H
