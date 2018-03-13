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

