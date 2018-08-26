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
#include "ILBinary32TagTest.h"
#include <ircommon/iltagstd.h>
#include <cstring>
using namespace ircommon;
using namespace ircommon::iltags;

//==============================================================================
// class ILBinary32TagTest
//------------------------------------------------------------------------------
ILBinary32TagTest::ILBinary32TagTest() {
}

//------------------------------------------------------------------------------
ILBinary32TagTest::~ILBinary32TagTest() {
}

//------------------------------------------------------------------------------
void ILBinary32TagTest::SetUp() {
}

//------------------------------------------------------------------------------
void ILBinary32TagTest::TearDown() {
}

//------------------------------------------------------------------------------
TEST_F(ILBinary32TagTest,Constructor) {
	ILBinary32Tag * t;

	t = new ILBinary32Tag();
	ASSERT_EQ(ILTag::TAG_BINARY32, t->id());
	ASSERT_EQ(float(0), t->value());
	ASSERT_EQ(sizeof(float), t->size());
	ASSERT_EQ(typeid(float), typeid(t->value()));
	delete t;
}

//------------------------------------------------------------------------------
TEST_F(ILBinary32TagTest, serialize) {
	ILBinary32Tag t;
	IRBuffer out;
	IRBuffer exp;
	float v;

	v = -1.234567;
	t.setValue(v);
	ASSERT_TRUE(t.serialize(out));

	ASSERT_TRUE(exp.writeILInt(ILTag::TAG_BINARY32));
	ASSERT_TRUE(exp.writeFloat(v));

	ASSERT_EQ(exp.size(), out.size());
	ASSERT_EQ(0, std::memcmp(exp.roBuffer(), out.roBuffer(), exp.size()));
}

//------------------------------------------------------------------------------

