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

