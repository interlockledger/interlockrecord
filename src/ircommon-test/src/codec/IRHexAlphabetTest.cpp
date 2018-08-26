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
#include "IRHexAlphabetTest.h"

using namespace ircommon;
using namespace ircommon::codec;

//==============================================================================
// class IRHexAlphabetTest
//------------------------------------------------------------------------------
IRHexAlphabetTest::IRHexAlphabetTest() {
}

//------------------------------------------------------------------------------
IRHexAlphabetTest::~IRHexAlphabetTest() {
}

//------------------------------------------------------------------------------
void IRHexAlphabetTest::SetUp() {
}

//------------------------------------------------------------------------------
void IRHexAlphabetTest::TearDown() {
}

//------------------------------------------------------------------------------
TEST_F(IRHexAlphabetTest, Constructor) {
	IRHexAlphabet * a;

	a = new IRHexAlphabet();
	ASSERT_EQ(16, a->size());
	ASSERT_EQ('A', a->getChar(10));
	delete a;

	a = new IRHexAlphabet(false);
	ASSERT_EQ(16, a->size());
	ASSERT_EQ('A', a->getChar(10));
	delete a;

	a = new IRHexAlphabet(true);
	ASSERT_EQ(16, a->size());
	ASSERT_EQ('a', a->getChar(10));
	delete a;
}

//------------------------------------------------------------------------------
TEST_F(IRHexAlphabetTest, Mapping) {
	IRHexAlphabet * a;

	a = new IRHexAlphabet(false);
	ASSERT_TRUE(this->checkMapping(*a));
	ASSERT_TRUE(this->checkUniqueChars(*a));
	delete a;

	a = new IRHexAlphabet(true);
	ASSERT_TRUE(this->checkMapping(*a));
	ASSERT_TRUE(this->checkUniqueChars(*a));
	delete a;
}

//------------------------------------------------------------------------------
TEST_F(IRHexAlphabetTest, getChar) {
	IRHexAlphabet * a;
	std::string map;

	map = "0123456789ABCDEF";
	a = new IRHexAlphabet(false);
	for (int i = 0; i < a->size(); i++) {
		ASSERT_EQ(map[i], a->getChar(i));
	}
	delete a;

	map = "0123456789abcdef";
	a = new IRHexAlphabet(true);
	for (int i = 0; i < a->size(); i++) {
		ASSERT_EQ(map[i], a->getChar(i));
	}
	delete a;
}

//------------------------------------------------------------------------------
TEST_F(IRHexAlphabetTest, getValue) {
	IRHexAlphabet * a;
	std::string map;

	map = "0123456789ABCDEF0123456789abcdef";
	a = new IRHexAlphabet(false);
	for (unsigned int i = 0; i < map.size(); i++) {
		ASSERT_EQ(i % 16, a->getValue(map[i]));
	}
	for (int i = 0; i < 256; i++) {
		if (map.find_first_of(i) < 0) {
			ASSERT_EQ(-1, a->getValue(i));
		}
	}
	delete a;

	map = "0123456789ABCDEF0123456789abcdef";
	a = new IRHexAlphabet(true);
	for (unsigned int i = 0; i < map.size(); i++) {
		ASSERT_EQ(i % 16, a->getValue(map[i]));
	}
	for (int i = 0; i < 256; i++) {
		if (map.find_first_of(i) < 0) {
			ASSERT_EQ(-1, a->getValue(i));
		}
	}
	delete a;
}
//------------------------------------------------------------------------------

