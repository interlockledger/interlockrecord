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
#include "IRRWLockTest.h"
#include <ircommon/irrwlock.h>
#include <vector>
#include <thread>
#include <memory>
#include <algorithm>
#include <chrono>

using namespace ircommon;

//==============================================================================
// class IRRWLockTest
//------------------------------------------------------------------------------
IRRWLockTest::IRRWLockTest() {
}

//------------------------------------------------------------------------------
IRRWLockTest::~IRRWLockTest() {
}

//------------------------------------------------------------------------------
void IRRWLockTest::SetUp() {
}

//------------------------------------------------------------------------------
void IRRWLockTest::TearDown() {
}

//------------------------------------------------------------------------------
TEST_F(IRRWLockTest, Constructor) {
	IRRWLock * l;

	l = new IRRWLock();
	delete l;
}

typedef struct _IRRWLockTest_SyncLog{
	int value;
	std::chrono::high_resolution_clock::time_point tstamp;
	_IRRWLockTest_SyncLog(int value, std::chrono::high_resolution_clock::time_point tstamp){
		this->value = value;
		this->tstamp = tstamp;
	}
} IRRWLockTest_SyncLog;

//------------------------------------------------------------------------------
TEST_F(IRRWLockTest, Sync) {
	IRRWLock lock;
	std::mutex logMutex;
	std::vector<IRRWLockTest_SyncLog> log;
	std::vector< std::shared_ptr<std::thread> > threads;
	volatile int shared;

	// TODO Check if this code is indeed enough to test the read/write lock. It appears to be so.
	/*
	 * This code works by creating a set of readers that will log the current value
	 * of shared and a set of writers that will increment its value by one but will log
	 * it as its negative value.
	 *
	 * This menas that the expected value for the sequence will be something like
	 * the following regular expression:
	 * 		'0'*'-1''1'*'-2''2'*'-3''3'*
	 *
	 * Anything different than that will mark the wrong behavior of the IRRWLock.
	 */
	shared = 0;
	for (int i = 0; i < 4; i++) {
		threads.push_back(std::make_shared<std::thread>([&shared, &log, & logMutex, &lock](){
			int i;

			do {
				lock.lockRead();
				logMutex.lock();
				i = shared;
				log.push_back(IRRWLockTest_SyncLog(i,  std::chrono::high_resolution_clock::now()));
				logMutex.unlock();
				std::this_thread::sleep_for(std::chrono::milliseconds(10));
				lock.unlockRead();
			} while (i < 2);
		}));
	}
	for (int i = 0; i < 2; i++) {
		threads.push_back(std::make_shared<std::thread>([&shared, &log, & logMutex, &lock](){
			int i;

			do {
				lock.lockWrite();
				shared++;
				logMutex.lock();
				i = shared;
				log.push_back(IRRWLockTest_SyncLog(-i, std::chrono::high_resolution_clock::now()));
				logMutex.unlock();
				std::this_thread::sleep_for(std::chrono::milliseconds(10));
				lock.unlockWrite();
			} while (i < 2);
		}));
	}

	for (int i = 0; i < threads.size(); i++) {
		threads[i]->join();
	}

	int last = log[0].value;
	auto lastTStamp =
			std::chrono::high_resolution_clock::time_point(std::chrono::high_resolution_clock::duration(0));
	std::uint64_t mDuration = UINT64_MAX;
	for (int i = 0; i < log.size(); i++) {
		auto timing = std::chrono::duration_cast<std::chrono::milliseconds>(log[i].tstamp - lastTStamp);
		//std::cout << log[i].value << " " << timing.count() << "\n";
		if (log[i].value < 0) {
			last = abs(log[i].value);
		} else {
#ifdef min
			mDuration = min(std::uint64_t(timing.count()), mDuration);
#else
			mDuration = std::min(std::uint64_t(timing.count()), mDuration);
#endif
			ASSERT_EQ(last, log[i].value);
		}
		lastTStamp = log[i].tstamp;
	}
	ASSERT_GT(10, mDuration);
}
//------------------------------------------------------------------------------

