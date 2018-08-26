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

