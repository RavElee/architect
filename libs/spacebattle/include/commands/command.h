#ifndef COMMAND_H
#define COMMAND_H

#include <functional>
#include <memory>

namespace engine
{
    class command
    {
    public:
        virtual ~command() = default;
        virtual void execute() = 0;
    };

    using command_shared = std::shared_ptr<command>;

} // namespace spacebattle
#endif // COMMAND_H
