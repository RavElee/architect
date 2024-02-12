#ifndef EXCEPTIONHANDLER_H
#define EXCEPTIONHANDLER_H

#include "command.h"
#include <functional>
#include <map>
#include <typeindex>

namespace engine
{

    using handlerFunc = std::function<spacebattle::command_shared(spacebattle::command_shared, const std::exception &e)>;

    class exception_handler
    {
        using exception_type = std::type_index;
        using command_type = std::type_index;

    public:
        static exception_handler &instance();

        void register_handler(const command_type c, const exception_type e, const handlerFunc func);

        spacebattle::command_shared handle(spacebattle::command_shared &c, const std::exception &e);
        spacebattle::command_shared handle(spacebattle::command &c, const std::exception &e);

        ~exception_handler() = default;
    private:
        exception_handler() = default;
        std::map<exception_type, std::map<command_type, handlerFunc>> storage;
    };
} // namespace engine
#endif // EXCEPTIONHANDLER_H
