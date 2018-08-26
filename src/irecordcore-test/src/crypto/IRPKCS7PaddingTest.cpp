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
#include "IRPKCS7PaddingTest.h"
#include <irecordcore/irciphpd.h>
#include <cstring>

using namespace irecordcore::crypto;

//==============================================================================
// class IRPKCS7PaddingTest
//------------------------------------------------------------------------------
IRPKCS7PaddingTest::IRPKCS7PaddingTest() {
}

//------------------------------------------------------------------------------
IRPKCS7PaddingTest::~IRPKCS7PaddingTest() {
}

//------------------------------------------------------------------------------
void IRPKCS7PaddingTest::SetUp() {
}

//------------------------------------------------------------------------------
void IRPKCS7PaddingTest::TearDown() {
}

//------------------------------------------------------------------------------
TEST_F(IRPKCS7PaddingTest, Constructor) {
	IRPKCS7Padding * p;

	p = new IRPKCS7Padding();
	delete p;
}

//------------------------------------------------------------------------------
TEST_F(IRPKCS7PaddingTest, addPadding) {
	IRPKCS7Padding p;
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
		std::memset(exp + srcSize, paddingSize, paddingSize);
		ASSERT_EQ(0, std::memcmp(exp, dst, dstSize));
	}
}

//------------------------------------------------------------------------------
TEST_F(IRPKCS7PaddingTest, removePadding) {
	IRPKCS7Padding p;
	std::uint8_t src[32];
	std::uint64_t srcSize;

	std::memset(src, 0, sizeof(src));
	srcSize = 0;
	ASSERT_TRUE(p.removePadding(32, src, srcSize));
	ASSERT_EQ(0, srcSize);

	for (unsigned int paddingSize = 1; paddingSize <= 16; paddingSize++) {
		srcSize = 16 - paddingSize;
		std::memset(src, 0, sizeof(src));
		std::memset(src + srcSize, paddingSize, paddingSize);

		srcSize = 16;
		ASSERT_TRUE(p.removePadding(16, src, srcSize));
		ASSERT_EQ(16 - paddingSize, srcSize);
	}

	for (unsigned int paddingSize = 1; paddingSize <= 16; paddingSize++) {
		srcSize = 16 - paddingSize;
		std::memset(src, 0, sizeof(src));
		std::memset(src + 16 + srcSize, paddingSize, paddingSize);

		srcSize = sizeof(src);
		ASSERT_TRUE(p.removePadding(16, src, srcSize));
		ASSERT_EQ(sizeof(src) - paddingSize, srcSize);
	}

	// Broken padding
	for (unsigned int paddingSize = 2; paddingSize <= 16; paddingSize++) {
		srcSize = 16 - paddingSize;
		std::memset(src, 0, sizeof(src));
		std::memset(src + srcSize, paddingSize, paddingSize);

		std::uint8_t tmp2[32];
		for (unsigned int i = 1; i < paddingSize; i++) {
			std::memcpy(tmp2, src, sizeof(tmp2));
			tmp2[15 - i]++;
			srcSize = 16;
			ASSERT_FALSE(p.removePadding(16, tmp2, srcSize));
			ASSERT_EQ(16, srcSize);
		}
	}

	// Invalid padding size
	for (unsigned int paddingSize = 17; paddingSize < 256; paddingSize++) {
		std::memset(src, paddingSize, sizeof(src));

		srcSize = 16;
		ASSERT_FALSE(p.removePadding(16, src, srcSize));
			ASSERT_EQ(16, srcSize);
	}
}

//------------------------------------------------------------------------------

