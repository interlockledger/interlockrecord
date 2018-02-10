# InterlockRecord Dependencies

## External libraries

The InterlockRecord implementation uses the following external dependencies:

* Botan 2.3.0;
* Google Test 1.8.0;

## Windows Dependencies

This library uses the same library structure defined by the project **ocs-cmake-utils**.
See the instructions to build those dependencies in:

* https://github.com/opencs/ocs-cmake-utils

## Linux Dependencies

### Botan

Most Linux distributions are not shipped with the Botan 2 library. It must be
compiled and installed manually. Download it from https://botan.randombit.net/
and follow the instructions at https://botan.randombit.net/manual/building.html
in order to build the library.

### Google Test

This library can be installed directly from most Linux distributions. See your
distribution instructions for more information.
