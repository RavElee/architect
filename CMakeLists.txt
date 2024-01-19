cmake_minimum_required(VERSION 3.1)

#set(CMAKE_CXX_COMPILER "/usr/bin/g++-12")
#set(CMAKE_C_COMPILER "/usr/bin/gcc-12")

project(architect CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -Wextra -Wpedantic -Woverloaded-virtual  -fno-common -Wnon-virtual-dtor -Wdelete-non-virtual-dtor")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


enable_testing()
find_package(GTest CONFIG REQUIRED)
include(GoogleTest)

add_executable(${PROJECT_NAME} main.cpp )

target_link_libraries(${PROJECT_NAME} gtest gtest_main)
gtest_discover_tests(${PROJECT_NAME})

install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_CURRENT_SOURCE_DIR})


