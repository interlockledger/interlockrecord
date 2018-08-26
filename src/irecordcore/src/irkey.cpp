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
#include <irecordcore/irkey.h>
#include <cstring>
#include <stdexcept>

using namespace irecordcore;
using namespace irecordcore::crypto;

//==============================================================================
// Class IRKey
//------------------------------------------------------------------------------
IRKey::IRKey(bool exportable): _exportable(exportable) {
}

//------------------------------------------------------------------------------
bool IRKey::serialize(ircommon::IRBuffer & out) {
	return false;
}

//------------------------------------------------------------------------------
bool IRKey::exportKey(void * key, std::uint64_t & keySize) {
	keySize = 0;
	return false;
}

//==============================================================================
// Class IRSecretKey
//------------------------------------------------------------------------------

//==============================================================================
// Class IRSecretKeyImpl
//------------------------------------------------------------------------------
IRSecretKeyImpl::IRSecretKeyImpl(const void * key, std::uint64_t keySize):
		IRSecretKey(true), _key(keySize) {

	this->_key.lock();
	std::memcpy(this->_key.value(), key, keySize);
	this->_key.unlock();
}

//------------------------------------------------------------------------------
IRSecretKeyImpl::~IRSecretKeyImpl() {
}

//------------------------------------------------------------------------------
std::uint64_t IRSecretKeyImpl::size() {
	return this->sizeInBytes() * 8;
}

//------------------------------------------------------------------------------
std::uint64_t IRSecretKeyImpl::sizeInBytes() {
	return this->_key.size();
}

//------------------------------------------------------------------------------
void IRSecretKeyImpl::lock() {

	if (!this->_key.lock()) {
		throw std::runtime_error("");
	}
}

//------------------------------------------------------------------------------
void IRSecretKeyImpl::unlock() {

	if (!this->_key.unlock()) {
		throw std::runtime_error("");
	}
}

//------------------------------------------------------------------------------
bool IRSecretKeyImpl::exportKey(void * key, std::uint64_t & keySize) {

	if ((!key) || (keySize < this->sizeInBytes())) {
		keySize = this->sizeInBytes();
		return false;
	} else {
		keySize = this->sizeInBytes();
		this->lock();
		std::memcpy(key, this->key(), keySize);
		this->unlock();
		return true;
	}
}

//------------------------------------------------------------------------------
bool IRSecretKeyImpl::serialize(ircommon::IRBuffer & out) {
	bool retval;

	this->lock();
	retval = out.write(this->key(), this->sizeInBytes());
	this->unlock();
	return retval;
}

//------------------------------------------------------------------------------
