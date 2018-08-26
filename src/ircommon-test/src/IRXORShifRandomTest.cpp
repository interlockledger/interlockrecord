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
#include "IRXORShifRandomTest.h"
#include <ircommon/irutils.h>
#include <ircommon/irrandom.h>
#include <cstring>

using namespace ircommon;

//==============================================================================
// class IRXORShifRandomTest
//------------------------------------------------------------------------------
#define IRXORShifRandomTest_SAMPLE_SEED0 0xf5539d6bc442958ell
#define IRXORShifRandomTest_SAMPLE_SEED1 0x4b0bdbb42366c4a6ll
static const std::uint64_t IRXORShifRandomTest_SAMPLES[16] = {
		0x56C6239360290227ll, 0xA65AAF65D320745Cll,
		0x19249AFA67C34BB9ll, 0xA5F38A78015E17FCll,
		0x7730C463AAE0D17ll, 0x257F01860A189412ll,
		0x49F8CF5B1FCA721Ell, 0x6576CFE9D28DC62All,
		0x500E083228C97224ll, 0xD5C99B68B396DE53ll,
		0x8CD00A7B2AD9E9C9ll, 0xEA4CEBD31EB2E195ll,
		0x1F0E1819B854F0CBll, 0x951E1D34B470177ll,
		0xD75FE84C0A2D26A0ll, 0xB4E8B5543989F36All};

static const std::uint8_t IRXORShifRandomTest_SAMPLE_SEED_BIN[32] = {
		0xf5, 0x53, 0x9d, 0x6b, 0xc4, 0x42, 0x95, 0x8e,
		0x4b, 0x0b, 0xdb, 0xb4, 0x23, 0x66, 0xc4, 0xa6,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

IRXORShifRandomTest::IRXORShifRandomTest() {
}

//------------------------------------------------------------------------------
IRXORShifRandomTest::~IRXORShifRandomTest() {
}

//------------------------------------------------------------------------------
void IRXORShifRandomTest::SetUp() {
}

//------------------------------------------------------------------------------
void IRXORShifRandomTest::TearDown() {
}

//------------------------------------------------------------------------------
TEST_F(IRXORShifRandomTest,Constructor) {
	IRXORShifRandom * r;

	r = new IRXORShifRandom();
	delete r;
}

//------------------------------------------------------------------------------
TEST_F(IRXORShifRandomTest,ConstructorUInt64) {

	for (unsigned int seed = 1; seed < 15; seed++) {
		IRXORShifRandom r(seed);
		IRXORShifRandom exp;
		exp.setSeed(seed);
		ASSERT_EQ(exp.next32(), r.next32());
	}
}

//------------------------------------------------------------------------------
TEST_F(IRXORShifRandomTest, setSeedUInt64) {
	IRXORShifRandom r;
	IRXORShifRandom exp;
	std::uint64_t seed;

	seed = 0x3a75e2e6a202e69dll;
	r.setSeed(seed);
	exp.setSeed(seed, seed ^ 0x6a09e667bb67ae85ll);

	for (int i = 0; i < 10; i++) {
		ASSERT_EQ(exp.nextValue(), r.nextValue());
	}
}

//------------------------------------------------------------------------------
TEST_F(IRXORShifRandomTest, setSeedVoidUInt64) {
	IRXORShifRandom r;
	IRXORShifRandom exp;

	r.setSeed(IRXORShifRandomTest_SAMPLE_SEED_BIN, 16);
	exp.setSeed(IRXORShifRandomTest_SAMPLE_SEED0, IRXORShifRandomTest_SAMPLE_SEED1);
	for (int i = 0; i < 10; i++) {
		ASSERT_EQ(exp.nextValue(), r.nextValue());
	}

	r.setSeed(IRXORShifRandomTest_SAMPLE_SEED_BIN, 32);
	exp.setSeed(IRXORShifRandomTest_SAMPLE_SEED0, IRXORShifRandomTest_SAMPLE_SEED1);
	for (int i = 0; i < 10; i++) {
		ASSERT_EQ(exp.nextValue(), r.nextValue());
	}

	r.setSeed(IRXORShifRandomTest_SAMPLE_SEED_BIN + 16, 16);
	exp.setSeed((std::uint64_t)0, (std::uint64_t)0);
	for (int i = 0; i < 10; i++) {
		ASSERT_EQ(exp.nextValue(), r.nextValue());
	}

	r.setSeed(IRXORShifRandomTest_SAMPLE_SEED_BIN, 8);
	exp.setSeed(IRXORShifRandomTest_SAMPLE_SEED0, 0);
	for (int i = 0; i < 10; i++) {
		ASSERT_EQ(exp.nextValue(), r.nextValue());
	}
}


//------------------------------------------------------------------------------
TEST_F(IRXORShifRandomTest, setSeedUInt64UInt64) {
	IRXORShifRandom r;
	IRXORShifRandom exp;

	r.setSeed(IRXORShifRandomTest_SAMPLE_SEED0, IRXORShifRandomTest_SAMPLE_SEED1);
	ASSERT_EQ(IRXORShifRandomTest_SAMPLES[0], r.nextValue());

	// Avoid zeroes
	r.setSeed((std::uint64_t)0, (std::uint64_t)0);
	exp.setSeed((std::uint64_t)1, (std::uint64_t)0);
	for (int i = 0; i < 10; i++) {
		ASSERT_EQ(exp.nextValue(), r.nextValue());
	}
}

//------------------------------------------------------------------------------
TEST_F(IRXORShifRandomTest, nextValue) {
	IRXORShifRandom r;

	// Comparison with a standard implementation
	r.setSeed(IRXORShifRandomTest_SAMPLE_SEED0, IRXORShifRandomTest_SAMPLE_SEED1);
	for (int i = 0; i < 16; i++) {
		std::uint64_t v = r.nextValue();
		ASSERT_EQ(IRXORShifRandomTest_SAMPLES[i], v);
	}
}

//------------------------------------------------------------------------------
TEST_F(IRXORShifRandomTest, next32) {
	IRXORShifRandom r;

	r.setSeed(IRXORShifRandomTest_SAMPLE_SEED0, IRXORShifRandomTest_SAMPLE_SEED1);
	for (int i = 0; i < 16; i++) {
		std::uint32_t v = r.next32();
		ASSERT_EQ((IRXORShifRandomTest_SAMPLES[i] >> 8) & 0xFFFFFFFF, v);
	}
}

//------------------------------------------------------------------------------
TEST_F(IRXORShifRandomTest, nextBytes) {
	IRXORShifRandom r;
	std::uint8_t out[32];
	std::uint8_t exp[32];

	std::memset(exp, 0, sizeof(exp));
	r.setSeed(IRXORShifRandomTest_SAMPLE_SEED0, IRXORShifRandomTest_SAMPLE_SEED1);
	for (unsigned int i = 0; i < sizeof(exp); i += 4) {
		std::uint32_t v = r.next32();
		IRUtils::int2BE(v, exp + i);
	}

	for (unsigned int size = 1; size <= sizeof(out); size++) {
		r.setSeed(IRXORShifRandomTest_SAMPLE_SEED0, IRXORShifRandomTest_SAMPLE_SEED1);
		std::memset(out, 0, sizeof(out));
		r.nextBytes(out, size);
		ASSERT_EQ(0, std::memcmp(exp, out, size));
	}
}

//------------------------------------------------------------------------------

