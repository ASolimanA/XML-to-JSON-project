cmake_minimum_required(VERSION 3.19)
project(GUIApp LANGUAGES CXX)

# Find the Qt6 package without specifying a version
find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

# Add common backend files
set(COMMON_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/../common/Tree.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../common/validation.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../common/compress.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../common/convert.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../common/graph.cpp
)



qt_add_executable(gui_app
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    adapter.cpp
    adapter.h
    ${COMMON_SOURCES}
)

target_link_libraries(gui_app
    PRIVATE
        Qt::Core
        Qt::Widgets
)
# Include common backend files
target_include_directories(gui_app PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../common)

include(GNUInstallDirs)

install(TARGETS gui_app
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

set_target_properties(gui_app PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../build/GUI"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../build/GUI"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../build/GUI"
)

qt_generate_deploy_app_script(
    TARGET gui_app
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
