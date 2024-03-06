#ifndef MOVABLE_ADAPTER_WITH_COURSE_H
#define MOVABLE_ADAPTER_WITH_COURSE_H

#include "direction.h"
#include "uobject.h"
#include <adapters/movable_adapter.h>
#include <cmath>

namespace engine
{
    // меняет вектор скорости в соответствии с курсом
    class movable_adapter_with_cource : public movable_adapter
    {
    public:
        using movable_adapter::movable_adapter;

        math::vector2D<std::int32_t> getVelocity() const override
        {
            auto dir = obj->getProperty<math::direction>(PROPERTY::DIRECTION);
            int d = dir.getDirection();
            int n = dir.getDirectionCount();
            double v = obj->getProperty<double>(PROPERTY::VELOCITY_ABS);
            return math::vectorInt2D( std::round(v * std::cos(static_cast<double>((double)d * 2 * M_PI / (double) n))),
                                      std::round(v * std::sin(static_cast<double>((double)d * 2 * M_PI / (double) n))));
        }

    };
} // namespace engine

#endif // MOVABLE_ADAPTER_WITH_COURSE_H
