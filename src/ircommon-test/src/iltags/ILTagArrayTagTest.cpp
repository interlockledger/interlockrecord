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
#include "ILTagArrayTagTest.h"
#include <ircommon/iltag.h>
#include <ircommon/iltagstd.h>
using namespace ircommon;
using namespace ircommon::iltags;

//==============================================================================
// class ILTagListTagTest
//------------------------------------------------------------------------------
ILTagArrayTagTest::ILTagArrayTagTest() {
}

//------------------------------------------------------------------------------
ILTagArrayTagTest::~ILTagArrayTagTest() {
}

//------------------------------------------------------------------------------
void ILTagArrayTagTest::SetUp() {
}

//------------------------------------------------------------------------------
void ILTagArrayTagTest::TearDown() {
}

//------------------------------------------------------------------------------
TEST_F(ILTagArrayTagTest, Constructor) {
	ILBaseTagListTag * tag;

	tag = new ILTagArrayTag();
	ASSERT_EQ(ILTag::TAG_ILTAG_ARRAY, tag->id());
	delete tag;
}
//------------------------------------------------------------------------------

