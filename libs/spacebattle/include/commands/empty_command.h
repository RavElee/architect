#ifndef EMPTY_COMMAND_H
#define EMPTY_COMMAND_H

#include "command.h"

namespace engine
{
    class empty_command : public engine::command
    {
    public:
        void execute() override
        {
        }
    };

} // namespace engine
#endif // EMPTY_COMMAND_H
