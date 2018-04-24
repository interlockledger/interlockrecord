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
#include "IRCBCBlockCipherModeTest.h"
#include "CryptoSamples.h"
#include <irecordcore/irbciphm.h>
#include <cstring>

using namespace irecordcore::crypto;
//==============================================================================
// class IRDummyCBCBlockCipherMode
//------------------------------------------------------------------------------
class IRDummyCBCBlockCipherMode : public IRCBCBlockCipherMode {
public:
	IRDummyCBCBlockCipherMode(IRBlockCipherAlgorithm * cipher,
			IRPadding * padding):IRCBCBlockCipherMode(cipher, padding) {}

	virtual ~IRDummyCBCBlockCipherMode() = default;

	const void * lastBlock() const {
		return this->_lastBlock.buff();
	}

	bool prepareBlockExp(std::uint8_t * src) {
		return this->prepareBlock(src);
	}

	bool postBlockExp(const std::uint8_t * src, std::uint8_t * dst) {
		return this->postBlock(src, dst);
	}
};


//==============================================================================
// class IRCBCBlockCipherModeTest
//------------------------------------------------------------------------------
IRCBCBlockCipherModeTest::IRCBCBlockCipherModeTest() {
}

//------------------------------------------------------------------------------
IRCBCBlockCipherModeTest::~IRCBCBlockCipherModeTest() {
}

//------------------------------------------------------------------------------
void IRCBCBlockCipherModeTest::SetUp() {
}

//------------------------------------------------------------------------------
void IRCBCBlockCipherModeTest::TearDown() {
}

//------------------------------------------------------------------------------
TEST_F(IRCBCBlockCipherModeTest,Constructor) {
	IRCBCBlockCipherMode * cm;
	std::uint8_t expectedIV[8];

	cm = new IRCBCBlockCipherMode(new IRNullBlockCipherAlgorithm(true, 8 * 8),
			new IRPKCS7Padding());
	ASSERT_EQ(typeid(const IRNullBlockCipherAlgorithm &), typeid(cm->cipher()));
	ASSERT_EQ(typeid(const IRPKCS7Padding &), typeid(cm->padding()));
	ASSERT_EQ(8, cm->blockSizeInBytes());
	std::memset(expectedIV, 0, sizeof(expectedIV));
	ASSERT_EQ(0, std::memcmp(expectedIV, cm->iv(), cm->blockSizeInBytes()));
	delete cm;
}

//------------------------------------------------------------------------------
TEST_F(IRCBCBlockCipherModeTest, iv) {
	IRCBCBlockCipherMode cme(new IRNullBlockCipherAlgorithm(true, 8 * 8),
			new IRPKCS7Padding());
	IRCBCBlockCipherMode cmd(new IRNullBlockCipherAlgorithm(false, 8 * 8),
			new IRPKCS7Padding());
	std::uint8_t expectedIV[8];

	std::memset(expectedIV, 0, sizeof(expectedIV));
	ASSERT_EQ(0, std::memcmp(expectedIV, cme.iv(), cme.blockSizeInBytes()));
	ASSERT_EQ(0, std::memcmp(expectedIV, cmd.iv(), cmd.blockSizeInBytes()));

	for (unsigned int size = 8; size <= sizeof(CRYPTOSAMPLES_SAMPLE5); size++) {
		ASSERT_TRUE(cme.setIV(CRYPTOSAMPLES_SAMPLE5, size));
		ASSERT_EQ(0, std::memcmp(CRYPTOSAMPLES_SAMPLE5, cme.iv(),
				cme.blockSizeInBytes()));
		ASSERT_TRUE(cmd.setIV(CRYPTOSAMPLES_SAMPLE5, size));
		ASSERT_EQ(0, std::memcmp(CRYPTOSAMPLES_SAMPLE5, cmd.iv(),
				cmd.blockSizeInBytes()));
	}

	for (unsigned int size = 0; size < 8; size++) {
		ASSERT_FALSE(cme.setIV(CRYPTOSAMPLES_SAMPLE5, size));
		ASSERT_FALSE(cmd.setIV(CRYPTOSAMPLES_SAMPLE5, size));
	}
}

