#ifndef CHANGE_VELOCITY_H
#define CHANGE_VELOCITY_H

#include "burn_fuel.h"
#include "check_fuel.h"
#include "commands/rotate.h"
#include "interfaces/fuelable.h"
#include "interfaces/movable.h"
#include "interfaces/rotatable.h"
#include "macro_command.h"

namespace engine
{
    class change_velocity : public macro_command
    {
    public:
        explicit change_velocity(rotatable& r_obj, fuelable& f_obj)
            : macro_command(
                {std::make_shared<engine::check_fuel>(f_obj),
                 std::make_shared<engine::burn_fuel>(f_obj),
                 std::make_shared<engine::rotate>(r_obj)}
                )
        {
        }
        change_velocity() = delete;
    };
} // namespace engine
#endif // CHANGE_VELOCITY_H
