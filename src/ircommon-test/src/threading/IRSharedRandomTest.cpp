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
#include "IRSharedRandomTest.h"
#include "../IRDummyRandom.h"
#include <ircommon/irshrand.h>
#include <ircommon/irutils.h>

#include <cstring>
#include <thread>

using namespace ircommon;
using namespace ircommon::threading;

//==============================================================================
// class IRSharedRandomTest
//------------------------------------------------------------------------------
IRSharedRandomTest::IRSharedRandomTest() {
}

//------------------------------------------------------------------------------
IRSharedRandomTest::~IRSharedRandomTest() {
}

//------------------------------------------------------------------------------
void IRSharedRandomTest::SetUp() {
}

//------------------------------------------------------------------------------
void IRSharedRandomTest::TearDown() {
}

//------------------------------------------------------------------------------
TEST_F(IRSharedRandomTest, Constructor) {
	IRSharedRandom * r;

	r = new IRSharedRandom(new IRDummyRandom());
	delete r;
}

//------------------------------------------------------------------------------
TEST_F(IRSharedRandomTest, setSeedUInt64) {
	IRDummyRandom * d = new IRDummyRandom();
	IRSharedRandom r(new IRDelayedRandom(d, 3));
	volatile int last = -1;

	std::thread t1([&r, &last]() {
		r.setSeed(0x01234567890ABCDEFll);
		last = 1;
	});
	std::thread t2([&r, &last]() {
		r.setSeed(0xFEDCBA0987654321ll);
		last = 2;
	});

	t1.join();
	t2.join();

	ASSERT_NE(-1, last);
	if (last == 1){
		ASSERT_EQ(0x01234567890ABCDEFll, d->seed());
	} else {
		ASSERT_EQ(0xFEDCBA0987654321ll, d->seed());
	}
}

//------------------------------------------------------------------------------
TEST_F(IRSharedRandomTest, setSeedVoidUInt64) {
	IRDummyRandom * d = new IRDummyRandom();
	IRSharedRandom r(new IRDelayedRandom(d, 3));
	volatile int last = -1;

	std::thread t1([&r, &last]() {
		std::uint8_t tmp[8];
		IRUtils::int2BE((std::uint64_t)0x0123456789ABCDEFll, tmp);
		r.setSeed(tmp, sizeof(tmp));
		last = 1;
	});
	std::thread t2([&r, &last]() {
		std::uint8_t tmp[8];
		IRUtils::int2BE((std::uint64_t)0xFEDCBA9876543210ll, tmp);
		r.setSeed(tmp, sizeof(tmp));
		last = 2;
	});
	t1.join();
	t2.join();
	ASSERT_NE(-1, last);
	if (last == 1){
		ASSERT_EQ(0x0123456789ABCDEFll, d->seed());
	} else {
		ASSERT_EQ(0xFEDCBA9876543210ll, d->seed());
	}
}

//------------------------------------------------------------------------------
TEST_F(IRSharedRandomTest, nextBytes) {
	IRSharedRandom r(new IRDelayedRandom(new IRDummyRandom(), 3));
	volatile int last = -1;
	std::uint8_t v1[8];
	std::uint8_t v2[8];
	std::uint8_t exp[8];
	std::uint64_t exp1;
	std::uint64_t exp2;

	r.setSeed(0);
	std::thread t1([&r,  &last, &v1]() {
		r.nextBytes(v1, sizeof(v1));
		last++;
	});
	std::thread t2([&r,  &last, &v2]() {
		r.nextBytes(v2, sizeof(v2));
		last++;
	});
	t1.join();
	t2.join();
	ASSERT_NE(-1, last);

	if (v1[0] == 0x00){
		exp1 = 0x0001020304050607ll;
		exp2 = 0x08090a0b0c0d0e0fll;
	} else {
		exp2 = 0x0001020304050607ll;
		exp1 = 0x08090a0b0c0d0e0fll;
	}

	IRUtils::int2BE(exp1, exp);
	ASSERT_EQ(0, std::memcmp(v1, exp, sizeof(exp)));

	IRUtils::int2BE(exp2, exp);
	ASSERT_EQ(0, std::memcmp(v2, exp, sizeof(exp)));
}

//------------------------------------------------------------------------------
TEST_F(IRSharedRandomTest, nextBoolean) {
	IRSharedRandom r(new IRDelayedRandom(new IRDummyRandom(), 3));
	volatile int last = -1;
	bool v1;
	bool v2;
	bool exp1;
	bool exp2;

	r.setSeed(1);
	exp1 = r.nextBoolean();
	exp2 = r.nextBoolean();
	ASSERT_NE(exp1, exp2);

	r.setSeed(1);
	std::thread t1([&r,  &last, &v1]() {
		v1 = r.nextBoolean();
		last = 1;
	});
	std::thread t2([&r,  &last, &v2]() {
		v2 = r.nextBoolean();
		last = 2;
	});
	t1.join();
	t2.join();
	ASSERT_NE(-1, last);

	if (last == 1){
		ASSERT_EQ(exp2, v1);
		ASSERT_EQ(exp1, v2);
	} else {
		ASSERT_EQ(exp1, v1);
		ASSERT_EQ(exp2, v2);
	}
}

