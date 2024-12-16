cmake_minimum_required(VERSION 3.19)

# Include Google Test using FetchContent
include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/release-1.13.0.tar.gz
)

# Prevent building Google Test's own tests
set(gtest_build_tests OFF CACHE BOOL "" FORCE)
set(gmock_build_tests OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

# Add your tests
add_executable(UnitTests 
    test_compress.cpp
    test_adapter.cpp
    test_validation.cpp
    test_Tree.cpp
    test_convert.cpp
    test_prettierfunc.cpp
)

# Link Google Test libraries
target_link_libraries(UnitTests gtest gtest_main)

# Add tests to CTest
add_test(NAME UnitTests COMMAND UnitTests)

# Include common backend files
target_include_directories(cli_app PRIVATE ${CMAKE_SOURCE_DIR}/common)