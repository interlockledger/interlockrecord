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
#include "IRSemaphoreTest.h"
#include <ircommon/irsemaph.h>
#include <memory>
#include <thread>
using namespace ircommon;
using namespace ircommon::threading;

//==============================================================================
// class IRSemaphoreTest
//------------------------------------------------------------------------------
IRSemaphoreTest::IRSemaphoreTest() {
}

//------------------------------------------------------------------------------
IRSemaphoreTest::~IRSemaphoreTest() {
}

//------------------------------------------------------------------------------
void IRSemaphoreTest::SetUp() {
}

//------------------------------------------------------------------------------
void IRSemaphoreTest::TearDown() {
}

//------------------------------------------------------------------------------
TEST_F(IRSemaphoreTest,Constructor) {
	IRSemaphore * s;

	s  = new IRSemaphore();
	delete s;
}

//------------------------------------------------------------------------------
TEST_F(IRSemaphoreTest, Sync) {
	IRSemaphore sem(0);
	volatile int shared = -1;
	int readRet;

	// The reader will wait until the writer sets shared to some value...
	std::thread reader([&readRet, &sem, &shared]() {
		if (!sem.wait()) {
			readRet = -2;
		} else {
			readRet = shared;
		}
	});
	ASSERT_EQ(-1, shared); // Ensure that it remains as is...

	// Start the writer that should set shared to 1.
	std::thread writer([&sem, &shared]() {
		shared = 1;
		sem.release();
	});

	writer.join();
	reader.join();
	ASSERT_EQ(1, readRet);
}

//------------------------------------------------------------------------------
TEST_F(IRSemaphoreTest, SyncFail) {
	IRSemaphore sem(0);
	volatile int shared = -1;
	int readRet;

	// The reader will wait until the writer sets shared to some value... It must
	// fail because of the delay of the writer
	std::thread reader([&readRet, &sem, &shared]() {
		if (!sem.tryWait(5)) {
			readRet = -2;
		} else {
			readRet = shared;
		}
	});
	ASSERT_EQ(-1, shared); // Ensure that it remains as is...

	// Start the writer that should set shared to 1.
	std::thread writer([&sem, &shared]() {
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
		shared = 1;
		sem.release();
	});

	writer.join();
	reader.join();
	ASSERT_EQ(-2, readRet);
}
//------------------------------------------------------------------------------

