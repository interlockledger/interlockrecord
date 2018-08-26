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
#include "ILILIntArrayTagTest.h"
#include <ircommon/iltagstd.h>
#include <ircommon/ilint.h>
#include <cstring>
using namespace ircommon;
using namespace ircommon::iltags;

//==============================================================================
// class IRILIntArrayTagTest
//------------------------------------------------------------------------------
ILILIntArrayTagTest::ILILIntArrayTagTest() {
}

//------------------------------------------------------------------------------
ILILIntArrayTagTest::~ILILIntArrayTagTest() {
}

//------------------------------------------------------------------------------
void ILILIntArrayTagTest::SetUp() {
}

//------------------------------------------------------------------------------
void ILILIntArrayTagTest::TearDown() {
}

//------------------------------------------------------------------------------
TEST_F(ILILIntArrayTagTest,Constructor) {
	ILILIntArrayTag * t;

	t = new ILILIntArrayTag();
	ASSERT_EQ(ILTag::TAG_ILINT64_ARRAY, t->id());
	ASSERT_EQ(0, t->count());
	delete t;
}

//------------------------------------------------------------------------------
TEST_F(ILILIntArrayTagTest, size) {
	ILILIntArrayTag t;

	std::uint64_t v = 0xFF;
	for(int i = 0; i < 8; i++) {
		std::uint64_t expected = ILInt::size(t.count());
		for(unsigned int j = 0; j < t.count(); j++) {
			expected += ILInt::size(t[j]);
		}
		ASSERT_EQ(expected, t.size());
		t.add(v);
		v = (v << 8) | 0xFF;
	}
}

//------------------------------------------------------------------------------
TEST_F(ILILIntArrayTagTest, serialize) {
	ILILIntArrayTag t;
	IRBuffer out;
	IRBuffer exp;

	// Empty
	ASSERT_TRUE(t.serialize(out));
	ASSERT_TRUE(exp.writeILInt(ILTag::TAG_ILINT64_ARRAY));
	ASSERT_TRUE(exp.writeILInt(t.size()));
	ASSERT_TRUE(exp.writeILInt(t.count()));

	ASSERT_EQ(exp.size(), out.size());
	ASSERT_EQ(0, std::memcmp(exp.roBuffer(), out.roBuffer(), exp.size()));

	// With elements
	out.setSize(0);
	exp.setSize(0);
	std::uint64_t v = 0xFF;
	for(int i = 0; i < 8; i++) {
		t.add(v);
		v = (v << 8) | 0xFF;
	}

	ASSERT_TRUE(t.serialize(out));
	ASSERT_TRUE(exp.writeILInt(ILTag::TAG_ILINT64_ARRAY));
	ASSERT_TRUE(exp.writeILInt(t.size()));
	ASSERT_TRUE(exp.writeILInt(t.count()));
	for(unsigned int i = 0; i < t.count(); i++) {
		ASSERT_TRUE(exp.writeILInt(t[i]));
	}
	ASSERT_EQ(exp.size(), out.size());
	ASSERT_EQ(0, std::memcmp(exp.roBuffer(), out.roBuffer(), exp.size()));
}

//------------------------------------------------------------------------------
TEST_F(ILILIntArrayTagTest, deserialize) {
	ILILIntArrayTag t;
	IRBuffer src;
	ILTagFactory f;
	std::uint64_t values[8];

	// Empty
	t.add(0);
	ASSERT_EQ(1, t.count());
	ASSERT_TRUE(src.writeILInt(0));
	ASSERT_TRUE(t.deserializeValue(f, src.roBuffer(), src.size()));
	ASSERT_EQ(0, t.count());

	// Non empty
	src.setSize(0);
	std::uint64_t v = 0xFF;
	ASSERT_TRUE(src.writeILInt(8));
	for(int i = 0; i < 8; i++) {
		values[i] = v;
		ASSERT_TRUE(src.writeILInt(v));
		v = (v << 8) | 0xFF;
	}

	t.clear();
	ASSERT_TRUE(t.deserializeValue(f, src.roBuffer(), src.size()));
	ASSERT_EQ(8, t.count());
	for(unsigned int i = 0; i < t.count(); i++) {
		ASSERT_EQ(values[i], t[i]);
	}
}

