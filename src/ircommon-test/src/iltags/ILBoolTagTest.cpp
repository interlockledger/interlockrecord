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
#include "ILBoolTagTest.h"
#include <ircommon/iltagstd.h>
using namespace ircommon;
using namespace ircommon::iltags;

//==============================================================================
// class ILBoolTagTest
//------------------------------------------------------------------------------
ILBoolTagTest::ILBoolTagTest() {
}

//------------------------------------------------------------------------------
ILBoolTagTest::~ILBoolTagTest() {
}

//------------------------------------------------------------------------------
void ILBoolTagTest::SetUp() {
}

//------------------------------------------------------------------------------
void ILBoolTagTest::TearDown() {
}

//------------------------------------------------------------------------------
TEST_F(ILBoolTagTest,Constructor) {
	ILBoolTag * t;

	t = new ILBoolTag();
	ASSERT_EQ(ILTag::TAG_BOOL, t->id());
	ASSERT_FALSE(t->value());
	delete t;
}

//------------------------------------------------------------------------------
TEST_F(ILBoolTagTest, size) {
	ILBoolTag t;

	ASSERT_EQ(1, t.size());
}

//------------------------------------------------------------------------------
TEST_F(ILBoolTagTest, serialize) {
	ILBoolTag t;
	IRBuffer out;

	ASSERT_TRUE(t.serialize(out));
	ASSERT_EQ(2, out.size());
	ASSERT_EQ(ILTag::TAG_BOOL, out.roBuffer()[0]);
	ASSERT_EQ(0, out.roBuffer()[1]);

	out.setSize(0);
	t.setValue(true);
	ASSERT_TRUE(t.serialize(out));
	ASSERT_EQ(2, out.size());
	ASSERT_EQ(ILTag::TAG_BOOL, out.roBuffer()[0]);
	ASSERT_EQ(1, out.roBuffer()[1]);
}

//------------------------------------------------------------------------------
TEST_F(ILBoolTagTest, deserializeValue) {
	ILBoolTag t;
	std::uint8_t serialized[8];
	ILTagFactory f;

	std::memset(serialized, 0, sizeof(serialized));
	t.setValue(true);
	ASSERT_TRUE(t.deserializeValue(f, serialized, 1));
	ASSERT_FALSE(t.value());

	std::memset(serialized, 0, sizeof(serialized));
	serialized[0] = 1;
	t.setValue(false);
	ASSERT_TRUE(t.deserializeValue(f, serialized, 1));
	ASSERT_TRUE(t.value());

	ASSERT_FALSE(t.deserializeValue(f, serialized, 0));
	ASSERT_FALSE(t.deserializeValue(f, serialized, 2));
}

//------------------------------------------------------------------------------

