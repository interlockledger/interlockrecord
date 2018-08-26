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
#include <irecordcore/irpbkdf2.h>
#include <ircommon/irutils.h>
#include <algorithm>

using namespace ircommon;
using namespace irecordcore;
using namespace irecordcore::crypto;

// Reference https://tools.ietf.org/html/rfc2898

//==============================================================================
// Class IRPBKDF2KeyGenerator
//------------------------------------------------------------------------------
IRPBKDF2KeyGenerator::IRPBKDF2KeyGenerator(IRMAC * prf, unsigned int rounds):
		_prf(prf), _rounds(rounds), _salt() {
}

//------------------------------------------------------------------------------
void IRPBKDF2KeyGenerator::setPassword(const void * password,
		std::uint64_t passwordSize) {
	this->_prf->setRawKey(password, passwordSize);
}

//------------------------------------------------------------------------------
void IRPBKDF2KeyGenerator::setSalt(const void * salt, std::uint64_t saltSize) {
	this->_salt.set(salt, saltSize);
}

//------------------------------------------------------------------------------
void IRPBKDF2KeyGenerator::generateBlock(std::uint32_t index,
		std::uint8_t * tmp, std::uint8_t * out) {

	// U_1
	this->_prf->reset();
	this->_prf->update(this->_salt.roBuffer(), this->_salt.size());
	IRUtils::int2BE(index, tmp);
	this->_prf->update(tmp, 4);
	this->_prf->finalize(out, this->blockSize());

	// U_2 to U_C
	std::memcpy(tmp, out, this->blockSize());
	for (unsigned int i = 1; i < this->rounds(); i++) {
		// Compute U_i
		this->_prf->reset();
		this->_prf->update(tmp, this->blockSize());
		this->_prf->finalize(tmp, this->blockSize());
		// Combine output with U_i
		for (unsigned int j = 0; j < this->blockSize(); j++) {
			out[j] = (out[j] ^ tmp[j]);
		}
	}
}

//------------------------------------------------------------------------------
bool IRPBKDF2KeyGenerator::generateRawCore(std::uint8_t * key,
		unsigned int keySize) {
	IRUtils::IRSecureTemp tmp(std::max(this->blockSize(), (unsigned int)4));
	IRUtils::IRSecureTemp out(this->blockSize());
	std::uint32_t blockNum;

	blockNum = 1;
	while (keySize > 0) {
		// Compute the block
		this->generateBlock(blockNum, tmp.buff(), out.buff());
		// Compose the key
		std::uint32_t used = std::min(this->blockSize(), keySize);
		std::memcpy(key, out.buff(), used);
		// Next block...
		keySize -= used;
		key += used;
		blockNum++;
	}
	return true;
}

//------------------------------------------------------------------------------
bool IRPBKDF2KeyGenerator::generateRaw(void * key, unsigned int keySize) {

	if (this->rounds() == 0) {
		return false;
	}
	if (this->keySize() == 0) {
		return false;
	}
	if (this->_salt.size() == 0) {
		return false;
	}
	if (keySize < this->keySizeInBytes()) {
		return false;
	}
	return this->generateRawCore((std::uint8_t *)key, this->keySizeInBytes());
}

//------------------------------------------------------------------------------
