cmake_minimum_required(VERSION 2.8)
project(algo3_tp3)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DEXPS -DPODAS -ggdb -O2 -std=c++11 -Wall -Wpedantic -Wextra -Wshadow -Wpointer-arith -Wcast-qual")

set(SOURCE_FILES src/main.cpp src/Problem.cpp src/Problem1.cpp src/Problem2.cpp src/Problem3.cpp src/Problem4.cpp src/Problem1.h)
add_executable(algo3_tp3 ${SOURCE_FILES})
