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
#include "IRKeyTest.h"
#include <irecordcore/irkey.h>
#include <ircommon/irbuffer.h>

using namespace irecordcore;
using namespace irecordcore::crypto;

//==============================================================================
// class IRKeyTest
//------------------------------------------------------------------------------
IRKeyTest::IRKeyTest() {
}

//------------------------------------------------------------------------------
IRKeyTest::~IRKeyTest() {
}

//------------------------------------------------------------------------------
void IRKeyTest::SetUp() {
}

//------------------------------------------------------------------------------
void IRKeyTest::TearDown() {
}

//------------------------------------------------------------------------------
TEST_F(IRKeyTest, Constructor) {
	IRKey * k;

	k = new IRKey(false);
	delete k;

	k = new IRKey(true);
	delete k;
}

//------------------------------------------------------------------------------
TEST_F(IRKeyTest, exportable) {
	IRKey * k;

	k = new IRKey(false);
	ASSERT_FALSE(k->exportable());
	delete k;

	k = new IRKey(true);
	ASSERT_TRUE(k->exportable());
	delete k;
}

//------------------------------------------------------------------------------
TEST_F(IRKeyTest, exportKey) {
	IRKey k(false);
	std::uint64_t outSize;
	std::uint8_t out[128];

	for (unsigned int size = 0; size <= sizeof(out); size ++) {
		outSize = size;
		ASSERT_FALSE(k.exportKey(out, outSize));
		ASSERT_EQ(0, outSize);

		outSize = size;
		ASSERT_FALSE(k.exportKey(nullptr, outSize));
		ASSERT_EQ(0, outSize);
	}
}

//------------------------------------------------------------------------------
TEST_F(IRKeyTest, serialize) {
	IRKey k(false);
	ircommon::IRBuffer out;

	ASSERT_FALSE(k.serialize(out));
	ASSERT_EQ(0, out.size());
}

//------------------------------------------------------------------------------

