#ifndef UOBJECT_H
#define UOBJECT_H

#include <vector.h>
#include <any>
#include <unordered_map>

namespace spacebattle
{
    enum class PROPERTY
    {
        POSITION,
        DIRECTION,
        DIRECTIONS_COUNT,
        VELOCITY_ABS,
        VELOCITY_VECTOR,
        ANGULAR_VELOCITY
    };

    class uobject
    {
    public:
        enum TYPES : std::uint32_t
        {
            INT,
            VECTOR_INT_2D
        };

        virtual ~uobject() =default;

        template<class T>
        T getProperty(const PROPERTY key) const
        {
            if (map.find(key) == map.end())
                throw std::exception();

            return std::any_cast<T>(map.at(key));
        }

        template<class T>
        void setProperty(const PROPERTY key, T val)
        {
            map[key] = val;
        }


    private:
        std::unordered_map<PROPERTY, std::any> map;
    };
} // namespace spacebattle


#endif // UOBJECT_H
