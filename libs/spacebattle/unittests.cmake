cmake_minimum_required(VERSION 3.1)

enable_testing()
find_package(GTest CONFIG REQUIRED)
include(GoogleTest)

set(HEADERS
    ./tests/include/spacebattle_tests.h
)
set(SOURCES
)

add_executable(${PROJECT_NAME}_tests tests/test.cxx ${HEADERS} ${SOURCES})

target_link_libraries(${PROJECT_NAME}_tests gtest gtest_main ${PROJECT_NAME})
gtest_discover_tests(${PROJECT_NAME}_tests)

add_custom_target(${PROJECT_NAME}_check ALL COMMAND ${PROJECT_NAME}_tests)

