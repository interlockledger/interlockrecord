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
#include "IRPBKDF2KeyGeneratorTest.h"
#include <irecordcore/irpbkdf2.h>
#include <cstring>

using namespace irecordcore::crypto;

#define IRPBKDF2KeyGenerator_ROUNDS 128

static const std::uint8_t IRPBKDF2KeyGenerator_SALT[20] = {
		0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
		0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x10,
		0x10, 0x11, 0x12, 0x13};

static const std::uint8_t IRPBKDF2KeyGenerator_PASSWD[10] = {
		0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
		0x08, 0x09};

static const std::uint8_t IRPBKDF2KeyGenerator_KEY[80] = {
		0x5F, 0x42, 0xF1, 0x77, 0x5F, 0x5F, 0x39, 0x35,
		0xA7, 0x88, 0xCB, 0x89, 0x7F, 0x51, 0xDC, 0x93,
		0xDB, 0x92, 0xFD, 0xDC, 0x57, 0xD5, 0xD9, 0xA7,
		0x31, 0x82, 0x26, 0x90, 0x52, 0xDF, 0xF2, 0x3B,
		0x52, 0x44, 0xD8, 0x18, 0xA1, 0x13, 0x8F, 0xCE,
		0xCD, 0x47, 0xE8, 0x5A, 0xDF, 0x11, 0x02, 0xA4,
		0xCB, 0xE3, 0x0F, 0x99, 0x9F, 0x74, 0xFA, 0x11,
		0xB9, 0xC0, 0xC6, 0x86, 0x1E, 0x7C, 0x54, 0x34,
		0x5F, 0x7B, 0xA6, 0x32, 0xCE, 0x9E, 0x86, 0xF9,
		0xBE, 0xC4, 0x2E, 0xB4, 0x0F, 0xA1, 0x83, 0xE1};

//==============================================================================
// class IRPBKDF2KeyGeneratorTest
//------------------------------------------------------------------------------
IRPBKDF2KeyGeneratorTest::IRPBKDF2KeyGeneratorTest() {
}

//------------------------------------------------------------------------------
IRPBKDF2KeyGeneratorTest::~IRPBKDF2KeyGeneratorTest() {
}

//------------------------------------------------------------------------------
void IRPBKDF2KeyGeneratorTest::SetUp() {
}

//------------------------------------------------------------------------------
void IRPBKDF2KeyGeneratorTest::TearDown() {
}

//------------------------------------------------------------------------------
TEST_F(IRPBKDF2KeyGeneratorTest, Constructor) {
	IRPBKDF2KeyGenerator * kg;

	kg = new IRPBKDF2KeyGenerator(new IRHMAC(new IRSHA1Hash()));
	ASSERT_EQ(1024, kg->rounds());
	ASSERT_EQ(20, kg->blockSize());
	delete kg;

	kg = new IRPBKDF2KeyGenerator(new IRHMAC(new IRSHA1Hash()), 10);
	ASSERT_EQ(10, kg->rounds());
	ASSERT_EQ(20, kg->blockSize());
	delete kg;
}

//------------------------------------------------------------------------------
TEST_F(IRPBKDF2KeyGeneratorTest, blockSize) {

	IRPBKDF2KeyGenerator kg1(new IRHMAC(new IRSHA1Hash()));
	ASSERT_EQ(20, kg1.blockSize());

	IRPBKDF2KeyGenerator kg2(new IRHMAC(new IRSHA256Hash()));
	ASSERT_EQ(32, kg2.blockSize());
}

//------------------------------------------------------------------------------
TEST_F(IRPBKDF2KeyGeneratorTest, rounds) {
	IRPBKDF2KeyGenerator kg(new IRHMAC(new IRSHA1Hash()));

	ASSERT_EQ(1024, kg.rounds());
	kg.setRounds(10);
	ASSERT_EQ(10, kg.rounds());
}

