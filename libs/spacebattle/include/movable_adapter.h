#ifndef MOVABLE_ADAPTER_H
#define MOVABLE_ADAPTER_H

#include <movable.h>

namespace spacebattle
{
    class uobject;

    class movable_adapter : public movable
    {
    public:
        movable_adapter(uobject& obj);

        math::vector2D<std::int32_t> getPosition() const override;
        void setPosition(math::vector2D<std::int32_t> position) override;
        math::vector2D<std::int32_t> getVelocity() const override;
    private:
        uobject &obj;
    };
} // namespace spacebattle

#endif // MOVABLE_ADAPTER_H
