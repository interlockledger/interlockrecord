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
#include "IRHMACTest.h"
#include "CryptoSamples.h"
#include <irecordcore/irmac.h>
#include <cstring>

using namespace irecordcore;
using namespace irecordcore::crypto;

//==============================================================================
// class IRHMACTest
//------------------------------------------------------------------------------
IRHMACTest::IRHMACTest() {
}

//------------------------------------------------------------------------------
IRHMACTest::~IRHMACTest() {
}

//------------------------------------------------------------------------------
void IRHMACTest::SetUp() {
}

//------------------------------------------------------------------------------
void IRHMACTest::TearDown() {
}

//------------------------------------------------------------------------------
TEST_F(IRHMACTest, Constructor) {
	IRHMAC * m;

	m = new IRHMAC(new IRSHA256Hash());
	ASSERT_EQ(64, m->blockSize());
	delete m;

	m = new IRHMAC(new IRSHA256Hash(), 128);
	ASSERT_EQ(128, m->blockSize());
	delete m;

	try {
		m = new IRHMAC(new IRSHA256Hash(), 31);
		FAIL();
	} catch (std::invalid_argument & e) {}
}

//------------------------------------------------------------------------------
TEST_F(IRHMACTest, blockSize) {

	for (unsigned int blockSize = 20; blockSize <= 128; blockSize++) {
		IRHMAC m(new IRSHA1Hash(), blockSize);
		ASSERT_EQ(blockSize, m.blockSize());
	}

	IRHMAC m1(new IRSHA256Hash());
	ASSERT_EQ(64, m1.blockSize());
	IRHMAC m2(new IRSHA512Hash());
	ASSERT_EQ(128, m2.blockSize());
}

//------------------------------------------------------------------------------
TEST_F(IRHMACTest, size) {
	IRHMAC m1(new IRSHA1Hash());
	IRHMAC m2(new IRSHA256Hash());

	ASSERT_EQ(160, m1.size());
	ASSERT_EQ(256, m2.size());
}

//------------------------------------------------------------------------------
TEST_F(IRHMACTest, sizeInBytes) {
	IRHMAC m1(new IRSHA1Hash());
	IRHMAC m2(new IRSHA256Hash());

	ASSERT_EQ(20, m1.sizeInBytes());
	ASSERT_EQ(32, m2.sizeInBytes());
}

//------------------------------------------------------------------------------
TEST_F(IRHMACTest, reset) {
	IRHMAC m(new IRSHA256Hash());
	std::uint8_t out[32];

	m.update(CRYPTOSAMPLES_SAMPLE2, sizeof(CRYPTOSAMPLES_SAMPLE2));
	ASSERT_TRUE(m.finalize(out, sizeof(out)));
	ASSERT_NE(0, std::memcmp(CRYPTOSAMPLES_HMAC_SHA256_EMPTY_EMPTY, out, sizeof(out)));

	m.reset();
	ASSERT_TRUE(m.finalize(out, sizeof(out)));
	ASSERT_EQ(0, std::memcmp(CRYPTOSAMPLES_HMAC_SHA256_EMPTY_EMPTY, out, sizeof(out)));
}

//------------------------------------------------------------------------------
TEST_F(IRHMACTest, setKey) {
	IRHMAC m(new IRSHA256Hash());
	std::uint8_t out[32];

	// Small key
	ASSERT_TRUE(m.setRawKey(CRYPTOSAMPLES_KEY128, sizeof(CRYPTOSAMPLES_KEY128)));
	ASSERT_TRUE(m.finalize(out, sizeof(out)));
	ASSERT_EQ(0, std::memcmp(CRYPTOSAMPLES_HMAC_SHA256_KEY128_EMPTY, out, sizeof(out)));

	m.reset();
	ASSERT_TRUE(m.finalize(out, sizeof(out)));
	ASSERT_EQ(0, std::memcmp(CRYPTOSAMPLES_HMAC_SHA256_KEY128_EMPTY, out, sizeof(out)));

	// Long key
	ASSERT_TRUE(m.setRawKey(CRYPTOSAMPLES_SAMPLE, sizeof(CRYPTOSAMPLES_SAMPLE)));
	ASSERT_TRUE(m.finalize(out, sizeof(out)));
	ASSERT_EQ(0, std::memcmp(CRYPTOSAMPLES_HMAC_SHA256_SAMPLE_EMPTY, out, sizeof(out)));
}