//------------------------------------------------------------------------------
TEST_F(IRPBKDF2KeyGeneratorTest, setPassword) {
	IRPBKDF2KeyGenerator kg(new IRHMAC(new IRSHA1Hash()));

	kg.setPassword(IRPBKDF2KeyGenerator_PASSWD,
			sizeof(IRPBKDF2KeyGenerator_PASSWD));
}

//------------------------------------------------------------------------------
TEST_F(IRPBKDF2KeyGeneratorTest, setSalt) {
	IRPBKDF2KeyGenerator kg(new IRHMAC(new IRSHA1Hash()));

	kg.setSalt(IRPBKDF2KeyGenerator_SALT,
			sizeof(IRPBKDF2KeyGenerator_SALT));
}

//------------------------------------------------------------------------------
TEST_F(IRPBKDF2KeyGeneratorTest, generateRawInvaldRounds) {
	IRPBKDF2KeyGenerator kg(new IRHMAC(new IRSHA1Hash()));
	std::uint8_t key[32];

	// Setup
	kg.setRounds(0);
	kg.setKeySize(128);
	kg.setPassword(IRPBKDF2KeyGenerator_PASSWD,
			sizeof(IRPBKDF2KeyGenerator_PASSWD));
	kg.setSalt(IRPBKDF2KeyGenerator_SALT,
			sizeof(IRPBKDF2KeyGenerator_SALT));

	ASSERT_FALSE(kg.generateRaw(key, sizeof(key)));
}

//------------------------------------------------------------------------------
TEST_F(IRPBKDF2KeyGeneratorTest, generateRawInvaldKeySize) {
	IRPBKDF2KeyGenerator kg(new IRHMAC(new IRSHA1Hash()));
	std::uint8_t key[32];

	// Setup
	kg.setRounds(IRPBKDF2KeyGenerator_ROUNDS);
	kg.setKeySize(0);
	kg.setPassword(IRPBKDF2KeyGenerator_PASSWD,
			sizeof(IRPBKDF2KeyGenerator_PASSWD));
	kg.setSalt(IRPBKDF2KeyGenerator_SALT,
			sizeof(IRPBKDF2KeyGenerator_SALT));

	ASSERT_FALSE(kg.generateRaw(key, sizeof(key)));
}

//------------------------------------------------------------------------------
TEST_F(IRPBKDF2KeyGeneratorTest, generateRawInvaldSalt) {
	IRPBKDF2KeyGenerator kg(new IRHMAC(new IRSHA1Hash()));
	std::uint8_t key[32];

	// Setup
	kg.setRounds(IRPBKDF2KeyGenerator_ROUNDS);
	kg.setKeySize(0);
	kg.setPassword(IRPBKDF2KeyGenerator_PASSWD,
			sizeof(IRPBKDF2KeyGenerator_PASSWD));
	ASSERT_FALSE(kg.generateRaw(key, sizeof(key)));
}

//------------------------------------------------------------------------------
TEST_F(IRPBKDF2KeyGeneratorTest, generateRaw) {
	IRPBKDF2KeyGenerator kg(new IRHMAC(new IRSHA1Hash()));
	std::uint8_t key[81];

	// Setup
	kg.setRounds(IRPBKDF2KeyGenerator_ROUNDS);
	kg.setPassword(IRPBKDF2KeyGenerator_PASSWD,
			sizeof(IRPBKDF2KeyGenerator_PASSWD));
	kg.setSalt(IRPBKDF2KeyGenerator_SALT,
			sizeof(IRPBKDF2KeyGenerator_SALT));
	for (unsigned int size = 1; size <= 80; size++) {
		kg.setKeySize(size * 8);
		std::memset(key, 0, sizeof(key));
		for (unsigned int candidateSize = 0; candidateSize < size; candidateSize++) {
			ASSERT_FALSE(kg.generateRaw(key, candidateSize));
			ASSERT_EQ(0, key[0]);
		}
		ASSERT_TRUE(kg.generateRaw(key, sizeof(key)));
		ASSERT_EQ(0, std::memcmp(key, IRPBKDF2KeyGenerator_KEY,	size));
		ASSERT_EQ(0, key[size]);
	}
}

//------------------------------------------------------------------------------

