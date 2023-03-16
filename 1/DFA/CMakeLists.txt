cmake_minimum_required(VERSION 3.24)
project(DFA)

set(CMAKE_CXX_STANDARD 20)

add_executable(DFA main.cpp dfa/DFA.cpp dfa/DFA.hpp)
