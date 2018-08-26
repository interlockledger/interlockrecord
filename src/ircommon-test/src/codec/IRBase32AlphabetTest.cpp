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

