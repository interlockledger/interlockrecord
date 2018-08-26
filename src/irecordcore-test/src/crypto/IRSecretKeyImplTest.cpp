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
#include "IRSecretKeyImplTest.h"
#include <irecordcore/irkey.h>
#include <ircommon/irbuffer.h>
#include <cstring>

using namespace irecordcore;
using namespace irecordcore::crypto;

// "It was the dawn of the third age of mankind"
const std::uint8_t IRSecretKeyImplTest_SAMPLE[43] = {
		0x49, 0x74, 0x20, 0x77, 0x61, 0x73, 0x20, 0x74,
		0x68, 0x65, 0x20, 0x64, 0x61, 0x77, 0x6e, 0x20,
		0x6f, 0x66, 0x20, 0x74, 0x68, 0x65, 0x20, 0x74,
		0x68, 0x69, 0x72, 0x64, 0x20, 0x61, 0x67, 0x65,
		0x20, 0x6f, 0x66, 0x20, 0x6d, 0x61, 0x6e, 0x6b,
		0x69, 0x6e, 0x64};

//==============================================================================
// class IRSecretKeyImplTest
//------------------------------------------------------------------------------
IRSecretKeyImplTest::IRSecretKeyImplTest() {
}

//------------------------------------------------------------------------------
IRSecretKeyImplTest::~IRSecretKeyImplTest() {
}

//------------------------------------------------------------------------------
void IRSecretKeyImplTest::SetUp() {
}

//------------------------------------------------------------------------------
void IRSecretKeyImplTest::TearDown() {
}

//------------------------------------------------------------------------------
TEST_F(IRSecretKeyImplTest,Constructor) {
	IRSecretKeyImpl * k;

	k = new IRSecretKeyImpl(IRSecretKeyImplTest_SAMPLE,
			sizeof(IRSecretKeyImplTest_SAMPLE));
	delete k;
}

//------------------------------------------------------------------------------
TEST_F(IRSecretKeyImplTest, exportable) {
	IRSecretKeyImpl k(IRSecretKeyImplTest_SAMPLE,
			sizeof(IRSecretKeyImplTest_SAMPLE));
	ASSERT_TRUE(k.exportable());
}

//------------------------------------------------------------------------------
TEST_F(IRSecretKeyImplTest, size) {

	for (unsigned int size = 1; size <= sizeof(IRSecretKeyImplTest_SAMPLE);
			size++) {
		IRSecretKeyImpl k(IRSecretKeyImplTest_SAMPLE, size);
		ASSERT_EQ(size * 8, k.size());
	}
}

//------------------------------------------------------------------------------
TEST_F(IRSecretKeyImplTest, sizeInBytes) {

	for (unsigned int size = 1; size <= sizeof(IRSecretKeyImplTest_SAMPLE);
			size++) {
		IRSecretKeyImpl k(IRSecretKeyImplTest_SAMPLE, size);
		ASSERT_EQ(size, k.sizeInBytes());
	}
}

//------------------------------------------------------------------------------
TEST_F(IRSecretKeyImplTest, exportKey) {
	IRSecretKeyImpl k(IRSecretKeyImplTest_SAMPLE,
			sizeof(IRSecretKeyImplTest_SAMPLE));
	std::uint8_t out[sizeof(IRSecretKeyImplTest_SAMPLE) + 1];
	std::uint64_t outSize;

	outSize = sizeof(IRSecretKeyImplTest_SAMPLE);
	ASSERT_TRUE(k.exportKey(out, outSize));
	ASSERT_EQ(sizeof(IRSecretKeyImplTest_SAMPLE), outSize);
	ASSERT_EQ(0, std::memcmp(out, IRSecretKeyImplTest_SAMPLE,
			sizeof(IRSecretKeyImplTest_SAMPLE)));

	outSize = sizeof(out);
	ASSERT_TRUE(k.exportKey(out, outSize));
	ASSERT_EQ(sizeof(IRSecretKeyImplTest_SAMPLE), outSize);
	ASSERT_EQ(0, std::memcmp(out, IRSecretKeyImplTest_SAMPLE,
			sizeof(IRSecretKeyImplTest_SAMPLE)));

	for (unsigned int size = 0; size < sizeof(IRSecretKeyImplTest_SAMPLE);
			size++) {
		outSize = size;
		ASSERT_FALSE(k.exportKey(out, outSize));
		ASSERT_EQ(sizeof(IRSecretKeyImplTest_SAMPLE), outSize);
	}

	outSize = sizeof(out);
	ASSERT_FALSE(k.exportKey(nullptr, outSize));
	ASSERT_EQ(sizeof(IRSecretKeyImplTest_SAMPLE), outSize);
}

//------------------------------------------------------------------------------
TEST_F(IRSecretKeyImplTest, serialize) {
	IRSecretKeyImpl k(IRSecretKeyImplTest_SAMPLE,
			sizeof(IRSecretKeyImplTest_SAMPLE));
	ircommon::IRBuffer out;

	ASSERT_TRUE(k.serialize(out));
	ASSERT_EQ(sizeof(IRSecretKeyImplTest_SAMPLE), out.size());
	ASSERT_EQ(0, std::memcmp(out.roBuffer(), IRSecretKeyImplTest_SAMPLE,
			sizeof(IRSecretKeyImplTest_SAMPLE)));

}

//------------------------------------------------------------------------------

