cmake_minimum_required(VERSION 3.1)


project(quadratic_equation CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -Wextra -Wpedantic -Woverloaded-virtual  -fno-common -Wnon-virtual-dtor -Wdelete-non-virtual-dtor")

set(HEADERS
    ./include/quadratic_solver.h
)

set(SOURCES
    ./src/quadratic_solver.cpp
)

add_library(${PROJECT_NAME} STATIC ${HEADERS} ${SOURCES})

target_include_directories(${PROJECT_NAME} 
					PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include 			
				   PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

#install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_CURRENT_SOURCE_DIR})


