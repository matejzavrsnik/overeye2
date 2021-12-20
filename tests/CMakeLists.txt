cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(library_tests
   VERSION 0.0.1
   DESCRIPTION "library_tests description"
   LANGUAGES CXX
)

# Include cmake scripts
include(../cmake/configurations.cmake)
include(../cmake/warnings.cmake)
include(../cmake/conan.cmake)

find_package (QT NAMES Qt6 Qt5 COMPONENTS Widgets WebEngineWidgets REQUIRED)
find_package (Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)
find_package (Qt${QT_VERSION_MAJOR} COMPONENTS WebEngineWidgets REQUIRED)

# Add these files to this binary
file(GLOB HeaderFiles *.h)
file(GLOB SourceFiles *.cpp)

set(SOURCES
   main.cpp
   test_settings_serialisation.cpp
   test_settings_load.cpp testing_tools.cpp testing_tools.h)

# The result
add_executable(tests ${SOURCES})

# Set compiler warnings as defined in cmake/warnings
set_project_warnings(tests)

# Link with libraries
target_link_libraries(tests
   PRIVATE Qt${QT_VERSION_MAJOR}::Widgets # installed on system
   PRIVATE Qt${QT_VERSION_MAJOR}::WebEngineWidgets # installed on system
   library # exists in this solution, imported in CMakeLists.txt
   CONAN_PKG::gtest # defined in root CMakeLists.txt
) 
