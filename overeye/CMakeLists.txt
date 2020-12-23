cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(executable
   VERSION 0.0.1
   DESCRIPTION "overeye"
   LANGUAGES CXX
)

# Add these files to this binary
file(GLOB HeaderFiles *.h)
file(GLOB SourceFiles *.cpp)

set(SOURCES ${HeaderFiles} ${SourceFiles})

# The result
add_executable(overeye ${SOURCES})

# set compiler warnings as defined in cmake/warnings and included in root CMakeLists.txt
set_project_warnings(overeye)

# Link with libraries
target_link_libraries(overeye
   PRIVATE library # exists in this solution, imported in CMakeLists.txt
)
