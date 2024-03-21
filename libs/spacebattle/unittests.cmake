cmake_minimum_required(VERSION 3.1)

enable_testing()
find_package(GTest CONFIG REQUIRED)
include(GoogleTest)

set(HEADERS
   ./tests/include/spacebattle_tests.h
   ./tests/include/mock.h
   ./tests/include/macro_commands_tests.h
   ./tests/include/solid_exception_tests.h
   ./tests/include/ioc_tests.h
   ./tests/include/autogen_tests.h
   ./tests/include/manual_reset_event.h
   ./tests/include/event_loop_tests.h
)
set(SOURCES
)

add_executable(${PROJECT_NAME}_tests tests/test.cxx ${HEADERS} ${SOURCES})

target_link_libraries(${PROJECT_NAME}_tests ${PROJECT_NAME} gtest gtest_main gmock)

target_include_directories(${PROJECT_NAME}_tests
            PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/tests/include 			
            PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/tests/include)

gtest_discover_tests(${PROJECT_NAME}_tests)

add_custom_target(${PROJECT_NAME}_check ALL COMMAND ${PROJECT_NAME}_tests)

