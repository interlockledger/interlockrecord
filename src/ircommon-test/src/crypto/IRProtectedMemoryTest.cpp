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
#include "IRProtectedMemoryTest.h"
#include <ircommon/irpmem.h>
#include <cstring>
using namespace ircommon;
using namespace ircommon::crypto;

//==============================================================================
// class IRProtectedMemoryTest
//------------------------------------------------------------------------------
IRProtectedMemoryTest::IRProtectedMemoryTest() {
}

//------------------------------------------------------------------------------
IRProtectedMemoryTest::~IRProtectedMemoryTest() {
}

//------------------------------------------------------------------------------
void IRProtectedMemoryTest::SetUp() {
}

//------------------------------------------------------------------------------
void IRProtectedMemoryTest::TearDown() {
}

//------------------------------------------------------------------------------
TEST_F(IRProtectedMemoryTest,Constructor) {
	IRProtectedMemory * p;

	p = new IRProtectedMemory(10);
	ASSERT_EQ(10, p->size());
	delete p;
}

//------------------------------------------------------------------------------
TEST_F(IRProtectedMemoryTest, size) {

	for (int i = 1; i < 32; i++) {
		IRProtectedMemory p(i);
		ASSERT_EQ(i, p.size());
	}
}

//------------------------------------------------------------------------------
TEST_F(IRProtectedMemoryTest, value) {
	std::uint8_t exp[10];
	IRProtectedMemory p(sizeof(exp));
	std::uint8_t * v;

	v = p.value();
	ASSERT_TRUE(p.lock());
	ASSERT_EQ(v, p.value());
	ASSERT_TRUE(p.unlock());
	ASSERT_EQ(v, p.value());
}

//------------------------------------------------------------------------------
TEST_F(IRProtectedMemoryTest, protectUnprotect) {
	std::uint8_t exp[10];
	IRProtectedMemory p(sizeof(exp));

	std::memset(exp, 0, sizeof(exp));
	ASSERT_NE(0, std::memcmp(exp, p.value(), p.size()));
	ASSERT_TRUE(p.lock());
	ASSERT_EQ(0, std::memcmp(exp, p.value(), p.size()));
	ASSERT_TRUE(p.unlock());
	ASSERT_NE(0, std::memcmp(exp, p.value(), p.size()));

	// Set a value
	for (unsigned int i = 0; i < sizeof(exp); i++) {
		exp[i] = i;
	}
	ASSERT_TRUE(p.lock());
	std::memcpy(p.value(), exp, p.size());
	ASSERT_EQ(0, std::memcmp(exp, p.value(), p.size()));
	ASSERT_TRUE(p.unlock());
	ASSERT_NE(0, std::memcmp(exp, p.value(), p.size()));
	ASSERT_TRUE(p.lock());
	ASSERT_EQ(0, std::memcmp(exp, p.value(), p.size()));
	ASSERT_TRUE(p.unlock());
	ASSERT_NE(0, std::memcmp(exp, p.value(), p.size()));
}


//------------------------------------------------------------------------------

