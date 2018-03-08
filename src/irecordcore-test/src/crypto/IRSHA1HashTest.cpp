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

