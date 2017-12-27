/*
 * Copyright (c) 2017, Open Communications Security
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the <organization> nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL OPEN COMMUNICATIONS SECURITY BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include "I32ObfuscatorTest.h"

#include <ircommon/i32obfus.h>
#include <cstdlib>

using namespace ircommon;

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

