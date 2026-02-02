cmake_minimum_required(VERSION 4.0)
project(computer_club)

set(CMAKE_CXX_STANDARD 20)

add_executable(computer_club src/main.cpp
        src/time.cpp
        src/time.hpp)
