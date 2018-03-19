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
#include "IRRandomTest.h"
#include <ircommon/irrandom.h>
#include <cstring>

using namespace ircommon;

//==============================================================================
// class IRDummyRandom
//------------------------------------------------------------------------------
class IRDummyRandom: public IRRandom {
private:
	std::uint64_t _seed;
public:
	IRDummyRandom(): _seed(0) {}

	virtual ~IRDummyRandom() = default;

	virtual void setSeed(std::uint64_t seed);

	std::uint64_t seed() const {
		return this->_seed;
	}

	virtual void nextBytes(void * out, std::uint64_t outSize);
};

//------------------------------------------------------------------------------
void IRDummyRandom::setSeed(std::uint64_t seed) {
	this->_seed = seed;
}

//------------------------------------------------------------------------------
void IRDummyRandom::nextBytes(void * out, std::uint64_t outSize) {
	std::uint8_t * p = (std::uint8_t *)out;

	for (unsigned int i = 0; i < outSize; i++, p++) {
		*p = (std::uint8_t)(this->_seed & 0xFF);
		this->_seed++;
	}
}

//==============================================================================
// class IRRandomTest
//------------------------------------------------------------------------------
IRRandomTest::IRRandomTest() {
}

//------------------------------------------------------------------------------
IRRandomTest::~IRRandomTest() {
}

//------------------------------------------------------------------------------
void IRRandomTest::SetUp() {
}

//------------------------------------------------------------------------------
void IRRandomTest::TearDown() {
}

//------------------------------------------------------------------------------
TEST_F(IRRandomTest,Constructor) {
	IRDummyRandom * r;

	r = new IRDummyRandom();
	ASSERT_EQ(0, r->seed());
	delete r;
}

//------------------------------------------------------------------------------
TEST_F(IRRandomTest, seed) {
	IRDummyRandom r;

	for (std::uint32_t seed = 0; seed < 16; seed++){
		r.setSeed(seed);
		ASSERT_EQ(seed, r.seed());
	}
}

//------------------------------------------------------------------------------
TEST_F(IRRandomTest, nextBytes) {
	IRDummyRandom r;
	std::uint8_t tmp[16];
	std::uint8_t exp[16];

	for (std::uint32_t seed = 0; seed < 16; seed++){
		r.setSeed(seed);
		for (std::uint32_t i = 0; i < sizeof(exp); i++) {
			exp[i] = (std::uint8_t)(seed + i);
		}
		r.nextBytes(tmp, sizeof(tmp));
		ASSERT_EQ(0, std::memcmp(exp, tmp, sizeof(tmp)));
		for (std::uint32_t i = 0; i < sizeof(exp); i++) {
			exp[i] = (std::uint8_t)(seed + i + sizeof(exp));
		}
		r.nextBytes(tmp, sizeof(tmp));
		ASSERT_EQ(0, std::memcmp(exp, tmp, sizeof(tmp)));
	}
}

//------------------------------------------------------------------------------
TEST_F(IRRandomTest, nextBoolean) {
	IRDummyRandom r;

	r.setSeed(0);
	ASSERT_FALSE(r.nextBoolean());

	r.setSeed(0xA1);
	ASSERT_TRUE(r.nextBoolean());

	r.setSeed(0xEE);
	ASSERT_FALSE(r.nextBoolean());

	r.setSeed(0xEF);
	ASSERT_TRUE(r.nextBoolean());
}

//------------------------------------------------------------------------------
TEST_F(IRRandomTest, next) {
	IRDummyRandom r;

	r.setSeed(0);
	ASSERT_EQ(0x03, r.next());
	ASSERT_EQ(0x07, r.next());
	ASSERT_EQ(0x0B, r.next());
}

//------------------------------------------------------------------------------
TEST_F(IRRandomTest, next16) {
	IRDummyRandom r;

	r.setSeed(0);
	ASSERT_EQ(0x0203, r.next16());
	ASSERT_EQ(0x0607, r.next16());
	ASSERT_EQ(0x0A0B, r.next16());
}

//------------------------------------------------------------------------------
TEST_F(IRRandomTest, next32) {
	IRDummyRandom r;

	r.setSeed(0);
	ASSERT_EQ(0x00010203, r.next32());

	r.setSeed(0xFA);
	ASSERT_EQ(0xFAFBFCFD, r.next32());
}

//------------------------------------------------------------------------------
TEST_F(IRRandomTest, next64) {
	IRDummyRandom r;

	r.setSeed(0);
	ASSERT_EQ(0x0001020304050607ll, r.next64());
	ASSERT_EQ(0x08090A0B0C0D0E0Fll, r.next64());
}

//------------------------------------------------------------------------------
TEST_F(IRRandomTest, nextFloat) {
	IRDummyRandom r;

	r.setSeed(0);
	ASSERT_FLOAT_EQ(0.007873893f, r.nextFloat());

	r.setSeed(0xFA);
	ASSERT_FLOAT_EQ(0.968658f, r.nextFloat());
}

//------------------------------------------------------------------------------
TEST_F(IRRandomTest, nextDouble) {
	IRDummyRandom r;

	r.setSeed(0);
	ASSERT_FLOAT_EQ(0.062991157, r.nextDouble());

	r.setSeed(0x9A);
	ASSERT_FLOAT_EQ(0.725736255, r.nextDouble());
}


//------------------------------------------------------------------------------
TEST_F(IRRandomTest, nextBytesFrom32) {
	IRDummyRandom r;
	std::uint8_t buff[32];
	std::uint8_t exp[32];

	for (unsigned int size = 1; size <= sizeof(buff); size++) {
		for (unsigned int i = 0; i < sizeof(buff); i++) {
			if (i < size) {
				exp[i] = i;
			} else {
				exp[i] = 0;
			}
		}
		r.setSeed(0);
		std::memset(buff, 0, sizeof(buff));
		IRRandom::nextBytesFrom32(r, buff, size);
		ASSERT_EQ(0, std::memcmp(exp, buff, sizeof(exp)));
	}
}


//------------------------------------------------------------------------------

