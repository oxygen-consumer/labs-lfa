cmake_minimum_required(VERSION 3.24)
project(E_NFA)

set(CMAKE_CXX_STANDARD 20)

add_executable(E_NFA main.cpp e-nfa/E_NFA.cpp e-nfa/E_NFA.hpp)
