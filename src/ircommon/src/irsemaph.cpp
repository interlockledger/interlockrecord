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
#include "ircommon/irsemaph.h"

using namespace ircommon;
using namespace ircommon::threading;

#ifndef _WIN32
	#include <ctime>
	#include <cstring>
#endif //_WIN32

//------------------------------------------------------------------------------
// Class IRSemaphore
//------------------------------------------------------------------------------
#ifdef _WIN32
//------------------------------------------------------------------------------
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
	if (this->_handle) {
		DWORD retval = WaitForSingleObject(this->_handle, ms);
		return (retval == WAIT_OBJECT_0);
	} else {
		return false;
	}
}

//------------------------------------------------------------------------------
bool IRSemaphore::wait() {
	if (this->_handle) {
		DWORD retval = WaitForSingleObject(this->_handle, INFINITE);
		return (retval == WAIT_OBJECT_0);
	} else {
		return false;
	}
}

//------------------------------------------------------------------------------
bool IRSemaphore::release() {
	if (this->_handle) {
		return (ReleaseSemaphore(this->_handle, 1, NULL) == TRUE);
	} else {
		return false;
	}
}

#else
//------------------------------------------------------------------------------
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
