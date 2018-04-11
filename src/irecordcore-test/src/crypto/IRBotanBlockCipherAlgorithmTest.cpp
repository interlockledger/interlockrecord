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
	IRDummyBotanBlockCipherAlgorithm ct(true);
	IRDummyBotanBlockCipherAlgorithm cf(true);

	ASSERT_EQ(192, ct.minKeySize());
	ASSERT_EQ(192, ct.maxKeySize());

	ASSERT_FALSE(ct.isValidKeySize(0));
	ASSERT_FALSE(ct.isValidKeySize(191));
	ASSERT_TRUE(ct.isValidKeySize(192));
	ASSERT_FALSE(ct.isValidKeySize(193));

	ASSERT_EQ(192, cf.minKeySize());
	ASSERT_EQ(192, cf.maxKeySize());

	ASSERT_FALSE(cf.isValidKeySize(0));
	ASSERT_FALSE(cf.isValidKeySize(191));
	ASSERT_TRUE(cf.isValidKeySize(192));
	ASSERT_FALSE(cf.isValidKeySize(193));
}

//------------------------------------------------------------------------------
TEST_F(IRBotanBlockCipherAlgorithmTest, blockSize) {
	IRDummyBotanBlockCipherAlgorithm ct(true);
	IRDummyBotanBlockCipherAlgorithm cf(true);

	ASSERT_EQ(128, ct.blockSize());
	ASSERT_EQ(16, ct.blockSizeInBytes());

	ASSERT_EQ(128, cf.blockSize());
	ASSERT_EQ(16, cf.blockSizeInBytes());
}

//------------------------------------------------------------------------------
TEST_F(IRBotanBlockCipherAlgorithmTest, setRawKey) {
	IRDummyBotanBlockCipherAlgorithm ct(true);
	IRDummyBotanBlockCipherAlgorithm cf(true);

	ASSERT_FALSE(ct.setRawKey(CRYPTOSAMPLES_KEY256, 0));
	ASSERT_FALSE(ct.setRawKey(CRYPTOSAMPLES_KEY256, 23));
	ASSERT_TRUE(ct.setRawKey(CRYPTOSAMPLES_KEY256, 24));
	ASSERT_FALSE(ct.setRawKey(CRYPTOSAMPLES_KEY256, 25));

	ASSERT_FALSE(cf.setRawKey(CRYPTOSAMPLES_KEY256, 0));
	ASSERT_FALSE(cf.setRawKey(CRYPTOSAMPLES_KEY256, 23));
	ASSERT_TRUE(cf.setRawKey(CRYPTOSAMPLES_KEY256, 24));
	ASSERT_FALSE(cf.setRawKey(CRYPTOSAMPLES_KEY256, 25));
}


//------------------------------------------------------------------------------

