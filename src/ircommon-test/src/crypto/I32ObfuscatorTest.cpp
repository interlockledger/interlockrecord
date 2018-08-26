/*
 * Copyright (c) 2017-2018 InterlockLedger Network
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "I32ObfuscatorTest.h"

#include <ircommon/i32obfus.h>
#include <cstdlib>

using namespace ircommon;
using namespace ircommon::crypto;

//==============================================================================
// class I32ObfuscatorTest
//------------------------------------------------------------------------------
I32ObfuscatorTest::I32ObfuscatorTest() {
}

//------------------------------------------------------------------------------
I32ObfuscatorTest::~I32ObfuscatorTest() {
}

//------------------------------------------------------------------------------
void I32ObfuscatorTest::SetUp() {
}

//------------------------------------------------------------------------------
void I32ObfuscatorTest::TearDown() {
}

//------------------------------------------------------------------------------
TEST_F(I32ObfuscatorTest, Constructor) {
	I32Obfuscator * o;

	o = new I32Obfuscator();
	delete o;
}

//------------------------------------------------------------------------------
TEST_F(I32ObfuscatorTest, ObfuscateDeobfuscate) {
	I32Obfuscator o;
	std::uint32_t value;
	std::uint32_t obfuscated;
	std::uint32_t actual;

	srand(0x12345678);
	for (int i = 0; i < 1000; i++) {
		value = rand();
		obfuscated = o.obfuscate(value);
		ASSERT_EQ(value, obfuscated);
		actual = o.deobfuscate(obfuscated);
		ASSERT_EQ(value, actual);
	}
}
//------------------------------------------------------------------------------

