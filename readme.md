 
# git help

## adding submodule

git submodule add [git repo] 3rdparty/[folder]

## check in changes in 3rdparty

1) cd 3rdparty/mzlib
2) git pull origin HEAD:master -> get latest version from gitgub
2) git add
3) git commit
4) git push origin HEAD:master
5) git checkout origin/master -> update to latest revision
6) cd ../..
7) git add
8) git commit
9) git pull in original folder so that I don't need to merge later

## check out the project

1) git clone <repository name> --recursive

or

1) gut pull
2) git submodule update --init --recursive

## update one submodule

git submodule update --remote ./3rdparty/mzlib/

# Building

## Ubuntu

1) sudo apt install cmake git build-essential python3-pip ???
2) sudo pip install conan
3) restart ubuntu or add ~/.local/bin to path yourself
4) git clone --recursive https://github.com/matejzavrsnik/overeye.git
5) ./build.sh all

# Conventions

## Documentation

Doxygen. Below is an example to be used.

Reason to document is to get as much help in the tooltip as possible.

I like comments on arguments inline because it makes it harder to inadvertently diverge the two.

Didn't find a good way to document templated stuff, so using HTML less-then tag for now.

    /**
     * @brief Brief
     * @details Details
     * @tparam Template parameter
     * @example
     * \code{.cpp}
     * std::vector &lt; std::string> var;
     * fun(var);
     * \endcode
     * @return Return
     */
    int fun(
       std::string& str, /**< [in/out] Str */
       int size /**< [in] Size */ 
    )
    {} 

## Folder structure

- overeye - a wrapper that compiles code into executable
- library - most of the code. It's in form of a library so that tests can be written.
  - include - header files meant to be included in executable
  - src - sources
    - gauge - logical part of gauges, uncoupled from GUI
    - gui - visual part of gauges
    - utils - standalone utilities, in some cases waiting room to get into mzlib
- tests - unit tests
- res - resource files that aren't code
  
## Include order

1) header of the cpp
2) files from this project
3) files from other projects in same solution
4) 3rdParty libraries
   1) my libraries
   2) other libraries
5) standard library

# projects used

## 3rdparty stuff used

- QT5
- gtest
- sigslot

## 3rdparty source preference

1) conan
2) submodule in 3rdparty
4) system install

If I can, I stick to these separately for different OSes. For example, QT is installed on openSUSE but Conaned on Windows and Ubuntu.