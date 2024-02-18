#ifndef MOVABLE_ADAPTER_H
#define MOVABLE_ADAPTER_H

#include <movable.h>

namespace engine
{
    class uobject;

    class movable_adapter : public movable
    {
    public:
        explicit movable_adapter(uobject& obj);

        math::vector2D<std::int32_t> getPosition() const override;
        void setPosition(math::vector2D<std::int32_t> position) override;
        math::vector2D<std::int32_t> getVelocity() const override;
    protected:
        uobject &obj;
    };
} // namespace spacebattle

#endif // MOVABLE_ADAPTER_H
