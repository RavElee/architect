#include <macro_commands_tests.h>
#include <solid_exception_tests.h>
#include <spacebattle_tests.h>
#include <ioc_tests.h>
#include <autogen_tests.h>
#include "event_loop_tests.h"

int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
