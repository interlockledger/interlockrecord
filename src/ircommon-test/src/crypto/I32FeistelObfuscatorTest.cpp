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
#include "I32FeistelObfuscatorTest.h"

#include <ircommon/i32obfus.h>
#include <cstdlib>

using namespace ircommon;
using namespace ircommon::crypto;

//==============================================================================
// class I32FeistelObfuscatorTest
//------------------------------------------------------------------------------
I32FeistelObfuscatorTest::I32FeistelObfuscatorTest() {
}

//------------------------------------------------------------------------------
I32FeistelObfuscatorTest::~I32FeistelObfuscatorTest() {
}

//------------------------------------------------------------------------------
void I32FeistelObfuscatorTest::SetUp() {
}

//------------------------------------------------------------------------------
void I32FeistelObfuscatorTest::TearDown() {
}

//------------------------------------------------------------------------------
TEST_F(I32FeistelObfuscatorTest,Constructor) {
	I32FeistelObfuscator * o;
	I32Obfuscator * o2;

	o = new I32FeistelObfuscator();
	delete o;

	o = new I32FeistelObfuscator(0xDAFACADA);
	delete o;

	o2 = new I32FeistelObfuscator();
	delete o2;
}

//------------------------------------------------------------------------------
TEST_F(I32FeistelObfuscatorTest,ObfuscateDeobfuscate) {
	I32FeistelObfuscator * o;
	std::uint32_t value;
	std::uint32_t obfuscated;
	std::uint32_t actual;

	srand(0x12345678);
	for (int j = 0; j < 100; j++) {
		o = new I32FeistelObfuscator(rand());
		for (int i = 0; i < 1000; i++) {
			value = rand();
			obfuscated = o->obfuscate(value);
			ASSERT_NE(value, obfuscated);
			actual = o->deobfuscate(obfuscated);
			ASSERT_EQ(value, actual);
		}
		delete o;
	}
}
//------------------------------------------------------------------------------

