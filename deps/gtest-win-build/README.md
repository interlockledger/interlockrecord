# gtest-win-build
Copyright (c) 2017 Open Communications Security. All rights reserved.

## Introduction

CMake (https://cmake.org/) is a very powerfull build tool for portable C/C++
programs. Under *nix systems, its execution is very straighforward but under
Windows, the lack of a standard location for library and headers may lead to
a few issues with 3rd party libraries. 

This script can be used to build the *Google Test* 
(https://github.com/google/googletest) under Windows using
*Microsoft Visual Studio 2017* and create a package suitable to be used with
CMake's FindGTest module.

## Dependencies

This build script requires the following dependencies in order to be executed:

* Microsoft Windows 10;
* Visual Studio 2017 with C/C++ support (any edition);
* CMake 2.9 or later;
* Apache Ant 1.9 or later;
* A Java 8 Virtual Machine;

## Running the build

In order to execute this script, go to this directory and run:

* ant -f build.xml all

The final result will be found inside the subdirectory *gtest*. All files will
be located in the layout expected by the CMake's FindGTest module.

## Installation

Once the package is complete, copy the directory <project-home>/gtest to the
desired location inside your computer and set the environment variable 
*GTEST_ROOT* to point to this location.

For example, if the binaries are copied to *C:\lib\gtest*, set the variable
*GTEST_ROOT* to *C:\lib\gtest*. Once this is done, the FindGTest module of
CMake will locate the Google Test for you.

## Known limitations

This version of the script will not compile the libraries for the DLL runtime
(/MD and /MDd).

## License

This script is licensed under the *BSD 3-Clause License*.
