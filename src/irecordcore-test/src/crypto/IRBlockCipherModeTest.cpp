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
#include "IRBlockCipherModeTest.h"
#include "CryptoSamples.h"
#include <irecordcore/irbciphm.h>
#include <cstring>

using namespace irecordcore::crypto;

//==============================================================================
// class IRBlockCipherModeTest
//------------------------------------------------------------------------------
IRBlockCipherModeTest::IRBlockCipherModeTest() {
}

//------------------------------------------------------------------------------
IRBlockCipherModeTest::~IRBlockCipherModeTest() {
}

//------------------------------------------------------------------------------
void IRBlockCipherModeTest::SetUp() {
}

//------------------------------------------------------------------------------
void IRBlockCipherModeTest::TearDown() {
}

//------------------------------------------------------------------------------
TEST_F(IRBlockCipherModeTest, Constructor) {
	IRBlockCipherMode * cm;

	cm = new IRBlockCipherMode(new IRNullBlockCipherAlgorithm(true, 64),
			new IRPKCS7Padding());
	ASSERT_EQ(typeid(const IRNullBlockCipherAlgorithm &), typeid(cm->cipher()));
	ASSERT_EQ(typeid(const IRPKCS7Padding &), typeid(cm->padding()));
	ASSERT_EQ(8, cm->blockSizeInBytes());
	delete cm;
}

//------------------------------------------------------------------------------
TEST_F(IRBlockCipherModeTest, blockSizeInBytes) {

	for (unsigned int size = 1; size < 16; size++) {
		IRBlockCipherMode cm(new IRNullBlockCipherAlgorithm(true, size * 8),
				new IRPKCS7Padding());
		ASSERT_EQ(size, cm.blockSizeInBytes());
	}
}

//------------------------------------------------------------------------------
TEST_F(IRBlockCipherModeTest, cipherMode) {
	IRBlockCipherMode cme(new IRNullBlockCipherAlgorithm(true, 8),
			new IRPKCS7Padding());
	IRBlockCipherMode cmd(new IRNullBlockCipherAlgorithm(false, 8),
			new IRPKCS7Padding());

	ASSERT_TRUE(cme.cipherMode());
	ASSERT_FALSE(cmd.cipherMode());
}

//------------------------------------------------------------------------------
TEST_F(IRBlockCipherModeTest, getOutputSize) {
	IRBlockCipherMode cme(new IRNullBlockCipherAlgorithm(true, 4 * 8),
			new IRPKCS7Padding());
	IRBlockCipherMode cmd(new IRNullBlockCipherAlgorithm(false, 4 * 8),
			new IRPKCS7Padding());

	for (std::uint64_t srcSize = 0; srcSize < 16; srcSize++) {
		std::uint64_t encSize = srcSize + (4 - (srcSize % 4));
		ASSERT_EQ(encSize, cme.getOutputSize(srcSize));
		ASSERT_EQ(srcSize, cmd.getOutputSize(srcSize));
	}
}

//------------------------------------------------------------------------------
TEST_F(IRBlockCipherModeTest, remaining) {
	IRBlockCipherMode cm(new IRNullBlockCipherAlgorithm(true, 16 * 8),
			new IRPKCS7Padding());
	std::uint8_t dst[32];

	for (unsigned int i = 0; i < 15; i++) {
		ASSERT_EQ(16 - i, cm.remaining());
		std::uint64_t dstSize = sizeof(dst);
		ASSERT_TRUE(cm.process(CRYPTOSAMPLES_SAMPLE4 + i, 1, dst, dstSize));
		ASSERT_EQ(0, dstSize);
		ASSERT_EQ(16 - i - 1, cm.remaining());
	}

	ASSERT_EQ(1, cm.remaining());
	std::uint64_t dstSize = sizeof(dst);
	ASSERT_TRUE(cm.process(CRYPTOSAMPLES_SAMPLE4 + 15, 1, dst, dstSize));
	ASSERT_EQ(16, dstSize);
	ASSERT_EQ(16, cm.remaining());
	ASSERT_EQ(0, std::memcmp(CRYPTOSAMPLES_SAMPLE4, dst, 16));
}

