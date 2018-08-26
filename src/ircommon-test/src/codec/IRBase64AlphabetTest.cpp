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
#include "IRBase64AlphabetTest.h"
using namespace ircommon;
using namespace ircommon::codec;

//==============================================================================
// class IRBase64AlphabetTest
//------------------------------------------------------------------------------
IRBase64AlphabetTest::IRBase64AlphabetTest() {
}

//------------------------------------------------------------------------------
IRBase64AlphabetTest::~IRBase64AlphabetTest() {
}

//------------------------------------------------------------------------------
void IRBase64AlphabetTest::SetUp() {
}

//------------------------------------------------------------------------------
void IRBase64AlphabetTest::TearDown() {
}

//------------------------------------------------------------------------------
TEST_F(IRBase64AlphabetTest, Constructor) {
	IRBase64Alphabet * a;

	a = new IRBase64Alphabet();
	ASSERT_EQ(64, a->size());
	ASSERT_EQ('+', a->getChar(62));
	ASSERT_EQ('/', a->getChar(63));
	delete a;

	a = new IRBase64Alphabet(false);
	ASSERT_EQ(64, a->size());
	ASSERT_EQ('+', a->getChar(62));
	ASSERT_EQ('/', a->getChar(63));
	delete a;

	a = new IRBase64Alphabet(true);
	ASSERT_EQ(64, a->size());
	ASSERT_EQ('-', a->getChar(62));
	ASSERT_EQ('_', a->getChar(63));
	delete a;

	a = new IRBase64Alphabet('$', '%');
	ASSERT_EQ(64, a->size());
	ASSERT_EQ('$', a->getChar(62));
	ASSERT_EQ('%', a->getChar(63));
	delete a;
}

//------------------------------------------------------------------------------
TEST_F(IRBase64AlphabetTest, Mapping) {
	IRBase64Alphabet * a;

	a = new IRBase64Alphabet(false);
	ASSERT_TRUE(checkMapping(*a));
	ASSERT_TRUE(checkUniqueChars(*a));
	delete a;

	a = new IRBase64Alphabet(true);
	ASSERT_TRUE(checkMapping(*a));
	ASSERT_TRUE(checkUniqueChars(*a));
	delete a;

	a = new IRBase64Alphabet('$', '%');
	ASSERT_TRUE(checkMapping(*a));
	ASSERT_TRUE(checkUniqueChars(*a));
	delete a;
}

//------------------------------------------------------------------------------
TEST_F(IRBase64AlphabetTest, getChar) {
	IRBase64Alphabet * a;
	std::string map;

	map = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	a = new IRBase64Alphabet(false);
	for (unsigned int i = 0; i < map.size(); i++) {
		ASSERT_EQ(map[i], a->getChar(i));
	}
	delete a;

	map = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_";
	a = new IRBase64Alphabet(true);
	for (unsigned int i = 0; i < map.size(); i++) {
		ASSERT_EQ(map[i], a->getChar(i));
	}
	delete a;

	map = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789$%";
	a = new IRBase64Alphabet('$', '%');
	for (unsigned int i = 0; i < map.size(); i++) {
		ASSERT_EQ(map[i], a->getChar(i));
	}
	delete a;
}

//------------------------------------------------------------------------------
TEST_F(IRBase64AlphabetTest, getValue) {
	IRBase64Alphabet * a;
	std::string map;

	map = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	a = new IRBase64Alphabet(false);
	for (unsigned int i = 0; i < map.size(); i++) {
		ASSERT_EQ(i, a->getValue(map[i]));
	}
	for (int i = 0; i < 256; i++) {
		if (map.find_first_of(i) < 0) {
			ASSERT_EQ(-1, a->getValue(i));
		}
	}
	delete a;

	map = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_";
	a = new IRBase64Alphabet(true);
	for (unsigned int i = 0; i < map.size(); i++) {
		ASSERT_EQ(i, a->getValue(map[i]));
	}
	for (int i = 0; i < 256; i++) {
		if (map.find_first_of(i) < 0) {
			ASSERT_EQ(-1, a->getValue(i));
		}
	}
	delete a;

	map = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789$%";
	a = new IRBase64Alphabet('$', '%');
	for (unsigned int i = 0; i < map.size(); i++) {
		ASSERT_EQ(i, a->getValue(map[i]));
	}
	for (int i = 0; i < 256; i++) {
		if (map.find_first_of(i) < 0) {
			ASSERT_EQ(-1, a->getValue(i));
		}
	}
	delete a;
}
//------------------------------------------------------------------------------

