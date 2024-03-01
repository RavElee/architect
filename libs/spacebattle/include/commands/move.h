#ifndef MOVE_H
#define MOVE_H

#include "command.h"

namespace engine
{
    class movable;

    class move : public command
    {
        movable &obj;

    public:
        explicit move(movable &obj);
        void execute() override;
    };
} // namespace engine

#endif // MOVE_H
