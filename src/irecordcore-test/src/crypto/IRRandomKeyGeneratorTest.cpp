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

