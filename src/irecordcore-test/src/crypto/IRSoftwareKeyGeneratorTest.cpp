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
#include "IRSoftwareKeyGeneratorTest.h"
#include "IRSecretKeyGeneratorTest.h"
#include <irecordcore/irkeygen.h>

using namespace irecordcore::crypto;
//==============================================================================
// class IRDummySoftwareKeyGenerator
//------------------------------------------------------------------------------
class IRDummySoftwareKeyGenerator: public IRSoftwareKeyGenerator {
public:
	IRDummySoftwareKeyGenerator() = default;
	virtual ~IRDummySoftwareKeyGenerator() = default;

	virtual bool generateRaw(void * key, unsigned int keySize);
};

//------------------------------------------------------------------------------
bool IRDummySoftwareKeyGenerator::generateRaw(void * key, unsigned int keySize) {
	std::uint8_t * p;

	if (this->keySize() <= 0) {
		return false;
	}
	if (keySize < this->keySizeInBytes()) {
		return false;
	}

	p = (std::uint8_t *)key;
	for (unsigned int i = 0; i < this->keySizeInBytes(); i++, p++) {
		*p = (0xFF & i);
	}
	return true;
}

//==============================================================================
// class IRSoftwareKeyGeneratorTest
//------------------------------------------------------------------------------
IRSoftwareKeyGeneratorTest::IRSoftwareKeyGeneratorTest() {
}

//------------------------------------------------------------------------------
IRSoftwareKeyGeneratorTest::~IRSoftwareKeyGeneratorTest() {
}

//------------------------------------------------------------------------------
void IRSoftwareKeyGeneratorTest::SetUp() {
}

//------------------------------------------------------------------------------
void IRSoftwareKeyGeneratorTest::TearDown() {
}

//------------------------------------------------------------------------------
TEST_F(IRSoftwareKeyGeneratorTest,Constructor) {
	IRSoftwareKeyGenerator * kg;

	kg = new IRDummySoftwareKeyGenerator();
	delete kg;
}

//------------------------------------------------------------------------------
TEST_F(IRSoftwareKeyGeneratorTest, generateRaw) {
	IRDummySoftwareKeyGenerator kg;
	std::uint8_t key[33];
	std::uint8_t exp[32];

	for (unsigned int i = 0; i < sizeof(exp); i++) {
		exp[i] = i & 0xFF;
	}

	// Invalid initial key size
	ASSERT_FALSE(kg.generateRaw(key, sizeof(key)));

	// Insufficient buffer
	ASSERT_TRUE(kg.setKeySize(128));
	for (unsigned int size = 0; size < 16; size++) {
		ASSERT_FALSE(kg.generateRaw(key, size));
	}

	// Extract the key
	for (unsigned int size = 1; size <= 32; size++) {
		ASSERT_TRUE(kg.setKeySize(size * 8));
		std::memset(key, 0, sizeof(key));
		ASSERT_TRUE(kg.generateRaw(key, size));
		ASSERT_EQ(0, std::memcmp(exp, key, size));
		ASSERT_EQ(0, key[size]);

		std::memset(key, 0, sizeof(key));
		ASSERT_TRUE(kg.generateRaw(key, size + 1));
		ASSERT_EQ(0, std::memcmp(exp, key, size));
		ASSERT_EQ(0, key[size]);
	}
}

//------------------------------------------------------------------------------
TEST_F(IRSoftwareKeyGeneratorTest, generate) {
	IRDummySoftwareKeyGenerator kg;
	std::uint8_t rawKey[32];
	std::uint64_t rawKeySize;
	std::uint8_t exp[32];
	IRSecretKey * key;

	for (unsigned int i = 0; i < sizeof(exp); i++) {
		exp[i] = i & 0xFF;
	}

	// Invalid initial key size
	ASSERT_TRUE(kg.generate() == nullptr);

	// Extract the key
	for (unsigned int size = 1; size <= 32; size++) {
		ASSERT_TRUE(kg.setKeySize(size * 8));

		key = kg.generate();
		ASSERT_TRUE(key != nullptr);
		ASSERT_EQ(size * 8, key->size());
		ASSERT_EQ(size, key->sizeInBytes());

		ASSERT_TRUE(key->exportable());

		rawKeySize = sizeof(rawKey);
		ASSERT_TRUE(key->exportKey(rawKey, rawKeySize));
		ASSERT_EQ(rawKeySize, size);
		ASSERT_EQ(0, std::memcmp(exp, rawKey, size));
	}
}

//------------------------------------------------------------------------------

