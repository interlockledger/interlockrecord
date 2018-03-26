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
		0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37,
		0x38, 0x39};

static const std::uint8_t IRPBKDF2KeyGenerator_KEY[16] = {
		0x3d, 0xc1, 0xd3, 0x0f, 0xc0, 0xfc, 0xe6, 0xbb,
		0xe2, 0x3a,	0xa5, 0x85, 0x00, 0x40, 0x4e, 0x1b};

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
TEST_F(IRPBKDF2KeyGeneratorTest, prf) {
	IRPBKDF2KeyGenerator kg(new IRHMAC(new IRSHA1Hash()));

	IRHMAC hmac(new IRSHA1Hash());
	std::uint8_t key[32];

	// Setup
	key[0] = 0;
	key[1] = 0;
	key[2] = 0;
	key[3] = 1;
	kg.prf().setKey(IRPBKDF2KeyGenerator_PASSWD, sizeof(IRPBKDF2KeyGenerator_PASSWD));
	kg.prf().update(IRPBKDF2KeyGenerator_SALT, sizeof(IRPBKDF2KeyGenerator_SALT));
	kg.prf().update(key, 4);
	kg.prf().finalize(key, sizeof(key));
	key[31] = 0;

	// Setup
	key[0] = 0;
	key[1] = 0;
	key[2] = 0;
	key[3] = 1;
	hmac.setKey(IRPBKDF2KeyGenerator_PASSWD, sizeof(IRPBKDF2KeyGenerator_PASSWD));
	hmac.update(IRPBKDF2KeyGenerator_SALT, sizeof(IRPBKDF2KeyGenerator_SALT));
	hmac.update(key, 4);
	hmac.finalize(key, sizeof(key));
	key[31] = 0;
}


//------------------------------------------------------------------------------
TEST_F(IRPBKDF2KeyGeneratorTest, generateRaw) {
	IRPBKDF2KeyGenerator kg(new IRHMAC(new IRSHA1Hash()));
	std::uint8_t key[32];

	// Setup
	kg.setRounds(IRPBKDF2KeyGenerator_ROUNDS);
	kg.setKeySize(128);
	kg.setPassword(IRPBKDF2KeyGenerator_PASSWD,
			sizeof(IRPBKDF2KeyGenerator_PASSWD));
	kg.setSalt(IRPBKDF2KeyGenerator_SALT,
			sizeof(IRPBKDF2KeyGenerator_SALT));

	ASSERT_TRUE(kg.generateRaw(key, sizeof(key)));

	ASSERT_EQ(0, std::memcmp(key, IRPBKDF2KeyGenerator_KEY,
			sizeof(IRPBKDF2KeyGenerator_KEY)));
}

//------------------------------------------------------------------------------

