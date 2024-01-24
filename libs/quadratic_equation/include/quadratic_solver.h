#ifndef QUADRATIC_SOLVER_H
#define QUADRATIC_SOLVER_H

#include <cmath>
#include <limits>
#include <vector>

namespace IDZ_1 {

template<class T>
constexpr bool almostEqual(T x, T y, decltype(std::numeric_limits<T>::epsilon()) eps = std::numeric_limits<T>::epsilon())
{
	return std::abs(x - y) < eps;
}

template<class T>
constexpr bool nearToZero(T x, decltype(std::numeric_limits<T>::epsilon()) eps = std::numeric_limits<T>::epsilon())
{
	return std::abs(x) < eps;
}

class quadratic_solver {
public:
    static std::vector<double> solve(double a, double b = 0, double c = 0, double eps = std::numeric_limits<double>::epsilon());
};
} // namespace IDZ_1

#endif // QUADRATIC_SOLVER_H
