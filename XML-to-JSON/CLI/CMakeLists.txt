cmake_minimum_required(VERSION 3.19)
project(CLIApp)

# Add common backend files
set(COMMON_SOURCES
    ${CMAKE_SOURCE_DIR}/../common/convert.cpp
    ${CMAKE_SOURCE_DIR}/../common/Tree.cpp
    ${CMAKE_SOURCE_DIR}/../common/validation.cpp
    ${CMAKE_SOURCE_DIR}/../common/compress.cpp
)
set(COMMON_HEADERS
    ${CMAKE_SOURCE_DIR}/../common/Tree.h
    ${CMAKE_SOURCE_DIR}/../common/validation.h
)

add_executable(cli_app
    main.cpp
    ${COMMON_SOURCES}
    ${COMMON_HEADERS}
)

# Include common backend files
target_include_directories(cli_app PRIVATE ${CMAKE_SOURCE_DIR}/../common)