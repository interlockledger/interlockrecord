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

