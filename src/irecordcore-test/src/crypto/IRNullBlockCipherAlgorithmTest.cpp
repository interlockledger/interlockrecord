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
#include "IRNullBlockCipherAlgorithmTest.h"
#include <irecordcore/ircipher.h>
#include <ircommon/irbuffer.h>
#include <cstring>
#include "CryptoSamples.h"

using namespace irecordcore::crypto;

//==============================================================================
// class IRNullBlockCipherAlgorithmTest
//------------------------------------------------------------------------------
IRNullBlockCipherAlgorithmTest::IRNullBlockCipherAlgorithmTest() {
}

//------------------------------------------------------------------------------
IRNullBlockCipherAlgorithmTest::~IRNullBlockCipherAlgorithmTest() {
}

//------------------------------------------------------------------------------
void IRNullBlockCipherAlgorithmTest::SetUp() {
}

//------------------------------------------------------------------------------
void IRNullBlockCipherAlgorithmTest::TearDown() {
}

//------------------------------------------------------------------------------
TEST_F(IRNullBlockCipherAlgorithmTest,Constructor) {
	IRNullBlockCipherAlgorithm * c;

	c = new IRNullBlockCipherAlgorithm(true, 8);
	ASSERT_TRUE(c->cipherMode());
	ASSERT_EQ(8, c->blockSize());
	delete c;

	c = new IRNullBlockCipherAlgorithm(false, 16);
	ASSERT_FALSE(c->cipherMode());
	ASSERT_EQ(16, c->blockSize());
	delete c;

	try {
		c = new IRNullBlockCipherAlgorithm(false, 0);
		FAIL();
	} catch (std::invalid_argument & e){}

	try {
		c = new IRNullBlockCipherAlgorithm(false, 1);
		FAIL();
	} catch (std::invalid_argument & e){}

	try {
		c = new IRNullBlockCipherAlgorithm(false, 7);
		FAIL();
	} catch (std::invalid_argument & e){}
}

//------------------------------------------------------------------------------
TEST_F(IRNullBlockCipherAlgorithmTest, keySize) {
	IRNullBlockCipherAlgorithm c(true, 8);

	ASSERT_EQ(0, c.minKeySize());
	ASSERT_EQ(~((unsigned int)0), c.maxKeySize());

	for (unsigned int keySize = 0; keySize < 1024; keySize++) {
		ASSERT_TRUE(c.isValidKeySize(keySize));
	}
	ASSERT_TRUE(c.isValidKeySize(~((unsigned int)0)));
}

//------------------------------------------------------------------------------
TEST_F(IRNullBlockCipherAlgorithmTest, setRawKey) {
	IRNullBlockCipherAlgorithm c(true, 8);

	for (unsigned int keySize = 1; keySize <= sizeof(CRYPTOSAMPLES_SAMPLE2); keySize++) {
		ASSERT_TRUE(c.setRawKey(CRYPTOSAMPLES_SAMPLE2, keySize));
	}
}

//------------------------------------------------------------------------------
TEST_F(IRNullBlockCipherAlgorithmTest, setKey) {
	IRNullBlockCipherAlgorithm c(true, 8);

	for (unsigned int keySize = 1; keySize <= sizeof(CRYPTOSAMPLES_SAMPLE2); keySize++) {
		IRSecretKeyImpl key(CRYPTOSAMPLES_SAMPLE2, keySize);
		ASSERT_TRUE(c.setKey(&key));
	}
}

//------------------------------------------------------------------------------
TEST_F(IRNullBlockCipherAlgorithmTest, blockSize) {

	for (unsigned int blockSize = 1; blockSize <= 64; blockSize++) {
		IRNullBlockCipherAlgorithm c(true, blockSize * 8);
		ASSERT_EQ(blockSize * 8, c.blockSize());
	}
}

//------------------------------------------------------------------------------
TEST_F(IRNullBlockCipherAlgorithmTest, processBlocksCipher) {
	IRNullBlockCipherAlgorithm c(true, 8 * 4);
	std::uint8_t dst[4 * 8 + 1];

	for (unsigned int blocks = 0; blocks <= 8 ; blocks++) {
		std::memset(dst, 0, sizeof(dst));
		ASSERT_TRUE(c.processBlocks(CRYPTOSAMPLES_SAMPLE2, dst, blocks));
		std::uint64_t size = 4 * blocks;
		ASSERT_EQ(0, dst[size]);
		ASSERT_EQ(0, std::memcmp(dst, CRYPTOSAMPLES_SAMPLE2, size));
	}
}

//------------------------------------------------------------------------------
TEST_F(IRNullBlockCipherAlgorithmTest, processBlocksDecipher) {
	IRNullBlockCipherAlgorithm c(false, 8 * 4);
	std::uint8_t dst[4 * 8 + 1];

	for (unsigned int blocks = 0; blocks <= 8 ; blocks++) {
		std::memset(dst, 0, sizeof(dst));
		ASSERT_TRUE(c.processBlocks(CRYPTOSAMPLES_SAMPLE2, dst, blocks));
		std::uint64_t size = 4 * blocks;
		ASSERT_EQ(0, dst[size]);
		ASSERT_EQ(0, std::memcmp(dst, CRYPTOSAMPLES_SAMPLE2, size));
	}
}

//------------------------------------------------------------------------------
