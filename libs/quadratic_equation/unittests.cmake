cmake_minimum_required(VERSION 3.1)

enable_testing()
find_package(GTest CONFIG REQUIRED)
include(GoogleTest)


add_executable(${PROJECT_NAME}_tests tests/test.cxx )

target_link_libraries(${PROJECT_NAME}_tests gtest gtest_main ${PROJECT_NAME})
gtest_discover_tests(${PROJECT_NAME}_tests)

add_custom_target(check ALL COMMAND ${PROJECT_NAME}_tests)

