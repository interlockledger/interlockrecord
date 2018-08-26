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
#include "IRAlphabetTest.h"
#include <set>

#include <ircommon/iralphab.h>

using namespace ircommon;
using namespace ircommon::codec;

//==============================================================================
// class IRDummyAlphabet - This class will be used to test IRAlphabet and
// IRAlphabetTest as well.
//------------------------------------------------------------------------------
class IRDummyAlphabet: public IRAlphabet {
private:
	std::string _map;
public:
	IRDummyAlphabet(int size);
	IRDummyAlphabet(const char * map, int size);
	virtual ~IRDummyAlphabet() = default;
	virtual int getValue(int c) const;
	virtual int getChar(int v) const;
};

//------------------------------------------------------------------------------
IRDummyAlphabet::IRDummyAlphabet(int size): IRDummyAlphabet("", size) {
}

IRDummyAlphabet::IRDummyAlphabet(const char * map, int size) : IRAlphabet(size),
		_map(map){
}

//------------------------------------------------------------------------------
int IRDummyAlphabet::getValue(int c) const {

	return this->_map.find_first_of(c);
}

//------------------------------------------------------------------------------
int IRDummyAlphabet::getChar(int v) const {

	return this->_map[v % this->_map.size()];
}

//==============================================================================
// class IRAlphabetTest
//------------------------------------------------------------------------------
IRAlphabetTest::IRAlphabetTest() {
}

//------------------------------------------------------------------------------
IRAlphabetTest::~IRAlphabetTest() {
}

//------------------------------------------------------------------------------
void IRAlphabetTest::SetUp() {
}

//------------------------------------------------------------------------------
void IRAlphabetTest::TearDown() {
}

//------------------------------------------------------------------------------
bool IRAlphabetTest::checkMapping(ircommon::codec::IRAlphabet & alphabet) {

	for (int i = 0; i < alphabet.size(); i++) {
		int c = alphabet.getChar(i);
		if ((alphabet.getValue(c)) != i) {
			return false;
		}
	}
	return true;
}

//------------------------------------------------------------------------------
bool IRAlphabetTest::checkUniqueChars(ircommon::codec::IRAlphabet & alphabet) {

	std::set<int> chars;
	for (int i = 0; i < alphabet.size(); i++) {
		int c = alphabet.getChar(i);
		if (chars.find(c) != chars.end()) {
			return false;
		}
		chars.insert(c);
	}
	return true;
}

//------------------------------------------------------------------------------
TEST_F(IRAlphabetTest, Constructor) {
	IRAlphabet * a;

	for(int i = 2; i < 100; i++) {
		a = new IRDummyAlphabet(i);
		ASSERT_EQ(i, a->size());
		delete a;
	}
}

//------------------------------------------------------------------------------
TEST_F(IRAlphabetTest, ConstructorFail) {

	for (int i = -10; i < 2; i++) {
		try {
			IRAlphabet * a = new IRDummyAlphabet(1);
			FAIL();
			delete a;
		} catch (std::invalid_argument & e) {
		}
	}
}

//------------------------------------------------------------------------------
TEST_F(IRAlphabetTest, getValue) {
	IRDummyAlphabet a("01", 2);

	ASSERT_EQ(0, a.getValue('0'));
	ASSERT_EQ(1, a.getValue('1'));
	ASSERT_EQ(-1, a.getValue('2'));
}

//------------------------------------------------------------------------------
TEST_F(IRAlphabetTest, getChar) {
	IRDummyAlphabet a("01", 2);

	ASSERT_EQ('0', a.getChar(0));
	ASSERT_EQ('1', a.getChar(1));
	ASSERT_EQ('0', a.getChar(2));
}

//------------------------------------------------------------------------------
TEST_F(IRAlphabetTest, checkMapping) {
	IRDummyAlphabet a("01", 2);

	ASSERT_TRUE(checkMapping(a));
}

//------------------------------------------------------------------------------
TEST_F(IRAlphabetTest, checkMappingFail) {
	IRDummyAlphabet a("00", 2);

	ASSERT_FALSE(checkMapping(a));
}

//------------------------------------------------------------------------------
TEST_F(IRAlphabetTest, checkUniqueChars) {
	IRDummyAlphabet a("01", 2);

	ASSERT_TRUE(checkUniqueChars(a));
}

//------------------------------------------------------------------------------
TEST_F(IRAlphabetTest, checkUniqueCharsFail) {
	IRDummyAlphabet a("00", 2);

	ASSERT_FALSE(checkUniqueChars(a));
}
//------------------------------------------------------------------------------

