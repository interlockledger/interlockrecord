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
#include "IRSecureRandomTest.h"
#include "CryptoSamples.h"
#include <irecordcore/irsrand.h>
#include <cstring>

using namespace irecordcore::crypto;

//==============================================================================
// class IRSecureRandomTest
//------------------------------------------------------------------------------
IRSecureRandomTest::IRSecureRandomTest() {
}

//------------------------------------------------------------------------------
IRSecureRandomTest::~IRSecureRandomTest() {
}

//------------------------------------------------------------------------------
void IRSecureRandomTest::SetUp() {
}

//------------------------------------------------------------------------------
void IRSecureRandomTest::TearDown() {
}

//------------------------------------------------------------------------------
TEST_F(IRSecureRandomTest,Constructor) {
	IRSecureRandom * r;

	r = new IRSecureRandom();
	delete r;
}

//------------------------------------------------------------------------------
TEST_F(IRSecureRandomTest,setSeedUInt64) {
	IRSecureRandom r;
	std::uint64_t seed;

	seed = 0xFACADA;
	r.setSeed(seed);
}

//------------------------------------------------------------------------------
TEST_F(IRSecureRandomTest,setSeedVoidUInt64) {
	IRSecureRandom r;

	for (unsigned int size = 0; size <= sizeof(CRYPTOSAMPLES_SAMPLE2); size++) {
		r.setSeed(CRYPTOSAMPLES_SAMPLE2, size);
	}
}

//------------------------------------------------------------------------------
TEST_F(IRSecureRandomTest,nextBytes) {
	IRSecureRandom r;
	std::uint8_t val[32];
	std::uint8_t exp[32];

	std::memset(exp, 0, sizeof(exp));
	std::memset(val, 0, sizeof(val));
	r.nextBytes(val, 0);
	ASSERT_EQ(0, std::memcmp(exp, val, sizeof(val)));

	for (unsigned int size = 1; size <= sizeof(val); size++) {
		std::memset(val, 0, sizeof(val));
		r.nextBytes(val, size);
		ASSERT_NE(0, std::memcmp(exp, val, size));
	}
}

//------------------------------------------------------------------------------

