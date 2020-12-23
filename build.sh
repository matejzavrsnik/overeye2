#!/bin/bash

create_directory () 
{
   if [ ! -d $1 ]
   then
      mkdir $1
   fi     
}

if [ $# -ge 1 ]
then

   if [ $1 == "clean" ]
   then
      if [ -e ./build/release/Makefile ]
      then
         cd ./build/release
         make clean
         cd -
      fi
      if [ -e ./build/debug/Makefile ]
      then
         cd ./build/debug
         make clean
         cd -
      fi
      rm -rf ./build
   fi

   if [ $1 == "debug" ] || [ $1 == "release" ] || [ $1 == "all" ]
   then
      if [ -e ./.gitmodules ]
      then
         git submodule update --init --recursive
      fi
   fi
   
   if [ $1 == "debug" ] || [ $1 == "all" ]
   then
      create_directory ./build
      create_directory ./build/debug
      cd ./build/debug
      cmake ../.. -DCMAKE_BUILD_TYPE=debug
      make
      cd -
   fi
   
   if [ $1 == "release" ] || [ $1 == "all" ]
   then
      create_directory ./build
      create_directory ./build/release
      cd ./build/release
      cmake ../.. -DCMAKE_BUILD_TYPE=release
      make
      cd -
   fi

else
   echo "Usage: build.sh [clean|release|debug|all]"
   exit 1
fi
