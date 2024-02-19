#ifndef MACRO_COMMANDS_TESTS_H
#define MACRO_COMMANDS_TESTS_H
// MACRO COMMANDS TESTS
#include <gtest/gtest.h>
#include <commands/burn_fuel.h>
#include <commands/change_velocity.h>
#include "adapters/fuelable_adapter.h"
#include <commands/macro_command.h>
#include "adapters/movable_adapter_with_course.h"
#include <commands/move_straight.h>
#include "adapters/rotatable_adapter.h"
#include <commands/check_fuel.h>

TEST(MACRO_COMMAND, CHEC_FUEL_CMD_NO_THROW)
{
    engine::uobject obj;
    obj.setProperty<float>(engine::PROPERTY::FUEL, 100);
    obj.setProperty<float>(engine::PROPERTY::FUEL_VELOCITY, 10);

    engine::fuelable_adapter adapter(obj);

    engine::check_fuel cmd(adapter);
    EXPECT_NO_THROW(cmd.execute());
}

TEST(MACRO_COMMAND, CHEC_FUEL_CMD_THROW_EXCEPTION)
{
    engine::uobject obj;
    obj.setProperty<float>(engine::PROPERTY::FUEL, 10);
    obj.setProperty<float>(engine::PROPERTY::FUEL_VELOCITY, 10);

    engine::fuelable_adapter adapter(obj);

    engine::check_fuel cmd(adapter);
    EXPECT_THROW(cmd.execute(), engine::check_fuel_exception);
}

TEST(MACRO_COMMAND, BURN_FUEL_CMD)
{
    engine::uobject obj;
    float f = 33.21;
    float f_v = 12.3;
    obj.setProperty<float>(engine::PROPERTY::FUEL, f);
    obj.setProperty<float>(engine::PROPERTY::FUEL_VELOCITY, f_v);

    engine::fuelable_adapter adapter(obj);
    engine::burn_fuel cmd(adapter);
    cmd.execute();

    EXPECT_FLOAT_EQ(obj.getProperty<float>(engine::PROPERTY::FUEL), f - f_v);
}

TEST(MACRO_COMMAND, MACRO_CMD_TEST_NO_THROW)
{
    engine::uobject obj;
    float f = 33.21;
    float f_v = 12.3;
    obj.setProperty<float>(engine::PROPERTY::FUEL, f);
    obj.setProperty<float>(engine::PROPERTY::FUEL_VELOCITY, f_v);

    engine::fuelable_adapter adapter(obj);

    engine::macro_command cmd(
        {std::make_shared<engine::check_fuel>(adapter), std::make_shared<engine::burn_fuel>(adapter)});

    EXPECT_NO_THROW(cmd.execute());
}

TEST(MACRO_COMMAND, MACRO_CMD_TEST_THROW_EXECEPT)
{
    engine::uobject obj;
    float f = 10;
    float f_v = 10;
    obj.setProperty<float>(engine::PROPERTY::FUEL, f);
    obj.setProperty<float>(engine::PROPERTY::FUEL_VELOCITY, f_v);

    engine::fuelable_adapter adapter(obj);

    {
        engine::macro_command cmd(
            {std::make_shared<engine::check_fuel>(adapter),
             std::make_shared<engine::burn_fuel>(adapter)});

        // исключение выбросится на выполнении первой команды
        EXPECT_THROW(cmd.execute(), engine::command_exception);
    }

    obj.setProperty<float>(engine::PROPERTY::FUEL, f);
    obj.setProperty<float>(engine::PROPERTY::FUEL_VELOCITY, f_v);
    {
        engine::macro_command cmd(
            {std::make_shared<engine::burn_fuel>(adapter),
             std::make_shared<engine::check_fuel>(adapter)});

        // исключение выбросится на выполнении второй команды
        EXPECT_THROW(cmd.execute(), engine::command_exception);
    }
}

