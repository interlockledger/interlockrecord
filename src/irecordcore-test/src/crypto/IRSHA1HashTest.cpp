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
#include "IRSHA1HashTest.h"
#include <irecordcore/irhash.h>
#include "CryptoSamples.h"

using namespace irecordcore;
using namespace irecordcore::crypto;

//==============================================================================
// class IRSHA1HashTest
//------------------------------------------------------------------------------
IRSHA1HashTest::IRSHA1HashTest() {
}

//------------------------------------------------------------------------------
IRSHA1HashTest::~IRSHA1HashTest() {
}

//------------------------------------------------------------------------------
void IRSHA1HashTest::SetUp() {
}

//------------------------------------------------------------------------------
void IRSHA1HashTest::TearDown() {
}

//------------------------------------------------------------------------------
TEST_F(IRSHA1HashTest,Constructor) {
	IRSHA1Hash * h;

	h = new IRSHA1Hash();
	ASSERT_EQ(IR_HASH_SHA1, h->type());
	delete h;
}

//------------------------------------------------------------------------------
TEST_F(IRSHA1HashTest, size) {
	IRSHA1Hash h;

	ASSERT_EQ(160, h.size());
}

//------------------------------------------------------------------------------
TEST_F(IRSHA1HashTest, update) {
	IRSHA1Hash h;
	std::uint8_t out[20];
	const std::uint8_t * p;
	const std::uint8_t * pEnd;

	p = CRYPTOSAMPLES_SAMPLE;
	pEnd = p + sizeof(CRYPTOSAMPLES_SAMPLE);

	while (p < pEnd) {
		h.update(p, 2);
		p += 2;
	}
	ASSERT_TRUE(h.finalize(out, sizeof(out)));
	ASSERT_EQ(0, memcmp(CRYPTOSAMPLES_SHA1_SAMPLE, out,
			sizeof(CRYPTOSAMPLES_SHA1_SAMPLE)));
}

//------------------------------------------------------------------------------
TEST_F(IRSHA1HashTest, finalize) {
	IRSHA1Hash h;
	std::uint8_t exp[20];
	std::uint8_t out[sizeof(exp)];

	ASSERT_TRUE(h.finalize(exp, sizeof(exp)));
	ASSERT_EQ(0, memcmp(exp, CRYPTOSAMPLES_SHA1_EMPTY, sizeof(exp)));

	h.update(CRYPTOSAMPLES_SAMPLE, sizeof(CRYPTOSAMPLES_SAMPLE));
	ASSERT_TRUE(h.finalize(out, sizeof(out)));
	ASSERT_EQ(0, memcmp(CRYPTOSAMPLES_SHA1_SAMPLE, out,
			sizeof(CRYPTOSAMPLES_SHA1_SAMPLE)));
}

//------------------------------------------------------------------------------

