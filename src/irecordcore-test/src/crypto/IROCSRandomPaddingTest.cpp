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
#include "IROCSRandomPaddingTest.h"
#include <irecordcore/irciphpd.h>
#include <ircommon/irrandom.h>
#include <cstring>

using namespace ircommon;
using namespace irecordcore::crypto;

//==============================================================================
// class IROCSRandomPaddingTest
//------------------------------------------------------------------------------
IROCSRandomPaddingTest::IROCSRandomPaddingTest() {
}

//------------------------------------------------------------------------------
IROCSRandomPaddingTest::~IROCSRandomPaddingTest() {
}

//------------------------------------------------------------------------------
void IROCSRandomPaddingTest::SetUp() {
}

//------------------------------------------------------------------------------
void IROCSRandomPaddingTest::TearDown() {
}

//------------------------------------------------------------------------------
TEST_F(IROCSRandomPaddingTest,Constructor) {
	IROCSRandomPadding * p;

	p = new IROCSRandomPadding(new IRXORShifRandom());
	delete p;
}

//------------------------------------------------------------------------------
TEST_F(IROCSRandomPaddingTest, addPadding) {
	IROCSRandomPadding p(new IRXORShifRandom(2258));
	IRXORShifRandom r(2258);
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
		r.nextBytes(exp + srcSize, paddingSize);
		exp[srcSize + paddingSize - 1] =
				exp[srcSize + paddingSize - 1] -
				(exp[srcSize + paddingSize - 1] % 16) + paddingSize;
		ASSERT_EQ(0, std::memcmp(exp, dst, dstSize));
	}
}

//------------------------------------------------------------------------------
TEST_F(IROCSRandomPaddingTest, removePadding) {
	IROCSRandomPadding p(new IRXORShifRandom(2258));
	IRXORShifRandom r(2258);
	std::uint8_t src[32];
	std::uint64_t srcSize;
	unsigned int paddingSize;

	std::memset(src, 0, sizeof(src));
	srcSize = 0;
	ASSERT_TRUE(p.removePadding(32, src, srcSize));
	ASSERT_EQ(0, srcSize);

	for (unsigned int last = 0; last < 256; last++) {
		r.nextBytes(src, sizeof(src));
		src[15] = last;
		paddingSize = last % 16;
		if (paddingSize == 0) {
			paddingSize = 16;
		}

		srcSize = 16;
		ASSERT_TRUE(p.removePadding(16, src, srcSize));
		ASSERT_EQ(16 - paddingSize, srcSize);
	}

	for (unsigned int last = 0; last < 256; last++) {
		r.nextBytes(src, sizeof(src));
		src[31] = last;
		paddingSize = last % 16;
		if (paddingSize == 0) {
			paddingSize = 16;
		}

		srcSize = 32;
		ASSERT_TRUE(p.removePadding(16, src, srcSize));
		ASSERT_EQ(32 - paddingSize, srcSize);
	}
}

//------------------------------------------------------------------------------

