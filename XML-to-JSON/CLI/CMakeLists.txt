cmake_minimum_required(VERSION 3.19)
project(CLIApp)



# Add common backend files
set(COMMON_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/../common/Tree.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../common/validation.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../common/compress.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../common/convert.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../common/graph.cpp
)

add_executable(cli_app
    main.cpp
    ${COMMON_SOURCES}
)

# Include common backend files
target_include_directories(cli_app PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../common)

set_target_properties(cli_app PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../build/CLI"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../build/CLI"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../build/CLI"
)