//------------------------------------------------------------------------------
TEST_F(IRHMACTest, setKeyKey) {
	IRHMAC m(new IRSHA256Hash());
	std::uint8_t out[32];
	IRSecretKeyImpl k1(CRYPTOSAMPLES_KEY128, sizeof(CRYPTOSAMPLES_KEY128));
	IRSecretKeyImpl k2(CRYPTOSAMPLES_SAMPLE, sizeof(CRYPTOSAMPLES_SAMPLE));

	// Small key
	ASSERT_TRUE(m.setKey(k1));
	ASSERT_TRUE(m.finalize(out, sizeof(out)));
	ASSERT_EQ(0, std::memcmp(CRYPTOSAMPLES_HMAC_SHA256_KEY128_EMPTY, out, sizeof(out)));

	// Long key
	ASSERT_TRUE(m.setKey(k2));
	ASSERT_TRUE(m.finalize(out, sizeof(out)));
	ASSERT_EQ(0, std::memcmp(CRYPTOSAMPLES_HMAC_SHA256_SAMPLE_EMPTY, out, sizeof(out)));

	// TODO Test an unexportable key for failure.
}

//------------------------------------------------------------------------------
TEST_F(IRHMACTest, update) {
	IRHMAC m(new IRSHA256Hash());
	std::uint8_t out[32];
	const std::uint8_t * p;
	const std::uint8_t * pEnd;

	// SAMPLE_SAMPLE2
	ASSERT_TRUE(m.setRawKey(CRYPTOSAMPLES_SAMPLE, sizeof(CRYPTOSAMPLES_SAMPLE)));
	m.update(CRYPTOSAMPLES_SAMPLE2, sizeof(CRYPTOSAMPLES_SAMPLE2));
	ASSERT_TRUE(m.finalize(out, sizeof(out)));
	ASSERT_EQ(0, std::memcmp(CRYPTOSAMPLES_HMAC_SHA256_SAMPLE_SAMPLE2, out, sizeof(out)));

	// SAMPLE_SAMPLE2
	m.reset();
	ASSERT_TRUE(m.setRawKey(CRYPTOSAMPLES_SAMPLE, sizeof(CRYPTOSAMPLES_SAMPLE)));
	p = CRYPTOSAMPLES_SAMPLE2;
	pEnd = p + sizeof(CRYPTOSAMPLES_SAMPLE2);
	for (; p != pEnd; p++) {
		m.update(p, 1);
	}
	ASSERT_TRUE(m.finalize(out, sizeof(out)));
	ASSERT_EQ(0, std::memcmp(CRYPTOSAMPLES_HMAC_SHA256_SAMPLE_SAMPLE2, out, sizeof(out)));
}

//------------------------------------------------------------------------------
TEST_F(IRHMACTest, finalize) {
	IRHMAC m(new IRSHA256Hash());
	std::uint8_t out[64];

	// EMPTY_EMPTY
	for (unsigned int size = 32; size <= 64; size++) {
		std::memset(out, 0xFF, sizeof(out));
		m.reset();
		ASSERT_TRUE(m.finalize(out, size));
		ASSERT_EQ(0xFF, out[32]);
		ASSERT_EQ(0, std::memcmp(CRYPTOSAMPLES_HMAC_SHA256_EMPTY_EMPTY, out, 32));
	}

	// EMPTY_EMPTY
	for (unsigned int size = 0; size < 32; size++) {
		std::memset(out, 0xFF, sizeof(out));
		m.reset();
		ASSERT_FALSE(m.finalize(out, size));
		ASSERT_EQ(0xFF, out[0]);
		ASSERT_EQ(0xFF, out[32]);
	}
}

