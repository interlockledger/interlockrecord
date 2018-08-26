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
#include "IRBinaryAlphabetTest.h"
using namespace ircommon;
using namespace ircommon::codec;

//==============================================================================
// class IRBinaryAlphabetTest
//------------------------------------------------------------------------------
IRBinaryAlphabetTest::IRBinaryAlphabetTest() {
}

//------------------------------------------------------------------------------
IRBinaryAlphabetTest::~IRBinaryAlphabetTest() {
}

//------------------------------------------------------------------------------
void IRBinaryAlphabetTest::SetUp() {
}

//------------------------------------------------------------------------------
void IRBinaryAlphabetTest::TearDown() {
}

//------------------------------------------------------------------------------
TEST_F(IRBinaryAlphabetTest, Constructor) {
	IRBinaryAlphabet * a;

	a = new IRBinaryAlphabet();
	ASSERT_EQ(2, a->size());
	delete a;

	a = new IRBinaryAlphabet('a', 'b');
	ASSERT_EQ(2, a->size());
	delete a;

	try {
		a = new IRBinaryAlphabet('a', 'a');
		delete a;
		FAIL();
	} catch (std::invalid_argument & e){}
}

//------------------------------------------------------------------------------
TEST_F(IRBinaryAlphabetTest, Mapping) {
	IRBinaryAlphabet a;

	ASSERT_TRUE(this->checkMapping(a));
	ASSERT_TRUE(this->checkUniqueChars(a));
}

//------------------------------------------------------------------------------
TEST_F(IRBinaryAlphabetTest, getChar) {
	IRBinaryAlphabet * a;

	a = new IRBinaryAlphabet();
	ASSERT_EQ('0', a->getChar(0));
	ASSERT_EQ('1', a->getChar(1));
	delete a;

	a = new IRBinaryAlphabet('F', 'T');
	ASSERT_EQ('F', a->getChar(0));
	ASSERT_EQ('T', a->getChar(1));
	delete a;
}

//------------------------------------------------------------------------------
TEST_F(IRBinaryAlphabetTest, getValue) {
	IRBinaryAlphabet * a;

	a = new IRBinaryAlphabet();
	for (int i = 0; i < 256; i++) {
		if (i == '0') {
			ASSERT_EQ(0, a->getValue(i));
		} else if (i == '1') {
			ASSERT_EQ(1, a->getValue(i));
		} else {
			ASSERT_EQ(-1, a->getValue(i));
		}
	}
	delete a;

	a = new IRBinaryAlphabet('F', 'T');
	for (int i = 0; i < 256; i++) {
		if (i == 'F') {
			ASSERT_EQ(0, a->getValue(i));
		} else if (i == 'T') {
			ASSERT_EQ(1, a->getValue(i));
		} else {
			ASSERT_EQ(-1, a->getValue(i));
		}
	}
	delete a;
}
//------------------------------------------------------------------------------


