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
#include "ILILIntTagTest.h"
#include <ircommon/iltagstd.h>
#include <ircommon/ilint.h>
#include <cstring>
using namespace ircommon;
using namespace ircommon::iltags;

//==============================================================================
// class ILILIntTagTest
//------------------------------------------------------------------------------
ILILIntTagTest::ILILIntTagTest() {
}

//------------------------------------------------------------------------------
ILILIntTagTest::~ILILIntTagTest() {
}

//------------------------------------------------------------------------------
void ILILIntTagTest::SetUp() {
}

//------------------------------------------------------------------------------
void ILILIntTagTest::TearDown() {
}

//------------------------------------------------------------------------------
TEST_F(ILILIntTagTest,Constructor) {
	ILILIntTag * t;

	t = new ILILIntTag();
	ASSERT_EQ(ILTag::TAG_ILINT64, t->id());
	ASSERT_EQ(0, t->value());
	ASSERT_EQ(1, t->size());
	delete t;
}

//------------------------------------------------------------------------------
TEST_F(ILILIntTagTest, getSetValue) {
	ILILIntTag t;

	ASSERT_EQ(0, t.value());

	std::uint64_t v = 0xFF;
	for (int i = 0; i < 8; i++) {
		t.setValue(v);
		ASSERT_EQ(v, t.value());
		v = (v << 8) | 0xFF;
	}
}

//------------------------------------------------------------------------------
TEST_F(ILILIntTagTest, size) {
	ILILIntTag t;

	ASSERT_EQ(0, t.value());

	std::uint64_t v = 0xFF;
	for (int i = 0; i < 8; i++) {
		t.setValue(v);
		ASSERT_EQ(ILInt::size(v), t.size());
		v = (v << 8) | 0xFF;
	}
}

//------------------------------------------------------------------------------
TEST_F(ILILIntTagTest, serialize) {
	ILILIntTag t;
	IRBuffer out;
	IRBuffer exp;

	ASSERT_EQ(0, t.value());
	ASSERT_TRUE(t.serialize(out));
	ASSERT_TRUE(exp.writeILInt(ILTag::TAG_ILINT64));
	ASSERT_TRUE(exp.writeILInt(0));
	ASSERT_EQ(exp.size(), out.size());
	ASSERT_EQ(0, std::memcmp(exp.roBuffer(), out.roBuffer(), exp.size()));

	std::uint64_t v = 0xFF;
	for (int i = 0; i < 8; i++) {
		out.setSize(0);
		exp.setSize(0);

		t.setValue(v);

		ASSERT_TRUE(t.serialize(out));
		ASSERT_TRUE(exp.writeILInt(ILTag::TAG_ILINT64));
		ASSERT_TRUE(exp.writeILInt(v));
		ASSERT_EQ(exp.size(), out.size());
		ASSERT_EQ(0, std::memcmp(exp.roBuffer(), out.roBuffer(), exp.size()));
		v = (v << 8) | 0xFF;
	}
}

//------------------------------------------------------------------------------
TEST_F(ILILIntTagTest, deserializeValue) {
	ILILIntTag t;
	IRBuffer src;
	ILTagFactory f;

	ASSERT_TRUE(src.writeILInt(0));
	t.setValue(1);
	ASSERT_TRUE(t.deserializeValue(f, src.roBuffer(), src.size()));
	ASSERT_EQ(0, t.value());

	std::uint64_t v = 0xFF;
	for (int i = 0; i < 8; i++) {
		src.setSize(0);
		ASSERT_TRUE(src.writeILInt(v));
		ASSERT_TRUE(t.deserializeValue(f, src.roBuffer(), src.size()));
		ASSERT_EQ(v, t.value());
		v = (v << 8) | 0xFF;
	}

	ASSERT_FALSE(t.deserializeValue(f, src.roBuffer(), src.size() - 1));
	src.write(0);
	ASSERT_FALSE(t.deserializeValue(f, src.roBuffer(), src.size()));
}

//------------------------------------------------------------------------------

