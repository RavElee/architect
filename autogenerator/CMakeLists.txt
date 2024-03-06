cmake_minimum_required(VERSION 3.1)

project(autogenerator CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -Wextra -Wpedantic -Woverloaded-virtual  -fno-common -Wnon-virtual-dtor -Wdelete-non-virtual-dtor")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT CMAKE_CXX_EXTENSIONS)
    set(CMAKE_CXX_EXTENSIONS OFF)
endif()

set(CMAKE_CXX_CPPCHECK "cppcheck")
find_program(CMAKE_CXX_CPPCHECK NAMES cppcheck)
if (CMAKE_CXX_CPPCHECK)
    list(
        APPEND CMAKE_CXX_CPPCHECK
#        "--enable=all"
        "--enable=warning"
		"--inconclusive"
		"--force"
		"--inline-suppr"
		"--quiet"
    )
endif()


set(HEADERS
    ./include/iautogen.h
)

set(SOURCES
)

add_executable(${PROJECT_NAME} main.cpp ${HEADERS} ${SOURCES})

target_include_directories(${PROJECT_NAME} 
PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include 			
PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

#include("unittests.cmake")

