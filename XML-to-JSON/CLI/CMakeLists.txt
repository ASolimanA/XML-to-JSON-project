cmake_minimum_required(VERSION 3.19)
project(CLIApp)

add_executable(cli_app
    WIN32 MACOSX_BUNDLE
    main.cpp
    ${COMMON_SOURCES}    
)

# Include common backend files
target_include_directories(cli_app PRIVATE ${CMAKE_SOURCE_DIR}/common)