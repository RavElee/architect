#ifndef LOG_COMMAND_H
#define LOG_COMMAND_H

#include "command.h"
#include <iostream>

namespace engine
{
    class log_command : public engine::command
    {
    public:
        log_command(const std::exception& e):e(e) {};

        void execute() override
        {
            std::cout << "Exception has been thrown: " << typeid(e).name() << " " << e.what() << std::endl;
        }

    private:
        const std::exception& e;
    };
} // namespace engine

#endif // LOG_COMMAND_H
