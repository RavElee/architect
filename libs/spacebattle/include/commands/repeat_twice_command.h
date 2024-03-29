#ifndef DOUBLE_REPEAT_COMMAND_H
#define DOUBLE_REPEAT_COMMAND_H

#include "repeat_command.h"
namespace engine
{
    class repeat_twice_command : public engine::repeat_command
    {
    public:
        explicit repeat_twice_command(command_shared cmd) : repeat_command(cmd) {};
    };
} // namespace engine

#endif // DOUBLE_REPEAT_COMMAND_H
