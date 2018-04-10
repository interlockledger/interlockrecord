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
#include "IRBlockCipherAlgorithmTest.h"
#include <irecordcore/ircipher.h>
#include <ircommon/irbuffer.h>
#include <cstring>
#include "CryptoSamples.h"

using namespace irecordcore::crypto;

//==============================================================================
// class IRDummyBlockCipherAlgorithm
//------------------------------------------------------------------------------
class IRDummyBlockCipherAlgorithm: public IRBlockCipherAlgorithm {
private:
	ircommon::IRBuffer _key;
public:
	IRDummyBlockCipherAlgorithm(bool cipherMode):
			IRBlockCipherAlgorithm(cipherMode) {
	}

	virtual ~IRDummyBlockCipherAlgorithm() = default;

	virtual unsigned int minKeySize() const override;

	virtual unsigned int maxKeySize() const override;

	virtual bool isValidKeySize(unsigned int keySize) const override;

	virtual bool setRawKey(const void * key, std::uint64_t keySize) override;

	virtual unsigned int blockSize() const override;

	virtual bool processBlocks(const void * src, void * dst,
			unsigned int blockCount) override;

	ircommon::IRBuffer & key() {
		return this->_key;
	}
};

//------------------------------------------------------------------------------
unsigned int IRDummyBlockCipherAlgorithm::minKeySize() const {
	return 8;
}

//------------------------------------------------------------------------------
unsigned int IRDummyBlockCipherAlgorithm::maxKeySize() const {
	return 8 * 4;
}

//------------------------------------------------------------------------------
bool IRDummyBlockCipherAlgorithm::isValidKeySize(unsigned int keySize) const {
	return (keySize >= this->minKeySize()) && (keySize <= this->maxKeySize());
}

//------------------------------------------------------------------------------
bool IRDummyBlockCipherAlgorithm::setRawKey(const void * key, std::uint64_t keySize) {
	return this->_key.set(key, keySize);
}

//------------------------------------------------------------------------------
unsigned int IRDummyBlockCipherAlgorithm::blockSize() const {
	return 8 * 4;
}

//------------------------------------------------------------------------------
bool IRDummyBlockCipherAlgorithm::processBlocks(const void * src, void * dst,
		unsigned int blockCount) {
	std::uint64_t size;

	size = blockCount * this->blockSizeInBytes();
	std::memcpy(dst, src, size);
	return true;
}


//==============================================================================
// class IRBlockCipherAlgorithmTest
//------------------------------------------------------------------------------
IRBlockCipherAlgorithmTest::IRBlockCipherAlgorithmTest() {
}

//------------------------------------------------------------------------------
IRBlockCipherAlgorithmTest::~IRBlockCipherAlgorithmTest() {
}

//------------------------------------------------------------------------------
void IRBlockCipherAlgorithmTest::SetUp() {
}

//------------------------------------------------------------------------------
void IRBlockCipherAlgorithmTest::TearDown() {
}

//------------------------------------------------------------------------------
TEST_F(IRBlockCipherAlgorithmTest, Constructor) {
	IRDummyBlockCipherAlgorithm * c;

	c = new IRDummyBlockCipherAlgorithm(true);
	ASSERT_TRUE(c->cipherMode());
	delete c;

	c = new IRDummyBlockCipherAlgorithm(false);
	ASSERT_FALSE(c->cipherMode());
	delete c;
}

//------------------------------------------------------------------------------
TEST_F(IRBlockCipherAlgorithmTest, keySize) {
	IRDummyBlockCipherAlgorithm c(true);

	ASSERT_EQ(8, c.minKeySize());
	ASSERT_EQ(8 * 4, c.maxKeySize());

	ASSERT_FALSE(c.isValidKeySize(0));
	ASSERT_FALSE(c.isValidKeySize(7));
	ASSERT_TRUE(c.isValidKeySize(8));
	ASSERT_TRUE(c.isValidKeySize(16));
	ASSERT_TRUE(c.isValidKeySize(32));
	ASSERT_FALSE(c.isValidKeySize(33));
}

