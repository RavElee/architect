#ifndef MOVE_STRAIGHT_H
#define MOVE_STRAIGHT_H

#include "check_fuel.h"
#include "burn_fuel.h"
#include "commands/move.h"
#include "interfaces/movable.h"
#include "macro_command.h"

namespace engine
{
    class move_straight : public macro_command
    {
    public:
        explicit move_straight(movable &m_obj, fuelable& f_obj)
            : macro_command(
                {std::make_shared<engine::check_fuel>(f_obj),
                 std::make_shared<engine::burn_fuel>(f_obj),
                 std::make_shared<engine::move>(m_obj)}
                )
        {
        }
        move_straight() = delete;
    };
} // namespace engine
#endif // MOVE_STRAIGHT_H
