cmake_minimum_required(VERSION 3.20 FATAL_ERROR)
project(computer_club)

include( ${PROJECT_SOURCE_DIR}/src/src.cmake )

set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME})

target_sources( ${PROJECT_NAME}
        PRIVATE
        ${PROJECT_SOURCE_DIR}/src/main.cpp
        ${${PROJECT_NAME}-sources}
)

target_include_directories( ${PROJECT_NAME}
        PRIVATE
        ${${PROJECT_NAME}-includes}
)

target_link_libraries( ${PROJECT_NAME}
        PRIVATE
        ${${PROJECT_NAME}-libraries}
)
