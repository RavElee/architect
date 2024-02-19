cmake_minimum_required(VERSION 3.1)


project(spacebattle CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -Wextra -Wpedantic -Woverloaded-virtual  -fno-common -Wnon-virtual-dtor -Wdelete-non-virtual-dtor")

set(HEADERS
    ./include/commands/command.h
    ./include/interfaces/movable.h
    ./include/commands/move.h
    ./include/direction.h
    ./include/adapters/movable_adapter.h
    ./include/interfaces/rotatable.h
    ./include/commands/rotate.h
    ./include/spaceship.h
    ./include/vector.h
    ./include/uobject.h
    ./include/adapters/rotatable_adapter.h
    ./include/threadsafe_q.h
    ./include/loop.h
    ./include/exception_handler.h
    ./include/commands/log_command.h
    ./include/commands/empty_command.h
    ./include/exceptions/empty_exception.h
    ./include/commands/repeat_command.h
    ./include/commands/repeat_twice_command.h
    ./include/commands/burn_fuel.h
    ./include/commands/check_fuel.h
    ./include/exceptions/check_fuel_exception.h
    ./include/interfaces/fuelable.h
    ./include/adapters/fuelable_adapter.h
    ./include/commands/macro_command.h
    ./include/adapters/movable_adapter_with_course.h
    ./include/commands/change_velocity.h
    ./include/ioc.h
    ./include/commands/ioc_init.h
)

set(SOURCES
    ./src/commands/move.cpp
    ./src/direction.cpp
    ./src/adapters/movable_adapter.cpp
    ./src/commands/rotate.cpp
    ./src/commands/log_command.cpp
    ./src/spaceship.cpp
    ./src/adapters/rotatable_adapter.cpp 
    ./src/loop.cpp
    ./src/exception_handler.cpp
)

add_library(${PROJECT_NAME} STATIC ${HEADERS} ${SOURCES})

target_include_directories(${PROJECT_NAME} 
PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include 			
PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

include("unittests.cmake")
