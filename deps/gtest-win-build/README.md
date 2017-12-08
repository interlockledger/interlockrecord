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

## Precompiled libraries

A precompiled version of this library can be found at:

*  http://brigadeiro.opencs.com.br/downloads/opensource/googletest/gtest-1.8.0-msvc14.7z

The **sha512sum** of this file is:

```
b58b56f6a309e05e647231530e67777dfc4a73ff9a18840e7559de8124aa4aee485040a593e5415b350a5db7f94ecf8fa6d466ca38c42a9fbf6dd7f0ca7e6748
```

Move the directory ``gtest`` inside the package to any location of your computer
(e.g.: ``c:\libs\gtest``) and set the environment variable ``GTEST_ROOT`` to the
proper value (e.g.: ``set GTEST_ROOT=c:\libs\gtest``).

## Dependencies

This build script requires the following dependencies in order to be executed:

* Microsoft Windows 10;
* Visual Studio 2017 with C/C++ support (any edition);
* CMake 2.9 or later;
* Apache Ant 1.9 or later;
* A Java 8 Virtual Machine;

## Running the build

In order to execute this script, go to this directory and run:

```
ant -f build.xml all
```

The final result will be found inside the subdirectory ``gtest``. All files will
be located in the layout expected by the CMake's FindGTest module.

## Installation

Once the package is complete, copy the directory <project-home>/gtest to the
desired location inside your computer and set the environment variable
``GTEST_ROOT`` to point to this location.

For example, if the binaries are copied to ``C:\libs\gtest``, set the variable
``GTEST_ROOT`` to ``C:\lib\gtest``. Once this is done, the FindGTest module of
**CMake** will locate the **Google Test** for you.

## Description of the directory structure

Under the directory ``gtest``, this build will contain two directories:

* include
* msvc

The ``msvc`` contains the libraries for MSVC. The subdirectory ``gtest`` will
hold the 32-bit libraries and the subdirectory ``x64`` will hold the 64-bit
libraries.

Inside the subdirectories ``gtest`` and ``x64``, there will be a subdirectory
called ``Release`` and another called ``Debug``. The ``Release`` subdirectory
will hold the libraries compiled with  ``/MT`` while the ``Debug`` subdirectory
will hold the libraries compiled with ``/MTd``.

## Known limitations

This version of the script will not compile the libraries for the DLL CRT
(/MD and /MDd).

## License

This script is licensed under the *BSD 3-Clause License*.
