cmake_minimum_required(VERSION 3.19)

include(CTest)


# Add Google Test
add_subdirectory(${CMAKE_SOURCE_DIR}/tests/googletest)

# Add your tests
add_executable(UnitTests 
    # test_compress.cpp
    # test_adapter.cpp
    test_validation.cpp
    # test_Tree.cpp
    # test_convert.cpp
    # test_prettierfunc.cpp
    ${COMMON_SOURCES}
)

# Link Google Test libraries
target_link_libraries(UnitTests
    gtest_main
)

# Add tests to CTest
add_test(NAME UnitTests COMMAND UnitTests)

# Include common backend files
target_include_directories(UnitTests PRIVATE ${CMAKE_SOURCE_DIR}/common)

# Copy sample.xml to the build directory
add_custom_command(TARGET UnitTests POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${CMAKE_SOURCE_DIR}/tests/sample.xml
    ${CMAKE_BINARY_DIR}/tests/sample.xml)