#ifndef BURN_FUEL_H
#define BURN_FUEL_H

#include "interfaces/fuelable.h"
#include <commands/command.h>

namespace engine
{
    class burn_fuel : public command
    {
        fuelable &obj;
    public:
        explicit burn_fuel(fuelable &obj) : obj(obj)
        {
        }

        void execute() override
        {
            obj.setFuel(obj.getFuel() - obj.getVelocity());
        }
    };
} // namespace engine

#endif // BURN_FUEL_H
