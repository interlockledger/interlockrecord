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
#include "IRBotanSecureRandomTest.h"
#include "CryptoSamples.h"
#include <irecordcore/irsrand.h>
#include <botan/system_rng.h>
#include <cstring>

using namespace irecordcore::crypto;

//==============================================================================
// class IRBotanSecureRandomTest
//------------------------------------------------------------------------------
IRBotanSecureRandomTest::IRBotanSecureRandomTest() {
}

//------------------------------------------------------------------------------
IRBotanSecureRandomTest::~IRBotanSecureRandomTest() {
}

//------------------------------------------------------------------------------
void IRBotanSecureRandomTest::SetUp() {
}

//------------------------------------------------------------------------------
void IRBotanSecureRandomTest::TearDown() {
}

//------------------------------------------------------------------------------
TEST_F(IRBotanSecureRandomTest, Constructor) {
	IRBotanSecureRandom * r;

	r = new IRBotanSecureRandom(new Botan::System_RNG());
	delete r;
}

//------------------------------------------------------------------------------
TEST_F(IRBotanSecureRandomTest, backend) {
	IRBotanSecureRandom r(new Botan::System_RNG());

	ASSERT_EQ(typeid(Botan::System_RNG&), typeid(r.backend()));
}

//------------------------------------------------------------------------------

