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
#include "IRSecureTempTest.h"
#include <ircommon/irutils.h>

#include <cstdint>
#include <cstring>

using namespace std;
using namespace ircommon;

//==============================================================================
// class IRSecureTempTest
//------------------------------------------------------------------------------
IRSecureTempTest::IRSecureTempTest() {
}

//------------------------------------------------------------------------------
IRSecureTempTest::~IRSecureTempTest() {
}

//------------------------------------------------------------------------------
void IRSecureTempTest::SetUp() {
}

//------------------------------------------------------------------------------
void IRSecureTempTest::TearDown() {
}

//------------------------------------------------------------------------------
TEST_F(IRSecureTempTest,Constructor) {

	for (unsigned int size = 1; size <= 64; size++) {
		IRUtils::IRSecureTemp tmp(size);
		IRUtils::IRSecureTemp & rTmp = tmp;

		ASSERT_EQ(size, tmp.size());
		ASSERT_TRUE(tmp.buff() != nullptr);
		ASSERT_TRUE(tmp.buff() == rTmp.buff());

		std::uint8_t exp[size];
		std::memset(exp, 0, sizeof(exp));
		std::memset(tmp.buff(), 0xFA, tmp.size());
		tmp.clear();
		ASSERT_EQ(0, std::memcmp(exp, tmp.buff(), size));
	}
}
//------------------------------------------------------------------------------

