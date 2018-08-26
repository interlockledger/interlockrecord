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
#include "ILRawTagTest.h"
#include <ircommon/iltag.h>
#include <cstring>
using namespace ircommon;
using namespace ircommon::iltags;

//==============================================================================
// class ILRawTagTest
//------------------------------------------------------------------------------
ILRawTagTest::ILRawTagTest() {
}

//------------------------------------------------------------------------------
ILRawTagTest::~ILRawTagTest() {
}

//------------------------------------------------------------------------------
void ILRawTagTest::SetUp() {
}

//------------------------------------------------------------------------------
void ILRawTagTest::TearDown() {
}

//------------------------------------------------------------------------------
TEST_F(ILRawTagTest,Constructor) {
	ILRawTag * t;

	t = new ILRawTag(ILTag::TAG_BYTE_ARRAY);
	ASSERT_EQ(ILTag::TAG_BYTE_ARRAY, t->id());
	ASSERT_FALSE(t->secure());
	ASSERT_EQ(0, t->value().size());
	ASSERT_EQ(IRBuffer::DEFAULT_INCREMENT, t->value().increment());
	delete t;

	t = new ILRawTag(0xFF, false);
	ASSERT_EQ(0xFF, t->id());
	ASSERT_FALSE(t->secure());
	ASSERT_EQ(0, t->value().size());
	ASSERT_EQ(IRBuffer::DEFAULT_INCREMENT, t->value().increment());
	delete t;

	t = new ILRawTag(0xFF, true);
	ASSERT_EQ(0xFF, t->id());
	ASSERT_TRUE(t->secure());
	ASSERT_EQ(0, t->value().size());
	ASSERT_EQ(IRBuffer::DEFAULT_INCREMENT, t->value().increment());
	delete t;

	t = new ILRawTag(0xFF, false, 32);
	ASSERT_EQ(0xFF, t->id());
	ASSERT_FALSE(t->secure());
	ASSERT_EQ(0, t->value().size());
	ASSERT_EQ(32, t->value().increment());
	delete t;

	t = new ILRawTag(0xFF, true, 32);
	ASSERT_EQ(0xFF, t->id());
	ASSERT_TRUE(t->secure());
	ASSERT_EQ(0, t->value().size());
	ASSERT_EQ(32, t->value().increment());
	delete t;
}

//------------------------------------------------------------------------------
TEST_F(ILRawTagTest, size) {
	ILRawTag t(0xFF);

	for (std::uint64_t size = 0; size < 1024; size++) {
		ASSERT_TRUE(t.value().setSize(size));
		ASSERT_EQ(size, t.size());
	}
}

//------------------------------------------------------------------------------
TEST_F(ILRawTagTest, deserializeValue) {
	ILTagFactory f;
	ILRawTag t(0xFF);
	std::uint8_t exp[512];

	std::memset(exp, 0xFA, sizeof(exp));
	ASSERT_TRUE(t.deserializeValue(f, exp, sizeof(exp)));
	ASSERT_EQ(sizeof(exp), t.size());
	ASSERT_EQ(0, std::memcmp(exp, t.value().roBuffer(), t.size()));
}

//------------------------------------------------------------------------------
TEST_F(ILRawTagTest, serialize) {
	ILTagFactory f;
	ILRawTag t(0xFF);
	IRBuffer exp;
	IRBuffer out;

	exp.writeILInt(0xFF);
	exp.writeILInt(0);
	ASSERT_TRUE(t.serialize(out));
	ASSERT_EQ(exp.size(), out.size());
	ASSERT_EQ(0, std::memcmp(exp.roBuffer(), out.roBuffer(), out.size()));

	exp.setSize(0);
	exp.writeILInt(0xFF);
	exp.writeILInt(256);
	t.value().setSize(0);
	for (int i = 0; i < 256; i++) {
		t.value().write(i);
		exp.write(i);
	}
	out.setSize(0);
	ASSERT_TRUE(t.serialize(out));
	ASSERT_EQ(exp.size(), out.size());
	ASSERT_EQ(0, std::memcmp(exp.roBuffer(), out.roBuffer(), out.size()));
}

//------------------------------------------------------------------------------
TEST_F(ILRawTagTest, value) {
	ILRawTag t(0xFF);
	const ILRawTag & rot = t;

	ASSERT_EQ(0, t.value().size());
	ASSERT_TRUE(t.value().write(1));
	ASSERT_EQ(1, rot.value().size());
}

//------------------------------------------------------------------------------
TEST_F(ILRawTagTest, secure) {

	ILRawTag t1(0xFF, false);
	ASSERT_EQ(t1.value().secure(), t1.secure());
	ASSERT_FALSE(t1.secure());

	ILRawTag t2(0xFF, true);
	ASSERT_EQ(t2.value().secure(), t2.secure());
	ASSERT_TRUE(t2.secure());
}
//------------------------------------------------------------------------------


