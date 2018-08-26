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
#include "ILInt16TagTest.h"
#include <ircommon/iltagstd.h>
#include <ircommon/ilint.h>
#include <cstring>
using namespace ircommon;
using namespace ircommon::iltags;

//==============================================================================
// class ILInt16TagTest
//------------------------------------------------------------------------------
ILInt16TagTest::ILInt16TagTest() {
}

//------------------------------------------------------------------------------
ILInt16TagTest::~ILInt16TagTest() {
}

//------------------------------------------------------------------------------
void ILInt16TagTest::SetUp() {
}

//------------------------------------------------------------------------------
void ILInt16TagTest::TearDown() {
}

//------------------------------------------------------------------------------
TEST_F(ILInt16TagTest,Constructor) {
	ILInt16Tag * t;

	t = new ILInt16Tag();
	ASSERT_EQ(ILTag::TAG_INT16, t->id());
	ASSERT_EQ(0, t->value());
	ASSERT_EQ(sizeof(std::int16_t), t->size());
	delete t;
}

//------------------------------------------------------------------------------
TEST_F(ILInt16TagTest, serialize) {
	ILInt16Tag t;
	IRBuffer out;
	IRBuffer exp;
	std::int16_t v;

	v = 0;
	for (unsigned int i = 0; i < sizeof(v); i++) {
		v = (v << 8) | i;
	}
	t.setValue(v);
	ASSERT_TRUE(t.serialize(out));

	ASSERT_TRUE(exp.writeILInt(ILTag::TAG_INT16));
	ASSERT_TRUE(exp.writeInt(v));
	ASSERT_EQ(exp.size(), out.size());
	ASSERT_EQ(0, std::memcmp(exp.roBuffer(), out.roBuffer(), exp.size()));
}

//------------------------------------------------------------------------------
TEST_F(ILInt16TagTest, deserializeValue) {
	ILInt16Tag t;
	IRBuffer src;
	std::int16_t v;
	ILTagFactory f;

	v = 0;
	for (unsigned int i = 0; i < sizeof(v); i++) {
		v = (v << 8) | i;
	}
	ASSERT_TRUE(src.writeInt(v));

	ASSERT_TRUE(t.deserializeValue(f, src.roBuffer(), src.size()));
	ASSERT_EQ(v, t.value());

	ASSERT_FALSE(t.deserializeValue(f, src.roBuffer(), src.size() - 1));
	src.write(0);
	ASSERT_FALSE(t.deserializeValue(f, src.roBuffer(), src.size()));
}

//------------------------------------------------------------------------------

