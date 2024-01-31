#include <cmath>
#include <iostream>
#include <quadratic_solver.h>

namespace IDZ_1 {
    std::vector<double> quadratic_solver::solve(double a, double b, double c, double eps)
    {
        if(std::isnan(a + b + c))
            throw std::exception();
        if(std::isinf(a + b + c))
            throw std::exception();

        if(nearToZero(a, eps))
            throw std::exception();

        std::vector<double> result;

        double d = b * b - 4.0 * a * c;
        if(std::signbit(d) == true)// no roots in real numbers
            return result;

        if(nearToZero(d, eps))
        {
            result.push_back(-b / (2 * a));
            result.push_back(-b / (2 * a));
        }
        else
        {
            result.push_back((-b + std::sqrt(d)) / (2 * a));
            result.push_back((-b - std::sqrt(d)) / (2 * a));
        }
        return result;
    }
}


