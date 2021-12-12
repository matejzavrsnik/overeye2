cmake_minimum_required (VERSION 3.10)

set (CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_STANDARD_REQUIRED True)

project (library
   VERSION 0.0.1
   DESCRIPTION "overeye library"
   LANGUAGES CXX
   )

find_package (QT NAMES Qt6 Qt5 COMPONENTS Widgets WebEngineWidgets REQUIRED)
find_package (Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)
find_package (Qt${QT_VERSION_MAJOR} COMPONENTS WebEngineWidgets REQUIRED)

# Turn on automatic invocation of the MOC, UIC & RCC
set (CMAKE_AUTOMOC ON)
set (CMAKE_AUTOUIC ON)
set (CMAKE_AUTORCC ON)

# Add these files to this binary
set (SOURCES

   src/logic/load_save_settings.cpp
   src/overeye.cpp
   #../3rdparty/mzlib/include/tools/metronome.h

   #src/gauge/configuration.h
   #src/gauge/basic_setting.h
   src/gauge/extended_setting.h
   src/gauge/extended_setting.cpp
   #src/gauge/i_gauge.h
   #src/logic/representation.h
   #src/gauge/location.h
   src/gauge/parameters.cpp
   #src/gauge/parameters.h
   src/gauge/webport.cpp
   #src/gauge/webport.h
   src/gauge/twitter.cpp
   #src/gauge/twitter.h
   src/gauge/clock.cpp
   #src/gauge/clock.h
   src/logic/manager.cpp
   #src/logic/manager.h
   src/gauge/factory.cpp
   #src/gauge/factory.h

   # QT dialogs
   src/gui/screen.ui src/gui/screen.cpp src/gui/screen.h
   src/gui/webport.ui src/gui/webport.cpp src/gui/webport.h
   src/gui/gauge_config.ui src/gui/gauge_config.cpp src/gui/gauge_config.h
   src/gui/custom_event_types.h
   src/utils/json.cpp src/utils/json.h)

# The result
add_library (library ${SOURCES})

# set_or_add compiler warnings as defined in cmake/warnings and included in root CMakeLists.txt
set_project_warnings (library)

# make this folder visible to executable
target_include_directories (library PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Link this library to others
target_link_libraries (library
   PRIVATE Qt${QT_VERSION_MAJOR}::Widgets # installed on system
   PRIVATE Qt${QT_VERSION_MAJOR}::WebEngineWidgets # installed on system
   CONAN_PKG::sigslot # defined in root CMakeLists.txt
   )
