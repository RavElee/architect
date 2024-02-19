#ifndef FUELABLE_ADAPTER_H
#define FUELABLE_ADAPTER_H

#include "uobject.h"
#include <interfaces/fuelable.h>
namespace engine
{
    class fuelable_adapter : public fuelable
    {
        uobject& obj;
    public:
        fuelable_adapter(uobject& obj) : obj(obj)
        {
        }

        void setFuel(float val) override
        {
            obj.setProperty(PROPERTY::FUEL, val);
        }

        float getFuel() const override
        {
            return obj.getProperty<float>(PROPERTY::FUEL);
        }

        float getVelocity() const override
        {
            return obj.getProperty<float>(PROPERTY::FUEL_VELOCITY);
        }

    };
} // namespace engine

#endif // FUELABLE_ADAPTER_H
