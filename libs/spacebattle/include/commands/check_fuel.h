#ifndef CHECK_FUEL_H
#define CHECK_FUEL_H

#include "check_fuel_exception.h"
#include "fuelable.h"
#include <commands/command.h>
#include <limits>

#include <iostream>

namespace engine
{
    class check_fuel : public command
    {
        fuelable& obj;
    public:
        explicit check_fuel(fuelable& obj) : obj(obj){}

        void execute() override
        {
            if ((obj.getFuel() - obj.getVelocity()) <
                std::numeric_limits<decltype(obj.getFuel())>::epsilon())
                throw check_fuel_exception();
        }
    };
} // namespace engine

#endif // CHECK_FUEL_H
