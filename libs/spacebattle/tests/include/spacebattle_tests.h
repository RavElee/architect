#ifndef SPACEBATTLE_TESTS_H
#define SPACEBATTLE_TESTS_H

#include <gtest/gtest.h>

#include "rotatable_adapter.h"
#include <gtest/gtest.h>
#include <move.h>
#include <rotate.h>
#include <spaceship.h>

// 7.3.1
TEST(MOVING, MOVE_TEST)
{
    engine::spaceship ship;
    ship.setProperty(engine::PROPERTY::POSITION, math::vectorInt2D(12, 5));
    ship.setProperty(engine::PROPERTY::DIRECTION, 0);
    ship.setProperty(engine::PROPERTY::DIRECTIONS_COUNT, 3600);
    ship.setProperty(engine::PROPERTY::VELOCITY_VECTOR, math::vectorInt2D(-7, 3));

    engine::movable_adapter mv_adapter(ship);
    engine::move mv_cmd(mv_adapter);

    mv_cmd.execute();

    EXPECT_EQ(ship.getProperty<math::vectorInt2D>(engine::PROPERTY::POSITION), math::vectorInt2D(5, 8));
}

// 7.3.2
TEST(MOVING, CANT_GET_POSITION)
{
    engine::spaceship ship;

    // Не проставили свойство Position. Ожидаем ошибку
    // ship.setProperty(engine::PROPERTY::POSITION, math::vectorInt2D(12,5));

    ship.setProperty(engine::PROPERTY::DIRECTION, 0);
    ship.setProperty(engine::PROPERTY::DIRECTIONS_COUNT, 3600);
    ship.setProperty(engine::PROPERTY::VELOCITY_VECTOR, math::vectorInt2D(-7, 3));
    engine::movable_adapter mv_adapter(ship);
    engine::move mv_cmd(mv_adapter);

    EXPECT_ANY_THROW(mv_cmd.execute());
}

// 7.3.3
TEST(MOVING, CANT_GET_VELOCITY)
{
    engine::spaceship ship;
    ship.setProperty(engine::PROPERTY::POSITION, math::vectorInt2D(12, 5));
    ship.setProperty(engine::PROPERTY::DIRECTION, 0);
    ship.setProperty(engine::PROPERTY::DIRECTIONS_COUNT, 3600);

    // Не проставили свойство Velocity. Ожидаем ошибку
    // ship.setProperty(engine::PROPERTY::VELOCITY_VECTOR, math::vectorInt2D(-7,3));

    engine::movable_adapter mv_adapter(ship);
    engine::move mv_cmd(mv_adapter);

    EXPECT_ANY_THROW(mv_cmd.execute());
}

TEST(ROTATING, ROTATE_TEST)
{
    engine::spaceship ship;
    ship.setProperty(engine::PROPERTY::DIRECTION, 900);
    ship.setProperty(engine::PROPERTY::DIRECTIONS_COUNT, (std::uint32_t) 3600);
    ship.setProperty(engine::PROPERTY::ANGULAR_VELOCITY, 100);

    engine::rotatable_adapter rotate_adapter(ship);
    engine::rotate rotate_cmd(rotate_adapter);

    rotate_cmd.execute();


    EXPECT_EQ(ship.getProperty<int>(engine::PROPERTY::DIRECTION),
              1000);
}


TEST(ROTATING, CANT_GET_DIRECTION)
{
    engine::spaceship ship;
    // ship.setProperty(engine::PROPERTY::DIRECTION, 900);
    ship.setProperty(engine::PROPERTY::DIRECTIONS_COUNT, (std::uint32_t) 3600);
    ship.setProperty(engine::PROPERTY::ANGULAR_VELOCITY, 100);

    engine::rotatable_adapter rotate_adapter(ship);
    engine::rotate rotate_cmd(rotate_adapter);

    EXPECT_ANY_THROW(rotate_cmd.execute());
}

TEST(ROTATING, CANT_GET_ANGULAR_VELOCITY)
{
    engine::spaceship ship;
    ship.setProperty(engine::PROPERTY::DIRECTION, 900);
    ship.setProperty(engine::PROPERTY::DIRECTIONS_COUNT, (std::uint32_t) 3600);
    // ship.setProperty(engine::PROPERTY::ANGULAR_VELOCITY, 100);

    engine::rotatable_adapter rotate_adapter(ship);
    engine::rotate rotate_cmd(rotate_adapter);

    EXPECT_ANY_THROW(rotate_cmd.execute());
}

TEST(ROTATING, CANT_GET_DIRECTIONS_COUNT)
{
    engine::spaceship ship;
    ship.setProperty(engine::PROPERTY::DIRECTION, 900);
    // ship.setProperty(engine::PROPERTY::DIRECTIONS_COUNT, (std::uint32_t) 3600);
    ship.setProperty(engine::PROPERTY::ANGULAR_VELOCITY, 100);

    engine::rotatable_adapter rotate_adapter(ship);
    engine::rotate rotate_cmd(rotate_adapter);

    EXPECT_ANY_THROW(rotate_cmd.execute());
}



#endif //.#SPACEBATTLE_TESTS_H
