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
#include "IRBotanHashTest.h"
#include <irecordcore/irhash.h>
#include <botan/sha160.h>
#include "CryptoSamples.h"

using namespace irecordcore;
using namespace irecordcore::crypto;

//==============================================================================
// class IRDummyBotanHash
//------------------------------------------------------------------------------
class IRDummyBotanHash: public IRBotanHash < Botan::SHA_160, IR_HASH_SHA1 > {
public:
	const Botan::SHA_160 & getBotanImpl() const {
		return this->_hash;
	}
};

//==============================================================================
// class IRBotanHashTest
//------------------------------------------------------------------------------
IRBotanHashTest::IRBotanHashTest() {
}

//------------------------------------------------------------------------------
IRBotanHashTest::~IRBotanHashTest() {
}

//------------------------------------------------------------------------------
void IRBotanHashTest::SetUp() {
}

//------------------------------------------------------------------------------
void IRBotanHashTest::TearDown() {
}

//------------------------------------------------------------------------------
TEST_F(IRBotanHashTest, Constructor) {
	IRDummyBotanHash * h;

	h = new IRDummyBotanHash();
	ASSERT_EQ(IR_HASH_SHA1, h->type());
	ASSERT_EQ(typeid(&(h->getBotanImpl())), typeid(const Botan::SHA_160 *));
	delete h;
}

//------------------------------------------------------------------------------
TEST_F(IRBotanHashTest, size) {
	IRDummyBotanHash h;

	ASSERT_EQ(160, h.size());
}

//------------------------------------------------------------------------------
TEST_F(IRBotanHashTest, reset) {
	IRDummyBotanHash h;
	std::uint8_t exp[20];
	std::uint8_t out[sizeof(exp)];

	ASSERT_TRUE(h.finalize(exp, sizeof(exp)));

	h.reset();
	h.update(CRYPTOSAMPLES_SAMPLE, sizeof(CRYPTOSAMPLES_SAMPLE));
	ASSERT_TRUE(h.finalize(out, sizeof(out)));
	ASSERT_EQ(0, memcmp(CRYPTOSAMPLES_SHA1_SAMPLE, out,
			sizeof(CRYPTOSAMPLES_SHA1_SAMPLE)));

	h.reset();
	ASSERT_TRUE(h.finalize(out, sizeof(out)));
	ASSERT_EQ(0, memcmp(exp, out, sizeof(exp)));
}

//------------------------------------------------------------------------------
TEST_F(IRBotanHashTest, update) {
	IRDummyBotanHash h;
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
TEST_F(IRBotanHashTest, finalizeEmpty) {
	IRDummyBotanHash h;
	std::uint8_t out[20];

	ASSERT_TRUE(h.finalize(out, sizeof(out)));
	ASSERT_EQ(0, memcmp(out, CRYPTOSAMPLES_SHA1_EMPTY, sizeof(out)));
}

//------------------------------------------------------------------------------
TEST_F(IRBotanHashTest, finalize) {
	IRDummyBotanHash h;
	std::uint8_t out[20];

	h.update(CRYPTOSAMPLES_SAMPLE, sizeof(CRYPTOSAMPLES_SAMPLE));
	ASSERT_TRUE(h.finalize(out, sizeof(out)));
	ASSERT_EQ(0, memcmp(CRYPTOSAMPLES_SHA1_SAMPLE, out,
			sizeof(CRYPTOSAMPLES_SHA1_SAMPLE)));

	h.reset();
	for (std::uint64_t i = 0; i < sizeof(out); i++) {
		ASSERT_FALSE(h.finalize(out, i));
	}
}

//------------------------------------------------------------------------------

