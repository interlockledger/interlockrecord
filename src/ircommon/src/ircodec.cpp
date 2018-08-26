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
#include <ircommon/ircodec.h>
#include <locale>
#include <stdexcept>
#include <cassert>

using namespace ircommon;
using namespace ircommon::codec;

//==============================================================================
// Class IRCodec
//------------------------------------------------------------------------------
int IRCodec::removePadding(const char * src, int srcSize) const {
	return srcSize;
}

//------------------------------------------------------------------------------
void IRCodec::addPadding(std::string & dst, int encodedSize) const {
}

//------------------------------------------------------------------------------
int IRCodec::encode(const void * src, int srcSize, std::string & dst) const {
	int initialSize;

	if (!src) {
		return -1;
	}
	if (srcSize < 0) {
		return -1;
	}
	initialSize = dst.size();
	this->encodeCore((const std::uint8_t*)src, srcSize, dst);
	this->addPadding(dst, dst.size() - initialSize);
	return dst.size() - initialSize;
}

//------------------------------------------------------------------------------
bool IRCodec::decode(const std::string & src, int srcStart, int srcSize,
			void * dst, int & dstSize) const {

	if ((srcStart < 0) || (dstSize < 0) || (!dst)) {
		return false;
	}
	if (src.size() < ((unsigned int)(srcStart + srcSize))) {
		return false;
	}
	if (dstSize < this->getDecodedSize(srcSize)) {
		return false;
	}
	int newSrcSize = this->removePadding(src.c_str() + srcStart, srcSize);
	if (newSrcSize < 0) {
		return false;
	} else {
		return this->decodeCore(src.c_str() + srcStart, newSrcSize,
				(std::uint8_t *)dst, dstSize);
	}
}

//==============================================================================
// Class IRBase2NCodec
//------------------------------------------------------------------------------
IRBase2NCodec::IRBase2NCodec(std::shared_ptr<IRAlphabet> alphabet, int blockSize,
		int paddingChar, bool ignoreSpaces):
				IRCodec(), _alphabet(alphabet), _blockSize(blockSize),
				_paddingChar(paddingChar), _ignoreSpaces(ignoreSpaces) {

	int charSize = 1;
	while ((charSize < 8) && ((0x1 << charSize) != this->_alphabet->size())) {
		charSize++;
	}
	if (charSize == 8) {
		throw std::invalid_argument("Invalid alphabet size.");
	}

	this->_charSize = charSize;
	this->_clearMask = (0x1 << this->_charSize) - 1;
}

//------------------------------------------------------------------------------
void IRBase2NCodec::encodeCore(const std::uint8_t * src, int srcSize,
			std::string & dst) const {
	int bitBuffer;
	int bitBufferSize;
	const std::uint8_t * srcEnd;

	bitBuffer = 0;
	bitBufferSize = 0;
	srcEnd = src + srcSize;
	while (src < srcEnd) {
		bitBuffer = (bitBuffer << 8) | (*src);
		bitBufferSize += 8;
		src++;

		while (bitBufferSize >= this->characterSize()) {
			bitBufferSize -= this->characterSize();
			dst.push_back(this->alphabet().getChar(
					(bitBuffer >> bitBufferSize) & this->clearMask()));
		}
	}

	if (bitBufferSize) {
		dst.push_back(this->alphabet().getChar(
				(bitBuffer << (this->characterSize() - bitBufferSize)) &
				this->clearMask()));
	}
}

//------------------------------------------------------------------------------
bool IRBase2NCodec::decodeCore(const char * src, int srcSize,
			std::uint8_t * dst, int & dstSize) const {
	const char * srcEnd;
	int c;
	int v;
	int bitBuffer;
	int bitBufferSize;
	std::uint8_t * pEnd;
	std::uint8_t * p;

	bitBuffer = 0;
	bitBufferSize = 0;
	p = dst;
	pEnd = dst + dstSize;
	srcEnd = src + srcSize;
	while (src < srcEnd) {
		c = *src;
		src++;
		if (!this->isIgnored(c)) {
			v = this->alphabet().getValue(c);
			if (v < 0) {
				return false;
			}
			bitBuffer = (bitBuffer << this->characterSize()) | v;
			bitBufferSize += this->characterSize();
			while (bitBufferSize >= 8) {
				bitBufferSize -= 8;
				assert(p < pEnd);
				*p = std::uint8_t((bitBuffer >> bitBufferSize) & 0xFF);
				p++;
			}
		}
	}
	dstSize = p - dst;
	return true;
}

//------------------------------------------------------------------------------
int IRBase2NCodec::removePadding(const char * src, int srcSize) const {

	if ((this->blockSize() <= 0) || (srcSize == 0)) {
		return srcSize;
	}

	if (srcSize < this->blockSize()) {
		return -1;
	}

	// Scan the value until a non padding/non ignored character is found.
	int padding = 0;
	const char * p = src + srcSize - 1;
	while ((p >= src) &&
			((*p == this->paddingCharacter()) || (this->isIgnored(*p)))) {
		if (*p == this->paddingCharacter()) {
			padding++;
		}
		p--;
	}

	// Check the padding size to see if it is indeed valid.
	int minBlock = (8 + (this->characterSize() - 1)) / this->characterSize();
	int maxPadding = this->blockSize() - minBlock;
	if (padding > maxPadding) {
		return -1;
	} else {
		return (p - src) + 1;
	}
}

//------------------------------------------------------------------------------
void IRBase2NCodec::addPadding(std::string & dst, int encodedSize) const {

	if (this->blockSize() > 0) {
		int extra;
		extra = encodedSize % this->blockSize();
		if (extra) {
			dst.append(this->blockSize() - extra, this->paddingCharacter());
		}
	}
}

//------------------------------------------------------------------------------
bool IRBase2NCodec::isIgnored(int c) const {

	if (this->ignoreSpaces()) {
		return std::isspace(char(c), std::locale::classic());
	} else {
		return false;
	}
}

//------------------------------------------------------------------------------
int IRBase2NCodec::getEncodedSize(int srcSize) const {
	int encSize;

	encSize = ((srcSize * 8) + (this->characterSize() - 1)) / this->characterSize();
	if (this->blockSize() > 0) {
		int extra = encSize % this->blockSize();
		if (extra) {
			encSize += (this->blockSize() - extra);
		}
	}
	return encSize;
}

//------------------------------------------------------------------------------
int IRBase2NCodec::getDecodedSize(int srcSize) const {

	// Padding and ignored characters are not considered.
	return (srcSize * this->characterSize()) / 8;
}
//------------------------------------------------------------------------------
