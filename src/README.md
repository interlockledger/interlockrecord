# IRCommonLib

## Minimum requirements

### All plaforms

   * CMake 3.9 or later;
   * Doxygen 1.8 or later;

### Linux

   * GCC 5.3 or later;
   * Eclipse Oxygen with CDT;

### Windows

   * Microsoft Visual Studio 2017

## Development environment

### Eclipse

In order to create the **Eclipse CDT** project, run the command:

```
$ cmake . -G"Eclipse CDT4 - Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug -DCMAKE_ECLIPSE_VERSION=4.7
```

### Microsoft Visual Studio

In order to create the **Microsoft Visual Studio** project, run the command:

```
$ cmake . -G"Visual Studio 15 2017 Win64" -DCMAKE_BUILD_TYPE=Debug
```

## Release build

```
cmake --build . --clean-first
```

## External dependencies