//------------------------------------------------------------------------------
TEST_F(IRBlockCipherModeTest, reset) {
	IRBlockCipherMode cme(new IRNullBlockCipherAlgorithm(true, 16 * 8),
			new IRPKCS7Padding());
	IRBlockCipherMode cmd(new IRNullBlockCipherAlgorithm(false, 16 * 8),
			new IRPKCS7Padding());
	std::uint8_t dst[32];

	for (unsigned int i = 0; i < 15; i++) {
		std::uint64_t dstSize = sizeof(dst);
		ASSERT_TRUE(cme.process(CRYPTOSAMPLES_SAMPLE4, i, dst, dstSize));
		ASSERT_EQ(16 - i, cme.remaining());
		cme.reset();
		ASSERT_EQ(16, cme.remaining());
	}

	for (unsigned int i = 0; i < 15; i++) {
		std::uint64_t dstSize = sizeof(dst);
		ASSERT_TRUE(cmd.process(CRYPTOSAMPLES_SAMPLE4, i, dst, dstSize));
		ASSERT_EQ(16 - i, cmd.remaining());
		cmd.reset();
		ASSERT_EQ(16, cmd.remaining());
	}
}

//------------------------------------------------------------------------------
TEST_F(IRBlockCipherModeTest, processEmptyFull) {
	IRBlockCipherMode cme(new IRNullBlockCipherAlgorithm(true, 4 * 8),
			new IRPKCS7Padding());
	IRBlockCipherMode cmd(new IRNullBlockCipherAlgorithm(false, 4 * 8),
			new IRPKCS7Padding());
	std::uint64_t dstSize;
	std::uint8_t dst[32];
	std::uint8_t exp[32];

	dstSize = sizeof(dst);
	ASSERT_TRUE(cme.process(CRYPTOSAMPLES_SAMPLE4, 0, dst, dstSize, true));
	ASSERT_EQ(4, dstSize);
	std::memset(exp, 4, sizeof(exp));
	ASSERT_EQ(0, std::memcmp(exp, dst, dstSize));

	dstSize = sizeof(dst);
	ASSERT_FALSE(cmd.process(CRYPTOSAMPLES_SAMPLE4, 0, dst, dstSize, true));
}

//------------------------------------------------------------------------------
TEST_F(IRBlockCipherModeTest, processEncryptFull) {
	IRBlockCipherMode cm(new IRNullBlockCipherAlgorithm(true, 4 * 8),
			new IRPKCS7Padding());
	std::uint8_t dst[32];

	std::uint64_t dstSize = sizeof(dst);
	ASSERT_TRUE(cm.process(CRYPTOSAMPLES_SAMPLE4, sizeof(CRYPTOSAMPLES_SAMPLE4),
			dst, dstSize, true));
	ASSERT_EQ(sizeof(CRYPTOSAMPLES_SAMPLE4_PADDED_PKCS7), dstSize);
	ASSERT_EQ(0, std::memcmp(CRYPTOSAMPLES_SAMPLE4_PADDED_PKCS7, dst, dstSize));
}

//------------------------------------------------------------------------------
TEST_F(IRBlockCipherModeTest, processDecryptFull) {
	IRBlockCipherMode cm(new IRNullBlockCipherAlgorithm(false, 8 * 8),
			new IRPKCS7Padding());
	std::uint8_t dst[32];

	std::uint64_t dstSize = sizeof(CRYPTOSAMPLES_SAMPLE4_PADDED_PKCS7);
	ASSERT_TRUE(cm.process(CRYPTOSAMPLES_SAMPLE4_PADDED_PKCS7,
			sizeof(CRYPTOSAMPLES_SAMPLE4_PADDED_PKCS7),
			dst, dstSize, true));
	ASSERT_EQ(sizeof(CRYPTOSAMPLES_SAMPLE4), dstSize);
	ASSERT_EQ(0, std::memcmp(CRYPTOSAMPLES_SAMPLE4, dst, dstSize));
}