//------------------------------------------------------------------------------
TEST_F(IRBlockCipherAlgorithmTest, setRawKey) {
	IRDummyBlockCipherAlgorithm c(true);

	// Note: This implementation adds no restriction.
	for (unsigned int keySize = 0; keySize < sizeof(CRYPTOSAMPLES_SAMPLE2); keySize++) {
		ASSERT_TRUE(c.setRawKey(CRYPTOSAMPLES_SAMPLE2, keySize));
		ASSERT_EQ(keySize, c.key().size());
		ASSERT_EQ(0, std::memcmp(c.key().roBuffer(), CRYPTOSAMPLES_SAMPLE2, keySize));
	}
}

//------------------------------------------------------------------------------
TEST_F(IRBlockCipherAlgorithmTest, blockSize) {
	IRDummyBlockCipherAlgorithm c(true);

	ASSERT_EQ(8 * 4, c.blockSize());
}

//------------------------------------------------------------------------------
TEST_F(IRBlockCipherAlgorithmTest, processBlock) {
	IRDummyBlockCipherAlgorithm c(true);
	std::uint8_t dst[33];

	for (unsigned int blocks = 0; blocks < 8; blocks++) {
		std::memset(dst, 0, sizeof(dst));
		ASSERT_TRUE(c.processBlocks(CRYPTOSAMPLES_SAMPLE, dst, blocks));
		std::uint64_t size = blocks * 4;
		ASSERT_EQ(0, std::memcmp(CRYPTOSAMPLES_SAMPLE, dst, size));
		ASSERT_EQ(0, dst[size]);
	}
}

//------------------------------------------------------------------------------
TEST_F(IRBlockCipherAlgorithmTest, blockSizeInBytes) {
	IRDummyBlockCipherAlgorithm c(true);

	ASSERT_EQ(4, c.blockSizeInBytes());
}

//------------------------------------------------------------------------------
TEST_F(IRBlockCipherAlgorithmTest, setKey) {
	IRDummyBlockCipherAlgorithm c(true);

	for (unsigned int keySize = 0; keySize < 32; keySize++) {
		IRSecretKeyImpl key(CRYPTOSAMPLES_SAMPLE, keySize);
		c.key().setSize(0);
		if (c.isValidKeySize(keySize * 8)) {
			ASSERT_TRUE(c.setKey(&key));
			ASSERT_EQ(keySize, c.key().size());
			ASSERT_EQ(0, std::memcmp(CRYPTOSAMPLES_SAMPLE,
					c.key().roBuffer(), keySize));
		} else {
			ASSERT_FALSE(c.setKey(&key));
			ASSERT_EQ(0, c.key().size());
		}
	}
}


//------------------------------------------------------------------------------
TEST_F(IRBlockCipherAlgorithmTest, process) {
	IRDummyBlockCipherAlgorithm c(true);
	std::uint8_t dst[33];
	std::uint64_t dstSize;

	for (unsigned int size = 0; size < 32; size += 4) {
		std::memset(dst, 0, sizeof(dst));
		dstSize= 32;
		ASSERT_TRUE(c.process(CRYPTOSAMPLES_SAMPLE, size, dst, dstSize));
		ASSERT_EQ(size, dstSize);
		ASSERT_EQ(0, std::memcmp(CRYPTOSAMPLES_SAMPLE, dst, size));
		ASSERT_EQ(0, dst[size]);
	}

	// Fail - not aligned with a block
	std::memset(dst, 0, sizeof(dst));
	dstSize = 32;
	ASSERT_FALSE(c.process(CRYPTOSAMPLES_SAMPLE, 1, dst, dstSize));
	ASSERT_EQ(32, dstSize);
	ASSERT_EQ(0, dst[0]);

	// Fail - output to small
	std::memset(dst, 0, sizeof(dst));
	dstSize = 32;
	ASSERT_FALSE(c.process(CRYPTOSAMPLES_SAMPLE, 36, dst, dstSize));
	ASSERT_EQ(32, dstSize);
	ASSERT_EQ(0, dst[0]);

}

//------------------------------------------------------------------------------

