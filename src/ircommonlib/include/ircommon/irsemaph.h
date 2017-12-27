/*
 * Copyright (c) 2017, Open Communications Security
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
#ifndef __IRCOMMON_IRSEMAPH_H__
#define __IRCOMMON_IRSEMAPH_H__

#ifdef _WIN32
	#include <windows.h>
#else
	#include <semaphore.h>
#endif //__WIN32

namespace ircommon {

/**
 * This class implements a semaphore. It is important to notice that
 * the lock and unlock operations are not required to be performed
 * by the same thread.
 *
 * @since 2017.12.27
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
 */
class IRSemaphore {
private:
	/**
	 * Type of the handle. Its actual type will depend on the platform.
	 */
#ifdef _WIN32
	typedef HANDLE Handle_t;
#else
	typedef sem_t Handle_t;
#endif //_WIN32
	Handle_t _handle;
public:
	/**
	 * Creates a new semaphore with a given initial value.
	 *
	 * @param[in] initial Initial value.
	 */
	IRSemaphore(int initial = 1);

	/**
	 * Disposes this instance and releases all associated resources.
	 *
	 * @note This implementation does not check if the semaphore is in use.
	 */
	virtual ~IRSemaphore();

	/**
	 * Waits for the semaphore (decreases the semaphore by 1).
	 *
	 * @param[in] ms Time to wait.
	 * @return true if the lock was acquired or false otherwise.
	 */
	bool tryWait(int ms);

	/**
	 * Waits for the semaphore (decreases the semaphore by 1).
	 *
	 * @return true if the lock was acquired or false otherwise.
	 */
	bool wait();

	/**
	 * Releases the semaphore (adds 1 to it).
	 *
	 * @return true if the lock was released or false otherwise.
	 */
	bool release();
};

} // namespace ircommon

#endif //__IRCOMMON_IRSEMAPH_H__
