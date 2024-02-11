#ifndef SHIP_H
#define SHIP_H

#include "movable_adapter.h"
#include <uobject.h>

namespace engine
{
    class spaceship : public uobject
    {
    public:
        spaceship();
    };
} // namespace spacebattle

#endif // SHIP_H
