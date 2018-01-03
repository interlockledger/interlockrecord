/*
 * Copyright (c) 2017-2018, Open Communications Security
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
#include "IRGenericAlphabetTest.h"

using namespace ircommon;

//==============================================================================
// class IRGenericAlphabetTest
//------------------------------------------------------------------------------
IRGenericAlphabetTest::IRGenericAlphabetTest() {
}

//------------------------------------------------------------------------------
IRGenericAlphabetTest::~IRGenericAlphabetTest() {
}

//------------------------------------------------------------------------------
void IRGenericAlphabetTest::SetUp() {
}

//------------------------------------------------------------------------------
void IRGenericAlphabetTest::TearDown() {
}

//------------------------------------------------------------------------------
TEST_F(IRGenericAlphabetTest, Constructor) {

	IRGenericAlphabet a("0123456789", 10);
	ASSERT_EQ(10, a.size());
}

//------------------------------------------------------------------------------
TEST_F(IRGenericAlphabetTest, Mapping) {

	IRGenericAlphabet a("0123456789", 10);
	ASSERT_TRUE(this->checkMapping(a));
	ASSERT_TRUE(this->checkUniqueChars(a));
}

//------------------------------------------------------------------------------
TEST_F(IRGenericAlphabetTest, getValue) {
	std::string map("0123456789");
	IRGenericAlphabet a(map.c_str(), map.size());

	for (int i = 0; i < map.size(); i++) {
		ASSERT_EQ(i, a.getValue(map[i]));
	}

	for (int i = 0; i < 256; i++) {
		if (map.find_first_of(i) == -1) {
			ASSERT_EQ(-1, a.getValue(i));
		} else {
			ASSERT_NE(-1, a.getValue(i));
		}
	}
}

//------------------------------------------------------------------------------
TEST_F(IRGenericAlphabetTest, getChar) {
	std::string map("0123456789");
	IRGenericAlphabet a(map.c_str(), map.size());

	for (int i = 0; i < map.size(); i++) {
		ASSERT_EQ(map[i], a.getChar(i));
	}
}


//------------------------------------------------------------------------------

