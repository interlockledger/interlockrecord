#!/bin/bash
# Copyright (c) 2017-2018 InterlockLedger Network
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
MY_HOME=$(dirname "$0")
pushd "$MY_HOME" > /dev/null
MY_HOME=$(pwd)
cd ..
BUILD_DIR="$(pwd)/build"
popd > /dev/null

if [ -d "$BUILD_DIR" ]; then
	echo "'$BUILD_DIR' already exists. Updating..."
	pushd "$BUILD_DIR" >/dev/null
	cmake ../src
	popd > /dev/null
	exit 1
else
	echo "Creating $BUILD_DIR..."
	mkdir "$BUILD_DIR"
	pushd "$BUILD_DIR" >/dev/null
	cmake ../src -G"Eclipse CDT4 - Ninja" -DCMAKE_BUILD_TYPE=Debug -DCMAKE_ECLIPSE_VERSION=4.6
	popd >/dev/null
	echo "Build environment created inside '$BUILD_DIR'. Load it as an Eclipse CDT project."
fi

