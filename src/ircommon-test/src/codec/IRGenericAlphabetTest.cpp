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
#include "IRGenericAlphabetTest.h"

using namespace ircommon;
using namespace ircommon::codec;

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

	for (unsigned int i = 0; i < map.size(); i++) {
		ASSERT_EQ(i, a.getValue(map[i]));
	}

	for (int i = 0; i < 256; i++) {
		if (map.find_first_of(i) == ((std::string::size_type)-1)) {
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

	for (unsigned int i = 0; i < map.size(); i++) {
		ASSERT_EQ(map[i], a.getChar(i));
	}
}


//------------------------------------------------------------------------------

