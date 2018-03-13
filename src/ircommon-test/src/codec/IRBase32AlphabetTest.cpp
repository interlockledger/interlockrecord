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
#include "IRBase32AlphabetTest.h"
using namespace ircommon;
using namespace ircommon::codec;

//==============================================================================
// class IRBase32AlphabetTest
//------------------------------------------------------------------------------
IRBase32AlphabetTest::IRBase32AlphabetTest() {
}

//------------------------------------------------------------------------------
IRBase32AlphabetTest::~IRBase32AlphabetTest() {
}

//------------------------------------------------------------------------------
void IRBase32AlphabetTest::SetUp() {
}

//------------------------------------------------------------------------------
void IRBase32AlphabetTest::TearDown() {
}

//------------------------------------------------------------------------------
TEST_F(IRBase32AlphabetTest, Constructor) {
	IRBase32Alphabet * a;

	a = new IRBase32Alphabet();
	ASSERT_EQ(32, a->size());
	ASSERT_EQ('A', a->getChar(0));
	delete a;

	a = new IRBase32Alphabet(false, false);
	ASSERT_EQ(32, a->size());
	ASSERT_EQ('A', a->getChar(0));
	delete a;

	a = new IRBase32Alphabet(true, false);
	ASSERT_EQ(32, a->size());
	ASSERT_EQ('a', a->getChar(0));
	delete a;

	a = new IRBase32Alphabet(false, true);
	ASSERT_EQ(32, a->size());
	ASSERT_EQ('A', a->getChar(10));
	delete a;

	a = new IRBase32Alphabet(true, true);
	ASSERT_EQ(32, a->size());
	ASSERT_EQ('a', a->getChar(10));
	delete a;
}

//------------------------------------------------------------------------------
TEST_F(IRBase32AlphabetTest, Mapping) {
	IRBase32Alphabet * a;

	a = new IRBase32Alphabet(false, false);
	ASSERT_TRUE(checkMapping(*a));
	ASSERT_TRUE(checkUniqueChars(*a));
	delete a;

	a = new IRBase32Alphabet(true, false);
	ASSERT_TRUE(checkMapping(*a));
	ASSERT_TRUE(checkUniqueChars(*a));
	delete a;

	a = new IRBase32Alphabet(false, true);
	ASSERT_TRUE(checkMapping(*a));
	ASSERT_TRUE(checkUniqueChars(*a));
	delete a;

	a = new IRBase32Alphabet(true, true);
	ASSERT_TRUE(checkMapping(*a));
	ASSERT_TRUE(checkUniqueChars(*a));
	delete a;
}

//------------------------------------------------------------------------------
TEST_F(IRBase32AlphabetTest, getValue) {
	IRBase32Alphabet * a;
	std::string map;

	map = "ABCDEFGHIJKLMNOPQRSTUVWXYZ234567abcdefghijklmnopqrstuvwxyz234567";
	a = new IRBase32Alphabet(false, false);
	for (unsigned int i = 0; i < map.size(); i++) {
		ASSERT_EQ(i % 32, a->getValue(map[i]));
	}
	for (int i = 0; i < 256; i++) {
		if (map.find_first_of(i) < 0) {
			ASSERT_EQ(-1, a->getValue(i));
		}
	}
	delete a;

	a = new IRBase32Alphabet(true, false);
	for (unsigned int i = 0; i < map.size(); i++) {
		ASSERT_EQ(i % 32, a->getValue(map[i]));
	}
	for (int i = 0; i < 256; i++) {
		if (map.find_first_of(i) < 0) {
			ASSERT_EQ(-1, a->getValue(i));
		}
	}
	delete a;

	map = "0123456789ABCDEFGHIJKLMNOPQRSTUV0123456789abcdefghijklmnopqrstuv";
	a = new IRBase32Alphabet(false, true);
	for (unsigned int i = 0; i < map.size(); i++) {
		ASSERT_EQ(i % 32, a->getValue(map[i]));
	}
	for (int i = 0; i < 256; i++) {
		if (map.find_first_of(i) < 0) {
			ASSERT_EQ(-1, a->getValue(i));
		}
	}
	delete a;

	a = new IRBase32Alphabet(true, true);
	for (unsigned int i = 0; i < map.size(); i++) {
		ASSERT_EQ(i % 32, a->getValue(map[i]));
	}
	for (int i = 0; i < 256; i++) {
		if (map.find_first_of(i) < 0) {
			ASSERT_EQ(-1, a->getValue(i));
		}
	}
	delete a;
}


//------------------------------------------------------------------------------
TEST_F(IRBase32AlphabetTest, getChar) {
	IRBase32Alphabet * a;
	std::string map;

	map = "ABCDEFGHIJKLMNOPQRSTUVWXYZ234567";
	a = new IRBase32Alphabet(false, false);
	for (unsigned int i = 0; i < map.size(); i++) {
		ASSERT_EQ(map[i], a->getChar(i));
	}
	delete a;

	map = "abcdefghijklmnopqrstuvwxyz234567";
	a = new IRBase32Alphabet(true, false);
	for (unsigned int i = 0; i < map.size(); i++) {
		ASSERT_EQ(map[i], a->getChar(i));
	}
	delete a;

	map = "0123456789ABCDEFGHIJKLMNOPQRSTUV";
	a = new IRBase32Alphabet(false, true);
	for (unsigned int i = 0; i < map.size(); i++) {
		ASSERT_EQ(map[i], a->getChar(i));
	}
	delete a;

	map = "0123456789abcdefghijklmnopqrstuv";
	a = new IRBase32Alphabet(true, true);
	for (unsigned int i = 0; i < map.size(); i++) {
		ASSERT_EQ(map[i], a->getChar(i));
	}
	delete a;
}
//------------------------------------------------------------------------------

