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
#include "IRSecretKeyGeneratorTest.h"
#include <irecordcore/irkeygen.h>

using namespace irecordcore::crypto;

//==============================================================================
// class IRSecretKeyGeneratorTest
//------------------------------------------------------------------------------
class IRDummySecretKeyGenerator: public IRSecretKeyGenerator{
public:
	IRDummySecretKeyGenerator() = default;

	virtual ~IRDummySecretKeyGenerator() = default;

	virtual bool generateRaw(void * key, unsigned int keySize);

	virtual IRSecretKey * generate();
};

//------------------------------------------------------------------------------
bool IRDummySecretKeyGenerator::generateRaw(void * key, unsigned int keySize) {
	return false;
}

//------------------------------------------------------------------------------
IRSecretKey * IRDummySecretKeyGenerator::generate() {
	return nullptr;
}

//==============================================================================
// class IRSecretKeyGeneratorTest
//------------------------------------------------------------------------------
IRSecretKeyGeneratorTest::IRSecretKeyGeneratorTest() {
}

//------------------------------------------------------------------------------
IRSecretKeyGeneratorTest::~IRSecretKeyGeneratorTest() {
}

//------------------------------------------------------------------------------
void IRSecretKeyGeneratorTest::SetUp() {
}

//------------------------------------------------------------------------------
void IRSecretKeyGeneratorTest::TearDown() {
}

//------------------------------------------------------------------------------
TEST_F(IRSecretKeyGeneratorTest, Constructor) {
	IRSecretKeyGenerator * kg;

	kg = new IRDummySecretKeyGenerator();
	ASSERT_EQ(0, kg->keySize());
	delete kg;
}

//------------------------------------------------------------------------------
TEST_F(IRSecretKeyGeneratorTest, setKeySize) {
	IRDummySecretKeyGenerator kg;

	for (int size = 0; size <= 512; size += 8) {
		ASSERT_TRUE(kg.setKeySize(size));
		ASSERT_EQ(size, kg.keySize());
	}

	ASSERT_TRUE(kg.setKeySize(8));
	for (int size = 1; size < 8; size++) {
		ASSERT_FALSE(kg.setKeySize(size));
		ASSERT_EQ(8, kg.keySize());
	}
}

//------------------------------------------------------------------------------
TEST_F(IRSecretKeyGeneratorTest, keySize) {
	IRDummySecretKeyGenerator kg;

	ASSERT_EQ(0, kg.keySize());
	for (int size = 0; size <= 512; size += 8) {
		ASSERT_TRUE(kg.setKeySize(size));
		ASSERT_EQ(size, kg.keySize());
	}
}

//------------------------------------------------------------------------------
TEST_F(IRSecretKeyGeneratorTest, keySizeInBytes) {
	IRDummySecretKeyGenerator kg;

	ASSERT_EQ(0, kg.keySizeInBytes());
	for (int size = 0; size <= 512; size += 8) {
		ASSERT_TRUE(kg.setKeySize(size));
		ASSERT_EQ(size / 8, kg.keySizeInBytes());
	}
}

//------------------------------------------------------------------------------

