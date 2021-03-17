cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(library
   VERSION 0.0.1
   DESCRIPTION "overeye library"
   LANGUAGES CXX
)

find_package(Qt5 COMPONENTS Widgets)

# Turn on automatic invocation of the MOC, UIC & RCC
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Add these files to this binary
set(SOURCES
   # externally visible
   src/implementation.cpp ./include/library/header.h
   # internally visible
   ./src/internal.cpp ./src/internal.h
   # QT dialogs
   ./src/dialog.cpp ./src/dialog.h ./src/dialog.ui)

# The result
add_library(library ${SOURCES})

# set compiler warnings as defined in cmake/warnings and included in root CMakeLists.txt
set_project_warnings(library)

# make this folder visible to executable
target_include_directories(library PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Link this library to others
target_link_libraries(library
   PRIVATE CONAN_PKG::qt # defined in root CMakeLists.txt
)
