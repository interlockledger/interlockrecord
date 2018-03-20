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

