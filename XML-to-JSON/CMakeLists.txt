#cmake_minimum_required(VERSION 3.19)
#project(XML-to-JSON LANGUAGES CXX)
#
#find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)
#
#qt_standard_project_setup()
#
#qt_add_executable(XML-to-JSON
#    WIN32 MACOSX_BUNDLE
#    src/Frontend/main.cpp
#    src/Frontend/mainwindow.cpp
#    src/Frontend/mainwindow.h
#    src/Frontend/mainwindow.ui
#    src/Backend/convert.cpp
#    src/Backend/prettierfunc.cpp
#    src/Backend/Tree.cpp
#    src/Backend/Tree.h
#    src/Backend/validation.cpp
#    src/Backend/validation.h
#)
#
#target_link_libraries(XML-to-JSON
#    PRIVATE
#        Qt::Core
#        Qt::Widgets
#)
#
#include(GNUInstallDirs)
#
#install(TARGETS XML-to-JSON
#    BUNDLE  DESTINATION .
#    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
#    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#)
#
#qt_generate_deploy_app_script(
#    TARGET XML-to-JSON
#    OUTPUT_SCRIPT deploy_script
#    NO_UNSUPPORTED_PLATFORM_ERROR
#)
#install(SCRIPT ${deploy_script})
cmake_minimum_required(VERSION 3.19)
project(XML-to-JSON LANGUAGES CXX)

add_executable(XML-to-JSON
        src/Backend/main.cpp
#    src/Frontend/mainwindow.cpp
#    src/Frontend/mainwindow.h
#    src/Frontend/mainwindow.ui
    src/Backend/convert.cpp
    src/Backend/prettierfunc.cpp
    src/Backend/Tree.cpp
    src/Backend/Tree.h
    src/Backend/validation.cpp
    src/Backend/validation.h
)

include(GNUInstallDirs)

install(TARGETS XML-to-JSON
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)