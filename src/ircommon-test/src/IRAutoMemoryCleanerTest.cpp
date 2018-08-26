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
#include "IRAutoMemoryCleanerTest.h"
#include <ircommon/irutils.h>

#include <cstdint>
#include <cstring>

using namespace std;
using namespace ircommon;

//==============================================================================
// class IRAutoMemoryCleanerTest
//------------------------------------------------------------------------------
IRAutoMemoryCleanerTest::IRAutoMemoryCleanerTest() {
}

//------------------------------------------------------------------------------
IRAutoMemoryCleanerTest::~IRAutoMemoryCleanerTest() {
}

//------------------------------------------------------------------------------
void IRAutoMemoryCleanerTest::SetUp() {
}

//------------------------------------------------------------------------------
void IRAutoMemoryCleanerTest::TearDown() {
}

//------------------------------------------------------------------------------
TEST_F(IRAutoMemoryCleanerTest, Constructor) {
	std::uint8_t exp[65];
	IRUtils::IRAutoMemoryCleaner * c;

	for (unsigned int size = 1; size < sizeof(exp); size++) {
		std::uint8_t * buff = new std::uint8_t[size + 1];
		std::memset(buff, 0x1, size + 1);
		std::memset(exp, 0x1, size + 1);

		c = new IRUtils::IRAutoMemoryCleaner(buff, size);
		ASSERT_EQ(0, std::memcmp(buff, exp, size + 1));
		delete c;
		ASSERT_EQ(0x1, buff[size]);
		std::memset(exp, 0x0, size);
		ASSERT_EQ(0, std::memcmp(buff, exp, size));

		delete [] buff;
	}
}

//------------------------------------------------------------------------------
TEST_F(IRAutoMemoryCleanerTest, Destructor) {
	std::uint8_t buff[65];
	std::uint8_t exp[65];

	for (unsigned int size = 0; size <= 64; size++) {
		std::memset(buff, 0xFA, sizeof(buff));
		std::memset(exp, 0xFA, sizeof(exp));
		{
			IRUtils::IRAutoMemoryCleaner c(buff, size);
			ASSERT_EQ(0, std::memcmp(exp, buff, size));
		}
		ASSERT_EQ(0xFA, buff[size]);
		std::memset(exp, 0x0, sizeof(exp));
		ASSERT_EQ(0, std::memcmp(exp, buff, size));
	}
}

//------------------------------------------------------------------------------
TEST_F(IRAutoMemoryCleanerTest, clear) {
	std::uint8_t buff[65];
	std::uint8_t exp[65];

	std::memset(exp, 0x0, sizeof(exp));
	for (unsigned int size = 0; size <= 64; size++) {
		std::memset(buff, 0xFA, sizeof(buff));
		{
			IRUtils::IRAutoMemoryCleaner c(buff, size);
			c.clear();
			ASSERT_EQ(0xFA, buff[size]);
			ASSERT_EQ(0, std::memcmp(exp, buff, size));
			std::memset(buff, 0xFA, sizeof(buff));
		}
		ASSERT_EQ(0xFA, buff[size]);
		ASSERT_EQ(0, std::memcmp(exp, buff, size));
	}
}

//------------------------------------------------------------------------------

