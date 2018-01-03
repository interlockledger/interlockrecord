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
#include "IRAlphabetTest.h"
#include <set>

#include <ircommon/iralphab.h>

using namespace ircommon;

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
bool IRAlphabetTest::checkMapping(ircommon::IRAlphabet & alphabet) {

	for (int i = 0; i < alphabet.size(); i++) {
		int c = alphabet.getChar(i);
		if ((alphabet.getValue(c)) != i) {
			return false;
		}
	}
	return true;
}

//------------------------------------------------------------------------------
bool IRAlphabetTest::checkUniqueChars(ircommon::IRAlphabet & alphabet) {

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