//------------------------------------------------------------------------------
TEST_F(IRBlockCipherModeTest, processCipher) {
	IRBlockCipherMode cm(new IRNullBlockCipherAlgorithm(true, 8 * 8),
			new IRPKCS7Padding());
	std::uint8_t dst[32];
	ircommon::IRBuffer out;
	std::uint64_t dstSize;

	// Increments of 1
	for (unsigned int i = 0; i < sizeof(CRYPTOSAMPLES_SAMPLE4); i++) {
		dstSize = sizeof(dst);
		ASSERT_TRUE(cm.process(CRYPTOSAMPLES_SAMPLE4 + i, 1,
				dst, dstSize));
		ASSERT_TRUE(out.write(dst, dstSize));
	}

	dstSize = sizeof(dst);
	ASSERT_TRUE(cm.process(NULL, 0,
			dst, dstSize, true));
	ASSERT_TRUE(out.write(dst, dstSize));
	ASSERT_EQ(sizeof(CRYPTOSAMPLES_SAMPLE4_PADDED_PKCS7), out.size());
	ASSERT_EQ(0, std::memcmp(CRYPTOSAMPLES_SAMPLE4_PADDED_PKCS7, out.roBuffer(),
			out.size()));

	// Increments of 2
	out.setSize(0);
	cm.reset();
	for (unsigned int i = 0; i < sizeof(CRYPTOSAMPLES_SAMPLE4); i += 2) {
		dstSize = sizeof(dst);
		ASSERT_TRUE(cm.process(CRYPTOSAMPLES_SAMPLE4 + i, 2,
				dst, dstSize));
		ASSERT_TRUE(out.write(dst, dstSize));
	}

	dstSize = sizeof(dst);
	ASSERT_TRUE(cm.process(NULL, 0,
			dst, dstSize, true));
	ASSERT_TRUE(out.write(dst, dstSize));
	ASSERT_EQ(sizeof(CRYPTOSAMPLES_SAMPLE4_PADDED_PKCS7), out.size());
	ASSERT_EQ(0, std::memcmp(CRYPTOSAMPLES_SAMPLE4_PADDED_PKCS7, out.roBuffer(),
			out.size()));
}

//------------------------------------------------------------------------------
TEST_F(IRBlockCipherModeTest, processDecipher) {
	IRBlockCipherMode cm(new IRNullBlockCipherAlgorithm(false, 8 * 8),
			new IRPKCS7Padding());
	std::uint8_t dst[32];
	ircommon::IRBuffer out;
	std::uint64_t dstSize;

	// Increments of 1
	for (unsigned int i = 0; i < sizeof(CRYPTOSAMPLES_SAMPLE4_PADDED_PKCS7) - 1; i++) {
		dstSize = sizeof(dst);
		ASSERT_TRUE(cm.process(CRYPTOSAMPLES_SAMPLE4_PADDED_PKCS7 + i, 1,
				dst, dstSize));
		ASSERT_TRUE(out.write(dst, dstSize));
	}

	dstSize = sizeof(dst);
	ASSERT_TRUE(cm.process(CRYPTOSAMPLES_SAMPLE4_PADDED_PKCS7 +
			(sizeof(CRYPTOSAMPLES_SAMPLE4_PADDED_PKCS7) - 1), 1,
			dst, dstSize, true));
	ASSERT_TRUE(out.write(dst, dstSize));
	ASSERT_EQ(sizeof(CRYPTOSAMPLES_SAMPLE4), out.size());
	ASSERT_EQ(0, std::memcmp(CRYPTOSAMPLES_SAMPLE4, out.roBuffer(),
			out.size()));

	// Increments of 2
	out.setSize(0);
	cm.reset();
	for (unsigned int i = 0; i < sizeof(CRYPTOSAMPLES_SAMPLE4_PADDED_PKCS7) - 2; i += 2) {
		dstSize = sizeof(dst);
		ASSERT_TRUE(cm.process(CRYPTOSAMPLES_SAMPLE4_PADDED_PKCS7 + i, 2,
				dst, dstSize));
		ASSERT_TRUE(out.write(dst, dstSize));
	}

	dstSize = sizeof(dst);
	ASSERT_TRUE(cm.process(CRYPTOSAMPLES_SAMPLE4_PADDED_PKCS7 +
			(sizeof(CRYPTOSAMPLES_SAMPLE4_PADDED_PKCS7) - 2), 2,
			dst, dstSize, true));
	ASSERT_TRUE(out.write(dst, dstSize));
	ASSERT_EQ(sizeof(CRYPTOSAMPLES_SAMPLE4), out.size());
	ASSERT_EQ(0, std::memcmp(CRYPTOSAMPLES_SAMPLE4, out.roBuffer(),
			out.size()));
}
//------------------------------------------------------------------------------

