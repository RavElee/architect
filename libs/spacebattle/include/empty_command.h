#ifndef EMPTY_COMMAND_H
#define EMPTY_COMMAND_H

#include <command.h>
#include <iostream>
#include <empty_exception.h>

namespace engine
{
    class empty_command : public spacebattle::command
    {
    public:
        void execute() override
        {
        }
    };

} // namespace engine
#endif // EMPTY_COMMAND_H
