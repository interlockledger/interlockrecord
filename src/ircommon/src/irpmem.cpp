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
	if (this->_arc4) {
		IRUtils::unlockMemory(this->_arc4, sizeof(IRARC4));
		delete this->_arc4;
	}
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
