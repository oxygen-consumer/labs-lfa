cmake_minimum_required(VERSION 3.24)
project(NFA)

set(CMAKE_CXX_STANDARD 20)

add_executable(NFA main.cpp nfa/NFA.cpp nfa/NFA.hpp)