//------------------------------------------------------------------------------
TEST_F(IRSharedRandomTest, next) {
	IRSharedRandom r(new IRDelayedRandom(new IRDummyRandom(), 3));
	volatile int last = -1;
	std::uint8_t v1;
	std::uint8_t v2;
	std::uint8_t exp1;
	std::uint8_t exp2;

	r.setSeed(1);
	exp1 = r.next();
	exp2 = r.next();
	ASSERT_NE(exp1, exp2);

	r.setSeed(1);
	std::thread t1([&r,  &last, &v1]() {
		v1 = r.next();
		last = 1;
	});
	std::thread t2([&r,  &last, &v2]() {
		v2 = r.next();
		last = 2;
	});
	t1.join();
	t2.join();
	ASSERT_NE(-1, last);

	if (last == 1){
		ASSERT_EQ(exp2, v1);
		ASSERT_EQ(exp1, v2);
	} else {
		ASSERT_EQ(exp1, v1);
		ASSERT_EQ(exp2, v2);
	}
}

//------------------------------------------------------------------------------
TEST_F(IRSharedRandomTest, next16) {
	IRSharedRandom r(new IRDelayedRandom(new IRDummyRandom(), 3));
	volatile int last = -1;
	std::uint16_t v1;
	std::uint16_t v2;
	std::uint16_t exp1;
	std::uint16_t exp2;

	r.setSeed(1);
	exp1 = r.next16();
	exp2 = r.next16();
	ASSERT_NE(exp1, exp2);

	r.setSeed(1);
	std::thread t1([&r,  &last, &v1]() {
		v1 = r.next16();
		last = 1;
	});
	std::thread t2([&r,  &last, &v2]() {
		v2 = r.next16();
		last = 2;
	});
	t1.join();
	t2.join();
	ASSERT_NE(-1, last);

	if (last == 1){
		ASSERT_EQ(exp2, v1);
		ASSERT_EQ(exp1, v2);
	} else {
		ASSERT_EQ(exp1, v1);
		ASSERT_EQ(exp2, v2);
	}
}

//------------------------------------------------------------------------------
TEST_F(IRSharedRandomTest, next32) {
	IRSharedRandom r(new IRDelayedRandom(new IRDummyRandom(), 3));
	volatile int last = -1;
	std::uint32_t v1;
	std::uint32_t v2;
	std::uint32_t exp1;
	std::uint32_t exp2;

	r.setSeed(1);
	exp1 = r.next32();
	exp2 = r.next32();
	ASSERT_NE(exp1, exp2);

	r.setSeed(1);
	std::thread t1([&r,  &last, &v1]() {
		v1 = r.next32();
		last = 1;
	});
	std::thread t2([&r,  &last, &v2]() {
		v2 = r.next32();
		last = 2;
	});
	t1.join();
	t2.join();
	ASSERT_NE(-1, last);

	if (last == 1){
		ASSERT_EQ(exp2, v1);
		ASSERT_EQ(exp1, v2);
	} else {
		ASSERT_EQ(exp1, v1);
		ASSERT_EQ(exp2, v2);
	}
}

//------------------------------------------------------------------------------
TEST_F(IRSharedRandomTest, next64) {
	IRSharedRandom r(new IRDelayedRandom(new IRDummyRandom(), 3));
	volatile int last = -1;
	std::uint64_t v1;
	std::uint64_t v2;
	std::uint64_t exp1;
	std::uint64_t exp2;

	r.setSeed(1);
	exp1 = r.next64();
	exp2 = r.next64();
	ASSERT_NE(exp1, exp2);

	r.setSeed(1);
	std::thread t1([&r,  &last, &v1]() {
		v1 = r.next64();
		last = 1;
	});
	std::thread t2([&r,  &last, &v2]() {
		v2 = r.next64();
		last = 2;
	});
	t1.join();
	t2.join();
	ASSERT_NE(-1, last);

	if (last == 1){
		ASSERT_EQ(exp2, v1);
		ASSERT_EQ(exp1, v2);
	} else {
		ASSERT_EQ(exp1, v1);
		ASSERT_EQ(exp2, v2);
	}
}

//------------------------------------------------------------------------------
TEST_F(IRSharedRandomTest, nextFloat) {
	IRSharedRandom r(new IRDelayedRandom(new IRDummyRandom(), 3));
	volatile int last = -1;
	float v1;
	float v2;
	float exp1;
	float exp2;

	r.setSeed(1);
	exp1 = r.nextFloat();
	exp2 = r.nextFloat();
	ASSERT_NE(exp1, exp2);

	r.setSeed(1);
	std::thread t1([&r,  &last, &v1]() {
		v1 = r.nextFloat();
		last = 1;
	});
	std::thread t2([&r,  &last, &v2]() {
		v2 = r.nextFloat();
		last = 2;
	});
	t1.join();
	t2.join();
	ASSERT_NE(-1, last);

	if (last == 1){
		ASSERT_EQ(exp2, v1);
		ASSERT_EQ(exp1, v2);
	} else {
		ASSERT_EQ(exp1, v1);
		ASSERT_EQ(exp2, v2);
	}
}

//------------------------------------------------------------------------------
TEST_F(IRSharedRandomTest, nextDouble) {
	IRSharedRandom r(new IRDelayedRandom(new IRDummyRandom(), 3));
	volatile int last = -1;
	double v1;
	double v2;
	double exp1;
	double exp2;

	r.setSeed(1);
	exp1 = r.nextDouble();
	exp2 = r.nextDouble();
	ASSERT_NE(exp1, exp2);

	r.setSeed(1);
	std::thread t1([&r,  &last, &v1]() {
		v1 = r.nextDouble();
		last = 1;
	});
	std::thread t2([&r,  &last, &v2]() {
		v2 = r.nextDouble();
		last = 2;
	});
	t1.join();
	t2.join();
	ASSERT_NE(-1, last);

	if (last == 1){
		ASSERT_EQ(exp2, v1);
		ASSERT_EQ(exp1, v2);
	} else {
		ASSERT_EQ(exp1, v1);
		ASSERT_EQ(exp2, v2);
	}
}

//------------------------------------------------------------------------------


