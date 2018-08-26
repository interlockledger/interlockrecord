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
#include <irecordcore/irciphpd.h>
#include <cstring>

using namespace irecordcore::crypto;

//==============================================================================
// Class IRBasicPadding
//------------------------------------------------------------------------------
std::uint64_t IRBasicPadding::getPaddingSize(unsigned int blockSize,
			std::uint64_t srcSize) const {
	return blockSize - (srcSize % blockSize);
}

//------------------------------------------------------------------------------
unsigned int IRBasicPadding::extractPaddingSize(unsigned int blockSize,
		const std::uint8_t * src,
		std::uint64_t srcSize) const {
	unsigned int paddingSize;

	paddingSize = src[srcSize - 1];
	if (paddingSize > blockSize) {
		paddingSize = 0;
	}
	return paddingSize;
}

//------------------------------------------------------------------------------
bool IRBasicPadding::checkPadding(const std::uint8_t * padding,
		unsigned int paddingSize) const {
	return true;
}

//------------------------------------------------------------------------------
bool IRBasicPadding::addPadding(unsigned int blockSize, const void * src,
		std::uint64_t srcSize, void * dst, std::uint64_t & dstSize) const {
	unsigned int paddingSize;

	paddingSize = this->getPaddingSize(blockSize, srcSize);
	if (dstSize < srcSize + paddingSize) {
		return false;
	}
	if (src != dst) {
		std::memcpy(dst, src, srcSize);
	}
	this->createPadding(blockSize, ((std::uint8_t *)dst) + srcSize, paddingSize);
	dstSize = srcSize + paddingSize;
	return true;
}

//------------------------------------------------------------------------------
bool IRBasicPadding::removePadding(unsigned int blockSize,
		const void * src, std::uint64_t & srcSize) const {
	const std::uint8_t * pSrc;
	std::uint64_t paddingSize;

	if (srcSize == 0) {
		return true;
	}
	if (srcSize % blockSize) {
		return false;
	}

	pSrc = (const std::uint8_t *)src;
	paddingSize = this->extractPaddingSize(blockSize, pSrc, srcSize);
	if (paddingSize == 0) {
		return false;
	}
	if (this->checkPadding(pSrc + srcSize - paddingSize, paddingSize)){
		srcSize = srcSize - paddingSize;
		return true;
	} else {
		return false;
	}
}

//==============================================================================
// Class IRZeroPadding
//------------------------------------------------------------------------------
void IRZeroPadding::createPadding(unsigned int blockSize, std::uint8_t * padding,
		unsigned int paddingSize) const {
	std::uint8_t * paddingEnd;

	paddingEnd = padding + paddingSize;
	for (; padding != paddingEnd; padding++) {
		(*padding) = 0;
	}
}

//------------------------------------------------------------------------------
unsigned int IRZeroPadding::extractPaddingSize(unsigned int blockSize,
		const std::uint8_t * src,
		std::uint64_t srcSize) const {
	const std::uint8_t * srcEnd;
	unsigned int paddingSize;

	srcEnd = src + (srcSize - 1);
	src = src + (srcSize - blockSize - 1);
	paddingSize = 0;
	while ((srcEnd != src) && (*srcEnd == 0)) {
		paddingSize++;
		srcEnd--;
	}
	return paddingSize;
}

//==============================================================================
// Class IRPKCS7Padding
//------------------------------------------------------------------------------
void IRPKCS7Padding::createPadding(unsigned int blockSize, std::uint8_t * padding,
		unsigned int paddingSize) const {
	std::uint8_t * paddingEnd;

	paddingEnd = padding + paddingSize;
	for (; padding != paddingEnd; padding++) {
		(*padding) = paddingSize & 0xFF;
	}
}

//------------------------------------------------------------------------------
bool IRPKCS7Padding::checkPadding(const std::uint8_t * padding,
		unsigned int paddingSize) const {
	const std::uint8_t * paddingEnd;

	paddingEnd = padding + paddingSize;
	for (; padding != paddingEnd; padding++) {
		if ((*padding) != paddingSize) {
			return false;
		}
	}
	return true;
}

//==============================================================================
// Class IRANSIX923Padding
//------------------------------------------------------------------------------
void IRANSIX923Padding::createPadding(unsigned int blockSize, std::uint8_t * padding,
		unsigned int paddingSize) const {
	std::uint8_t * paddingEnd;

	paddingEnd = padding + paddingSize - 1;
	for (; padding != paddingEnd; padding++) {
		(*padding) = 0;
	}
	(*padding) = paddingSize & 0xFF;
}

//------------------------------------------------------------------------------
bool IRANSIX923Padding::checkPadding(const std::uint8_t * padding,
		unsigned int paddingSize) const {
	const std::uint8_t * paddingEnd;

	paddingEnd = padding + paddingSize - 1;
	for (; padding != paddingEnd; padding++) {
		if (*padding) {
			return false;
		}
	}
	return (*padding) == paddingSize;
}

//==============================================================================
// Class IRISO10126Padding
//------------------------------------------------------------------------------
IRISO10126Padding::IRISO10126Padding(ircommon::IRRandom * random):
		_random(random) {
}

//------------------------------------------------------------------------------
void IRISO10126Padding::createPadding(unsigned int blockSize, std::uint8_t * padding,
			unsigned int paddingSize) const {
	this->_random->nextBytes(padding, paddingSize - 1);
	padding[paddingSize - 1] = paddingSize & 0xFF;
}

//==============================================================================
// Class IROCSRandomPadding
//------------------------------------------------------------------------------
IROCSRandomPadding::IROCSRandomPadding(ircommon::IRRandom * random):
		IRISO10126Padding(random){
}

//------------------------------------------------------------------------------
void IROCSRandomPadding::createPadding(unsigned int blockSize, std::uint8_t * padding,
		unsigned int paddingSize) const {
	this->_random->nextBytes(padding, paddingSize);
	padding[paddingSize - 1] = (padding[paddingSize - 1] -
			(padding[paddingSize - 1] % blockSize) + paddingSize) & 0xFF;
}

//------------------------------------------------------------------------------
unsigned int IROCSRandomPadding::extractPaddingSize(unsigned int blockSize,
		const std::uint8_t * src,
		std::uint64_t srcSize) const {
	unsigned int paddingSize;

	paddingSize = src[srcSize - 1] % blockSize;
	if (paddingSize == 0) {
		paddingSize = blockSize;
	}
	return paddingSize;
}

//------------------------------------------------------------------------------
