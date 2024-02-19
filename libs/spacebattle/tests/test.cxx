#include <solid_exception_tests.h>
#include <spacebattle_tests.h>
#include <macro_commands_tests.h>

// IOC TESTS
#include "ioc.h"
#include "commands/ioc_init.h"

TEST(IOC_TESTS, IOC_INIT)
{
    std::make_shared<engine::ioc_init>()->execute();
    using namespace engine;

    // TODO: переместить мапины в команду Init
    auto scope = ioc::resolve<ioc::scope>("IoC.Scope.Current");
    auto scope3 = ioc::resolve<ioc::scope>("IoC.Scope.Create", scope);
    ioc::resolve<command>("IoC.Scope.Current.Set", scope3)->execute();

    std::cout << scope << "; "<< ioc::resolve<ioc::scope>("IoC.Scope.Current") << std::endl;
    std::cout << scope << "; "<< ioc::resolve<ioc::scope>("IoC.Scope.Parent") << std::endl;

    // auto scope = engine::ioc::resolve<engine::ioc::scope>("IoC.Scope.Current");
    // EXPECT_EQ(scope,nullptr);
}

int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
