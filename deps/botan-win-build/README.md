# Building Botan 2 on Windows

## About Botan

As stated in its official site, *Botan (Japanese for peony) is a cryptography
library written in C++11 and released under the permissive Simplified BSD
license*. More about Botan can be found at https://botan.randombit.net/.

This document describes how to download and build the Botan 2 library for Windows
in a way that it could be used to build the InterlockRecord binaries.

## Precompiled libraries

A precompiled version of this library can be found at:

* http://brigadeiro.opencs.com.br/downloads/opensource/botan/botan-2.3.0-x64-msvc14.7z

The **sha512sum** of this file is:

```
bfbd8ed1f2cc12d046688fe1ea89e8bd32650a0aa8a4f22fe39aa0150ed35ac7b43d6f13d514c00e56034a9e836c2a6126ddda8de0b281417990130f18ae0300
```

Once decompressed, move the ``botan`` directory inside the package to ``c:\botan``.

## Downloading the source

The version 2.3.0 of Botan can be downloaded from:

* https://botan.randombit.net/releases/Botan-2.3.0.tgz

Its sha512sum is:

```
a8575bdb2eaa01fb45d8565bea0b54ddf47a21d2fb761fc0a286373b09d51e5a00e84d5cefc51040c5720db66f5625c6bc73ab09cffa9cd42472545610f9892a
```

## Compiling

### Prerequisites

In order to compile Botan 2, it is necessary to have the following tools
installed on the system:

* Microsoft Windows 10;
* Visual Studio 2017 with C/C++ support (any edition);
* A Python 3.x interpreter (https://www.python.org/);

### About editions

Since Botan 2 is heavly dependent on templates, it is necessary to create at
least one build of the library for each MSVC CRT mode. This means that at least
4 versions are necessary per platform:

* Multi-Thread (/MT)
* Multi-Thread Debug (/MTd)
* Multi-Thread DLL (/MD)
* Multi-Thread DLL Debug (/MDd)

It is important to notice that your code must be linked with the library compiled
with the same CRT mode of your application.

### Compile for release with /MD and /MT

Decompress the source file inside a given directory.

Create the default release ``Makefile`` by running
``configure.py --cpu=x86_64 --disable-shared --cc=msvc``
inside the source directory.

Once the Makefile is ready, open a VC command prompt (**x64 Native Tools Command
Prompt for VC 2017**) and go to the source directory.

Inside this command prompt, run ``nmake`` in order to build the binaries and the
libraries.

Once the previous command is done without errors, install the binaries by
running ``nmake install``. This should install the files under ``c:\botan``.

Now, move the file ``C:\Botan\lib\botan.lib`` to ``C:\Botan\lib\x64\botan-md.lib`` in
order to make room to other versions od this library.

In order to create the ``/MT`` version, run the command ``nmake clean`` to remove
all binaries generated in the previous step.

Open the file ``Makefile`` and change the line:

```
CXX            = cl /MD /bigobj
```

with:

```
CXX            = cl /MT /bigobj
```

Save the ``Makefile`` and compile the code again by running ``nmake`` once again.

Once done, the new version of ``botan.lib`` will be found in the same directory
of the ``Makefile``. Copy this file to ``C:\Botan\lib\x64\botan-mt.lib``.

### Compile for debug with /MDd and /MTd

Decompress the source file inside a given directory again.

Create the default debug ``Makefile`` by running
``configure.py --cpu=x86_64 --disable-shared --cc=msvc --debug-mode``
inside the source directory.

Once the Makefile is ready, open a VC command prompt (**x64 Native Tools Command
Prompt for VC 2017**) and go to the source directory.

Inside this command prompt, run ``nmake`` in order to build the binaries and the
libraries.

Once done, the new version of ``botan.lib`` will be found in the same directory
of the ``Makefile``. Copy this file to ``C:\Botan\lib\x64\botan-mdd.lib``.

In order to create the ``/MTd`` version, run the command ``nmake clean`` to remove
all binaries generated in the previous step.

Open the file ``Makefile`` and change the line:

```
CXX            = cl /MDd /bigobj
```

with:

```
CXX            = cl /MTd /bigobj
```
Save the ``Makefile`` and compile the code again by running ``nmake`` once again.

Once done, the new version of ``botan.lib`` will be found in the same directory
of the ``Makefile``. Copy this file to ``C:\Botan\lib\x64\botan-mtd.lib``.
