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
#include "ILNullTagTest.h"
#include <ircommon/iltagstd.h>
using namespace ircommon;
using namespace ircommon::iltags;

//==============================================================================
// class ILNullTagTest
//------------------------------------------------------------------------------
ILNullTagTest::ILNullTagTest() {
}

//------------------------------------------------------------------------------
ILNullTagTest::~ILNullTagTest() {
}

//------------------------------------------------------------------------------
void ILNullTagTest::SetUp() {
}

//------------------------------------------------------------------------------
void ILNullTagTest::TearDown() {
}

//------------------------------------------------------------------------------
TEST_F(ILNullTagTest,Constructor) {
	ILNullTag * t;

	t = new ILNullTag();
	ASSERT_EQ(ILTag::TAG_NULL, t->id());
	delete t;
}

//------------------------------------------------------------------------------
TEST_F(ILNullTagTest, size) {
	ILNullTag t;

	ASSERT_EQ(0, t.size());
}

//------------------------------------------------------------------------------
TEST_F(ILNullTagTest, serializeValue) {
	ILNullTag t;
	IRBuffer out;

	ASSERT_TRUE(t.serialize(out));
	ASSERT_EQ(1, out.size());
	ASSERT_EQ(0, out.roBuffer()[0]);
}

//------------------------------------------------------------------------------

