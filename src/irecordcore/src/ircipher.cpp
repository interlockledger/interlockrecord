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
#include <irecordcore/ircipher.h>
#include <ircommon/irutils.h>
#include <cstring>

using namespace irecordcore;
using namespace irecordcore::crypto;

//==============================================================================
// Class IRBlockCipherAlgorithm
//------------------------------------------------------------------------------
IRBlockCipherAlgorithm::IRBlockCipherAlgorithm(bool cipherMode):
		IRCipherAlgorithm(cipherMode) {
}

//------------------------------------------------------------------------------
unsigned int IRBlockCipherAlgorithm::blockSizeInBytes() const {
	return this->blockSize() / 8;
}

//------------------------------------------------------------------------------
bool IRBlockCipherAlgorithm::process(const void * src, std::uint64_t srcSize,
		void * dst, std::uint64_t & dstSize) {

	if (srcSize == 0) {
		dstSize = srcSize;
		return true;
	}
	if (srcSize % this->blockSizeInBytes()) {
		return false;
	}
	if (dstSize < srcSize) {
		return false;
	}
	if (this->processBlocks(src, dst, srcSize / this->blockSizeInBytes())) {
		dstSize = srcSize;
		return true;
	} else {
		return false;
	}
}

//------------------------------------------------------------------------------
bool IRBlockCipherAlgorithm::setKey(IRSecretKey * key) {
	std::uint64_t rawKeySize;

	if (!this->isValidKeySize(key->size())) {
		return false;
	}
	if (!key->exportable()) {
		return false;
	}
	rawKeySize = key->sizeInBytes();
	if (rawKeySize == 0) {
		return false;
	}

	ircommon::IRUtils::IRSecureTemp rawKey(rawKeySize);
	if (key->exportKey(rawKey.buff(), rawKeySize)) {
		return this->setRawKey((const void *)rawKey.buff(), rawKeySize);
	} else {
		return false;
	}
}

//==============================================================================
// Class IRNullBlockCipherAlgorithm
//------------------------------------------------------------------------------
IRNullBlockCipherAlgorithm::IRNullBlockCipherAlgorithm(bool cipherMode,
		unsigned int blockSize):IRBlockCipherAlgorithm(cipherMode),
				_blockSize(blockSize) {
	if ((this->_blockSize == 0) || (this->_blockSize % 8)) {
		throw std::invalid_argument(
				"The block size must multiple of 8 larger than 0.");
	}
}

//------------------------------------------------------------------------------
unsigned int IRNullBlockCipherAlgorithm::minKeySize() const {
	return 0;
}

//------------------------------------------------------------------------------
unsigned int IRNullBlockCipherAlgorithm::maxKeySize() const {
	return ~((unsigned int)0);
}

//------------------------------------------------------------------------------
bool IRNullBlockCipherAlgorithm::isValidKeySize(unsigned int keySize) const {
	return true;
}

//------------------------------------------------------------------------------
bool IRNullBlockCipherAlgorithm::setRawKey(const void * key, std::uint64_t keySize) {
	return true;
}

//------------------------------------------------------------------------------
bool IRNullBlockCipherAlgorithm::setKey(IRSecretKey * key) {
	return true;
}

//------------------------------------------------------------------------------
unsigned int IRNullBlockCipherAlgorithm::blockSize() const {
	return this->_blockSize;
}

//------------------------------------------------------------------------------
bool IRNullBlockCipherAlgorithm::processBlocks(const void * src, void * dst,
		unsigned int blockCount) {
	std::uint64_t size;

	size = this->blockSizeInBytes() * blockCount;
	std::memcpy(dst, src, size);
	return true;
}

//------------------------------------------------------------------------------
