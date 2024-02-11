#include <iostream>
#include <exception_handler.h>

namespace engine
{
    exception_handler& exception_handler::instance()
    {
        static exception_handler handler;
        return handler;
    }

    void exception_handler::register_handler(const command_type c, const exception_type e, const handlerFunc func)
    {
        storage[c][e] = func;
    }

    spacebattle::command_shared exception_handler::handle(spacebattle::command_shared &c, const std::exception &e)
    {
        auto t_cmd = std::type_index(typeid(*c));
        auto t_exc = std::type_index(typeid(e));

        return storage.at(t_cmd).at(t_exc)(c, e);
    }
}
