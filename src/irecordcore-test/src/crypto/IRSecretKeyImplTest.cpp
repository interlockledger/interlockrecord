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
	ASSERT_EQ(sizeof(IRSecretKeyImplTest_SAMPLE), k->sizeInBytes());
	ASSERT_NE(0, std::memcmp(k->key(), IRSecretKeyImplTest_SAMPLE,
			sizeof(IRSecretKeyImplTest_SAMPLE)));
	delete k;
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
TEST_F(IRSecretKeyImplTest, lockUnlock) {
	IRSecretKeyImpl k(IRSecretKeyImplTest_SAMPLE,
			sizeof(IRSecretKeyImplTest_SAMPLE));

	ASSERT_NE(0, std::memcmp(k.key(), IRSecretKeyImplTest_SAMPLE,
			sizeof(IRSecretKeyImplTest_SAMPLE)));
	k.lock();
	ASSERT_EQ(0, std::memcmp(k.key(), IRSecretKeyImplTest_SAMPLE,
			sizeof(IRSecretKeyImplTest_SAMPLE)));
	k.unlock();
}

//------------------------------------------------------------------------------
TEST_F(IRSecretKeyImplTest, copy) {
	IRSecretKeyImpl k(IRSecretKeyImplTest_SAMPLE,
			sizeof(IRSecretKeyImplTest_SAMPLE));
	std::uint8_t out[sizeof(IRSecretKeyImplTest_SAMPLE) + 1];

	ASSERT_EQ(sizeof(IRSecretKeyImplTest_SAMPLE), k.copy(out,
			sizeof(IRSecretKeyImplTest_SAMPLE)));
	ASSERT_EQ(0, std::memcmp(out, IRSecretKeyImplTest_SAMPLE,
			sizeof(IRSecretKeyImplTest_SAMPLE)));

	ASSERT_EQ(sizeof(IRSecretKeyImplTest_SAMPLE), k.copy(out, sizeof(out)));
	ASSERT_EQ(0, std::memcmp(out, IRSecretKeyImplTest_SAMPLE,
			sizeof(IRSecretKeyImplTest_SAMPLE)));

	for (unsigned int size = 0; size < sizeof(IRSecretKeyImplTest_SAMPLE);
			size++) {
		ASSERT_EQ(0, k.copy(out, size));
	}
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

