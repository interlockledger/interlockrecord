
#include "IRSemaphore.h"
#include <cassert>
#ifndef _WIN32
	#include <time.h>
#endif //_WIN32

IRSemaphore::IRSemaphore(int initial) {
	
#ifdef _WIN32
	this->_handle = CreateSemaphore(NULL, initial, 0x7FFFFFFF, NULL);
#else
	this->_handle = &(this->_handle_concrete);
	sem_init(this->_handle, 0, initial);
#endif //_WIN32
}

IRSemaphore::~IRSemaphore() {
#ifdef _WIN32
	if (this->_handle) {
		CloseHandle(this->_handle);
	}
#else
	sem_destroy(this->_handle);
#endif //_WIN32
}

bool IRSemaphore::tryWait(int ms) {
	if (!this->_handle) {
#ifdef _WIN32
		return (WaitForSingleObject(this->_handle, ms) == WAIT_OBJECT_0);
#else
		struct timespec tm;
		tm.tv_sec = 0;
		tm.tv_nsec = (ms * 1000);
		return (sem_timedwait(this->_handle, &tm) == 0);
#endif //_WIN32
	} else {
		return false;
	}
}
	
bool IRSemaphore::wait() {
	if (!this->_handle) {
#ifdef _WIN32
		return (WaitForSingleObject(this->_handle, INFINITE) == WAIT_OBJECT_0);
#else
		sem_wait(this->_handle);
#endif //_WIN32
	} else {
		return false;
	}
}
	
bool IRSemaphore::release() {
#ifdef _WIN32
	return (ReleaseSemaphore(this->_handle, 1, NULL) == TRUE);
#else
	sem_wait(this->_handle);
#endif //_WIN32
}