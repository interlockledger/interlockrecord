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


