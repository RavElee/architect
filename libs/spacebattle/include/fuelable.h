#ifndef FUELABLE_H
#define FUELABLE_H

namespace engine
{
    class fuelable
    {
    public:
        fuelable() = default;
        virtual ~fuelable() = default;

        virtual void setFuel(float val) = 0;
        virtual float getFuel() const = 0;

        virtual float getVelocity() const = 0;
    };
} // namespace engine

#endif // FUELABLE_H
