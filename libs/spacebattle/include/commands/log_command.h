#ifndef LOG_COMMAND_H
#define LOG_COMMAND_H

#include "command.h"
#include <iostream>

namespace engine
{
    class log_command : public engine::command
    {
    public:
        explicit log_command(const std::exception& e);

        void execute() override;

    private:
        const std::exception& e;
    };
} // namespace engine

#endif // LOG_COMMAND_H