//------------------------------------------------------------------------------
TEST_F(ILILIntArrayTagTest, add) {
	ILILIntArrayTag t;
	std::uint64_t values[8];

	std::uint64_t v = 0xFF;
	for(int i = 0; i < 8; i++) {
		ASSERT_EQ(i, t.count());
		values[i] = v;
		ASSERT_TRUE(t.add(v));
		ASSERT_EQ(i + 1, t.count());
		for (int j = 0; j <= i; j++) {
			ASSERT_EQ(values[j], t[j]);
		}
		v = (v << 8) | 0xFF;
	}
}

//------------------------------------------------------------------------------
TEST_F(ILILIntArrayTagTest, insert) {
	ILILIntArrayTag t;

	ASSERT_EQ(0, t.count());
	ASSERT_TRUE(t.insert(0, 0x01));
	ASSERT_EQ(1, t.count());
	ASSERT_EQ(0x01, t[0]);

	ASSERT_TRUE(t.insert(0, 0x02));
	ASSERT_EQ(2, t.count());
	ASSERT_EQ(0x02, t[0]);
	ASSERT_EQ(0x01, t[1]);

	ASSERT_TRUE(t.insert(1, 0x03));
	ASSERT_EQ(3, t.count());
	ASSERT_EQ(0x02, t[0]);
	ASSERT_EQ(0x03, t[1]);
	ASSERT_EQ(0x01, t[2]);

	ASSERT_TRUE(t.insert(3, 0x04));
	ASSERT_EQ(4, t.count());
	ASSERT_EQ(0x02, t[0]);
	ASSERT_EQ(0x03, t[1]);
	ASSERT_EQ(0x01, t[2]);
	ASSERT_EQ(0x04, t[3]);
}

//------------------------------------------------------------------------------
TEST_F(ILILIntArrayTagTest, remove) {
	ILILIntArrayTag t;

	ASSERT_TRUE(t.add(0x00));
	ASSERT_TRUE(t.add(0x01));
	ASSERT_TRUE(t.add(0x02));
	ASSERT_TRUE(t.add(0x03));
	ASSERT_EQ(4, t.count());

	ASSERT_TRUE(t.remove(0));
	ASSERT_EQ(3, t.count());
	ASSERT_EQ(0x01, t[0]);
	ASSERT_EQ(0x02, t[1]);
	ASSERT_EQ(0x03, t[2]);

	ASSERT_TRUE(t.remove(1));
	ASSERT_EQ(2, t.count());
	ASSERT_EQ(0x01, t[0]);
	ASSERT_EQ(0x03, t[1]);

	ASSERT_TRUE(t.remove(1));
	ASSERT_EQ(1, t.count());
	ASSERT_EQ(0x01, t[0]);

	ASSERT_TRUE(t.remove(0));
	ASSERT_EQ(0, t.count());
}

//------------------------------------------------------------------------------
TEST_F(ILILIntArrayTagTest, get) {
	ILILIntArrayTag t;

	ASSERT_TRUE(t.add(0x00));
	ASSERT_TRUE(t.add(0x01));
	ASSERT_TRUE(t.add(0x02));
	ASSERT_TRUE(t.add(0x03));
	ASSERT_EQ(4, t.count());

	ASSERT_EQ(0x00, t.get(0));
	ASSERT_EQ(0x01, t.get(1));
	ASSERT_EQ(0x02, t.get(2));
	ASSERT_EQ(0x03, t.get(3));
}

