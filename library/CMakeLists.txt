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

# I had trouble importing conan packages for SDL2, QT, and SFML because they
# required libgl1-mesa-dev package to be installed, which isn't a package on
# my openSUSE 15.1 so I was unable to install it. Instead I installed these
# as system packages rather than conan packages and linked to library this way.
if(BUILDING_ON_OPENSUSE)
   target_link_libraries(library
      PRIVATE QT5::Widgets # installed on the system
   )
else()
   target_link_libraries(library 
      PRIVATE CONAN_PKG::qt # defined in root CMakeLists.txt
   )
endif()
