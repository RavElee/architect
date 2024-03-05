#ifndef AUTOGEN_TESTS_H
#define AUTOGEN_TESTS_H

#include <gtest/gtest.h>
#include <commands/ioc_init.h>
#include <interfaces/movable.h>
#include <adapters/movable_adapter.h>
#include <uobject.h>

TEST(AUTOGEN_TESTS, REGISTER_ADAPTERS_CREATING_STRATEGY)
{
    std::make_shared<engine::ioc_init>()->execute();
    engine::ioc::scoped_ioc si;
    IOC_REGISTER(typeid(engine::movable).name(),
                 (engine::ioc::strategy<engine::movable, engine::shared_uobject>)
                 [](engine::shared_uobject obj)
                 {
                     return std::make_shared<engine::movable_adapter>(obj);
                 });

    engine::shared_uobject obj;
    auto adapter = engine::ioc::resolve<engine::movable>(typeid(engine::movable).name(), obj);
    EXPECT_NE(adapter, std::shared_ptr<engine::movable>(nullptr));
}

TEST(AUTOGEN_TESTS, USING_ADAPTER)
{
    std::make_shared<engine::ioc_init>()->execute();
    engine::ioc::scoped_ioc si;
    using namespace engine;
    IOC_REGISTER(typeid(engine::movable).name(),
                 (engine::ioc::strategy<engine::movable, engine::shared_uobject>)
                 [](engine::shared_uobject obj)
                 {
                     return std::make_shared<engine::movable_adapter>(obj);
                 });
    IOC_REGISTER("movable.getPosition",
                 (ioc::strategy<math::vector2D<std::int32_t>, shared_uobject>)
                 [](shared_uobject obj){
                     return std::make_shared<math::vector2D<std::int32_t>>(obj->getProperty<math::vector2D<std::int32_t>>(PROPERTY::POSITION));
                 });

    IOC_REGISTER("movable.getVelocity",
                 (ioc::strategy<math::vector2D<std::int32_t>, shared_uobject>)
                 [](shared_uobject obj){
                     return std::make_shared<math::vector2D<std::int32_t>>(obj->getProperty<math::vector2D<std::int32_t>>(PROPERTY::VELOCITY_VECTOR));
                 });

    IOC_REGISTER("movable.setPosition",
                 ((ioc::strategy<command, shared_uobject, math::vector2D<std::int32_t>>)
                  [](shared_uobject obj, math::vector2D<std::int32_t> var){
                     class cmd_set_pos: public command
                     {
                         shared_uobject obj;
                         math::vector2D<std::int32_t>& pos;
                     public:
                         cmd_set_pos(shared_uobject obj,
                                     math::vector2D<std::int32_t>& pos):
                             obj(obj),
                             pos(pos)
                         {}
                         void execute() override
                         {
                             obj->setProperty(PROPERTY::POSITION, pos);
                         }
                     };
                     return std::make_shared<cmd_set_pos>(obj, var);
                 }));

    auto obj = std::make_shared<uobject>();
    auto velocity = math::vectorInt2D(200, -10);
    obj->setProperty(engine::PROPERTY::VELOCITY_VECTOR, velocity);
    auto adapter = engine::ioc::resolve<engine::movable>(typeid(engine::movable).name(), obj);

    EXPECT_EQ(adapter->getVelocity(), velocity);
    auto init_pos = math::vectorInt2D(-20, 13);
    adapter->setPosition(init_pos);
    EXPECT_EQ(adapter->getPosition(), init_pos);
}

#endif //AUTOGEN_TESTS_H
