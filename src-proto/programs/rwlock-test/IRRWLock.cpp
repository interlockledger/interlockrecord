
#include "IRRWLock.h"

IRRWLock::IRRWLock():_readerCount(0) {
}

IRRWLock::~IRRWLock() {
}

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

void IRRWLock::unlockRead() {

	this->_readLock.lock();
	this->_readerCount--;
	if (this->_readerCount == 0) {
		this->_writeLock.release();
	}
	this->_readLock.unlock();
}

void IRRWLock::lockWrite() {

	this->_writeReq.lock();
	this->_writeLock.wait();
	this->_writeReq.unlock();
}

void IRRWLock::unlockWrite() {
	this->_writeLock.release();
}
