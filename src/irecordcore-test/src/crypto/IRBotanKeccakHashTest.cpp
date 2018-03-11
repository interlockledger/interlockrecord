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

