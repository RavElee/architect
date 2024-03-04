#ifndef ROTATABLE_H
#define ROTATABLE_H

#include <cstdint>
#include <direction.h>

namespace engine
{
    class rotatable
    {
    public:
        virtual ~rotatable() = default;
        virtual math::direction getDirection() const = 0;
        virtual void setDirection(math::direction direct) = 0;
        virtual std::int32_t getAngularVelocity() const = 0;
    };
} // namespace spacebattle

#endif // ROTATABLE_H
