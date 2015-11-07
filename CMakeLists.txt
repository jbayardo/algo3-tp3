cmake_minimum_required(VERSION 2.8)
project(algo3_tp3)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ggdb -std=c++11 -Wall -Wpedantic -Wextra -Wshadow -Wpointer-arith -Wcast-qual")

set(SOURCE_FILES src/main.cpp src/Problem.cpp src/Graph.cpp src/Coloring.cpp src/DGraph.cpp)
add_executable(algo3_tp3 ${SOURCE_FILES})