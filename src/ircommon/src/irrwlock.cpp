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
#include "ircommon/irrwlock.h"

using namespace ircommon;
using namespace ircommon::threading;

//------------------------------------------------------------------------------
// class IRRWLock
//------------------------------------------------------------------------------
IRRWLock::IRRWLock():_readerCount(0) {
}

//------------------------------------------------------------------------------
IRRWLock::~IRRWLock() {
}

//------------------------------------------------------------------------------
void IRRWLock::lockRead() {

	this->_writeReq.lock();
	this->_writeReq.unlock();

	this->_readLock.lock();
	this->_readerCount++;
	if (this->_readerCount == 1) {
		this->_writeLock.wait();
	}
	this->_readLock.unlock();
}

//------------------------------------------------------------------------------
void IRRWLock::unlockRead() {

	this->_readLock.lock();
	this->_readerCount--;
	if (this->_readerCount == 0) {
		this->_writeLock.release();
	}
	this->_readLock.unlock();
}

//------------------------------------------------------------------------------
void IRRWLock::lockWrite() {

	this->_writeReq.lock();
	this->_writeLock.wait();
	this->_writeReq.unlock();
}

//------------------------------------------------------------------------------
void IRRWLock::unlockWrite() {
	this->_writeLock.release();
}

//------------------------------------------------------------------------------