//------------------------------------------------------------------------------
TEST_F(IRCBCBlockCipherModeTest, reset) {
	IRDummyCBCBlockCipherMode cme(new IRNullBlockCipherAlgorithm(true, 8 * 8),
			new IRPKCS7Padding());
	IRDummyCBCBlockCipherMode cmd(new IRNullBlockCipherAlgorithm(false, 8 * 8),
			new IRPKCS7Padding());
	std::uint8_t expectedIV[8];
	std::uint8_t dst[16];

	std::memset(expectedIV, 0, sizeof(expectedIV));
	for (unsigned int size = 8; size <= sizeof(CRYPTOSAMPLES_SAMPLE5); size++) {
		std::uint64_t dstSize = sizeof(dst);
		ASSERT_TRUE(cme.process(CRYPTOSAMPLES_SAMPLE5, 9, dst, dstSize, false));
		ASSERT_EQ(7, cme.remaining());
		ASSERT_EQ(0, std::memcmp(CRYPTOSAMPLES_SAMPLE5, cme.lastBlock(),
				cme.blockSizeInBytes()));
		cme.reset();
		ASSERT_EQ(8, cme.remaining());
		ASSERT_EQ(0, std::memcmp(expectedIV, cme.lastBlock(),
				cme.blockSizeInBytes()));

		dstSize = sizeof(dst);
		ASSERT_TRUE(cmd.process(CRYPTOSAMPLES_SAMPLE5, 9, dst, dstSize, false));
		ASSERT_EQ(7, cmd.remaining());
		ASSERT_EQ(0, std::memcmp(CRYPTOSAMPLES_SAMPLE5, cmd.lastBlock(),
				cmd.blockSizeInBytes()));
		cmd.reset();
		ASSERT_EQ(8, cmd.remaining());
		ASSERT_EQ(0, std::memcmp(expectedIV, cmd.lastBlock(),
				cmd.blockSizeInBytes()));
	}
}

//------------------------------------------------------------------------------
TEST_F(IRCBCBlockCipherModeTest, prepareBlock) {
	IRDummyCBCBlockCipherMode cme(new IRNullBlockCipherAlgorithm(true, 8 * 8),
			new IRPKCS7Padding());
	IRDummyCBCBlockCipherMode cmd(new IRNullBlockCipherAlgorithm(false, 8 * 8),
			new IRPKCS7Padding());
	std::uint8_t expectedBlock[8];
	std::uint8_t block[8];

	std::memset(expectedBlock, 0, sizeof(expectedBlock));
	ASSERT_TRUE(cme.setIV(CRYPTOSAMPLES_IV_8, sizeof(CRYPTOSAMPLES_IV_8)));
	ASSERT_TRUE(cmd.setIV(CRYPTOSAMPLES_IV_8, sizeof(CRYPTOSAMPLES_IV_8)));

	for (unsigned int offs = 0; offs < sizeof(CRYPTOSAMPLES_SAMPLE5);
			offs += 8) {
		// Cipher
		std::memcpy(block, CRYPTOSAMPLES_SAMPLE5 + offs, 8);
		cme.reset();
		for (int i = 0; i < 8; i++) {
			expectedBlock[i] = block[i] ^ CRYPTOSAMPLES_IV_8[i];
		}
		ASSERT_TRUE(cme.prepareBlockExp(block));
		ASSERT_EQ(0, std::memcmp(expectedBlock, block, 8));

		// Decipher
		std::memcpy(block, CRYPTOSAMPLES_SAMPLE5 + offs, 8);
		cmd.reset();
		ASSERT_TRUE(cmd.prepareBlockExp(block));
		ASSERT_EQ(0, std::memcmp(CRYPTOSAMPLES_SAMPLE5 + offs, block, 8));
		ASSERT_EQ(0, std::memcmp(CRYPTOSAMPLES_IV_8, cmd.lastBlock(), 8));
	}
}

