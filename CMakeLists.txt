cmake_minimum_required(VERSION 3.1)


project(architect CXX)
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


add_subdirectory(tests)
add_subdirectory(libs)

add_executable(${PROJECT_NAME} main.cpp )

target_link_libraries(${PROJECT_NAME} quadratic_equation)                   

#install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_CURRENT_SOURCE_DIR})


