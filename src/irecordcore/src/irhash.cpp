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
#include <irecordcore/irhash.h>
#include <cstring>

using namespace irecordcore;
using namespace irecordcore::crypto;

//==============================================================================
// Class IRHashAlgorithm
//------------------------------------------------------------------------------
std::uint64_t IRHashAlgorithm::sizeInBytes() const {
	return this->size() / 8;
}

//==============================================================================
// Class IRHash
//------------------------------------------------------------------------------
IRHash::IRHash(IRHashAlg type): IRHashAlgorithm(), 	_type(type) {
}

//------------------------------------------------------------------------------
IRHash::~IRHash() {
}

//==============================================================================
// Class IRCopyHash
//------------------------------------------------------------------------------
void IRCopyHash::reset() {
	this->_state.setSize(0);
	this->_state.shrink();
}

//------------------------------------------------------------------------------
std::uint64_t IRCopyHash::size() const {
	return this->_state.size() * 8;
}

//------------------------------------------------------------------------------
void IRCopyHash::update(const void * buff, std::uint64_t size) {
	this->_state.write(buff, size);
}

//------------------------------------------------------------------------------
bool IRCopyHash::finalize(void * out, std::uint64_t size) {
	if (size < this->sizeInBytes()) {
		return false;
	}
	std::memcpy(out, this->_state.roBuffer(), this->_state.size());
	return true;
}

//==============================================================================
// Class IRHashFactory
//------------------------------------------------------------------------------
IRHash * IRHashFactory::create(std::uint16_t type) {

	switch(type) {
	case IR_HASH_SHA1:
		return new IRSHA1Hash();
	case IR_HASH_SHA256:
		return new IRSHA256Hash();
	case IR_HASH_SHA512:
		return new IRSHA512Hash();
	case IR_HASH_SHA3_256:
		return new IRSHA3_256Hash();
	case IR_HASH_SHA3_512:
		return new IRSHA3_512Hash();
	default:
		return nullptr;
	}
}

//------------------------------------------------------------------------------

