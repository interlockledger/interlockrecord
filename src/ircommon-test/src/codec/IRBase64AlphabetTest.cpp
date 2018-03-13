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

