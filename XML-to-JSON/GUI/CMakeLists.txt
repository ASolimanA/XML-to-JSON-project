cmake_minimum_required(VERSION 3.19)
project(GUIApp LANGUAGES CXX)

# Find the Qt6 package without specifying a version
find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

qt_add_executable(gui_app
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    ${COMMON_SOURCES}
)

target_link_libraries(gui_app
    PRIVATE
        Qt::Core
        Qt::Widgets
)

include(GNUInstallDirs)

install(TARGETS gui_app
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET gui_app
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
