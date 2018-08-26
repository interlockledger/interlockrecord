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
#include "IRSHA3_512HashTest.h"
#include <irecordcore/irhash.h>
#include "CryptoSamples.h"

using namespace irecordcore;
using namespace irecordcore::crypto;

//==============================================================================
// class IRSHA3_512HashTest
//------------------------------------------------------------------------------
IRSHA3_512HashTest::IRSHA3_512HashTest() {
}

//------------------------------------------------------------------------------
IRSHA3_512HashTest::~IRSHA3_512HashTest() {
}

//------------------------------------------------------------------------------
void IRSHA3_512HashTest::SetUp() {
}

//------------------------------------------------------------------------------
void IRSHA3_512HashTest::TearDown() {
}

//------------------------------------------------------------------------------
TEST_F(IRSHA3_512HashTest,Constructor) {
	IRSHA3_512Hash * h;

	h = new IRSHA3_512Hash();
	ASSERT_EQ(IR_HASH_SHA3_512, h->type());
	delete h;
}

//------------------------------------------------------------------------------
TEST_F(IRSHA3_512HashTest, size) {
	IRSHA3_512Hash h;

	ASSERT_EQ(512, h.size());
}

//------------------------------------------------------------------------------
TEST_F(IRSHA3_512HashTest, update) {
	IRSHA3_512Hash h;
	std::uint8_t out[64];
	const std::uint8_t * p;
	const std::uint8_t * pEnd;

	p = CRYPTOSAMPLES_SAMPLE;
	pEnd = p + sizeof(CRYPTOSAMPLES_SAMPLE);

	while (p < pEnd) {
		h.update(p, 2);
		p += 2;
	}
	ASSERT_TRUE(h.finalize(out, sizeof(out)));
	ASSERT_EQ(0, memcmp(CRYPTOSAMPLES_SHA3_512_SAMPLE, out,
			sizeof(CRYPTOSAMPLES_SHA3_512_SAMPLE)));
}

//------------------------------------------------------------------------------
TEST_F(IRSHA3_512HashTest, finalize) {
	IRSHA3_512Hash h;
	std::uint8_t exp[64];
	std::uint8_t out[sizeof(exp)];

	ASSERT_TRUE(h.finalize(exp, sizeof(exp)));
	ASSERT_EQ(0, memcmp(exp, CRYPTOSAMPLES_SHA3_512_EMPTY, sizeof(exp)));

	h.update(CRYPTOSAMPLES_SAMPLE, sizeof(CRYPTOSAMPLES_SAMPLE));
	ASSERT_TRUE(h.finalize(out, sizeof(out)));
	ASSERT_EQ(0, memcmp(CRYPTOSAMPLES_SHA3_512_SAMPLE, out,
			sizeof(CRYPTOSAMPLES_SHA3_512_SAMPLE)));
}
//------------------------------------------------------------------------------

