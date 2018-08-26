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
#include "IRSharedPtrHandleListTest.h"
#include <ircommon/irrwlock.h>
#include <ircommon/irhndlst.h>
#include <string>
using namespace ircommon;

//==============================================================================
// class IRSharedPtrHandleListTest
//------------------------------------------------------------------------------
IRSharedPtrHandleListTest::IRSharedPtrHandleListTest() {
}

//------------------------------------------------------------------------------
IRSharedPtrHandleListTest::~IRSharedPtrHandleListTest() {
}

//------------------------------------------------------------------------------
void IRSharedPtrHandleListTest::SetUp() {
}

//------------------------------------------------------------------------------
void IRSharedPtrHandleListTest::TearDown() {
}

//------------------------------------------------------------------------------
TEST_F(IRSharedPtrHandleListTest,Constructor) {
	IRSharedPtrHandleList<std::string> * l;

	l = new IRSharedPtrHandleList<std::string>(0);
	delete l;
}

//------------------------------------------------------------------------------
TEST_F(IRSharedPtrHandleListTest, InsertPtr) {
	IRSharedPtrHandleList<std::string> l(0);

	for (int i = 0; i < 10; i++) {
		l.insertPtr(new std::string("a"));
	}
	ASSERT_EQ(10, l.size());

	l.insert(IRSharedPtrHandleList<std::string>::SharedPointer(
			new std::string("1")));
	ASSERT_EQ(11, l.size());
}
//------------------------------------------------------------------------------

