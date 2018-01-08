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
#include "IRSemaphore.h"
#include <cassert>
#ifndef _WIN32
	#include <ctime>
	#include <cstring>	
#endif //_WIN32

//------------------------------------------------------------------------------
// Class IRSemaphore
//------------------------------------------------------------------------------
#ifdef _WIN32
// Win32 version
//------------------------------------------------------------------------------
IRSemaphore::IRSemaphore(int initial) {
	this->_handle = CreateSemaphore(NULL, initial, 0x7FFFFFFF, NULL);
}

//------------------------------------------------------------------------------
IRSemaphore::~IRSemaphore() {
	if (this->_handle) {
		CloseHandle(this->_handle);
	}
}

//------------------------------------------------------------------------------
bool IRSemaphore::tryWait(int ms) {
	if (!this->_handle) {
		return (WaitForSingleObject(this->_handle, ms) == WAIT_OBJECT_0);
	} else {
		return false;
	}
}

//------------------------------------------------------------------------------
bool IRSemaphore::wait() {
	if (!this->_handle) {
		return (WaitForSingleObject(this->_handle, INFINITE) == WAIT_OBJECT_0);
	} else {
		return false;
	}
}

//------------------------------------------------------------------------------
bool IRSemaphore::release() {
	if (!this->_handle) {
		return (ReleaseSemaphore(this->_handle, 1, NULL) == TRUE);
	} else {
		return false;
	}
}

#else
// Posix version
//------------------------------------------------------------------------------
IRSemaphore::IRSemaphore(int initial) {
	std::memset(&(this->_handle), 0, sizeof(this->_handle));
	sem_init(&(this->_handle), 0, initial);
}

//------------------------------------------------------------------------------
IRSemaphore::~IRSemaphore() {
	sem_destroy(&(this->_handle));
}

//------------------------------------------------------------------------------
bool IRSemaphore::tryWait(int ms) {
	struct timespec tm;
	tm.tv_sec = (ms / 1000);
	tm.tv_nsec = ((ms % 1000) * 1000);
	return (sem_timedwait(&(this->_handle), &tm) == 0);
}

//------------------------------------------------------------------------------
bool IRSemaphore::wait() {
	return (sem_wait(&(this->_handle)) == 0);
}

//------------------------------------------------------------------------------
bool IRSemaphore::release() {
	return (sem_post(&(this->_handle)) == 0);
}
//------------------------------------------------------------------------------

#endif //_WIN32


