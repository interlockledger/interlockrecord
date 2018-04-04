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
#include "IRBasicPaddingTest.h"
#include <irecordcore/irciphpd.h>
#include <cstring>

using namespace irecordcore::crypto;

//==============================================================================
// class IRDummyBasicPadding
//------------------------------------------------------------------------------
class IRDummyBasicPadding : public IRBasicPadding {
protected:
	virtual void createPadding(unsigned int blockSize, std::uint8_t * padding,
			unsigned int paddingSize) const;
public:
	IRDummyBasicPadding() = default;
	virtual ~IRDummyBasicPadding() = default;

	void expCreatePadding(unsigned int blockSize, std::uint8_t * padding,
			unsigned int paddingSize) const {
		this->createPadding(blockSize, padding, paddingSize);
	}

	unsigned int expExtractPaddingSize(unsigned int blockSize,
			const std::uint8_t * src,
			std::uint64_t srcSize) const {
		return this->extractPaddingSize(blockSize, src, srcSize);
	}

	bool expCheckPadding(const std::uint8_t * padding,
			unsigned int paddingSize) const {
		return this->checkPadding(padding, paddingSize);
	}
};

//------------------------------------------------------------------------------
void IRDummyBasicPadding::createPadding(unsigned int blockSize,
		std::uint8_t * padding, unsigned int paddingSize) const {
	std::memset(padding, paddingSize, paddingSize);
}

//==============================================================================
// class IRBasicPaddingTest
//------------------------------------------------------------------------------
IRBasicPaddingTest::IRBasicPaddingTest() {
}

//------------------------------------------------------------------------------
IRBasicPaddingTest::~IRBasicPaddingTest() {
}

//------------------------------------------------------------------------------
void IRBasicPaddingTest::SetUp() {
}

//------------------------------------------------------------------------------
void IRBasicPaddingTest::TearDown() {
}

//------------------------------------------------------------------------------
TEST_F(IRBasicPaddingTest,Constructor) {
	IRDummyBasicPadding * p;

	p = new IRDummyBasicPadding();
	delete p;
}

//------------------------------------------------------------------------------
TEST_F(IRBasicPaddingTest, createPadding) {
	IRDummyBasicPadding p;
	std::uint8_t buff[33];
	std::uint8_t exp[33];

	for (unsigned int paddingSize = 1; paddingSize < sizeof(buff); paddingSize++) {
		std::memset(buff, 0, sizeof(buff));
		std::memset(exp, paddingSize, sizeof(exp));
		p.expCreatePadding(0, buff, paddingSize);
		ASSERT_EQ(0, buff[paddingSize]);
		ASSERT_EQ(0, std::memcmp(buff, exp, paddingSize));
	}
}

//------------------------------------------------------------------------------
TEST_F(IRBasicPaddingTest, extractPaddingSize) {
	IRDummyBasicPadding p;
	std::uint8_t buff[32];

	for (unsigned int paddingSize = 1; paddingSize <= sizeof(buff); paddingSize++) {
		std::memset(buff, 0, sizeof(buff));
		buff[sizeof(buff) - 1] = paddingSize;
		ASSERT_EQ(paddingSize,
				p.expExtractPaddingSize(sizeof(buff), buff, sizeof(buff)));
	}

	std::memset(buff, 0, sizeof(buff));
	ASSERT_EQ(0, p.expExtractPaddingSize(sizeof(buff), buff, sizeof(buff)));

	for (unsigned int paddingSize = sizeof(buff) + 1; paddingSize < 256; paddingSize++) {
		std::memset(buff, 0, sizeof(buff));
		buff[sizeof(buff) - 1] = paddingSize;
		ASSERT_EQ(0, p.expExtractPaddingSize(sizeof(buff), buff, sizeof(buff)));
	}
}

//------------------------------------------------------------------------------
TEST_F(IRBasicPaddingTest, checkPadding) {
	IRDummyBasicPadding p;
	std::uint8_t buff[32];

	for (unsigned int paddingSize = 0; paddingSize <= sizeof(buff); paddingSize++) {
		std::memset(buff, 0, sizeof(buff));
		ASSERT_TRUE(p.expCheckPadding(buff, paddingSize));
	}
	ASSERT_TRUE(p.expCheckPadding(nullptr, 0));
}

//------------------------------------------------------------------------------
TEST_F(IRBasicPaddingTest, getPaddingSize) {
	IRDummyBasicPadding p;

	for (unsigned int blockSize = 1; blockSize <= 8; blockSize++) {
		for (std::uint64_t srcSize = 0; srcSize <= 16; srcSize++) {
			ASSERT_EQ(blockSize - (srcSize % blockSize),
					p.getPaddingSize(blockSize, srcSize));
		}
	}
}

