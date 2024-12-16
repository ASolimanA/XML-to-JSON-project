cmake_minimum_required(VERSION 3.19)
project(XML-to-JSON LANGUAGES CXX)

# Add common backend files
set(COMMON_SOURCES
    common/convert.cpp
    common/prettierfunc.cpp
    common/Tree.cpp
    common/validation.cpp
    common/adapter.cpp
)
set(COMMON_HEADERS
    common/Tree.h
    common/validation.h
    common/adapter.h
)


# Add Subdirectories for GUI and CLI applications
add_subdirectory(CLI)
add_subdirectory(GUI)