# InterlockRecord Dependencies

This directory contains a few utilities that can be used to build the
**InterlockRecord** dependencies on Windows and other platforms.

## Microsoft Windows

### gtest-win-build

This subdirectory contains the scripts used to build the **Google Test** library
for **Windows** using **Microsoft Visual Studio**. It also creates a distrbution
package that is suitableto be used with **CMake** on **Windows**.

See the *README.md* inside for more information.

This subdirectory were added into this repository using the command:

```
git subtree add --prefix deps/gtest-win-build https://github.com/opencs/gtest-win-build.git master
```

More about subtrees can be found at:

https://www.atlassian.com/blog/git/alternatives-to-git-submodule-git-subtree

### openssl-win-build

This subdirectory contains scripts and instructions used to build OpenSSL
on Windows.

See the *README.md* inside for more information.
