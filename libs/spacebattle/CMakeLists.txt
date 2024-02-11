cmake_minimum_required(VERSION 3.1)


project(spacebattle CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -Wextra -Wpedantic -Woverloaded-virtual  -fno-common -Wnon-virtual-dtor -Wdelete-non-virtual-dtor")

set(HEADERS
    ./include/command.h
    ./include/movable.h
    ./include/move.h
    ./include/direction.h
    ./include/movable_adapter.h
    ./include/rotatable.h
    ./include/rotate.h
    ./include/spaceship.h
    ./include/vector.h
    ./include/uobject.h
    ./include/rotatable_adapter.h
    ./include/threadsafe_q.h
    ./include/loop.h
    ./include/exception_handler.h
    ./include/log_command.h
    ./include/empty_command.h
    ./include/empty_exception.h
    ./include/repeat_command.h
    ./include/repeat_twice_command.h
)

set(SOURCES
    ./src/move.cpp
    ./src/direction.cpp
    ./src/movable_adapter.cpp
    ./src/rotate.cpp
    ./src/spaceship.cpp
    ./src/rotatable_adapter.cpp 
    ./src/loop.cpp
    ./src/exception_handler.cpp
)

add_library(${PROJECT_NAME} STATIC ${HEADERS} ${SOURCES})

target_include_directories(${PROJECT_NAME} 
PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include 			
PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

include("unittests.cmake")
