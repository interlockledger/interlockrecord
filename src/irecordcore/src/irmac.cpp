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
	this->setRawKey(nullptr, 0);
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
bool IRHMAC::setRawKey(const void * key, std::uint64_t keySize) {

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

	if (!key.exportable()) {
		return false;
	}
	rawKeySize = key.sizeInBytes();
	if (rawKeySize == 0) {
		return false;
	}

	ircommon::IRUtils::IRSecureTemp rawKey(rawKeySize);
	if (key.exportKey(rawKey.buff(), rawKeySize)) {
		return this->setRawKey(rawKey.buff(), rawKeySize);
	} else {
		return false;
	}
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