//------------------------------------------------------------------------------
TEST_F(IRCBCBlockCipherModeTest, postBlock) {
	IRDummyCBCBlockCipherMode cme(new IRNullBlockCipherAlgorithm(true, 8 * 8),
			new IRPKCS7Padding());
	IRDummyCBCBlockCipherMode cmd(new IRNullBlockCipherAlgorithm(false, 8 * 8),
			new IRPKCS7Padding());
	std::uint8_t expectedBlock[8];
	std::uint8_t block[8];

	ASSERT_TRUE(cmd.setIV(CRYPTOSAMPLES_IV_8, sizeof(CRYPTOSAMPLES_IV_8)));
	for (unsigned int offs = 0; offs < sizeof(CRYPTOSAMPLES_SAMPLE5);
			offs += 8) {
		// Cipher
		std::memcpy(block, CRYPTOSAMPLES_SAMPLE5 + offs, 8);
		ASSERT_TRUE(cme.postBlockExp(CRYPTOSAMPLES_SAMPLE5 + offs, block));
		ASSERT_EQ(0, std::memcmp(CRYPTOSAMPLES_SAMPLE5 + offs, block, 8));
		ASSERT_EQ(0, std::memcmp(CRYPTOSAMPLES_SAMPLE5 + offs, cme.lastBlock(), 8));

		// Decipher
		cmd.reset();
		std::memcpy(block, CRYPTOSAMPLES_SAMPLE5 + offs, 8);
		for (int i = 0; i < 8; i++) {
			expectedBlock[i] = block[i] ^ CRYPTOSAMPLES_IV_8[i];
		}
		ASSERT_TRUE(cmd.postBlockExp(CRYPTOSAMPLES_SAMPLE5 + offs, block));
		ASSERT_EQ(0, std::memcmp(expectedBlock, block, 8));
		ASSERT_EQ(0, std::memcmp(CRYPTOSAMPLES_SAMPLE5 + offs, cme.lastBlock(), 8));
	}
}

//------------------------------------------------------------------------------
TEST_F(IRCBCBlockCipherModeTest, processEncryptFull) {
	IRCBCBlockCipherMode cm(new IRNullBlockCipherAlgorithm(true, 8 * 8),
			new IRPKCS7Padding());
	std::uint8_t dst[32];

	ASSERT_TRUE(cm.setIV(CRYPTOSAMPLES_IV_8, sizeof(CRYPTOSAMPLES_IV_8)));

	std::uint64_t dstSize = sizeof(dst);
	ASSERT_TRUE(cm.process(CRYPTOSAMPLES_SAMPLE4, sizeof(CRYPTOSAMPLES_SAMPLE4),
			dst, dstSize, true));
	ASSERT_EQ(sizeof(CRYPTOSAMPLES_SAMPLE4_PADDED_PKCS7_CBC), dstSize);

	ASSERT_EQ(0, std::memcmp(CRYPTOSAMPLES_SAMPLE4_PADDED_PKCS7_CBC, dst, dstSize));
}

//------------------------------------------------------------------------------
TEST_F(IRCBCBlockCipherModeTest, processDecryptFull) {
	IRCBCBlockCipherMode cm(new IRNullBlockCipherAlgorithm(false, 8 * 8),
			new IRPKCS7Padding());
	std::uint8_t dst[32];

	ASSERT_TRUE(cm.setIV(CRYPTOSAMPLES_IV_8, sizeof(CRYPTOSAMPLES_IV_8)));

	std::uint64_t dstSize = sizeof(dst);
	ASSERT_TRUE(cm.process(CRYPTOSAMPLES_SAMPLE4_PADDED_PKCS7_CBC,
			sizeof(CRYPTOSAMPLES_SAMPLE4_PADDED_PKCS7_CBC),
			dst, dstSize, true));

	ASSERT_EQ(sizeof(CRYPTOSAMPLES_SAMPLE4), dstSize);
	ASSERT_EQ(0, std::memcmp(CRYPTOSAMPLES_SAMPLE4, dst, dstSize));
}

//------------------------------------------------------------------------------

