#ifndef EMPTY_EXCEPTION_H
#define EMPTY_EXCEPTION_H

#include <exception>

namespace engine
{
    class empty_exception : public std::exception
    {
    public:
        const char *what() const noexcept override
        {
            return "empty_exception";
        }
    };
} // namespace engine

#endif // EMPTY_EXCEPTION_H