//------------------------------------------------------------------------------
TEST_F(ILILIntArrayTagTest, getOperator) {
	ILILIntArrayTag t;

	ASSERT_TRUE(t.add(0x00));
	ASSERT_TRUE(t.add(0x01));
	ASSERT_TRUE(t.add(0x02));
	ASSERT_TRUE(t.add(0x03));
	ASSERT_EQ(4, t.count());

	ASSERT_EQ(0x00, t[0]);
	ASSERT_EQ(0x01, t[1]);
	ASSERT_EQ(0x02, t[2]);
	ASSERT_EQ(0x03, t[3]);
}

//------------------------------------------------------------------------------
TEST_F(ILILIntArrayTagTest, set) {
	ILILIntArrayTag t;

	ASSERT_TRUE(t.add(0x00));
	ASSERT_TRUE(t.add(0x01));
	ASSERT_TRUE(t.add(0x02));
	ASSERT_TRUE(t.add(0x03));
	ASSERT_EQ(4, t.count());

	t.set(0, 0xFF);
	ASSERT_EQ(0xFF, t.get(0));
	ASSERT_EQ(0x01, t.get(1));
	ASSERT_EQ(0x02, t.get(2));
	ASSERT_EQ(0x03, t.get(3));

	t.set(3, 0xFF);
	ASSERT_EQ(0xFF, t.get(0));
	ASSERT_EQ(0x01, t.get(1));
	ASSERT_EQ(0x02, t.get(2));
	ASSERT_EQ(0xFF, t.get(3));

	t.set(1, 0xFF);
	ASSERT_EQ(0xFF, t.get(0));
	ASSERT_EQ(0XFF, t.get(1));
	ASSERT_EQ(0x02, t.get(2));
	ASSERT_EQ(0xFF, t.get(3));

	t.set(2, 0xFF);
	ASSERT_EQ(0xFF, t.get(0));
	ASSERT_EQ(0XFF, t.get(1));
	ASSERT_EQ(0xFF, t.get(2));
	ASSERT_EQ(0xFF, t.get(3));
}


//------------------------------------------------------------------------------
TEST_F(ILILIntArrayTagTest, setOperator) {
	ILILIntArrayTag t;

	ASSERT_TRUE(t.add(0x00));
	ASSERT_TRUE(t.add(0x01));
	ASSERT_TRUE(t.add(0x02));
	ASSERT_TRUE(t.add(0x03));
	ASSERT_EQ(4, t.count());

	t[0] = 0xFF;
	ASSERT_EQ(0xFF, t.get(0));
	ASSERT_EQ(0x01, t.get(1));
	ASSERT_EQ(0x02, t.get(2));
	ASSERT_EQ(0x03, t.get(3));

	t[3] = 0xFF;
	ASSERT_EQ(0xFF, t.get(0));
	ASSERT_EQ(0x01, t.get(1));
	ASSERT_EQ(0x02, t.get(2));
	ASSERT_EQ(0xFF, t.get(3));

	t[1] = 0xFF;
	ASSERT_EQ(0xFF, t.get(0));
	ASSERT_EQ(0XFF, t.get(1));
	ASSERT_EQ(0x02, t.get(2));
	ASSERT_EQ(0xFF, t.get(3));

	t[2] = 0xFF;
	ASSERT_EQ(0xFF, t.get(0));
	ASSERT_EQ(0XFF, t.get(1));
	ASSERT_EQ(0xFF, t.get(2));
	ASSERT_EQ(0xFF, t.get(3));
}

//------------------------------------------------------------------------------
TEST_F(ILILIntArrayTagTest, clear) {
	ILILIntArrayTag t;

	ASSERT_TRUE(t.add(0x00));
	ASSERT_TRUE(t.add(0x01));
	ASSERT_TRUE(t.add(0x02));
	ASSERT_TRUE(t.add(0x03));
	ASSERT_EQ(4, t.count());
	t.clear();
	ASSERT_EQ(0, t.count());
}
//------------------------------------------------------------------------------
