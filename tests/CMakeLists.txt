cmake_minimum_required(VERSION 4.2 FATAL_ERROR)

include(FetchContent)
include( ${PROJECT_SOURCE_DIR}/../src/src.cmake )

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        v1.17.0
)

FetchContent_MakeAvailable(googletest)

add_executable(${PROJECT_NAME}_tests
        test_time.cpp
        test_events.cpp
)

target_sources( ${PROJECT_NAME}_tests
        PRIVATE
        ${${PROJECT_NAME}-sources}
)

target_include_directories( ${PROJECT_NAME}_tests
        PRIVATE
        ${${PROJECT_NAME}-includes}
)

target_compile_definitions(${PROJECT_NAME}_tests
        PRIVATE TEST_DATA_DIR="${CMAKE_CURRENT_SOURCE_DIR}/input"
)

target_link_libraries(${PROJECT_NAME}_tests
        PRIVATE
        GTest::gtest
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}_tests)