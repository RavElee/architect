#ifndef MOCK_H
#define MOCK_H

#include <gmock/gmock.h>
#include <command.h>
#include <exception_handler.h>

class mock_command : public spacebattle::command
{
public:
    MOCK_METHOD(void, execute, (), (override));
};

class mock_exception : public std::exception
{
    const char * what() const noexcept override
    {
        return "mock exception";
    }
};



engine::handlerFunc mock_handler = [](spacebattle::command_shared cmd, const std::exception&)->spacebattle::command_shared
{
    return cmd;
};



#endif //MOCK_H
