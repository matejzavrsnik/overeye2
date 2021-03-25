cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(library
   VERSION 0.0.1
   DESCRIPTION "overeye library"
   LANGUAGES CXX
)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets WebEngineWidgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS WebEngineWidgets REQUIRED)

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
   src/gauge/general.cpp src/gauge/general.h
   src/gauge/twitter.cpp src/gauge/twitter.h
   # QT dialogs
   src/qt/dialog.cpp src/qt/dialog.h src/qt/dialog.ui
   src/qt/gauge.cpp src/qt/gauge.h src/qt/gauge.ui
   src/gauge/manager.cpp src/gauge/manager.h src/gauge/configuration.h src/gauge/factory.cpp src/gauge/factory.h src/settings.h src/gauge/base.h src/gauge/base.cpp
   src/qt/gauge_config.cpp src/qt/gauge_config.h src/qt/gauge_config.ui src/gauge/information.h src/gauge/parameters.h src/gauge/parameters.cpp)

# The result
add_library(library ${SOURCES})

# set compiler warnings as defined in cmake/warnings and included in root CMakeLists.txt
set_project_warnings(library)

# make this folder visible to executable
target_include_directories(library PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Link this library to others
target_link_libraries(library
   PRIVATE Qt${QT_VERSION_MAJOR}::Widgets # installed on system
   PRIVATE Qt${QT_VERSION_MAJOR}::WebEngineWidgets # installed on system
   CONAN_PKG::sigslot # defined in root CMakeLists.txt
)
