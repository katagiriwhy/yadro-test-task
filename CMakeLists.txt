cmake_minimum_required(VERSION 4.0)
project(computer_club)

set(CMAKE_CXX_STANDARD 20)

add_executable(computer_club src/main.cpp)

target_sources(computer_club
        PRIVATE
        src/time/time.cpp
        src/scope_guard/scope_guard.cpp
        src/club/club.cpp
        src/event_handler/event_handler.cpp
)

target_include_directories(computer_club
        PRIVATE src
)