#ifndef ROTATE_H
#define ROTATE_H

#include "command.h"

namespace engine
{
    class rotatable;

    class rotate : public command
    {
        rotatable &obj;

    public:
        rotate(rotatable &obj);
        void execute() override;
    };

} // namespace engine

#endif // ROTATE_H
