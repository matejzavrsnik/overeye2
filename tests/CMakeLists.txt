cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(library_tests
   VERSION 0.0.1
   DESCRIPTION "library_tests description"
   LANGUAGES CXX
)

# Add these files to this binary
file(GLOB HeaderFiles *.h)
file(GLOB SourceFiles *.cpp)

set(SOURCES ${HeaderFiles} ${SourceFiles})

# The result
add_executable(tests ${SOURCES})

# Set compiler warnings as defined in cmake/warnings
set_project_warnings(tests)

# Link with libraries
target_link_libraries(tests 
   library # exists in this solution, imported in CMakeLists.txt
   CONAN_PKG::gtest # defined in root CMakeLists.txt
) 
