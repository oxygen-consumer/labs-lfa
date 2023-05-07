cmake_minimum_required(VERSION 3.24)
project(Lab2)

set(CMAKE_CXX_STANDARD 20)

add_executable(Lab2 main.cpp src/Automat/Automat.hpp src/NFA/NFA.cpp src/NFA/NFA.hpp src/DFA/DFA.cpp src/DFA/DFA.hpp src/Automat/Automat.cpp)
