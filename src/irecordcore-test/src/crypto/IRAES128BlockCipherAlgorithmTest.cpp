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
#include "IRAES128BlockCipherAlgorithmTest.h"
#include <irecordcore/irbciphr.h>
#include "CryptoSamples.h"

using namespace irecordcore::crypto;

//==============================================================================
// class IRAES128BlockCipherAlgorithmTest
//------------------------------------------------------------------------------
IRAES128BlockCipherAlgorithmTest::IRAES128BlockCipherAlgorithmTest() {
}

//------------------------------------------------------------------------------
IRAES128BlockCipherAlgorithmTest::~IRAES128BlockCipherAlgorithmTest() {
}

//------------------------------------------------------------------------------
void IRAES128BlockCipherAlgorithmTest::SetUp() {
}

//------------------------------------------------------------------------------
void IRAES128BlockCipherAlgorithmTest::TearDown() {
}

//------------------------------------------------------------------------------
TEST_F(IRAES128BlockCipherAlgorithmTest,Constructor) {
	IRAES128BlockCipherAlgorithm * c;

	c = new IRAES128BlockCipherAlgorithm(true);
	ASSERT_TRUE(c->cipherMode());
	delete c;

	c = new IRAES128BlockCipherAlgorithm(false);
	ASSERT_FALSE(c->cipherMode());
	delete c;
}

//------------------------------------------------------------------------------
TEST_F(IRAES128BlockCipherAlgorithmTest, keySize) {
	IRAES128BlockCipherAlgorithm ce(true);
	IRAES128BlockCipherAlgorithm cd(false);

	ASSERT_EQ(128, ce.minKeySize());
	ASSERT_EQ(128, ce.maxKeySize());

	ASSERT_FALSE(ce.isValidKeySize(0));
	ASSERT_FALSE(ce.isValidKeySize(127));
	ASSERT_TRUE(ce.isValidKeySize(128));
	ASSERT_FALSE(ce.isValidKeySize(129));

	ASSERT_EQ(128, cd.minKeySize());
	ASSERT_EQ(128, cd.maxKeySize());

	ASSERT_FALSE(cd.isValidKeySize(0));
	ASSERT_FALSE(cd.isValidKeySize(127));
	ASSERT_TRUE(cd.isValidKeySize(128));
	ASSERT_FALSE(cd.isValidKeySize(129));
}

//------------------------------------------------------------------------------
TEST_F(IRAES128BlockCipherAlgorithmTest, blockSize) {
	IRAES128BlockCipherAlgorithm ce(true);
	IRAES128BlockCipherAlgorithm cd(false);

	ASSERT_EQ(128, ce.blockSize());
	ASSERT_EQ(16, ce.blockSizeInBytes());

	ASSERT_EQ(128, cd.blockSize());
	ASSERT_EQ(16, cd.blockSizeInBytes());
}

//------------------------------------------------------------------------------
TEST_F(IRAES128BlockCipherAlgorithmTest, setRawKey) {
	IRAES128BlockCipherAlgorithm ce(true);
	IRAES128BlockCipherAlgorithm cd(false);

	ASSERT_FALSE(ce.setRawKey(CRYPTOSAMPLES_KEY128, 0));
	ASSERT_FALSE(ce.setRawKey(CRYPTOSAMPLES_KEY128, 15));
	ASSERT_TRUE(ce.setRawKey(CRYPTOSAMPLES_KEY128, 16));
	ASSERT_FALSE(ce.setRawKey(CRYPTOSAMPLES_KEY128, 17));

	ASSERT_FALSE(cd.setRawKey(CRYPTOSAMPLES_KEY128, 0));
	ASSERT_FALSE(cd.setRawKey(CRYPTOSAMPLES_KEY128, 15));
	ASSERT_TRUE(cd.setRawKey(CRYPTOSAMPLES_KEY128, 16));
	ASSERT_FALSE(cd.setRawKey(CRYPTOSAMPLES_KEY128, 17));
}

//------------------------------------------------------------------------------
TEST_F(IRAES128BlockCipherAlgorithmTest, processBlocks) {
	IRAES128BlockCipherAlgorithm ce(true);
	IRAES128BlockCipherAlgorithm cd(false);
	std::uint8_t enc[33];
	std::uint8_t dec[33];

	ASSERT_TRUE(ce.setRawKey(CRYPTOSAMPLES_KEY128, 16));
	ASSERT_TRUE(cd.setRawKey(CRYPTOSAMPLES_KEY128, 16));

	std::memset(enc, 0, sizeof(enc));
	ASSERT_TRUE(ce.processBlocks(CRYPTOSAMPLES_KEY256, enc, 1));
	ASSERT_EQ(0, enc[16]);
	ASSERT_EQ(0, std::memcmp(CRYPTOSAMPLES_AES128_ECB, enc, 16));

	std::memset(dec, 0, sizeof(dec));
	ASSERT_TRUE(cd.processBlocks(enc, dec, 1));
	ASSERT_EQ(0, dec[16]);
	ASSERT_EQ(0, std::memcmp(CRYPTOSAMPLES_KEY256, dec, 16));

	std::memset(enc, 0, sizeof(enc));
	ASSERT_TRUE(ce.processBlocks(CRYPTOSAMPLES_KEY256, enc, 2));
	ASSERT_EQ(0, enc[32]);
	ASSERT_EQ(0, std::memcmp(CRYPTOSAMPLES_AES128_ECB, enc, 32));

	std::memset(dec, 0, sizeof(dec));
	ASSERT_TRUE(cd.processBlocks(enc, dec, 2));
	ASSERT_EQ(0, dec[32]);
	ASSERT_EQ(0, std::memcmp(CRYPTOSAMPLES_KEY256, dec, 32));
}

//------------------------------------------------------------------------------

