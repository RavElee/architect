#ifndef MACRO_COMMAND_H
#define MACRO_COMMAND_H
#include <commands/command.h>
#include <vector>
#include <exception>

namespace engine
{
    class command_exception : public std::exception
    {
    public:
    };

    class macro_command : public command
    {
        std::vector<command_shared> cmd_vec;

    public:
        explicit macro_command(const std::vector<command_shared> &vec) : cmd_vec(std::move(vec))
        {
        }
        explicit macro_command(std::initializer_list<command_shared> list) : macro_command(std::vector<command_shared>(list))
        {
        }
        macro_command() = delete;

        void execute() override
        {
            try
            {
                for (auto &cmd : cmd_vec)
                    cmd->execute();
            }
            catch (const std::exception &e)
            {
                throw command_exception();
            }
        }
    };
} // namespace engine

#endif // MACRO_COMMAND_H
