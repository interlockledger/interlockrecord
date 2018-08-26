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
#include "ILByteArrayTagTest.h"
#include <ircommon/iltagstd.h>
#include <cstring>
using namespace ircommon;
using namespace ircommon::iltags;

//==============================================================================
// class IRByteArrayTagTest
//------------------------------------------------------------------------------
ILByteArrayTagTest::ILByteArrayTagTest() {
}

//------------------------------------------------------------------------------
ILByteArrayTagTest::~ILByteArrayTagTest() {
}

//------------------------------------------------------------------------------
void ILByteArrayTagTest::SetUp() {
}

//------------------------------------------------------------------------------
void ILByteArrayTagTest::TearDown() {
}

//------------------------------------------------------------------------------
TEST_F(ILByteArrayTagTest, Constructor) {
	ILByteArrayTag * t;

	t = new ILByteArrayTag();
	ASSERT_EQ(ILTag::TAG_BYTE_ARRAY, t->id());
	ASSERT_EQ(0, t->value().size());
	ASSERT_FALSE(t->value().secure());
	delete t;

	t = new ILByteArrayTag(false);
	ASSERT_EQ(ILTag::TAG_BYTE_ARRAY, t->id());
	ASSERT_EQ(0, t->value().size());
	ASSERT_FALSE(t->value().secure());
	delete t;

	t = new ILByteArrayTag(true);
	ASSERT_EQ(ILTag::TAG_BYTE_ARRAY, t->id());
	ASSERT_EQ(0, t->value().size());
	ASSERT_TRUE(t->value().secure());
	delete t;
}
//------------------------------------------------------------------------------

