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

