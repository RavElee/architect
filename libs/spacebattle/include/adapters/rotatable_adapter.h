#ifndef ROTATABLE_ADAPTER_H
#define ROTATABLE_ADAPTER_H

#include <interfaces/rotatable.h>

namespace engine
{
    class uobject;

    class rotatable_adapter : public rotatable
    {
    public:
        rotatable_adapter(uobject& obj);
        math::direction getDirection() const override;
        void setDirection(math::direction direct) override;
        std::int32_t getAngularVelocity() const override;

    private:
        uobject& obj;
    };
} // namespace spacebattle

#endif // ROTATABLE_ADAPTER_H