//------------------------------------------------------------------------------
TEST_F(IRBasicPaddingTest, addPadding) {
	IRDummyBasicPadding p;
	std::uint8_t src[32];
	std::uint8_t dst[32];
	std::uint8_t exp[32];
	std::uint64_t srcSize;
	std::uint64_t dstSize;
	unsigned int paddingSize;

	for (srcSize = 0; srcSize < 16; srcSize++) {
		std::memset(src, 0xFF, sizeof(src));
		std::memset(dst, 0x00, sizeof(dst));

		dstSize = sizeof(dst);
		ASSERT_TRUE(p.addPadding(16, src, srcSize, dst, dstSize));
		ASSERT_EQ(16, dstSize);
		ASSERT_EQ(0, dst[16]);

		paddingSize = 16 - srcSize;
		std::memset(exp, 0xFF, sizeof(exp));
		std::memset(exp + srcSize, paddingSize, paddingSize);

		ASSERT_EQ(0xFF, exp[16]);
		ASSERT_EQ(0, std::memcmp(dst, exp, 16));
	}

	for (srcSize = 0; srcSize < 16; srcSize++) {
		std::memset(src, 0xFF, sizeof(src));
		std::memset(dst, 0x00, sizeof(dst));

		dstSize = 16;
		ASSERT_TRUE(p.addPadding(16, src, srcSize, dst, dstSize));
		ASSERT_EQ(16, dstSize);
		ASSERT_EQ(0, dst[16]);

		paddingSize = 16 - srcSize;
		std::memset(exp, 0xFF, sizeof(exp));
		std::memset(exp + srcSize, paddingSize, paddingSize);

		ASSERT_EQ(0xFF, exp[16]);
		ASSERT_EQ(0, std::memcmp(dst, exp, 16));
	}

	for (srcSize = 0; srcSize < 16; srcSize++) {
		std::memset(dst, 0xFF, sizeof(dst));

		dstSize = sizeof(dst);
		ASSERT_TRUE(p.addPadding(16, dst, srcSize, dst, dstSize));
		ASSERT_EQ(16, dstSize);
		ASSERT_EQ(0xFF, dst[16]);

		paddingSize = 16 - srcSize;
		std::memset(exp, 0xFF, sizeof(exp));
		std::memset(exp + srcSize, paddingSize, paddingSize);

		ASSERT_EQ(0xFF, exp[16]);
		ASSERT_EQ(0, std::memcmp(dst, exp, 16));
	}

	// Failure
	for (srcSize = 0; srcSize < 16; srcSize++) {
		std::memset(src, 0xFF, sizeof(src));
		std::memset(dst, 0x00, sizeof(dst));

		dstSize = 15;
		ASSERT_FALSE(p.addPadding(16, src, srcSize, dst, dstSize));
		ASSERT_EQ(15, dstSize);

		std::memset(exp, 0x00, sizeof(exp));
		ASSERT_EQ(0, std::memcmp(dst, exp, sizeof(exp)));
	}
}

//------------------------------------------------------------------------------
TEST_F(IRBasicPaddingTest, removePadding) {
	IRDummyBasicPadding p;
	std::uint8_t buff[32];
	std::uint64_t srcSize;

	std::memset(buff, 0, sizeof(buff));
	srcSize = 0;
	ASSERT_TRUE(p.removePadding(32, buff, srcSize));
	ASSERT_EQ(0, srcSize);

	std::memset(buff, 0, sizeof(buff));
	for (unsigned int paddingSize = 1; paddingSize <= sizeof(buff); paddingSize++) {
		buff[sizeof(buff) - 1] = paddingSize;
		srcSize = sizeof(buff);
		ASSERT_TRUE(p.removePadding(32, buff, srcSize));
		ASSERT_EQ(sizeof(buff) - paddingSize, srcSize);
	}

	buff[sizeof(buff) - 1] = 0;
	srcSize = sizeof(buff);
	ASSERT_FALSE(p.removePadding(32, buff, srcSize));
	ASSERT_EQ(sizeof(buff), srcSize);

	buff[sizeof(buff) - 1] = 33;
	srcSize = sizeof(buff);
	ASSERT_FALSE(p.removePadding(32, buff, srcSize));
	ASSERT_EQ(sizeof(buff), srcSize);

	buff[sizeof(buff) - 1] = 1;
	srcSize = sizeof(buff) - 1;
	ASSERT_FALSE(p.removePadding(32, buff, srcSize));
	ASSERT_EQ(sizeof(buff)- 1, srcSize);
}

//------------------------------------------------------------------------------

