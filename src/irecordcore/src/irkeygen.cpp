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
#include <irecordcore/irkeygen.h>
#include <ircommon/irutils.h>

using namespace ircommon;
using namespace irecordcore;
using namespace irecordcore::crypto;

//==============================================================================
// Class IRSecretKeyGenerator
//------------------------------------------------------------------------------
IRSecretKeyGenerator::IRSecretKeyGenerator(): IRKeyGenerator(), _keySize(0){
}

//------------------------------------------------------------------------------
unsigned int IRSecretKeyGenerator::keySize() const {
	return this->_keySize;
}

//------------------------------------------------------------------------------
unsigned int IRSecretKeyGenerator::keySizeInBytes() const {
	return this->keySize() / 8;
}

//------------------------------------------------------------------------------
bool IRSecretKeyGenerator::setKeySize(unsigned int keySize) {

	if (keySize % 8) {
		return false;
	} else {
		this->_keySize = keySize;
		return true;
	}
}

//==============================================================================
// Class IRSoftwareKeyGenerator
//------------------------------------------------------------------------------
IRSecretKey * IRSoftwareKeyGenerator::generate() {
	std::uint64_t keySize;
	IRSecretKeyImpl * key = nullptr;

	keySize = this->keySizeInBytes();
	if (keySize != 0) {
		IRUtils::IRSecureTemp tmp(keySize);
		if (this->generateRaw(tmp.buff(), keySize)) {
			key = new IRSecretKeyImpl(tmp.buff(), keySize);
		}
	}
	return key;
}

//==============================================================================
// Class IRRandomKeyGenerator
//------------------------------------------------------------------------------
IRRandomKeyGenerator::IRRandomKeyGenerator(ircommon::IRRandom * random):
	_random(random){
}

//------------------------------------------------------------------------------
IRRandomKeyGenerator::IRRandomKeyGenerator(
		std::shared_ptr<ircommon::IRRandom> random) {
	this->_random = random;
}

//------------------------------------------------------------------------------
bool IRRandomKeyGenerator::generateRaw(void * key, unsigned int keySize) {

	if (this->keySize() == 0) {
		return false;
	}
	if (keySize < this->keySizeInBytes()) {
		return false;
	}
	this->_random->nextBytes(key, this->keySizeInBytes());
	return true;
}
//------------------------------------------------------------------------------


