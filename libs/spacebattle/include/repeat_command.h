#ifndef REPEAT_COMMAND_H
#define REPEAT_COMMAND_H

#include "command.h"
#include <iostream>
namespace engine
{

    class repeat_command : public spacebattle::command
    {
        spacebattle::command_shared cmd;
    public:
        repeat_command(spacebattle::command_shared cmd): cmd(cmd) {}

        void execute() override
        {
            cmd->execute();
        }
    };

} // namespace engine

#endif // REPEAT_COMMAND_H
