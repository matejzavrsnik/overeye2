# Set a default build type if none was specified
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
   message(STATUS "CMAKE_BUILD_TYPE not specified. Using Release.")
   
   set(CMAKE_BUILD_TYPE Release 
      CACHE STRING "Choose the type of build." FORCE)
  
   # Set the possible values of build type for cmake-gui, ccmake
   set_property(
      CACHE 
         CMAKE_BUILD_TYPE 
      PROPERTY STRINGS
         "Debug"
         "Release")
endif()
