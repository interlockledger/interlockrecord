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
#include "IRARC4RandomTest.h"
#include <ircommon/irarc4.h>
#include <ircommon/irutils.h>
#include <cstring>

using namespace ircommon;
using namespace ircommon::crypto;

//==============================================================================
// class IRARC4RandomTest
//------------------------------------------------------------------------------
IRARC4RandomTest::IRARC4RandomTest() {
}

//------------------------------------------------------------------------------
IRARC4RandomTest::~IRARC4RandomTest() {
}

//------------------------------------------------------------------------------
void IRARC4RandomTest::SetUp() {
}

//------------------------------------------------------------------------------
void IRARC4RandomTest::TearDown() {
}

//------------------------------------------------------------------------------
TEST_F(IRARC4RandomTest, Constructor) {
	IRARC4Random * r;

	r = new IRARC4Random();
	delete r;
}

//------------------------------------------------------------------------------
TEST_F(IRARC4RandomTest, setSeedUInt64) {
	IRARC4Random r;
	IRARC4 a;
	std::uint64_t key;
	std::uint8_t seed[8];
	std::uint8_t out[16];
	std::uint8_t exp[16];

	key = 0x0123456789ABCDEFll;
	IRUtils::int2BE(key, seed);

	a.setKey(seed, sizeof(seed));
	std::memset(exp, 0, sizeof(exp));
	a.apply(exp, sizeof(exp));

	r.setSeed(key);
	r.nextBytes(out, sizeof(out));
	ASSERT_EQ(0, std::memcmp(exp, out, sizeof(exp)));
}

//------------------------------------------------------------------------------
TEST_F(IRARC4RandomTest, setSeedVoidUInt64) {
	IRARC4Random r;
	IRARC4 a;
	std::uint64_t key;
	std::uint8_t seed[8];
	std::uint8_t out[16];
	std::uint8_t exp[16];

	key = 0x0123456789ABCDEFll;
	IRUtils::int2BE(key, seed);

	a.setKey(seed, sizeof(seed));
	std::memset(exp, 0, sizeof(exp));
	a.apply(exp, sizeof(exp));

	r.setSeed(seed, sizeof(seed));
	r.nextBytes(out, sizeof(out));
	ASSERT_EQ(0, std::memcmp(exp, out, sizeof(exp)));
}

//------------------------------------------------------------------------------
TEST_F(IRARC4RandomTest, nextBytes) {
	IRARC4Random r;
	IRARC4 a;
	std::uint64_t key;
	std::uint8_t seed[8];
	std::uint8_t out[16];
	std::uint8_t exp[16];

	key = 0x0123456789ABCDEFll;
	IRUtils::int2BE(key, seed);

	a.setKey(seed, sizeof(seed));
	r.setSeed(seed, sizeof(seed));

	for (unsigned int size = 1; size <= sizeof(exp); size++) {
		std::memset(exp, 0, sizeof(exp));
		a.apply(exp, size);
		r.nextBytes(out, size);
		ASSERT_EQ(0, std::memcmp(exp, out, size));
	}
}

//------------------------------------------------------------------------------

