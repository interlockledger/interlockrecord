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
#include "IRRandomKeyGeneratorTest.h"
#include <ircommon/irrandom.h>
#include <irecordcore/irkeygen.h>

using namespace ircommon;
using namespace irecordcore::crypto;

//==============================================================================
// class IRRandomKeyGeneratorTest
//------------------------------------------------------------------------------
IRRandomKeyGeneratorTest::IRRandomKeyGeneratorTest() {
}

//------------------------------------------------------------------------------
IRRandomKeyGeneratorTest::~IRRandomKeyGeneratorTest() {
}

//------------------------------------------------------------------------------
void IRRandomKeyGeneratorTest::SetUp() {
}

//------------------------------------------------------------------------------
void IRRandomKeyGeneratorTest::TearDown() {
}

//------------------------------------------------------------------------------
TEST_F(IRRandomKeyGeneratorTest, Constructor) {
	IRRandomKeyGenerator * kg;

	kg = new IRRandomKeyGenerator(new IRXORShifRandom());
	ASSERT_EQ(typeid(IRXORShifRandom&), typeid(kg->random()));
	delete kg;
}

//------------------------------------------------------------------------------
TEST_F(IRRandomKeyGeneratorTest, random) {
	IRRandomKeyGenerator kg(new IRXORShifRandom());

	ASSERT_EQ(typeid(IRXORShifRandom&), typeid(kg.random()));
}

//------------------------------------------------------------------------------
TEST_F(IRRandomKeyGeneratorTest, generateRaw) {
	IRRandomKeyGenerator kg(new IRXORShifRandom());
	IRXORShifRandom random;
	std::uint8_t key[33];
	std::uint8_t exp[32];

	random.setSeed(0);
	random.nextBytes(exp, sizeof(exp));

	ASSERT_FALSE(kg.generateRaw(key, sizeof(key)));

	// Insufficient buffer
	ASSERT_TRUE(kg.setKeySize(128));
	for (unsigned int size = 0; size < 16; size++) {
		ASSERT_FALSE(kg.generateRaw(key, size));
	}

	// Extract the key
	for (unsigned int size = 1; size <= 32; size++) {
		ASSERT_TRUE(kg.setKeySize(size * 8));
		kg.random().setSeed(0);
		std::memset(key, 0, sizeof(key));
		ASSERT_TRUE(kg.generateRaw(key, size));
		ASSERT_EQ(0, std::memcmp(exp, key, size));
		ASSERT_EQ(0, key[size]);

		kg.random().setSeed(0);
		std::memset(key, 0, sizeof(key));
		ASSERT_TRUE(kg.generateRaw(key, size + 1));
		ASSERT_EQ(0, std::memcmp(exp, key, size));
		ASSERT_EQ(0, key[size]);
	}
}

//------------------------------------------------------------------------------

