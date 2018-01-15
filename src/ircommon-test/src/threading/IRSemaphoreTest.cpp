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