//------------------------------------------------------------------------------
TEST_F(IRHMACTest, CryptoSamplesSHA1) {
	IRHMAC m(new IRSHA1Hash());
	std::uint8_t out[20];

	// EMPTY_EMPTY
	ASSERT_TRUE(m.finalize(out, sizeof(out)));
	ASSERT_EQ(0, std::memcmp(CRYPTOSAMPLES_HMAC_SHA1_EMPTY_EMPTY, out, sizeof(out)));

}

//------------------------------------------------------------------------------
TEST_F(IRHMACTest, CryptoSamplesSHA256) {
	IRHMAC m(new IRSHA256Hash());
	std::uint8_t out[32];

	// EMPTY_EMPTY
	ASSERT_TRUE(m.finalize(out, sizeof(out)));
	ASSERT_EQ(0, std::memcmp(CRYPTOSAMPLES_HMAC_SHA256_EMPTY_EMPTY, out, sizeof(out)));

	// KEY128_EMPTY
	ASSERT_TRUE(m.setRawKey(CRYPTOSAMPLES_KEY128, sizeof(CRYPTOSAMPLES_KEY128)));
	ASSERT_TRUE(m.finalize(out, sizeof(out)));
	ASSERT_EQ(0, std::memcmp(CRYPTOSAMPLES_HMAC_SHA256_KEY128_EMPTY, out, sizeof(out)));

	// SAMPLE_EMPTY
	ASSERT_TRUE(m.setRawKey(CRYPTOSAMPLES_SAMPLE, sizeof(CRYPTOSAMPLES_SAMPLE)));
	ASSERT_TRUE(m.finalize(out, sizeof(out)));
	ASSERT_EQ(0, std::memcmp(CRYPTOSAMPLES_HMAC_SHA256_SAMPLE_EMPTY, out, sizeof(out)));

	// KEY128_SAMPLE2
	ASSERT_TRUE(m.setRawKey(CRYPTOSAMPLES_KEY128, sizeof(CRYPTOSAMPLES_KEY128)));
	m.update(CRYPTOSAMPLES_SAMPLE2, sizeof(CRYPTOSAMPLES_SAMPLE2));
	ASSERT_TRUE(m.finalize(out, sizeof(out)));
	ASSERT_EQ(0, std::memcmp(CRYPTOSAMPLES_HMAC_SHA256_KEY128_SAMPLE2, out, sizeof(out)));

	// SAMPLE_SAMPLE2
	ASSERT_TRUE(m.setRawKey(CRYPTOSAMPLES_SAMPLE, sizeof(CRYPTOSAMPLES_SAMPLE)));
	m.update(CRYPTOSAMPLES_SAMPLE2, sizeof(CRYPTOSAMPLES_SAMPLE2));
	ASSERT_TRUE(m.finalize(out, sizeof(out)));
	ASSERT_EQ(0, std::memcmp(CRYPTOSAMPLES_HMAC_SHA256_SAMPLE_SAMPLE2, out, sizeof(out)));
}

//------------------------------------------------------------------------------
TEST_F(IRHMACTest, CryptoSamplesSHA512) {
	IRHMAC m(new IRSHA512Hash());
	std::uint8_t out[64];

	// SAMPLE_SAMPLE2
	ASSERT_TRUE(m.setRawKey(CRYPTOSAMPLES_SAMPLE, sizeof(CRYPTOSAMPLES_SAMPLE)));
	m.update(CRYPTOSAMPLES_SAMPLE2, sizeof(CRYPTOSAMPLES_SAMPLE2));
	ASSERT_TRUE(m.finalize(out, sizeof(out)));
	ASSERT_EQ(0, std::memcmp(CRYPTOSAMPLES_HMAC_SHA512_SAMPLE_SAMPLE2, out, sizeof(out)));
}

//------------------------------------------------------------------------------

