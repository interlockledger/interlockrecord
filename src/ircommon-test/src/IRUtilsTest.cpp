/*
 * Copyright (c) 2017, Open Communications Security
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
#include "IRUtilsTest.h"
#include <ircommon/irutils.h>

#include <cstdint>

using namespace std;
using namespace ircommon;

//==============================================================================
// class IRUtilsTest
//------------------------------------------------------------------------------
IRUtilsTest::IRUtilsTest() {
}

//------------------------------------------------------------------------------
IRUtilsTest::~IRUtilsTest() {
}

//------------------------------------------------------------------------------
void IRUtilsTest::SetUp() {
}

//------------------------------------------------------------------------------
void IRUtilsTest::TearDown() {
}

//------------------------------------------------------------------------------
TEST_F(IRUtilsTest, getPaddingSizeUInt64) {
	uint64_t blockSize;

	blockSize = 16;
	ASSERT_EQ(blockSize, IRUtils::getPaddingSize(uint64_t(0), blockSize));
	for (uint64_t v = 1; v < blockSize; v++) {
		ASSERT_EQ(blockSize - (v % blockSize), IRUtils::getPaddingSize(v, blockSize));
	}
}

//------------------------------------------------------------------------------
TEST_F(IRUtilsTest, getPaddingSizeUInt32) {
	uint32_t blockSize;

	blockSize = 13;
	ASSERT_EQ(blockSize, IRUtils::getPaddingSize(uint32_t(0), blockSize));
	for (uint32_t v = 1; v < blockSize; v++) {
		ASSERT_EQ(blockSize - (v % blockSize), IRUtils::getPaddingSize(v, blockSize));
	}
}

//------------------------------------------------------------------------------
TEST_F(IRUtilsTest, getPaddedSizeUInt64) {
	uint64_t blockSize;

	blockSize = 16;
	for (uint64_t v = 0; v <= blockSize * 4; v++) {
		ASSERT_EQ(
				blockSize * ((v / blockSize) + 1),
				IRUtils::getPaddedSize(v, blockSize));
	}
}

//------------------------------------------------------------------------------
TEST_F(IRUtilsTest, getPaddedSizeUInt32) {
	uint32_t blockSize;

	blockSize = 13;
	for (uint32_t v = 0; v <= blockSize * 4; v++) {
		ASSERT_EQ(
				blockSize * ((v / blockSize) + 1),
				IRUtils::getPaddedSize(v, blockSize));
	}
}

//------------------------------------------------------------------------------
TEST_F(IRUtilsTest, getPaddedSizeBestFitUInt64) {
	uint64_t blockSize;

	blockSize = 16;
	for (uint64_t v = 0; v <= blockSize * 4; v++) {
		int add = std::min(v % blockSize, uint64_t(1));
		ASSERT_EQ(
				blockSize * ((v / blockSize) + add),
				IRUtils::getPaddedSizeBestFit(v, blockSize));
	}
}

//------------------------------------------------------------------------------
TEST_F(IRUtilsTest, getPaddedSizeBestFitUInt32) {
	uint32_t blockSize;

	blockSize = 13;
	for (uint32_t v = 0; v <= blockSize * 4; v++) {
		int add = std::min(v % blockSize, uint32_t(1));
		ASSERT_EQ(
				blockSize * ((v / blockSize) + add),
				IRUtils::getPaddedSizeBestFit(v, blockSize));
	}
}

//------------------------------------------------------------------------------
const static std::uint8_t BE_SAMPLE[8] = {
		0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF};

TEST_F(IRUtilsTest, BE2Int16) {
	uint16_t v;

	IRUtils::BE2Int(BE_SAMPLE, v);
	ASSERT_EQ(0x0123, v);
}

//------------------------------------------------------------------------------
TEST_F(IRUtilsTest, BE2IntU16) {
	int16_t v;

	IRUtils::BE2Int(BE_SAMPLE, v);
	ASSERT_EQ(0x0123, v);
}

//------------------------------------------------------------------------------
TEST_F(IRUtilsTest, BE2Int32) {
	uint32_t v;

	IRUtils::BE2Int(BE_SAMPLE, v);
	ASSERT_EQ(0x01234567, v);
}

//------------------------------------------------------------------------------
TEST_F(IRUtilsTest, BE2IntU32) {
	int32_t v;

	IRUtils::BE2Int(BE_SAMPLE, v);
	ASSERT_EQ(0x01234567, v);
}

//------------------------------------------------------------------------------
TEST_F(IRUtilsTest, BE2Int64) {
	uint64_t v;

	IRUtils::BE2Int(BE_SAMPLE, v);
	ASSERT_EQ(0x0123456789ABCDEFll, v);
}

//------------------------------------------------------------------------------
TEST_F(IRUtilsTest, BE2IntU64) {
	int64_t v;

	IRUtils::BE2Int(BE_SAMPLE, v);
	ASSERT_EQ(0x0123456789ABCDEFll, v);
}

//------------------------------------------------------------------------------
TEST_F(IRUtilsTest, Int2BE16) {
	uint8_t * buff;
	int16_t v;

	v = 0x0123;
	buff = new uint8_t[sizeof(v)];
	IRUtils::int2BE(v, buff);
	ASSERT_EQ(0, memcmp(buff, BE_SAMPLE, sizeof(v)));
	delete [] buff;
}

//------------------------------------------------------------------------------
TEST_F(IRUtilsTest, Int2BEU16) {
	uint8_t * buff;
	uint16_t v;

	v = 0x0123;
	buff = new uint8_t[sizeof(v)];
	IRUtils::int2BE(v, buff);
	ASSERT_EQ(0, memcmp(buff, BE_SAMPLE, sizeof(v)));
	delete [] buff;
}

//------------------------------------------------------------------------------
TEST_F(IRUtilsTest, Int2BE32) {
	uint8_t * buff;
	int32_t v;

	v = 0x01234567;
	buff = new uint8_t[sizeof(v)];
	IRUtils::int2BE(v, buff);
	ASSERT_EQ(0, memcmp(buff, BE_SAMPLE, sizeof(v)));
	delete [] buff;
}

//------------------------------------------------------------------------------
TEST_F(IRUtilsTest, Int2BEU32) {
	uint8_t * buff;
	uint32_t v;

	v = 0x01234567;
	buff = new uint8_t[sizeof(v)];
	IRUtils::int2BE(v, buff);
	ASSERT_EQ(0, memcmp(buff, BE_SAMPLE, sizeof(v)));
	delete [] buff;
}

//------------------------------------------------------------------------------
TEST_F(IRUtilsTest, Int2BE64) {
	uint8_t * buff;
	int64_t v;

	v = 0x0123456789ABCDEFll;
	buff = new uint8_t[sizeof(v)];
	IRUtils::int2BE(v, buff);
	ASSERT_EQ(0, memcmp(buff, BE_SAMPLE, sizeof(v)));
	delete [] buff;
}

//------------------------------------------------------------------------------
TEST_F(IRUtilsTest, Int2BEU64) {
	uint8_t * buff;
	uint64_t v;

	v = 0x0123456789ABCDEFll;
	buff = new uint8_t[sizeof(v)];
	IRUtils::int2BE(v, buff);
	ASSERT_EQ(0, memcmp(buff, BE_SAMPLE, sizeof(v)));
	delete [] buff;
}

//------------------------------------------------------------------------------
TEST_F(IRUtilsTest, clearMemory) {
	std::uint8_t * buff;
	int size;

	size = 32;
	buff = new std::uint8_t[size];
	for (int i = 0; i < size; i++) {
		buff[i] = 0xFF;
	}
	IRUtils::clearMemory(buff, size);
	for (int i = 0; i < size; i++) {
		ASSERT_EQ(0, buff[i]);
	}
	delete [] buff;
	buff = nullptr;
	IRUtils::clearMemory(buff, size);
}

//------------------------------------------------------------------------------
TEST_F(IRUtilsTest, lockUnlockMemory) {
	std::uint8_t * buff;
	int size;

	size = 32;
	buff = new std::uint8_t[size];
	ASSERT_TRUE(IRUtils::lockMemory(buff, size));
	ASSERT_TRUE(IRUtils::unlockMemory(buff, size));
	delete [] buff;
}


//------------------------------------------------------------------------------



