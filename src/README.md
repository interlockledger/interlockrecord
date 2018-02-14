# InterlockRecord

## Minimum requirements

### All plaforms

   * CMake 3.9 or later;
   * Doxygen 1.8 or later;

### Linux

   * GCC 5.3 or later;
   * Eclipse Oxygen with CDT;

### Windows

   * Microsoft Visual Studio 2017

### External dependencies

      * Botan 2.3.0;
      * Google Test 1.8.0;

More instructions about those dependencies can be found inside **DEPS.md**.

## Development environment

### Code::Blocks

Code::Blocks with Ninja:

```
$ cmake ../src -G"CodeBlocks - Ninja" -DCMAKE_BUILD_TYPE=Debug
```

Code::Blocks with Makefile:

```
$ cmake ../src -G"CodeBlocks - Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug
```

### Eclipse

In order to create the **Eclipse CDT** project, create a directory called **build** side by side of the
directory **src**. Go to this directory and run the command:

For Neon with Ninja:

```
$ cmake ../src -G"Eclipse CDT4 - Ninja" -DCMAKE_BUILD_TYPE=Debug -DCMAKE_ECLIPSE_VERSION=4.6
```

For Neon with Makefile:

```
$ cmake ../src -G"Eclipse CDT4 - Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug -DCMAKE_ECLIPSE_VERSION=4.6
```

For Oxygen with Ninja:

```
$ cmake ../src -G"Eclipse CDT4 - Ninja" -DCMAKE_BUILD_TYPE=Debug -DCMAKE_ECLIPSE_VERSION=4.7
```

For Oxygen with Makefile:

```
$ cmake ../src -G"Eclipse CDT4 - Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug -DCMAKE_ECLIPSE_VERSION=4.7
```

### Microsoft Visual Studio

In order to create the **Microsoft Visual Studio** project, run the command:

```
$ cmake ../src -G"Visual Studio 15 2017 Win64"
```

## Release build


```
$ cmake ../src -DCMAKE_BUILD_TYPE=Release
$ cmake --build . --clean-first
```
