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
#ifndef __IRCOMMON_IRRWLOCK_H__
#define __IRCOMMON_IRRWLOCK_H__

#include <mutex>
#include <ircommon/irsemaph.h>

namespace ircommon {
namespace threading {

/**
 * This class implements a read/write lock that allows multiple simultaneous
 * readers but only a single writer access to the resource.
 *
 * @since 2017.12.26
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
 */
class IRRWLock {
private:
	/**
	 * Mutex that prevents the concurrent access to _readerCount.
	 */
	std::mutex _readLock;

	/**
	 * Mutex that prevents concurrent writers.
	 */
	IRSemaphore _writeLock;

	/**
	 * Mutex that prevents new readers after the first write lock request.
	 */
	std::mutex _writeReq;

	/**
	 * Number of readers using the resource.
	 */
	volatile int _readerCount;
public:
	/**
	 * Creates a new instance of this class.
	 */
	IRRWLock();

	/**
	 * Disposes this class and releases all associated resources.
 	 */
	virtual ~IRRWLock();

	/**
	 * Acquire the lock for reading. This method will block if a writer is
	 * running.
	 */
	void lockRead();

	/**
	 * Releases the lock for reading.
	 */
	void unlockRead();

	/**
	 * Acquire the lock for writting. This method will block until the
	 * exclusive access to the resource can be acquired. Furthermore, it
	 * will prevent new readers from acquiring the the lock.
	 */
	void lockWrite();

	/**
	 * Releases the lock for writting.
	 */
	void unlockWrite();
};

} // namespace threading
} // namespace ircommon

#endif /* __IRCOMMON_IRRWLOCK_H__ */
