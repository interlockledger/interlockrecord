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
#include "IRTagTypeTest.h"
#include <irecordcore/irtags.h>
using namespace irecordcore::tags;

//==============================================================================
// class IRTagTypeTest
//------------------------------------------------------------------------------
IRTagTypeTest::IRTagTypeTest() {
}

//------------------------------------------------------------------------------
IRTagTypeTest::~IRTagTypeTest() {
}

//------------------------------------------------------------------------------
void IRTagTypeTest::SetUp() {
}

//------------------------------------------------------------------------------
void IRTagTypeTest::TearDown() {
}

//------------------------------------------------------------------------------
TEST_F(IRTagTypeTest, Constants) {

	ASSERT_EQ(32, TAG_BLOCK);
	ASSERT_EQ(33, TAG_SIGNED);
	ASSERT_EQ(34, TAG_BLOCK_SIG);
	ASSERT_EQ(35, TAG_HEADER);
	ASSERT_EQ(36, TAG_PAYLOAD);
	ASSERT_EQ(37, TAG_PUB);
	ASSERT_EQ(38, TAG_SIG);
	ASSERT_EQ(39, TAG_HASH);
}
//------------------------------------------------------------------------------

