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
#ifndef __IRRWLock_H__
#define __IRRWLock_H__

#include <mutex>
#include "IRSemaphore.h"

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

#endif //__IRRWLock_H__


