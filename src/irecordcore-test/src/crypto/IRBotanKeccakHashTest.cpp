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
#include "IRBotanKeccakHashTest.h"
#include <irecordcore/irhash.h>
#include "CryptoSamples.h"

using namespace irecordcore;
using namespace irecordcore::crypto;

//==============================================================================
// class IRDummyBotanHash
//------------------------------------------------------------------------------
typedef IRBotanKeccakHash <Botan::SHA_3, 256, IR_HASH_SHA3_256> IRDummyBotanKeccakHash;

//==============================================================================
// class IRBotanKeccakHashTest
//------------------------------------------------------------------------------
IRBotanKeccakHashTest::IRBotanKeccakHashTest() {
}

//------------------------------------------------------------------------------
IRBotanKeccakHashTest::~IRBotanKeccakHashTest() {
}

//------------------------------------------------------------------------------
void IRBotanKeccakHashTest::SetUp() {
}

//------------------------------------------------------------------------------
void IRBotanKeccakHashTest::TearDown() {
}

//------------------------------------------------------------------------------
TEST_F(IRBotanKeccakHashTest, Constructor) {
	IRDummyBotanKeccakHash * h;

	h = new IRDummyBotanKeccakHash();
	ASSERT_EQ(IR_HASH_SHA3_256, h->type());
	delete h;
}

//------------------------------------------------------------------------------
TEST_F(IRBotanKeccakHashTest, size) {
	IRDummyBotanKeccakHash h;

	ASSERT_EQ(256, h.size());
}

//------------------------------------------------------------------------------
TEST_F(IRBotanKeccakHashTest, reset) {
	IRDummyBotanKeccakHash h;
	std::uint8_t exp[32];
	std::uint8_t out[sizeof(exp)];

	ASSERT_TRUE(h.finalize(exp, sizeof(exp)));
	h.reset();

	h.update(CRYPTOSAMPLES_SAMPLE, sizeof(CRYPTOSAMPLES_SAMPLE));
	ASSERT_TRUE(h.finalize(out, sizeof(out)));
	ASSERT_EQ(0, memcmp(CRYPTOSAMPLES_SHA3_256_SAMPLE, out,
			sizeof(CRYPTOSAMPLES_SHA3_256_SAMPLE)));

	h.reset();
	ASSERT_TRUE(h.finalize(out, sizeof(out)));
	ASSERT_EQ(0, memcmp(exp, out, sizeof(exp)));
}

//------------------------------------------------------------------------------
TEST_F(IRBotanKeccakHashTest, update) {
	IRDummyBotanKeccakHash h;
	std::uint8_t out[32];
	const std::uint8_t * p;
	const std::uint8_t * pEnd;

	p = CRYPTOSAMPLES_SAMPLE;
	pEnd = p + sizeof(CRYPTOSAMPLES_SAMPLE);

	while (p < pEnd) {
		h.update(p, 2);
		p += 2;
	}
	ASSERT_TRUE(h.finalize(out, sizeof(out)));
	ASSERT_EQ(0, memcmp(CRYPTOSAMPLES_SHA3_256_SAMPLE, out,
			sizeof(CRYPTOSAMPLES_SHA3_256_SAMPLE)));
}

//------------------------------------------------------------------------------
TEST_F(IRBotanKeccakHashTest, finalizeEmpty) {
	IRDummyBotanKeccakHash h;
	std::uint8_t out[32];

	h.reset();
	ASSERT_TRUE(h.finalize(out, sizeof(out)));
	ASSERT_EQ(0, memcmp(out, CRYPTOSAMPLES_SHA3_256_EMPTY, sizeof(out)));
}

//------------------------------------------------------------------------------
TEST_F(IRBotanKeccakHashTest, finalize) {
	IRDummyBotanKeccakHash h;
	std::uint8_t out[32];

	h.update(CRYPTOSAMPLES_SAMPLE, sizeof(CRYPTOSAMPLES_SAMPLE));
	ASSERT_TRUE(h.finalize(out, sizeof(out)));
	ASSERT_EQ(0, memcmp(CRYPTOSAMPLES_SHA3_256_SAMPLE, out,
			sizeof(CRYPTOSAMPLES_SHA3_256_SAMPLE)));

	h.reset();
	for (std::uint64_t i = 0; i < sizeof(out); i++) {
		ASSERT_FALSE(h.finalize(out, i));
	}
}
//------------------------------------------------------------------------------

