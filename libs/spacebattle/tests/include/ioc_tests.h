#ifndef IOC_TESTS_H
#define IOC_TESTS_H

#include <gtest/gtest.h>
// IOC TESTS
#include "commands/ioc_init.h"
#include "ioc.h"
#include <cstring>
#include <future>



TEST(IOC_TESTS, IOC_INIT)
{
    EXPECT_NO_THROW(std::make_shared<engine::ioc_init>()->execute());
}

TEST(IOC_TESTS, IOC_CREATE_NEW_SCOPE)
{
    using namespace engine;
    std::make_shared<engine::ioc_init>()->execute();
    auto globalParent = ioc::resolve<ioc::scope>("IoC.Scope.Current");

    auto scope1 = ioc::resolve<ioc::scope, ioc::scope_ptr>("IoC.Scope.Create", nullptr);
    auto scope2 = ioc::resolve<ioc::scope, ioc::scope_ptr>("IoC.Scope.Create", scope1);
    ioc::resolve<command>("IoC.Scope.Current.Set", scope2)->execute();
    auto parentScope = ioc::resolve<ioc::scope>("IoC.Scope.Parent");
    EXPECT_EQ(scope1, parentScope);

    ioc::resolve<command>("IoC.Scope.Current.Set", globalParent)->execute();
    ioc::resolve<command>("IoC.Scope.Current.Clear", scope2)->execute();
    ioc::resolve<command>("IoC.Scope.Current.Clear", scope1)->execute();


    EXPECT_EQ(ioc::resolve<ioc::scope>("IoC.Scope.Current"), globalParent);
}

TEST(IOC_TESTS, IOC_REGISTER)
{
    std::make_shared<engine::ioc_init>()->execute();
    using namespace engine;

    // RAII scope
    engine::ioc::scoped_ioc si;

    std::shared_ptr<uobject> obj2 = std::make_shared<uobject>();
    auto cmd = ioc::resolve<command, std::string_view, std::any>("IoC.Register", "object#1",
                                                                 (ioc::strategy<uobject>)
                                                                 [obj2](){return obj2;});
    EXPECT_NO_THROW(cmd->execute());
}

TEST(IOC_TESTS, IOC_REGISTER_AND_RESOLVE)
{
    using namespace engine;
    std::make_shared<engine::ioc_init>()->execute();

    ioc::scoped_ioc si;
    {
        std::shared_ptr<uobject> obj_set = std::make_shared<uobject>();
        obj_set->setProperty(PROPERTY::VELOCITY_ABS, (int) 100);

        ioc::resolve<command, std::string_view, std::any>(
            "IoC.Register", "object#1", (ioc::strategy<uobject>) [obj_set]() { return obj_set; })->execute();
    }

    auto obj_get = ioc::resolve<uobject>("object#1");
    EXPECT_TRUE(obj_get->size() != 0);
    EXPECT_EQ(obj_get->getProperty<int>(PROPERTY::VELOCITY_ABS), 100);
}

TEST(IOC_TESTS, IOC_MULTITHREADING)
{
    using namespace engine;
    std::make_shared<engine::ioc_init>()->execute();
    ioc::scoped_ioc si;

    auto thr1 = [](){
        // current == root scope
        return ioc::resolve<ioc::scope>("IoC.Scope.Current");
    };

    auto thr1ScopeId = std::async(thr1);
    auto current = ioc::resolve<ioc::scope>("IoC.Scope.Current");
    auto scopeFromThread = thr1ScopeId.get();

    EXPECT_NE(scopeFromThread, current);
    EXPECT_EQ(scopeFromThread, ioc::resolve<ioc::scope>("IoC.Scope.Parent"));
}

#endif //IOC_TESTS_H
