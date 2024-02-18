#ifndef REPEAT_COMMAND_H
#define REPEAT_COMMAND_H

#include "command.h"

namespace engine
{

    class repeat_command : public command
    {
        command_shared cmd;

    public:
        explicit repeat_command(command_shared cmd) : cmd(cmd)
        {
        }

        void execute() override
        {
            cmd->execute();
        }
    };

} // namespace engine

#endif // REPEAT_COMMAND_H
