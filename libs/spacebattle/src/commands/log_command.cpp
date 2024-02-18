
#include <commands/log_command.h>

namespace engine
{
    log_command::log_command(const std::exception &e) : e(e)
    {
    }

    void log_command::execute()
    {
        std::cout << "Exception has been thrown: " << typeid(e).name() << " " << e.what() << std::endl;
    }
} // namespace engine
