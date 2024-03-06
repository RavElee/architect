#ifndef UOBJECT_H
#define UOBJECT_H

#include <iostream>
#include <memory>
#include <vector.h>
#include <any>
#include <unordered_map>

namespace engine
{
    enum class PROPERTY
    {
        POSITION,
        DIRECTION,
        DIRECTIONS_COUNT,
        VELOCITY_ABS,
        VELOCITY_VECTOR,
        ANGULAR_VELOCITY,
        FUEL,
        FUEL_VELOCITY
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
                // throw std::exception();
                throw std::runtime_error("undefined key");

            return std::any_cast<std::decay_t<T>>(map.at(key));
        }

        template<class T>
        void setProperty(const PROPERTY key, T val)
        {
            setPropertyHelper<std::decay_t<T>>(key, val);
        }

        uobject& operator=(uobject&& other)
        {
            std::cout << "move operator="<< std::endl;
            if(this == &other)
                return *this;
            this->map = std::move(other.map);
            return *this;
        }

        uobject& operator=(const uobject& other)
        {
            std::cout << "copy operator="<< std::endl;
            if(this == &other)
                return *this;

            this->map = other.map;

            return *this;
        }

        uobject(const uobject& other):
            map(other.map)
        {
            std::cout << "copy cnstr"<< std::endl;
        }

        uobject(uobject&& other):
            map(std::move(other.map))
        {
            std::cout << "move cnstr"<< std::endl;
        }

        uobject() = default;

        std::size_t size() const
        {
            return map.size();
        }

    private:
        template<class T, std::enable_if_t<std::is_same<T, std::decay_t<T>>::value, bool> = true>
        void setPropertyHelper(const PROPERTY key, T val)
        {
            map[key] = val;
        }

        std::unordered_map<PROPERTY, std::any> map;
    };

    using shared_uobject = std::shared_ptr<uobject>;
} // namespace spacebattle


#endif // UOBJECT_H
