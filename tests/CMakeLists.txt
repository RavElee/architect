cmake_minimum_required(VERSION 3.1)

project(tests_architect CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -Wextra -Wpedantic -Woverloaded-virtual  -fno-common -Wnon-virtual-dtor -Wdelete-non-virtual-dtor")

enable_testing()
find_package(GTest CONFIG REQUIRED)
include(GoogleTest)

add_executable(${PROJECT_NAME} test.cxx )

target_link_libraries(${PROJECT_NAME} gtest gtest_main quadratic_equation)
gtest_discover_tests(${PROJECT_NAME})

# auto start tests while building (chec - fake target)
add_custom_target(check ALL COMMAND ${PROJECT_NAME})

#install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_CURRENT_SOURCE_DIR})

