cmake_minimum_required(VERSION 3.16)
project(RubiksKBSolver LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -march=native -Wall -Wextra")

include_directories(include)

add_executable(solver 
    src/main.cpp 
    src/graph_engine.cpp 
    src/automaton_compiler.cpp
    src/solver.cpp
    src/cli.cpp
)