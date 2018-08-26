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
#include "IRBotanBlockCipherAlgorithmTest.h"
#include <irecordcore/irbciphr.h>
#include "CryptoSamples.h"

using namespace irecordcore::crypto;

typedef IRBotanBlockCipherAlgorithm<Botan::AES_192>
		IRDummyBotanBlockCipherAlgorithm;

//==============================================================================
// class IRBotanBlockCipherAlgorithmTest
//------------------------------------------------------------------------------
IRBotanBlockCipherAlgorithmTest::IRBotanBlockCipherAlgorithmTest() {
}

//------------------------------------------------------------------------------
IRBotanBlockCipherAlgorithmTest::~IRBotanBlockCipherAlgorithmTest() {
}

//------------------------------------------------------------------------------
void IRBotanBlockCipherAlgorithmTest::SetUp() {
}

//------------------------------------------------------------------------------
void IRBotanBlockCipherAlgorithmTest::TearDown() {
}

//------------------------------------------------------------------------------
TEST_F(IRBotanBlockCipherAlgorithmTest,Constructor) {
	IRDummyBotanBlockCipherAlgorithm * c;

	c = new IRDummyBotanBlockCipherAlgorithm(true);
	ASSERT_TRUE(c->cipherMode());
	delete c;

	c = new IRDummyBotanBlockCipherAlgorithm(false);
	ASSERT_FALSE(c->cipherMode());
	delete c;
}

//------------------------------------------------------------------------------
TEST_F(IRBotanBlockCipherAlgorithmTest, keySize) {
	IRDummyBotanBlockCipherAlgorithm ce(true);
	IRDummyBotanBlockCipherAlgorithm cd(false);

	ASSERT_EQ(192, ce.minKeySize());
	ASSERT_EQ(192, ce.maxKeySize());

	ASSERT_FALSE(ce.isValidKeySize(0));
	ASSERT_FALSE(ce.isValidKeySize(191));
	ASSERT_TRUE(ce.isValidKeySize(192));
	ASSERT_FALSE(ce.isValidKeySize(193));

	ASSERT_EQ(192, cd.minKeySize());
	ASSERT_EQ(192, cd.maxKeySize());

	ASSERT_FALSE(cd.isValidKeySize(0));
	ASSERT_FALSE(cd.isValidKeySize(191));
	ASSERT_TRUE(cd.isValidKeySize(192));
	ASSERT_FALSE(cd.isValidKeySize(193));
}

//------------------------------------------------------------------------------
TEST_F(IRBotanBlockCipherAlgorithmTest, blockSize) {
	IRDummyBotanBlockCipherAlgorithm ce(true);
	IRDummyBotanBlockCipherAlgorithm cd(false);

	ASSERT_EQ(128, ce.blockSize());
	ASSERT_EQ(16, ce.blockSizeInBytes());

	ASSERT_EQ(128, cd.blockSize());
	ASSERT_EQ(16, cd.blockSizeInBytes());
}

//------------------------------------------------------------------------------
TEST_F(IRBotanBlockCipherAlgorithmTest, setRawKey) {
	IRDummyBotanBlockCipherAlgorithm ce(true);
	IRDummyBotanBlockCipherAlgorithm cd(false);

	ASSERT_FALSE(ce.setRawKey(CRYPTOSAMPLES_KEY256, 0));
	ASSERT_FALSE(ce.setRawKey(CRYPTOSAMPLES_KEY256, 23));
	ASSERT_TRUE(ce.setRawKey(CRYPTOSAMPLES_KEY256, 24));
	ASSERT_FALSE(ce.setRawKey(CRYPTOSAMPLES_KEY256, 25));

	ASSERT_FALSE(cd.setRawKey(CRYPTOSAMPLES_KEY256, 0));
	ASSERT_FALSE(cd.setRawKey(CRYPTOSAMPLES_KEY256, 23));
	ASSERT_TRUE(cd.setRawKey(CRYPTOSAMPLES_KEY256, 24));
	ASSERT_FALSE(cd.setRawKey(CRYPTOSAMPLES_KEY256, 25));
}

//------------------------------------------------------------------------------
TEST_F(IRBotanBlockCipherAlgorithmTest, processBlocks) {
	IRDummyBotanBlockCipherAlgorithm ce(true);
	IRDummyBotanBlockCipherAlgorithm cd(false);
	std::uint8_t enc[33];
	std::uint8_t dec[33];

	ASSERT_TRUE(ce.setRawKey(CRYPTOSAMPLES_KEY256, 24));
	ASSERT_TRUE(cd.setRawKey(CRYPTOSAMPLES_KEY256, 24));

	std::memset(enc, 0, sizeof(enc));
	ASSERT_TRUE(ce.processBlocks(CRYPTOSAMPLES_KEY256, enc, 1));
	ASSERT_EQ(0, enc[16]);
	std::memset(dec, 0, sizeof(dec));
	ASSERT_TRUE(cd.processBlocks(enc, dec, 1));
	ASSERT_EQ(0, dec[16]);
	ASSERT_EQ(0, std::memcmp(CRYPTOSAMPLES_KEY256, dec, 16));

	std::memset(enc, 0, sizeof(enc));
	ASSERT_TRUE(ce.processBlocks(CRYPTOSAMPLES_KEY256, enc, 2));
	ASSERT_EQ(0, enc[32]);
	std::memset(dec, 0, sizeof(dec));
	ASSERT_TRUE(cd.processBlocks(enc, dec, 2));
	ASSERT_EQ(0, dec[32]);
	ASSERT_EQ(0, std::memcmp(CRYPTOSAMPLES_KEY256, dec, 32));
}

//------------------------------------------------------------------------------

