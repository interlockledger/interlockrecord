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
#include "IRBotanHashTest.h"
#include <irecordcore/irhash.h>
#include <botan-2/botan/sha160.h>
#include "CryptoSamples.h"

using namespace irecordcore;
using namespace irecordcore::crypto;

class IRDummyBotanHash: public IRBotanHash < Botan::SHA_160, IR_HASH_SHA1 > {
public:
	const Botan::SHA_160 & getBotanImpl() const {
		return this->_hash;
	}
};

static const std::uint8_t IRBotanHashTest_EMPTY[20] = {
		0xda, 0x39, 0xa3, 0xee, 0x5e, 0x6b, 0x4b, 0x0d, 0x32, 0x55,
		0xbf, 0xef, 0x95, 0x60, 0x18, 0x90, 0xaf, 0xd8, 0x07, 0x09};

// SHA1 of CRYPTOSAMPLES_SAMPLE
// Samples generated with:
//		printf "Human sacrifice, dogs and cats living together, mass hysteria!" | openssl sha1 -binary| xxd -g1
static const std::uint8_t IRBotanHashTest_SAMPLE[20] = {
		0x30, 0xb7, 0xb3, 0x2d, 0x08, 0xf2, 0x70, 0xcf, 0xe3, 0x30,
		0x0e, 0xff, 0x12, 0x61, 0xdf, 0x53,	0x45, 0x72, 0x60, 0x34};

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
	ASSERT_EQ(0, memcmp(IRBotanHashTest_SAMPLE, out,
			sizeof(IRBotanHashTest_SAMPLE)));

	h.reset();
	ASSERT_TRUE(h.finalize(out, sizeof(out)));
	ASSERT_EQ(0, memcmp(exp, out, sizeof(exp)));
}


//------------------------------------------------------------------------------
TEST_F(IRBotanHashTest, finalizeEmpty) {
	IRDummyBotanHash h;
	std::uint8_t exp[20];
	std::uint8_t out[sizeof(exp)];

	ASSERT_TRUE(h.finalize(exp, sizeof(exp)));
	ASSERT_EQ(0, memcmp(exp, IRBotanHashTest_EMPTY, sizeof(exp)));
}

//------------------------------------------------------------------------------
TEST_F(IRBotanHashTest, finalize) {
	IRDummyBotanHash h;
	std::uint8_t exp[20];
	std::uint8_t out[sizeof(exp)];

	h.update(CRYPTOSAMPLES_SAMPLE, sizeof(CRYPTOSAMPLES_SAMPLE));
	ASSERT_TRUE(h.finalize(out, sizeof(out)));
	ASSERT_EQ(0, memcmp(IRBotanHashTest_SAMPLE, out,
			sizeof(IRBotanHashTest_SAMPLE)));
}

//------------------------------------------------------------------------------

