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
#include <ircommon/irpmem.h>
#include <ircommon/irutils.h>
#include <stdexcept>
#include <cstring>
#include <cassert>
using namespace ircommon;
using namespace ircommon::crypto;

#ifdef _WIN32
	#include <windows.h>
#else
	#include <chrono>
#endif //_WIN32

//==============================================================================
// Class IRProtectedMemory
//------------------------------------------------------------------------------
IRProtectedMemory::IRProtectedMemory(std::uint64_t size) {

#ifdef _WIN32
	this->_valueBufferSize = size + (CRYPTPROTECTMEMORY_BLOCK_SIZE - (size % CRYPTPROTECTMEMORY_BLOCK_SIZE));
	assert((this->_valueBufferSize % CRYPTPROTECTMEMORY_BLOCK_SIZE) == 0);
	assert(this->_valueBufferSize >= size);
#else 
	this->_valueBufferSize = size;
	auto now = std::chrono::high_resolution_clock::now();
	std::uint64_t key = now.time_since_epoch().count();
	this->_arc4 = new IRARC4(&key, sizeof(key));
	IRUtils::lockMemory(this->_arc4, sizeof(IRARC4));
#endif // _WIN32

	this->_valueSize = size;
	this->_value = new std::uint8_t[this->_valueBufferSize];
	std::memset(this->_value, 0, this->_valueBufferSize);
	IRUtils::lockMemory(this->_value, this->_valueBufferSize);
	this->protect();
}

//------------------------------------------------------------------------------
IRProtectedMemory::~IRProtectedMemory() {
#ifndef _WIN32
	if (this->_arc4) {
		IRUtils::unlockMemory(this->_arc4, sizeof(IRARC4));
		delete this->_arc4;
	}
#endif //_WIN32
	if (this->_value) {
		IRUtils::unlockMemory(this->_value, this->_valueBufferSize);
		IRUtils::clearMemory(this->_value, this->_valueBufferSize);
		delete[] this->_value;
	}
}

//------------------------------------------------------------------------------
bool IRProtectedMemory::protect() {
#ifdef _WIN32
	return (CryptProtectMemory(this->_value, this->_valueBufferSize, 
		CRYPTPROTECTMEMORY_SAME_PROCESS) == TRUE);
#else
	this->_arc4->save();
	this->_arc4->apply(this->_value, this->_valueBufferSize);
	return true;
#endif //_WIN32
}

//------------------------------------------------------------------------------
bool IRProtectedMemory::unprotect() {
#ifdef _WIN32
	return (CryptUnprotectMemory(this->_value, this->_valueBufferSize, 
		CRYPTPROTECTMEMORY_SAME_PROCESS) == TRUE);
#else
	this->_arc4->load();
	this->_arc4->apply(this->_value, this->_valueBufferSize);
	return true;
#endif //_WIN32
}

//------------------------------------------------------------------------------
bool IRProtectedMemory::lock() {
	this->_mutex.lock();
	if (this->unprotect()) {
		return true;
	} else {
		this->_mutex.unlock();
		return false;
	}
}

//------------------------------------------------------------------------------
bool IRProtectedMemory::unlock() {
	bool retval;

	retval = this->protect();
	this->_mutex.unlock();
	return retval;
}

//------------------------------------------------------------------------------
