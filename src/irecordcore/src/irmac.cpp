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
#include <irecordcore/irmac.h>
#include <ircommon/irutils.h>
#include <stdexcept>
#include <cstring>

using namespace irecordcore;
using namespace irecordcore::crypto;

//==============================================================================
// Class IRMAC
//------------------------------------------------------------------------------
IRMAC::IRMAC(): IRHashAlgorithm() {
}

//------------------------------------------------------------------------------
IRMAC::~IRMAC() {
}

//==============================================================================
// Class IRHMAC
//------------------------------------------------------------------------------
IRHMAC::IRHMAC(IRHashAlgorithm * hash, std::uint64_t blockSize): IRMAC(),
		_hash(hash){

	if (blockSize == 0) {
		if (this->_hash->sizeInBytes() <= 32) {
			// RFC2104
			blockSize = 64;
		} else if (this->_hash->sizeInBytes() <= 64) {
			// RFC4868
			blockSize = 128;
		} else {
			throw std::invalid_argument("Unsupported hash algorithm.");
		}
	}

	if (blockSize < this->_hash->sizeInBytes()) {
		throw std::invalid_argument("Invalid block size.");
	}

	this->_blockSize = blockSize;

	this->_ipad = std::unique_ptr<std::uint8_t[]>(new std::uint8_t[this->_blockSize]);
	this->_opad = std::unique_ptr<std::uint8_t[]>(new std::uint8_t[this->_blockSize]);
	this->setKey(nullptr, 0);
}

//------------------------------------------------------------------------------
IRHMAC::~IRHMAC() {

	if (this->_opad) {
		ircommon::IRUtils::clearMemory(this->_opad.get(), this->_blockSize);
	}
	if (this->_ipad) {
		ircommon::IRUtils::clearMemory(this->_ipad.get(), this->_blockSize);
	}
}

//------------------------------------------------------------------------------
void IRHMAC::mask(std::uint8_t * pad, std::uint8_t mask) {
	std::uint8_t * padEnd;

	padEnd = pad + this->_blockSize;
	for(; pad != padEnd; pad++) {
		(*pad) = (*pad) ^ mask;
	}
}

//------------------------------------------------------------------------------
bool IRHMAC::setKey(const void * key, std::uint64_t keySize) {

	std::memset(this->_opad.get(), 0, this->blockSize());
	if (keySize > this->blockSize()) {
		this->_hash->reset();
		this->_hash->update(key, keySize);
		this->_hash->finalize(this->_opad.get(), this->blockSize());
	} else {
		std::memcpy(this->_opad.get(), key, keySize);
	}
	std::memcpy(this->_ipad.get(), this->_opad.get(), this->_blockSize);
	this->mask(this->_opad.get(), 0x5c);
	this->mask(this->_ipad.get(), 0x36);
	this->reset();
	return true;
}

//------------------------------------------------------------------------------
bool IRHMAC::setKey(IRSecretKey & key) {
	std::uint64_t rawKeySize;
	std::uint8_t * rawKey;
	bool retval;

	if (!key.exportable()) {
		return false;
	}
	rawKeySize = key.sizeInBytes();
	if (rawKeySize == 0) {
		return false;
	}
	rawKey = new std::uint8_t[rawKeySize];
	if (key.exportKey(rawKey, rawKeySize)) {
		retval = this->setKey(rawKey, rawKeySize);
	} else {
		retval = false;
	}
	ircommon::IRUtils::clearMemory(rawKey, rawKeySize);
	delete [] rawKey;
	return retval;
}

//------------------------------------------------------------------------------
void IRHMAC::reset() {
	this->_hash->reset();
	this->_hash->update(this->_ipad.get(), this->_blockSize);
}

//------------------------------------------------------------------------------
std::uint64_t IRHMAC::size() const {
	return this->_hash->size();
}

//------------------------------------------------------------------------------
std::uint64_t IRHMAC::sizeInBytes() const {
	return this->_hash->sizeInBytes();
}

//------------------------------------------------------------------------------
void IRHMAC::update(const void * buff, std::uint64_t size) {
	this->_hash->update(buff, size);
}

//------------------------------------------------------------------------------
bool IRHMAC::finalize(void * out, std::uint64_t size) {

	if (size < this->sizeInBytes()) {
		return false;
	}
	if (!this->_hash->finalize(out, size)){
		return false;
	}
	this->_hash->reset();
	this->_hash->update(this->_opad.get(), this->_blockSize);
	this->_hash->update(out, this->sizeInBytes());
	return this->_hash->finalize(out, size);
}

//------------------------------------------------------------------------------
