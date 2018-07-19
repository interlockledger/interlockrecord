#!/bin/bash

BUILD_DIR=build

run_test() {
	if ! ./$1; then
		exit 3
	fi
}

# Go to the script directory
pushd $(dirname $0)

# Cleanup
rm -Rf "$BUILD_DIR"

# Prepare the cmake project
mkdir "$BUILD_DIR"

# Goto the build dir
pushd "$BUILD_DIR"

# Run cmake
if ! cmake -G Ninja ../src; then
	echo "CMake generation failed!"
	exit 1
fi

# Building...
if ! ninja; then
	echo "Build failed!"
	exit 2
fi

# Running the Unit tests
pushd bin
run_test ircommon-test
run_test irecordcore-test
run_test irecord-tests
popd 

# Return to the project root dir
popd

# Return the current directory
popd

