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
#include "IRCopyHashTest.h"
#include "CryptoSamples.h"
#include <irecordcore/irhash.h>
#include <cstring>

using namespace irecordcore;
using namespace irecordcore::crypto;

//==============================================================================
// class IRCopyHashTest
//------------------------------------------------------------------------------
IRCopyHashTest::IRCopyHashTest() {
}

//------------------------------------------------------------------------------
IRCopyHashTest::~IRCopyHashTest() {
}

//------------------------------------------------------------------------------
void IRCopyHashTest::SetUp() {
}

//------------------------------------------------------------------------------
void IRCopyHashTest::TearDown() {
}

//------------------------------------------------------------------------------
TEST_F(IRCopyHashTest,Constructor) {
	IRCopyHash * h;

	h = new IRCopyHash();
	ASSERT_EQ(IR_HASH_COPY, h->type());
	delete h;

	h = new IRCopyHash(128);
	ASSERT_EQ(IR_HASH_COPY, h->type());
	delete h;
}

//------------------------------------------------------------------------------
TEST_F(IRCopyHashTest, size) {
	IRCopyHash h;
	std::uint64_t size;
	const std::uint8_t * p;
	const std::uint8_t * pEnd;

	ASSERT_EQ(0, h.size());

	size = 0;
	p = CRYPTOSAMPLES_SAMPLE;
	pEnd = p + sizeof(CRYPTOSAMPLES_SAMPLE);
	while (p < pEnd) {
		ASSERT_EQ(size * 8, h.size());
		h.update(p, 2);
		p += 2;
		size += 2;
		ASSERT_EQ(size * 8, h.size());
	}
}

//------------------------------------------------------------------------------
TEST_F(IRCopyHashTest, reset) {
	IRCopyHash h;

	h.reset();
	ASSERT_EQ(0, h.size());

	h.update(CRYPTOSAMPLES_SAMPLE, sizeof(CRYPTOSAMPLES_SAMPLE));

	h.reset();
	ASSERT_EQ(0, h.size());
}

//------------------------------------------------------------------------------
TEST_F(IRCopyHashTest, update) {
	IRCopyHash h;
	std::uint8_t out[sizeof(CRYPTOSAMPLES_SAMPLE)];
	const std::uint8_t * p;
	const std::uint8_t * pEnd;

	ASSERT_EQ(0, h.size());

	p = CRYPTOSAMPLES_SAMPLE;
	pEnd = p + sizeof(CRYPTOSAMPLES_SAMPLE);
	while (p < pEnd) {
		h.update(p, 2);
		p += 2;
		std::memset(out, 0, sizeof(out));
		ASSERT_TRUE(h.finalize(out, sizeof(out)));
		ASSERT_EQ(0, std::memcmp(out, CRYPTOSAMPLES_SAMPLE, h.sizeInBytes()));
	}
}

//------------------------------------------------------------------------------
TEST_F(IRCopyHashTest, finalize) {
	IRCopyHash h;
	std::uint8_t out[sizeof(CRYPTOSAMPLES_SAMPLE)];
	std::uint8_t exp[sizeof(CRYPTOSAMPLES_SAMPLE)];

	ASSERT_EQ(0, h.size());
	ASSERT_TRUE(h.finalize(out, sizeof(out)));

	h.update(CRYPTOSAMPLES_SAMPLE, sizeof(CRYPTOSAMPLES_SAMPLE));
	std::memset(out, 0, sizeof(out));
	ASSERT_TRUE(h.finalize(out, sizeof(out)));
	ASSERT_EQ(0, std::memcmp(out, CRYPTOSAMPLES_SAMPLE, sizeof(CRYPTOSAMPLES_SAMPLE)));

	std::memset(exp, 0, sizeof(exp));
	for (std::uint64_t size = 0; size < sizeof(out); size++) {
		std::memset(out, 0, sizeof(out));
		ASSERT_FALSE(h.finalize(out, size));
		ASSERT_EQ(0, std::memcmp(out, exp, sizeof(exp)));
	}
}

//------------------------------------------------------------------------------

