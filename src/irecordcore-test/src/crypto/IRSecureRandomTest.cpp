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

