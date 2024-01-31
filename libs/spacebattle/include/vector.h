#ifndef VECTOR_H
#define VECTOR_H

#include <array>
#include <cstdint>
#include <ostream>

namespace math
{
    template <class T, std::uint32_t N>
    class vector
    {
    public:
        vector()
        {
            coords.fill(0);
        }

        template<class A1, class... A2>
        vector(A1 var, A2... var2)
        {
            constexpr std::size_t n = sizeof...(A2);
            static_assert(n <= N);
            int i = 0;
            coords.at(i++) = var;
            fill(i, var2...);
        }

        friend vector<T, N> operator+(const vector<T, N> in1, const vector<T, N> in2)
        {
            vector<T, N> out;
            for (std::uint32_t i = 0; i < N; i++)
            {
                out.coords.at(i) = in1.coords.at(i) + in2.coords.at(i);
            }
            return out;
        }

        vector<T, N> plus(const vector<T, N> in1, const vector<T, N> in2)
        {
            return in1 + in2;
        }

        friend std::ostream& operator<<(std::ostream& os, vector<T,N> vec)
        {
            for(const auto& it : vec.coords)
                os << it << " ";
            os << std::endl;
            return os;
        }

        bool operator==(const vector<T, N>& other) const
        {
            return coords == other.coords;
        }

    private:
        void fill(int& ){};

        template<class A1, class... A2>
        void fill(int& iter, A1 var, A2... var2)
        {
            coords.at(iter++) = var;
            fill(iter, var2...);
        }

        std::array<T, N> coords;
    };

    template <class T>
    using vector2D = vector<T, 2>;

    using vectorInt2D = vector2D<std::int32_t>;


} // namespace math

#endif // VECTOR_H
