#include "rotatable_adapter.h"
#include <gtest/gtest.h>
#include <move.h>
#include <rotate.h>
#include <spaceship.h>

// 7.3.1
TEST(MOVING, MOVE_TEST)
{
    spacebattle::spaceship ship;
    ship.setProperty(spacebattle::PROPERTY::POSITION, math::vectorInt2D(12, 5));
    ship.setProperty(spacebattle::PROPERTY::DIRECTION, 0);
    ship.setProperty(spacebattle::PROPERTY::DIRECTIONS_COUNT, 3600);
    ship.setProperty(spacebattle::PROPERTY::VELOCITY_VECTOR, math::vectorInt2D(-7, 3));

    spacebattle::movable_adapter mv_adapter(ship);
    spacebattle::move mv_cmd(mv_adapter);

    mv_cmd.execute();

    EXPECT_EQ(ship.getProperty<math::vectorInt2D>(spacebattle::PROPERTY::POSITION), math::vectorInt2D(5, 8));
}

// 7.3.2
TEST(MOVING, CANT_GET_POSITION)
{
    spacebattle::spaceship ship;

    // Не проставили свойство Position. Ожидаем ошибку
    // ship.setProperty(spacebattle::PROPERTY::POSITION, math::vectorInt2D(12,5));

    ship.setProperty(spacebattle::PROPERTY::DIRECTION, 0);
    ship.setProperty(spacebattle::PROPERTY::DIRECTIONS_COUNT, 3600);
    ship.setProperty(spacebattle::PROPERTY::VELOCITY_VECTOR, math::vectorInt2D(-7, 3));
    spacebattle::movable_adapter mv_adapter(ship);
    spacebattle::move mv_cmd(mv_adapter);

    EXPECT_ANY_THROW(mv_cmd.execute());
}

// 7.3.3
TEST(MOVING, CANT_GET_VELOCITY)
{
    spacebattle::spaceship ship;
    ship.setProperty(spacebattle::PROPERTY::POSITION, math::vectorInt2D(12, 5));
    ship.setProperty(spacebattle::PROPERTY::DIRECTION, 0);
    ship.setProperty(spacebattle::PROPERTY::DIRECTIONS_COUNT, 3600);

    // Не проставили свойство Velocity. Ожидаем ошибку
    // ship.setProperty(spacebattle::PROPERTY::VELOCITY_VECTOR, math::vectorInt2D(-7,3));

    spacebattle::movable_adapter mv_adapter(ship);
    spacebattle::move mv_cmd(mv_adapter);

    EXPECT_ANY_THROW(mv_cmd.execute());
}

TEST(ROTATING, ROTATE_TEST)
{
    spacebattle::spaceship ship;
    ship.setProperty(spacebattle::PROPERTY::DIRECTION, 900);
    ship.setProperty(spacebattle::PROPERTY::DIRECTIONS_COUNT, (std::uint32_t) 3600);
    ship.setProperty(spacebattle::PROPERTY::ANGULAR_VELOCITY, 100);

    spacebattle::rotatable_adapter rotate_adapter(ship);
    spacebattle::rotate rotate_cmd(rotate_adapter);

    rotate_cmd.execute();


    EXPECT_EQ(ship.getProperty<int>(spacebattle::PROPERTY::DIRECTION),
              1000);
}


TEST(ROTATING, CANT_GET_DIRECTION)
{
    spacebattle::spaceship ship;
    // ship.setProperty(spacebattle::PROPERTY::DIRECTION, 900);
    ship.setProperty(spacebattle::PROPERTY::DIRECTIONS_COUNT, (std::uint32_t) 3600);
    ship.setProperty(spacebattle::PROPERTY::ANGULAR_VELOCITY, 100);

    spacebattle::rotatable_adapter rotate_adapter(ship);
    spacebattle::rotate rotate_cmd(rotate_adapter);

    EXPECT_ANY_THROW(rotate_cmd.execute());
}

TEST(ROTATING, CANT_GET_ANGULAR_VELOCITY)
{
    spacebattle::spaceship ship;
    ship.setProperty(spacebattle::PROPERTY::DIRECTION, 900);
    ship.setProperty(spacebattle::PROPERTY::DIRECTIONS_COUNT, (std::uint32_t) 3600);
    // ship.setProperty(spacebattle::PROPERTY::ANGULAR_VELOCITY, 100);

    spacebattle::rotatable_adapter rotate_adapter(ship);
    spacebattle::rotate rotate_cmd(rotate_adapter);

    EXPECT_ANY_THROW(rotate_cmd.execute());
}

TEST(ROTATING, CANT_GET_DIRECTIONS_COUNT)
{
    spacebattle::spaceship ship;
    ship.setProperty(spacebattle::PROPERTY::DIRECTION, 900);
    // ship.setProperty(spacebattle::PROPERTY::DIRECTIONS_COUNT, (std::uint32_t) 3600);
    ship.setProperty(spacebattle::PROPERTY::ANGULAR_VELOCITY, 100);

    spacebattle::rotatable_adapter rotate_adapter(ship);
    spacebattle::rotate rotate_cmd(rotate_adapter);

    EXPECT_ANY_THROW(rotate_cmd.execute());
}


int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
