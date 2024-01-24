#include <gtest/gtest.h>
#include <quadratic_solver.h>

// p.3
TEST(Quadratic_eq_solver, CHECK_NO_ROOTS)
{
    ASSERT_EQ(IDZ_1::quadratic_solver::solve(1, 0, 1).size(), 0);
}
// p.5
TEST(Quadratic_eq_solver, CHECK_TWO_DIFF_ROOTS)
{
    auto roots = IDZ_1::quadratic_solver::solve(1, 0, -1);
    ASSERT_EQ(roots.size(), 2);
    ASSERT_EQ(roots.at(0), 1);
    ASSERT_EQ(roots.at(1), -1);
}
// p.7
TEST(Quadratic_eq_solver, CHECK_TWO_SAME_ROOTS)
{
    auto roots = IDZ_1::quadratic_solver::solve(1, 2, 1);
    ASSERT_EQ(roots.size(), 2);
    ASSERT_EQ(roots.at(0), -1);
    ASSERT_EQ(roots.at(1), -1);
}
// p.9
TEST(Quadratic_eq_solver, IS_QUADRATIC_EQUATION)
{
    EXPECT_ANY_THROW(IDZ_1::quadratic_solver::solve(0));
}
// p.11
TEST(Quadratic_eq_solver, CHECK_NEAR_TO_ZERO_DISCRIMINANT)
{
    constexpr double eps = 1e-12;

    constexpr double div = 5.0f;

    // Проверка на то, что eps / div != 0 (> чем double's epsilon)
    ASSERT_EQ(IDZ_1::nearToZero(eps / div , std::numeric_limits<double>::epsilon()), false);

    double c_coeff = 1.0 / 4.0 - eps / div;
    auto roots = IDZ_1::quadratic_solver::solve(1, 1, c_coeff, eps);
    ASSERT_EQ(roots.size(), 2);
    ASSERT_EQ(std::abs(roots.at(0) - roots.at(1)) < eps, true);
}

TEST(Quadratic_eq_solver, CHECK_NEAR_TO_ZERO_DISCRIMINANT_A_GT_ZERO)
{
    /*
      условие 0 < D < eps
      0 < b^2 - 4*a*c < eps
      if a > 0 =>  (b^2 / (4a) - eps/(4a)) < c < (b^2 / (4a))
    */

    double eps = 1e-12;


    double a = 10.0f;

    double b = -13.21f;
    double temp_1 = b * b / (4.0f * a);
    double temp_2 = -eps / (4.0f * a);
    double div = 2.0f;
    double min_adjust = eps / (4.0f * a * div);

    // Проверка на то, что (eps/(4a)) / div != 0 (> чем double's epsilon)
    ASSERT_EQ(IDZ_1::nearToZero(min_adjust , std::numeric_limits<double>::epsilon()), false);
    double c_coeff = temp_1 + temp_2 + min_adjust;
    // проверка, что дискриминант >= 0
    ASSERT_EQ(IDZ_1::nearToZero(temp_1 - c_coeff, eps), true);

    auto roots = IDZ_1::quadratic_solver::solve(a, b, c_coeff, eps);
    ASSERT_EQ(roots.size(), 2);
    ASSERT_EQ(IDZ_1::almostEqual(roots.at(0), roots.at(1), eps), true);
}

TEST(Quadratic_eq_solver, CHECK_NEAR_TO_ZERO_DISCRIMINANT_A_LT_ZERO)
{
    /*
      условие 0 < D < eps
      0 < b^2 - 4*a*c < eps
      if a < 0 =>  (-b^2 / (4a)) < c < (eps/(4a) - b^2 / (4a))
    */

    double eps = 1e-12;

    double a = -10.0f;
    double b = -13.21f;
    double temp_1 = b * b / (4.0f * a);
    double temp_2 = -eps / (4.0f * a);
    double div = 2.0f;
    double min_adjust = eps / (4.0f * a * div);

    // Проверка на то, что (eps/(4a)) / div != 0 (> чем double's epsilon)
    ASSERT_EQ(IDZ_1::nearToZero(min_adjust , std::numeric_limits<double>::epsilon()), false);
    double c_coeff = temp_1 + temp_2 + min_adjust;
    // проверка, что дискриминант >= 0
    ASSERT_EQ(IDZ_1::nearToZero(temp_1 - c_coeff, eps), true);

    auto roots = IDZ_1::quadratic_solver::solve(a, b, c_coeff, eps);
    ASSERT_EQ(roots.size(), 2);
    ASSERT_EQ(IDZ_1::almostEqual(roots.at(0), roots.at(1), eps), true);
}

TEST(Quadratic_eq_solver, CHECK_ALL_NAN)
{
    double a = std::numeric_limits<double>::quiet_NaN();
    double b = std::numeric_limits<double>::quiet_NaN();
    double c = std::numeric_limits<double>::quiet_NaN();
    EXPECT_ANY_THROW(IDZ_1::quadratic_solver::solve(a, b, c));
}

TEST(Quadratic_eq_solver, CHECK_ONE_NAN)
{
    double a = std::numeric_limits<double>::quiet_NaN();
    double b = 10.0;
    double c = -3.0;
    EXPECT_ANY_THROW(IDZ_1::quadratic_solver::solve(a, b, c));
    std::swap(a, b);
    EXPECT_ANY_THROW(IDZ_1::quadratic_solver::solve(a, b, c));
    std::swap(b, c);
    EXPECT_ANY_THROW(IDZ_1::quadratic_solver::solve(a, b, c));
}

TEST(Quadratic_eq_solver, CHECK_ALL_INF)
{
    double a = std::numeric_limits<double>::infinity();
    double b = std::numeric_limits<double>::infinity();
    double c = std::numeric_limits<double>::infinity();
    EXPECT_ANY_THROW(IDZ_1::quadratic_solver::solve(a, b, c));
}

TEST(Quadratic_eq_solver, CHECK_ONE_INF)
{
    double a = std::numeric_limits<double>::infinity();
    double b = 10.0;
    double c = -3.0;
    EXPECT_ANY_THROW(IDZ_1::quadratic_solver::solve(a, b, c));
    std::swap(a, b);
    EXPECT_ANY_THROW(IDZ_1::quadratic_solver::solve(a, b, c));
    std::swap(b, c);
    EXPECT_ANY_THROW(IDZ_1::quadratic_solver::solve(a, b, c));
}





int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


