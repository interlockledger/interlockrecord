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
#include "IRCryptoTest.h"
#include <irecordcore/ircrypto.h>

using namespace irecordcore::crypto;

//==============================================================================
// class IRCryptoTest
//------------------------------------------------------------------------------
IRCryptoTest::IRCryptoTest() {
}

//------------------------------------------------------------------------------
IRCryptoTest::~IRCryptoTest() {
}

//------------------------------------------------------------------------------
void IRCryptoTest::SetUp() {
}

//------------------------------------------------------------------------------
void IRCryptoTest::TearDown() {
}

//------------------------------------------------------------------------------
TEST_F(IRCryptoTest, IRHashAlg) {

	ASSERT_EQ(0, IR_HASH_SHA1);
	ASSERT_EQ(1, IR_HASH_SHA256);
	ASSERT_EQ(2, IR_HASH_SHA512);
	ASSERT_EQ(3, IR_HASH_SHA3_256);
	ASSERT_EQ(4, IR_HASH_SHA3_512);
	ASSERT_EQ(5, IR_HASH_SHA224);
	ASSERT_EQ(6, IR_HASH_SHA384);
	ASSERT_EQ(7, IR_HASH_SHA3_224);
	ASSERT_EQ(8, IR_HASH_SHA3_384);
	ASSERT_EQ(9, IR_WHIRLPOOL);
	ASSERT_EQ(10, IR_RIPEMD_160);
	ASSERT_EQ(0xFFFF, IR_HASH_COPY);
}

//------------------------------------------------------------------------------
TEST_F(IRCryptoTest, IRSignAlg) {

	ASSERT_EQ(0, IR_SIG_RSA);
	ASSERT_EQ(1, IR_SIG_RSA_1_5);
	ASSERT_EQ(2, IR_SIG_DSA);
	ASSERT_EQ(3, IR_SIG_ELGAMAL);
	ASSERT_EQ(4, IR_SIG_ECDSA);
	ASSERT_EQ(5, IR_SIG_EDDSA);
}
//------------------------------------------------------------------------------

