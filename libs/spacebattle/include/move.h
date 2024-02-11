#ifndef MOVE_H
#define MOVE_H

#include "command.h"
#include "movable.h"

namespace engine
{
    class move : public command
    {
        movable &obj;

    public:
        move(movable &obj);
        void execute() override;
    };
} // namespace spacebattle

#endif // MOVE_H
