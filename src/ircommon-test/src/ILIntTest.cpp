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
TEST_F(ILIntTest, encode_SingleByte) {
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
TEST_F(ILIntTest, encode_MultiByte) {
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
TEST_F(ILIntTest, decode_SingleByte) {
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
TEST_F(ILIntTest, decode_MultiByte) {
	uint8_t enc[16];
	uint64_t v;

	memset(enc, 0xA5, sizeof(enc));
	int size = 2;
	uint64_t exp = 0xA5;
	for (int i = 0xF8; i <= 0xFF; i++, size++) {
		enc[1] = i;
		ASSERT_EQ(size, ILInt::decode(enc + 1, size, &v));
		ASSERT_EQ(exp + 0xF8, v);
		exp = (exp << 8) | 0xA5;
		// Fail
		ASSERT_EQ(0, ILInt::decode(enc + 1, size - 1, &v));
	}

	// Borderline
	memset(enc, 0xFF, sizeof(enc));
	enc[9] = 0x07;
	ASSERT_EQ(9, ILInt::decode(enc + 1, 9, &v));
	ASSERT_EQ(0xFFFFFFFFFFFFFFFFll, v);

	enc[9] = 0x08;
	ASSERT_EQ(0, ILInt::decode(enc + 1, 9, &v));
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
TEST_F(ILIntTest, encodedSize) {

	for (int prefix = 0; prefix < 0xF8; prefix++) {
		ASSERT_EQ(1, ILInt::encodedSize(prefix));
	}
	ASSERT_EQ(2, ILInt::encodedSize(0xF8));
	ASSERT_EQ(3, ILInt::encodedSize(0xF9));
	ASSERT_EQ(4, ILInt::encodedSize(0xFA));
	ASSERT_EQ(5, ILInt::encodedSize(0xFB));
	ASSERT_EQ(6, ILInt::encodedSize(0xFC));
	ASSERT_EQ(7, ILInt::encodedSize(0xFD));
	ASSERT_EQ(8, ILInt::encodedSize(0xFE));
	ASSERT_EQ(9, ILInt::encodedSize(0xFF));
}
//------------------------------------------------------------------------------

