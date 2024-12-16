cmake_minimum_required(VERSION 3.19)
project(XML-to-JSON LANGUAGES CXX)


# Add common backend files
set(COMMON_SOURCES
    ${CMAKE_SOURCE_DIR}/common/convert.cpp
    ${CMAKE_SOURCE_DIR}/common/prettierfunc.cpp
    ${CMAKE_SOURCE_DIR}/common/Tree.cpp
    ${CMAKE_SOURCE_DIR}/common/validation.cpp
    ${CMAKE_SOURCE_DIR}/common/adapter.cpp
    ${CMAKE_SOURCE_DIR}/common/compress.cpp
)
set(COMMON_HEADERS
    ${CMAKE_SOURCE_DIR}/common/Tree.h
    ${CMAKE_SOURCE_DIR}/common/validation.h
    ${CMAKE_SOURCE_DIR}/common/adapter.h
)


# Add Subdirectories for GUI and CLI applications
add_subdirectory(CLI)
add_subdirectory(GUI)


# Enable testing and include tests
# enable_testing()
# add_subdirectory(tests)