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
#include <irecordcore/irbciphm.h>
#include <cstring>
#include <algorithm>

using namespace irecordcore::crypto;

//==============================================================================
// Class IRBlockCipherMode
//------------------------------------------------------------------------------
IRBlockCipherMode::IRBlockCipherMode(IRBlockCipherAlgorithm * cipher,
		IRPadding * padding) : _padding(padding), _cipher(cipher),
				_tmpBlock(cipher->blockSizeInBytes()) {
}

//------------------------------------------------------------------------------
bool IRBlockCipherMode::processBlock(std::uint8_t * src, std::uint8_t * dst) {

	if (!this->prepareBlock(src)) {
		return false;
	}
	if (!this->cipherDecipherBlock(src, dst)){
		return false;
	}
	return this->postBlock(src, dst);
}

//------------------------------------------------------------------------------
bool IRBlockCipherMode::prepareBlock(std::uint8_t * src) {
	return true;
}

//------------------------------------------------------------------------------
bool IRBlockCipherMode::cipherDecipherBlock(std::uint8_t * src,
		std::uint8_t * dst) {
	return this->_cipher->processBlocks(src, dst, 1);
}

//------------------------------------------------------------------------------
bool IRBlockCipherMode::postBlock(const std::uint8_t * src, std::uint8_t * dst) {
	return true;
}

//------------------------------------------------------------------------------
std::uint64_t IRBlockCipherMode::getOutputSize(std::uint64_t srcSize) const {

	if (this->cipherMode()) {
		return srcSize + (this->cipher().blockSizeInBytes() -
				(srcSize % this->cipher().blockSizeInBytes()));
	} else {
		return srcSize;
	}
}

//------------------------------------------------------------------------------
void IRBlockCipherMode::reset() {
	this->_tmpBlock.reset();
}

//------------------------------------------------------------------------------
bool IRBlockCipherMode::process(const void * src, std::uint64_t srcSize,
		void * dst, std::uint64_t & dstSize, bool last) {
	const std::uint8_t * pSrc;
	std::uint8_t * pDst;
	std::uint64_t processedSize;

	if (this->cipherMode()) {
		if (dstSize < this->getOutputSize(srcSize)) {
			return false;
		}
	} else {
		if (dstSize < srcSize) {
			return false;
		}
	}

	processedSize = 0;
	pSrc = (const std::uint8_t *) src;
	pDst = (std::uint8_t *) dst;
	while (srcSize) {
		std::uint64_t needed = std::min(srcSize,
				this->_tmpBlock.remaining());
		srcSize -= needed;
		std::memcpy(this->_tmpBlock.posBuff(), pSrc, needed);
		this->_tmpBlock.setPosition(this->_tmpBlock.position() + needed);
		if (this->_tmpBlock.position() == this->blockSizeInBytes()) {
			if (this->processBlock(this->_tmpBlock.buff(), pDst)) {
				this->_tmpBlock.reset();
				pDst += this->blockSizeInBytes();
				pSrc += this->blockSizeInBytes();
				processedSize += this->_tmpBlock.size();
			} else {
				return false;
			}
		}
	}

	if (last) {
		if (this->cipherMode()) {
			std::uint64_t blockSize = this->blockSizeInBytes();
			if (!this->padding().addPadding(blockSize,
					this->_tmpBlock.buff(), this->_tmpBlock.position(),
					this->_tmpBlock.buff(), blockSize)) {
				return false;
			}
			if (!this->processBlock(this->_tmpBlock.buff(), pDst)) {
				return false;
			}
			processedSize += blockSize;
		} else {
			if (this->_tmpBlock.position() == this->blockSizeInBytes()) {
				return false;
			}

			// Remove the padding
			std::uint64_t blockSize = this->blockSizeInBytes();
			pDst -= blockSize;
			if (!this->padding().removePadding(blockSize, pDst,
					blockSize)){
				return false;
			}
			processedSize -= (this->blockSizeInBytes() - blockSize);
		}
	}
	dstSize = processedSize;
	return true;
}

//==============================================================================
// Class IRCBCBlockCipherMode
//------------------------------------------------------------------------------
IRCBCBlockCipherMode::IRCBCBlockCipherMode(IRBlockCipherAlgorithm * cipher,
		IRPadding * padding): IRBlockCipherMode(cipher, padding),
				_iv(cipher->blockSizeInBytes()),
				_lastBlock(cipher->blockSizeInBytes()){
	this->_iv.clear();
	this->_lastBlock.clear();
}

//------------------------------------------------------------------------------
void IRCBCBlockCipherMode::xorBlock(const std::uint8_t * src, std::uint8_t * dst) {
	const std::uint8_t * srcEnd;

	srcEnd = src + this->blockSizeInBytes();
	for ( ; src != srcEnd; src++, dst++) {
		(*dst) = (*dst) ^ (*src);
	}

}


//------------------------------------------------------------------------------
bool IRCBCBlockCipherMode::IRCBCBlockCipherMode::prepareBlock(std::uint8_t * plain) {

	if (this->cipherMode()) {
		this->xorBlock(this->_lastBlock.buff(), plain);
	}
	return true;
}

//------------------------------------------------------------------------------
bool IRCBCBlockCipherMode::IRCBCBlockCipherMode::postBlock(
		const std::uint8_t * src, std::uint8_t * block) {

	if (this->cipherMode()) {
		std::memcpy(this->_lastBlock.buff(), block, this->blockSizeInBytes());
	} else {
		this->xorBlock(this->_lastBlock.buff(), block);
		std::memcpy(this->_lastBlock.buff(), src, this->blockSizeInBytes());
	}
	return true;
}

//------------------------------------------------------------------------------
bool IRCBCBlockCipherMode::setIV(const void * iv, std::uint64_t ivSize) {

	if (ivSize < this->blockSizeInBytes()) {
		return false;
	} else {
		std::memcpy(this->_iv.buff(), iv, this->blockSizeInBytes());
		this->reset();
		return true;
	}
}

//------------------------------------------------------------------------------
void IRCBCBlockCipherMode::reset() {
	IRBlockCipherMode::reset();
	std::memcpy(this->_lastBlock.buff(), this->_iv.buff(), this->_iv.size());
}

//------------------------------------------------------------------------------