TEST(MACRO_COMMAND, MOVE_STRAIGHT_CMD)
{
    engine::uobject obj;
    float f = 12.2;
    float f_v = 0.4;
    obj.setProperty<float>(engine::PROPERTY::FUEL, f);
    obj.setProperty<float>(engine::PROPERTY::FUEL_VELOCITY, f_v);

    auto init_pos = math::vectorInt2D(-20, 13);
    auto velocity = math::vectorInt2D(5, 0);
    obj.setProperty(engine::PROPERTY::POSITION, init_pos);
    obj.setProperty(engine::PROPERTY::VELOCITY_VECTOR, velocity);

    // obj.setProperty<int>(engine::PROPERTY::DIRECTIONS_COUNT, 3600);
    // obj.setProperty(engine::PROPERTY::VELOCITY_ABS, velocity.abs());
    // obj.setProperty(engine::PROPERTY::DIRECTION, velocity.discreteAngle(obj.getProperty<int>(engine::PROPERTY::DIRECTIONS_COUNT)));

    engine::fuelable_adapter f_adapter(obj);
    engine::movable_adapter m_adapter(obj);

    engine::move_straight cmd(m_adapter, f_adapter);

    EXPECT_NO_THROW(cmd.execute());
    EXPECT_FLOAT_EQ(obj.getProperty<float>(engine::PROPERTY::FUEL), f - f_v);
    EXPECT_EQ(obj.getProperty<math::vectorInt2D>(engine::PROPERTY::POSITION),
              init_pos + velocity);
}

TEST(MACRO_COMMAND, CHANGE_VELOCITY_CMD)
{
    engine::uobject obj;
    float f = 12.2;
    float f_v = 0.4;

    obj.setProperty<float>(engine::PROPERTY::FUEL, f);
    obj.setProperty<float>(engine::PROPERTY::FUEL_VELOCITY, f_v);

    auto init_pos = math::vectorInt2D(-20, 13);
    auto velocity = math::vectorInt2D(0, 0);

    obj.setProperty(engine::PROPERTY::POSITION,init_pos);

    obj.setProperty(engine::PROPERTY::VELOCITY_VECTOR, velocity);
    obj.setProperty<std::uint32_t>(engine::PROPERTY::DIRECTIONS_COUNT, 360);
    obj.setProperty<std::int32_t>(engine::PROPERTY::ANGULAR_VELOCITY, 100);
    obj.setProperty(engine::PROPERTY::VELOCITY_ABS, velocity.abs());
    obj.setProperty<std::int32_t>(engine::PROPERTY::DIRECTION,
                                  static_cast<std::int32_t>(velocity.discreteAngle(
                                                                obj.getProperty<std::uint32_t>(engine::PROPERTY::DIRECTIONS_COUNT)
                                                                                             )));
    auto init_angle = obj.getProperty<std::int32_t>(engine::PROPERTY::DIRECTION);


    engine::fuelable_adapter f_adapter(obj);
    engine::rotatable_adapter r_adapter(obj);

    engine::change_velocity cmd(r_adapter, f_adapter);

    EXPECT_NO_THROW(cmd.execute());
    EXPECT_FLOAT_EQ(obj.getProperty<float>(engine::PROPERTY::FUEL), f - f_v);

    EXPECT_EQ(obj.getProperty<std::int32_t>(engine::PROPERTY::DIRECTION),
              init_angle + obj.getProperty<std::int32_t>(engine::PROPERTY::ANGULAR_VELOCITY));

    engine::movable_adapter_with_cource m_adapter(obj);
    EXPECT_EQ(m_adapter.getVelocity(),
              math::vectorInt2D(std::round(velocity.abs() * std::cos(obj.getProperty<std::int32_t>(engine::PROPERTY::DIRECTION) * 2 * M_PI / 360.0)),
                                std::round(velocity.abs() * std::sin(obj.getProperty<std::int32_t>(engine::PROPERTY::DIRECTION) * 2 * M_PI / 360.0)))
        );
}

#endif //MACRO_COMMANDS_TESTS_H
