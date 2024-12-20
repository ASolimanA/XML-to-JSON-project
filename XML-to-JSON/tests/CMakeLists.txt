cmake_minimum_required(VERSION 3.19)

enable_testing()
include(CTest)


# Add Google Test
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/googletest)



set(COMMON_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/../common/Tree.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../common/validation.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../common/compress.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../common/convert.cpp
)

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


# Include common backend files
target_include_directories(UnitTests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../common)

# Link Google Test libraries
target_link_libraries(UnitTests
    gtest_main
)

# Add tests to CTest
add_test(NAME UnitTests COMMAND UnitTests)

set_target_properties(UnitTests PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../build/tests"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../build/tests"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../build/tests"
)


# Copy sample.xml to the build directory
add_custom_command(TARGET UnitTests POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${CMAKE_CURRENT_SOURCE_DIR}/sample.xml
    ${CMAKE_BINARY_DIR}/tests/sample.xml)

