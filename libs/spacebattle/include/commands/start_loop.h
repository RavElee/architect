#ifndef CREATE_EVENT_LOOP_H
#define CREATE_EVENT_LOOP_H

#include "command.h"
#include "loop.h"

namespace engine
{
    class start_loop : public command
    {
        loop& eventLoop;
    public:
        inline explicit start_loop(loop& el):
            eventLoop(el)
        {
        }

        inline void execute() override
        {
            eventLoop.start();
        }
    };
} // namespace engine

#endif // CREATE_EVENT_LOOP_H
