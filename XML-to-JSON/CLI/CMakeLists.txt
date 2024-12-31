cmake_minimum_required(VERSION 3.19)
project(CLIApp)



# Add common backend files
set(COMMON_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/../common/Tree.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../common/validation.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../common/compress-decompress.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../common/graph.cpp
)

add_executable(xml_editor
    main.cpp
    ${COMMON_SOURCES}
)

# Include common backend files
target_include_directories(xml_editor PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../common)

set_target_properties(xml_editor PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/cmake-build-debug/build/CLI"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/cmake-build-debug/build/CLI"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/cmake-build-debug/build/CLI"
)


set(CMAKE_BUILD_TYPE "Release")

include(InstallRequiredSystemLibraries)
set(CPACK_PACKAGE_NAME "CLIApp-Release")
set(CPACK_GENERATOR "ZIP")
install(CODE "execute_process(COMMAND windeployqt \"\$<TARGET_FILE:xml_editor>\" --release)")
include(CPack)