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
#include "ILIntTest.h"
#include <ircommon/ilint.h>

using namespace ircommon;

//==============================================================================
// class ILIntTest
//------------------------------------------------------------------------------
ILIntTest::ILIntTest() {
}

//------------------------------------------------------------------------------
ILIntTest::~ILIntTest() {
}

//------------------------------------------------------------------------------
void ILIntTest::SetUp() {
}

//------------------------------------------------------------------------------
void ILIntTest::TearDown() {
}

//------------------------------------------------------------------------------
TEST_F(ILIntTest, Size) {

	ASSERT_EQ(1, ILInt::size(0));
	ASSERT_EQ(1, ILInt::size(247));

	ASSERT_EQ(2, ILInt::size(248));
	ASSERT_EQ(2, ILInt::size(0xFF + 248));

	ASSERT_EQ(3, ILInt::size(0xFF + 248 + 1));
	ASSERT_EQ(3, ILInt::size(0xFFFF + 248));

	ASSERT_EQ(4, ILInt::size(0xFFFF + 248 + 1));
	ASSERT_EQ(4, ILInt::size(0xFFFFFF + 248));

	ASSERT_EQ(5, ILInt::size(0xFFFFFF + 248 + 1));
	ASSERT_EQ(5, ILInt::size(0xFFFFFFFFll + 248));

	ASSERT_EQ(6, ILInt::size(0xFFFFFFFFll + 248 + 1));
	ASSERT_EQ(6, ILInt::size(0xFFFFFFFFFFll + 248));

	ASSERT_EQ(7, ILInt::size(0xFFFFFFFFFFll + 248 + 1));
	ASSERT_EQ(7, ILInt::size(0xFFFFFFFFFFFFll + 248));

	ASSERT_EQ(8, ILInt::size(0xFFFFFFFFFFFFll + 248 + 1));
	ASSERT_EQ(8, ILInt::size(0xFFFFFFFFFFFFFFll + 248));

	ASSERT_EQ(9, ILInt::size(0xFFFFFFFFFFFFFFll + 248 + 1));
	ASSERT_EQ(9, ILInt::size(0xFFFFFFFFFFFFFFFFll));
}

//------------------------------------------------------------------------------
TEST_F(ILIntTest, ILIntEncode_SingleByte) {
	uint8_t enc[16];
	int encSize;

	for (uint64_t v = 0; v < 248; v++) {
		memset(enc, 0xFF, sizeof(enc));
		encSize = ILInt::encode(v, enc + 1, sizeof(enc) - 1);
		ASSERT_EQ(1, encSize);
		ASSERT_EQ(0xFF, enc[0]);
		ASSERT_EQ(v, enc[1]);
		ASSERT_EQ(0xFF, enc[2]);
	}

	ASSERT_EQ(0, ILInt::encode(1, enc, 0));
	for (uint64_t v = 248; v < 256; v++) {
		ASSERT_EQ(0, ILInt::encode(v, enc, 1));
	}
}

//------------------------------------------------------------------------------
TEST_F(ILIntTest, ILIntEncode_MultiByte) {
	uint8_t enc[16];
	int encSize;
	int i;
	uint64_t v;
	uint64_t addition;

	// Lower bound
	memset(enc, 0xA5, sizeof(enc));
	v = 248;
	encSize = ILInt::encode(v, enc + 1, sizeof(enc) - 1);
	ASSERT_EQ(2, encSize);
	ASSERT_EQ(0xA5, enc[0]);
	ASSERT_EQ(248, enc[1]);
	ASSERT_EQ(0, enc[2]);
	ASSERT_EQ(0xA5, enc[3]);

	addition = 0x100;
	for (int size = 3; size < 10; size++) {
		v = 248 + addition;
		memset(enc, 0xA5, sizeof(enc));
		encSize = ILInt::encode(v, enc + 1, sizeof(enc) - 1);
		ASSERT_EQ(size, encSize);
		ASSERT_EQ(0xA5, enc[0]);
		ASSERT_EQ(248 + (size - 2), enc[1]);
		ASSERT_EQ(0x1, enc[2]);
		for (i = 3; i < size + 1; i++) {
			ASSERT_EQ(0x0, enc[i]);
		}
		ASSERT_EQ(0xA5, enc[i]);
		addition = addition << 8;
	}

	// Upper bound
	addition = 0xFFFF;
	for (int size = 3; size < 9; size++) {
		v = 248 + addition;
		memset(enc, 0xA5, sizeof(enc));
		encSize = ILInt::encode(v, enc + 1, sizeof(enc) - 1);
		ASSERT_EQ(size, encSize);
		ASSERT_EQ(0xA5, enc[0]);
		ASSERT_EQ(248 + (size - 2), enc[1]);
		for (i = 2; i < size + 1; i++) {
			ASSERT_EQ(0xFF, enc[i]);
		}
		ASSERT_EQ(0xA5, enc[i]);
		addition = (addition << 8) | 0xFF;
	}

	// Max value
	memset(enc, 0xA5, sizeof(enc));
	v = 0xFFFFFFFFFFFFFFFFl;
	encSize = ILInt::encode(v, enc + 1, sizeof(enc) - 1);
	ASSERT_EQ(9, encSize);
	ASSERT_EQ(0xA5, enc[0]);
	ASSERT_EQ(248 + 7, enc[1]);
	ASSERT_EQ(0xFF, enc[2]);
	ASSERT_EQ(0xFF, enc[3]);
	ASSERT_EQ(0xFF, enc[4]);
	ASSERT_EQ(0xFF, enc[5]);
	ASSERT_EQ(0xFF, enc[6]);
	ASSERT_EQ(0xFF, enc[7]);
	ASSERT_EQ(0xFF, enc[8]);
	ASSERT_EQ(0x07, enc[9]);
	ASSERT_EQ(0xA5, enc[10]);
}

//------------------------------------------------------------------------------
TEST_F(ILIntTest, ILIntDecode_SingleByte) {
	uint8_t enc[16];
	uint64_t v;

	memset(enc, 0xA5, sizeof(enc));
	for (int i = 0; i < 248; i++) {
		memset(enc, 0xFF, sizeof(enc));
		enc[1] = i;
		ASSERT_EQ(1, ILInt::decode(enc + 1, 1, &v));
		ASSERT_EQ(i, v);

	}

	ASSERT_EQ(0, ILInt::decode(enc + 1, 0, &v));
	for (int i = 248; i < 256; i++) {
		memset(enc, 0xFF, sizeof(enc));
		enc[1] = i;
		ASSERT_EQ(0, ILInt::decode(enc + 1, 1, &v));

	}

}

//------------------------------------------------------------------------------
TEST_F(ILIntTest, ILIntDecode_MultiByte) {
	//TODO Implement it later
}

//------------------------------------------------------------------------------
TEST_F(ILIntTest, ILIntEncodeDecode) {
	uint64_t v;
	uint64_t vDec;
	uint8_t enc[16];
	int encSize;

	for (int i = 0; i < 10000; i++) {
		v = rand() | ((uint64_t)rand() << 32);
		// Encode
		memset(enc, 0xA5, sizeof(enc));
		encSize = ILInt::encode(v, enc + 1, sizeof(enc) - 1);
		// Test guard
		ASSERT_EQ(0xA5, enc[0]);
		ASSERT_EQ(0xA5, enc[encSize + 1]);

		// Decode
		ASSERT_EQ(encSize, ILInt::decode(enc + 1, encSize, &vDec));
		ASSERT_EQ(v, vDec);
	}
}
//------------------------------------------------------------------------------

