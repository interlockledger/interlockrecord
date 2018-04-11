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
