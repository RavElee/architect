#ifndef ROTATE_H
#define ROTATE_H

#include <command.h>
#include <rotatable.h>

namespace engine {
class rotate : public command {
    rotatable &obj;
public:
    rotate(rotatable &obj);
    void execute() override;
};

} // namespace spacebattle

#endif // ROTATE_H
