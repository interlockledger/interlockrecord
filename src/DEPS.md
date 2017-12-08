# InterlockRecord Dependencies

## External libraries

The InterlockRecord implementation uses the following external dependencies:

* Botan 2.3.0;
* Google Test 1.8.0;

## Windows Dependencies

### Botan

Instructions about this library can be found inside the directory
``/deps/botan-win-build`` inside this repository.

### Google Test

Instructions about this library can be found inside the directory
``/deps/gtest-win-build`` inside this repository.

## Linux Dependencies

### Botan

Most Linux distributions are not shipped with the Botan 2 library. It must be
compiled and installed manually. Download it from https://botan.randombit.net/
and follow the instructions at https://botan.randombit.net/manual/building.html
in order to build the library.

### Google Test

This library can be installed directly from most Linux distributions.
