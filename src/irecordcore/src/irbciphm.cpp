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
#include <irecordcore/irbciphm.h>
#include <cstring>
#include <algorithm>

using namespace irecordcore::crypto;

//==============================================================================
// Class IRBlockCipherMode
//------------------------------------------------------------------------------
IRBlockCipherMode::IRBlockCipherMode(IRPadding * padding,
		IRBlockCipherAlgorithm * cipher) : _padding(padding), _cipher(cipher),
				_tmpBlock(cipher->blockSizeInBytes()) {
}

//------------------------------------------------------------------------------
bool IRBlockCipherMode::processBlock(void * plain, void * enc) {

	if (!this->prepareBlock(plain)) {
		return false;
	}
	if (!this->_cipher->processBlocks(plain, enc, 1)){
		return false;
	}
	return this->postBlock(enc);
}

//------------------------------------------------------------------------------
bool IRBlockCipherMode::prepareBlock(void * plain) {
	return true;
}

//------------------------------------------------------------------------------
bool IRBlockCipherMode::postBlock(const void * block) {
	return true;
}

//------------------------------------------------------------------------------
std::uint64_t IRBlockCipherMode::getOutputSize(std::uint64_t srcSize) const {
	return srcSize + (this->cipher().blockSizeInBytes() -
			(srcSize % this->cipher().blockSizeInBytes()));
}

//------------------------------------------------------------------------------
void IRBlockCipherMode::reset() {
	this->_tmpBlock.position(0);
}

//------------------------------------------------------------------------------
bool IRBlockCipherMode::process(const void * src, std::uint64_t srcSize,
		void * dst, std::uint64_t & dstSize, bool last) {
	const std::uint8_t * pSrc;
	std::uint8_t * pDst;
	std::uint64_t processedSize;

	if (dstSize < this->getOutputSize(srcSize)) {
		return false;
	}

	processedSize = 0;
	pSrc = (const std::uint8_t *) src;
	pDst = (std::uint8_t *) dst;
	while (srcSize) {
		std::uint64_t needed = std::min(srcSize,
				this->_tmpBlock.remaining());
		srcSize -= needed;
		std::memcpy(this->_tmpBlock.posBuff(), pSrc, needed);
		if (this->_tmpBlock.position() == this->blockSizeInBytes()) {
			if (this->processBlock(this->_tmpBlock.buff(), pDst)) {
				this->_tmpBlock.setPosition(0);
				pDst += this->blockSizeInBytes();
				pSrc += this->blockSizeInBytes();
				processedSize += this->_tmpBlock.size();
			} else {
				return false;
			}
		}
	}

	if (last) {
		if (this->cipher().cipherMode()) {
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
			if (this->_tmpBlock.position() == this->_tmpBlock.size()) {
				if (!this->processBlock(this->_tmpBlock.buff(), pDst)) {
					return false;
				}
				this->_tmpBlock.setPosition(0);
				std::uint64_t blockSize;
				blockSize = this->blockSizeInBytes();
				if (!this->padding().removePadding(this->blockSizeInBytes(), pDst,
						blockSize)){
					return false;
				}
				processedSize += blockSize;
			} else {
				return false;
			}
		}
	}
	dstSize = processedSize;
	return true;
}

//------------------------------------------------------------------------------