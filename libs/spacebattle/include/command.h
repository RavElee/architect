#ifndef COMMAND_H
#define COMMAND_H

namespace spacebattle
{
    class command
    {
    public:
        virtual ~command() = default;
        virtual void execute() = 0;
    };
} // namespace spacebattle
#endif // COMMAND_H
