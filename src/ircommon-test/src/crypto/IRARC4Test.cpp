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
#include "IRARC4Test.h"
#include <ircommon/irarc4.h>
#include <cstring>
using namespace ircommon::crypto;

//==============================================================================
// class IRARC4Test
//------------------------------------------------------------------------------
const std::uint8_t IRARC4Test_KEY[16] = {
		0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
		0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F};
const std::uint8_t IRARC4Test_KEYSTREAM[32] = {
		0xE9, 0x9C, 0x40, 0xF9, 0x47, 0xE2, 0x19, 0xCC,
		0x06, 0xDB, 0x97, 0xC6, 0x0E, 0xDD, 0x2A, 0x4F,
		0xD3, 0x71, 0x81, 0x5F, 0xF2, 0xB7, 0x42, 0xEE,
		0x8F, 0x9E, 0xA5, 0xD9, 0xF9, 0x37, 0xE3, 0x02};

IRARC4Test::IRARC4Test() {
}

//------------------------------------------------------------------------------
IRARC4Test::~IRARC4Test() {
}

//------------------------------------------------------------------------------
void IRARC4Test::SetUp() {
}

//------------------------------------------------------------------------------
void IRARC4Test::TearDown() {
}

//------------------------------------------------------------------------------
TEST_F(IRARC4Test,Constructor) {
	IRARC4 * c;

	c = new IRARC4();
	for (int i = 0; i < 256; i++) {
		ASSERT_EQ(0, c->next());
	}
	delete c;

	c = new IRARC4(IRARC4Test_KEY, sizeof(IRARC4Test_KEY));
	for (int i = 0; i < sizeof(IRARC4Test_KEYSTREAM); i++) {
		ASSERT_EQ(IRARC4Test_KEYSTREAM[i], c->next());
	}
	delete c;
}

//------------------------------------------------------------------------------
TEST_F(IRARC4Test,setKey) {
	IRARC4 c;

	// No key set
	for (int i = 0; i < 256; i++) {
		ASSERT_EQ(0, c.next());
	}

	// Set the key
	c.setKey(IRARC4Test_KEY, sizeof(IRARC4Test_KEY));
	for (int i = 0; i < sizeof(IRARC4Test_KEYSTREAM); i++) {
		ASSERT_EQ(IRARC4Test_KEYSTREAM[i], c.next());
	}
}

//------------------------------------------------------------------------------
TEST_F(IRARC4Test, remixKey) {
	IRARC4 c;

	// No key set - the remix should generate all values as zeroes
	c.remixKey(IRARC4Test_KEY, sizeof(IRARC4Test_KEY));
	for (int i = 0; i < 256; i++) {
		ASSERT_EQ(0, c.next());
	}

	// Set key and them remix it
	c.setKey(IRARC4Test_KEY, sizeof(IRARC4Test_KEY));
	c.remixKey(IRARC4Test_KEY, sizeof(IRARC4Test_KEY));
	int count = 0;
	for (int i = 0; i < sizeof(IRARC4Test_KEYSTREAM); i++) {
		if (IRARC4Test_KEYSTREAM[i] != c.next()) {
			count++;
		}
	}
	ASSERT_EQ(sizeof(IRARC4Test_KEYSTREAM), count);

	// Compare the remix
	c.setKey(IRARC4Test_KEY, sizeof(IRARC4Test_KEY));
	c.remixKey(IRARC4Test_KEY, sizeof(IRARC4Test_KEY));
	IRARC4 d;
	d.setKey(IRARC4Test_KEY, sizeof(IRARC4Test_KEY));
	d.remixKey(IRARC4Test_KEY, sizeof(IRARC4Test_KEY));
	for (int i = 0; i < 512; i++) {
		ASSERT_EQ(c.next(), d.next());
	}
}

//------------------------------------------------------------------------------
TEST_F(IRARC4Test, saveLoad) {
	IRARC4 c(IRARC4Test_KEY, sizeof(IRARC4Test_KEY));
	IRARC4 d(IRARC4Test_KEY, sizeof(IRARC4Test_KEY));

	c.save();
	for (int i = 0; i < 512; i++) {
		c.next();
	}

	c.load();
	for (int i = 0; i < 512; i++) {
		ASSERT_EQ(c.next(), d.next());
	}
}

//------------------------------------------------------------------------------
TEST_F(IRARC4Test, next) {
	IRARC4 c(IRARC4Test_KEY, sizeof(IRARC4Test_KEY));

	for (int i = 0; i < sizeof(IRARC4Test_KEYSTREAM); i++) {
		ASSERT_EQ(IRARC4Test_KEYSTREAM[i], c.next());
	}
}

//------------------------------------------------------------------------------
TEST_F(IRARC4Test, skip) {
	IRARC4 c(IRARC4Test_KEY, sizeof(IRARC4Test_KEY));
	IRARC4 d(IRARC4Test_KEY, sizeof(IRARC4Test_KEY));

	c.skip(512);
	for (int i = 0; i < 512; i++) {
		d.next();
	}
	for (int i = 0; i < 512; i++) {
		ASSERT_EQ(c.next(), d.next());
	}
}

//------------------------------------------------------------------------------
TEST_F(IRARC4Test, apply) {
	IRARC4 c(IRARC4Test_KEY, sizeof(IRARC4Test_KEY));
	std::uint8_t exp[256];
	std::uint8_t buff[sizeof(exp)];

	for (int i = 0; i < sizeof(exp); i++) {
		exp[i] = i;
	}
	std::memcpy(buff, exp, sizeof(exp));

	c.save();
	c.apply(buff, sizeof(buff));
	ASSERT_NE(0, std::memcmp(exp, buff, sizeof(exp)));
	c.load();
	c.apply(buff, sizeof(buff));
	ASSERT_EQ(0, std::memcmp(exp, buff, sizeof(exp)));
}

//------------------------------------------------------------------------------
