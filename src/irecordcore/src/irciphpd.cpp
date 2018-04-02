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
#include <irecordcore/irciphpd.h>
#include <cstring>

using namespace irecordcore::crypto;

//==============================================================================
// Class IRPadding
//------------------------------------------------------------------------------
std::uint64_t IRPadding::getPaddingSize(unsigned int blockSize,
			std::uint64_t srcSize) const {
	return blockSize - (srcSize % blockSize);
}

//==============================================================================
// Class IRZeroPadding
//------------------------------------------------------------------------------
bool IRZeroPadding::addPadding(unsigned int blockSize, const void * src,
		std::uint64_t srcSize, void * dst, std::uint64_t & dstSize) const {
	unsigned int paddingSize;
	std::uint8_t * p;
	std::uint8_t * pEnd;

	paddingSize = this->getPaddingSize(blockSize, srcSize);
	if (dstSize < srcSize + paddingSize) {
		return false;
	}
	if (src != dst) {
		std::memcpy(dst, src, srcSize);
	}
	p = (std::uint8_t *)dst;
	pEnd = p + srcSize + paddingSize;
	for (p = p + srcSize; p != pEnd; p++) {
		*p = 0;
	}
	dstSize = srcSize + paddingSize;
	return true;
}

//------------------------------------------------------------------------------
bool IRZeroPadding::removePadding(unsigned int blockSize,
		const void * src, std::uint64_t & srcSize) const {
	const std::uint8_t * p;
	std::uint64_t paddingSize;

	if ((srcSize == 0) || (srcSize % blockSize)) {
		return false;
	}

	p = (const std::uint8_t *)src;
	paddingSize = 0;
	while ((p[srcSize - paddingSize - 1] == 0) && (paddingSize < blockSize)) {
		paddingSize++;
	}
	srcSize = srcSize - paddingSize;
	return (paddingSize > 0);
}

//==============================================================================
// Class IRPKCS7Padding
//------------------------------------------------------------------------------
bool IRPKCS7Padding::addPadding(unsigned int blockSize, const void * src,
		std::uint64_t srcSize, void * dst, std::uint64_t & dstSize) const {
	unsigned int paddingSize;
	std::uint8_t * p;
	std::uint8_t * pEnd;

	paddingSize = this->getPaddingSize(blockSize, srcSize);
	if (dstSize < srcSize + paddingSize) {
		return false;
	}
	if (src != dst) {
		std::memcpy(dst, src, srcSize);
	}
	p = (std::uint8_t *)dst;
	pEnd = p + srcSize + paddingSize;
	for (p = p + srcSize; p != pEnd; p++) {
		*p = paddingSize;
	}

	dstSize = srcSize + paddingSize;
	return true;
}

//------------------------------------------------------------------------------
bool IRPKCS7Padding::removePadding(unsigned int blockSize,
		const void * src, std::uint64_t & srcSize) const {
	unsigned int paddingSize;
	const std::uint8_t * p;
	const std::uint8_t * pEnd;

	if ((srcSize == 0) || (srcSize % blockSize)) {
		return false;
	}
	p = (const std::uint8_t *)src;
	paddingSize = p[srcSize - 1];
	if ((paddingSize == 0) || (paddingSize > blockSize)) {
		return false;
	}

	pEnd = p + srcSize;
	p = p + srcSize - paddingSize;
	for (; p != pEnd; p++) {
		if (*p != paddingSize) {
			return false;
		}
	}
	srcSize = srcSize - paddingSize;
	return true;
}

//==============================================================================
// Class IRANSIX923Padding
//------------------------------------------------------------------------------
bool IRANSIX923Padding::addPadding(unsigned int blockSize, const void * src,
		std::uint64_t srcSize, void * dst, std::uint64_t & dstSize) const {
	unsigned int paddingSize;
	std::uint8_t * p;
	std::uint8_t * pEnd;

	paddingSize = this->getPaddingSize(blockSize, srcSize);
	if (dstSize < srcSize + paddingSize) {
		return false;
	}
	if (src != dst) {
		std::memcpy(dst, src, srcSize);
	}
	p = (std::uint8_t *)dst;
	pEnd = p + srcSize + paddingSize - 1;
	for (p = p + srcSize; p != pEnd; p++) {
		*p = 0;
	}
	*p = paddingSize;

	dstSize = srcSize + paddingSize;
	return true;
}

//------------------------------------------------------------------------------
bool IRANSIX923Padding::removePadding(unsigned int blockSize,
		const void * src, std::uint64_t & srcSize) const {
	unsigned int paddingSize;
	const std::uint8_t * p;
	const std::uint8_t * pEnd;

	if ((srcSize == 0) || (srcSize % blockSize)) {
		return false;
	}
	p = (const std::uint8_t *)src;
	paddingSize = p[srcSize - 1];
	if ((paddingSize == 0) || (paddingSize > blockSize)) {
		return false;
	}

	pEnd = p + srcSize - 1;
	p = p + srcSize - paddingSize;
	for (; p != pEnd; p++) {
		if (*p != 0) {
			return false;
		}
	}
	if (*p != paddingSize) {
		return false;
	} else {
		srcSize = srcSize - paddingSize;
		return true;
	}
}

//==============================================================================
// Class IROCSRandomPadding
//------------------------------------------------------------------------------
IROCSRandomPadding::IROCSRandomPadding(ircommon::IRRandom * random,
		bool iso10126): _random(random), _iso10126(iso10126) {
}

//------------------------------------------------------------------------------
bool IROCSRandomPadding::addPadding(unsigned int blockSize, const void * src,
		std::uint64_t srcSize, void * dst, std::uint64_t & dstSize) const {
	unsigned int paddingSize;
	std::uint8_t * p;
	std::uint8_t pad;

	paddingSize = this->getPaddingSize(blockSize, srcSize);
	if (dstSize < srcSize + paddingSize) {
		return false;
	}
	if (src != dst) {
		std::memcpy(dst, src, srcSize);
	}

	p = (std::uint8_t *)dst;
	this->_random->nextBytes(p + srcSize, paddingSize);
	p = p + srcSize + paddingSize - 1;
	if (this->iso10126()) {
		*p = paddingSize;
	} else {
		*p = (*p) - ((*p) % blockSize) + paddingSize;
	}
	dstSize = srcSize + paddingSize;
	return true;
}

//------------------------------------------------------------------------------
bool IROCSRandomPadding::removePadding(unsigned int blockSize,
		const void * src, std::uint64_t & srcSize) const {
	unsigned int paddingSize;
	const std::uint8_t * p;
	const std::uint8_t * pEnd;

	if ((srcSize == 0) || (srcSize % blockSize)) {
		return false;
	}
	p = (const std::uint8_t *)src;
	paddingSize = p[srcSize - 1];
	if ((paddingSize == 0) || (paddingSize > blockSize)) {
		return false;
	}

	pEnd = p + srcSize - 1;
	p = p + srcSize - paddingSize;
	for (; p != pEnd; p++) {
		if (*p != 0) {
			return false;
		}
	}
	if (*p != paddingSize) {
		return false;
	} else {
		srcSize = srcSize - paddingSize;
		return true;
	}
}
//------------------------------------------------------------------------------
