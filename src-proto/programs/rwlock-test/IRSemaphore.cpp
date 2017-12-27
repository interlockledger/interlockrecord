
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


