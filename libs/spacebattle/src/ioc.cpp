
#include <ioc.h>

namespace engine
{
    ioc::scope_ptr ioc::rootScope = std::make_shared<ioc::scope>();
    thread_local ioc::scope_ptr ioc::currentScope = nullptr;
} // namespace enginep
