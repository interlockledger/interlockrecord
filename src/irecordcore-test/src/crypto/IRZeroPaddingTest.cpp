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
#include "IRZeroPaddingTest.h"
#include <irecordcore/irciphpd.h>
#include <cstring>

using namespace irecordcore::crypto;

//==============================================================================
// class IRZeroPaddingTest
//------------------------------------------------------------------------------
IRZeroPaddingTest::IRZeroPaddingTest() {
}

//------------------------------------------------------------------------------
IRZeroPaddingTest::~IRZeroPaddingTest() {
}

//------------------------------------------------------------------------------
void IRZeroPaddingTest::SetUp() {
}

//------------------------------------------------------------------------------
void IRZeroPaddingTest::TearDown() {
}

//------------------------------------------------------------------------------
TEST_F(IRZeroPaddingTest, Constructor) {
	IRZeroPadding * p;

	p = new IRZeroPadding();
	delete p;
}

//------------------------------------------------------------------------------
TEST_F(IRZeroPaddingTest, addPadding) {
	IRZeroPadding p;
	std::uint8_t src[33];
	std::uint8_t dst[33];
	std::uint8_t exp[33];
	std::uint64_t srcSize;
	std::uint64_t dstSize;
	unsigned int paddingSize;

	for (srcSize = 0; srcSize <= 16; srcSize++) {
		std::memset(src, 1, sizeof(src));
		std::memset(dst, 2, sizeof(dst));

		paddingSize = 16 - (srcSize % 16);
		dstSize = sizeof(dst);
		ASSERT_TRUE(p.addPadding(16, src, srcSize, dst, dstSize));
		ASSERT_EQ(srcSize + paddingSize, dstSize);
		ASSERT_EQ(2, dst[dstSize]);

		std::memset(exp, 1, srcSize);
		std::memset(exp + srcSize, 0, paddingSize);
		ASSERT_EQ(0, std::memcmp(exp, dst, dstSize));
	}
}

//------------------------------------------------------------------------------
TEST_F(IRZeroPaddingTest, removePadding) {
	IRZeroPadding p;
	std::uint8_t src[32];
	std::uint64_t srcSize;

	std::memset(src, 0, sizeof(src));
	srcSize = 0;
	ASSERT_TRUE(p.removePadding(32, src, srcSize));
	ASSERT_EQ(0, srcSize);

	for (unsigned int paddingSize = 1; paddingSize <= 16; paddingSize++) {
		std::memset(src, 0, sizeof(src));
		std::memset(src, 1, 16 - paddingSize);

		srcSize = 16;
		ASSERT_TRUE(p.removePadding(16, src, srcSize));
		ASSERT_EQ(16 - paddingSize, srcSize);
	}

	for (unsigned int paddingSize = 1; paddingSize <= 16; paddingSize++) {
		std::memset(src, 0, sizeof(src));
		std::memset(src + 16, 1, 16 - paddingSize);

		srcSize = sizeof(src);
		ASSERT_TRUE(p.removePadding(16, src, srcSize));
		ASSERT_EQ(sizeof(src) - paddingSize, srcSize);
	}
}

//------------------------------------------------------------------------------
