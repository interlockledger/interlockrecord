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
#include <irecordcore/irkey.h>
#include <cstring>
#include <stdexcept>

using namespace irecordcore;
using namespace irecordcore::crypto;

//==============================================================================
// Class IRKey
//------------------------------------------------------------------------------
bool IRKey::serialize(ircommon::IRBuffer & out) {
	return false;
}

//==============================================================================
// Class IRSecretKeyImpl
//------------------------------------------------------------------------------
IRSecretKeyImpl::IRSecretKeyImpl(const void * key, std::uint64_t keySize):
		IRSecretKey(), _key(keySize) {

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
std::uint64_t  IRSecretKeyImpl::copy(void * key, std::uint64_t keySize) {

	if (keySize < this->sizeInBytes()) {
		return 0;
	}
	this->lock();
	std::memcpy(key, this->key(), this->sizeInBytes());
	this->unlock();
	return this->sizeInBytes();
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
