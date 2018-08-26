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
#ifndef __IRCOMMON_IRSEMAPH_H__
#define __IRCOMMON_IRSEMAPH_H__

#ifdef _WIN32
	#include <windows.h>
#else
	#include <semaphore.h>
#endif //__WIN32

namespace ircommon {
namespace threading {

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

} // namespace threading
} // namespace ircommon

#endif //__IRCOMMON_IRSEMAPH_H__
