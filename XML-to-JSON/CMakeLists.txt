cmake_minimum_required(VERSION 3.19)
project(XML-to-JSON LANGUAGES CXX)

# Add Subdirectories for GUI and CLI applications
add_subdirectory(CLI)
add_subdirectory(GUI)


# Enable testing and include tests
add_subdirectory(tests)