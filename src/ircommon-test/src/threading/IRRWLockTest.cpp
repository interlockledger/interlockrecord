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
#include "IRRWLockTest.h"
#include <ircommon/irrwlock.h>
#include <vector>
#include <thread>
#include <memory>
#include <algorithm>
#include <chrono>

using namespace ircommon;
using namespace ircommon::threading;

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

	for (unsigned int i = 0; i < threads.size(); i++) {
		threads[i]->join();
	}

	int last = log[0].value;
	auto lastTStamp =
			std::chrono::high_resolution_clock::time_point(std::chrono::high_resolution_clock::duration(0));
	std::uint64_t mDuration = UINT64_MAX;
	for (unsigned int i = 0; i < log.size(); i++) {
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

