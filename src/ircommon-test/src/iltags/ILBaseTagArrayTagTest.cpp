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
#include "ILBaseTagArrayTagTest.h"
#include "ILBaseTagListTagTest.h"
#include <ircommon/iltag.h>
#include <ircommon/ilint.h>
#include <cstring>
using namespace ircommon;
using namespace ircommon::iltags;

//==============================================================================
// class ILBaseTagArrayTagTest
//------------------------------------------------------------------------------
ILBaseTagArrayTagTest::ILBaseTagArrayTagTest() {
}

//------------------------------------------------------------------------------
ILBaseTagArrayTagTest::~ILBaseTagArrayTagTest() {
}

//------------------------------------------------------------------------------
void ILBaseTagArrayTagTest::SetUp() {
}

//------------------------------------------------------------------------------
void ILBaseTagArrayTagTest::TearDown() {
}

//------------------------------------------------------------------------------
TEST_F(ILBaseTagArrayTagTest,Constructor) {
	ILBaseTagArrayTag * tag;

	tag = new ILBaseTagArrayTag(ILTag::TAG_ILTAG_ARRAY);
	ASSERT_EQ(ILTag::TAG_ILTAG_ARRAY, tag->id());
	ASSERT_EQ(ILInt::size(tag->count()), tag->size());
	ASSERT_EQ(0, tag->count());
	delete tag;

}

//------------------------------------------------------------------------------
TEST_F(ILBaseTagArrayTagTest, size) {
	ILBaseTagArrayTag tag(ILTag::TAG_ILTAG_ARRAY);
	ILTag * t;
	std::uint64_t payloadSize;

	ASSERT_EQ(ILInt::size(tag.count()), tag.size());
	payloadSize = 0;
	for (int i = 0; i < 256; i++) {
		t =  ILBaseTagListTagTest::createSample(0xFF, 10);
		payloadSize += t->tagSize();
		tag.add(t);
		ASSERT_EQ(ILInt::size(tag.count()) + payloadSize, tag.size());
	}
}

//------------------------------------------------------------------------------
TEST_F(ILBaseTagArrayTagTest, count) {
	ILBaseTagArrayTag tag(ILTag::TAG_ILTAG_ARRAY);
	ILTag * t;

	ASSERT_EQ(0, tag.count());
	for (int i = 0; i < 256; i++) {
		t =  ILBaseTagListTagTest::createSample(0xFF, i);
		tag.add(t);
		ASSERT_EQ(i + 1, tag.count());
	}
}

//------------------------------------------------------------------------------
TEST_F(ILBaseTagArrayTagTest, add) {
	ILBaseTagArrayTag tag(ILTag::TAG_ILTAG_ARRAY);
	ILTag * t;

	ASSERT_EQ(0, tag.count());
	for (int i = 0; i < 16; i++) {
		t =  ILBaseTagListTagTest::createSample(0xFF + i, 1);
		ASSERT_TRUE(tag.add(ILBaseTagArrayTag::SharedPointer(t)));
		ASSERT_EQ(i + 1, tag.count());
		for (int j = 0; j <= i; j++) {
			ASSERT_EQ(0xFF + j, tag[j]->id());
		}
	}
}

//------------------------------------------------------------------------------
TEST_F(ILBaseTagArrayTagTest, addPtr) {
	ILBaseTagArrayTag tag(ILTag::TAG_ILTAG_ARRAY);
	ILTag * t;

	ASSERT_EQ(0, tag.count());
	for (int i = 0; i < 16; i++) {
		t =  ILBaseTagListTagTest::createSample(0xFF + i, 1);
		ASSERT_TRUE(tag.add(t));
		ASSERT_EQ(i + 1, tag.count());
		for (int j = 0; j <= i; j++) {
			ASSERT_EQ(0xFF + j, tag[j]->id());
		}
	}
}

//------------------------------------------------------------------------------
TEST_F(ILBaseTagArrayTagTest, insert) {
	ILBaseTagArrayTag tag(ILTag::TAG_ILTAG_ARRAY);
	ILTag * t;

	ASSERT_EQ(0, tag.count());

	t =  ILBaseTagListTagTest::createSample(0xFF, 1);
	ASSERT_TRUE(tag.insert(0, ILBaseTagArrayTag::SharedPointer(t)));
	ASSERT_EQ(1, tag.count());
	ASSERT_EQ(0xFF, tag[0]->id());

	t =  ILBaseTagListTagTest::createSample(0xFF + 1, 1);
	ASSERT_TRUE(tag.insert(0, ILBaseTagArrayTag::SharedPointer(t)));
	ASSERT_EQ(2, tag.count());
	ASSERT_EQ(0xFF + 1, tag[0]->id());
	ASSERT_EQ(0xFF, tag[1]->id());

	t =  ILBaseTagListTagTest::createSample(0xFF + 2, 1);
	ASSERT_TRUE(tag.insert(1, ILBaseTagArrayTag::SharedPointer(t)));
	ASSERT_EQ(3, tag.count());
	ASSERT_EQ(0xFF + 1, tag[0]->id());
	ASSERT_EQ(0xFF + 2, tag[1]->id());
	ASSERT_EQ(0xFF, tag[2]->id());

	t =  ILBaseTagListTagTest::createSample(0xFF + 3, 1);
	ASSERT_TRUE(tag.insert(3, ILBaseTagArrayTag::SharedPointer(t)));
	ASSERT_EQ(4, tag.count());
	ASSERT_EQ(0xFF + 1, tag[0]->id());
	ASSERT_EQ(0xFF + 2, tag[1]->id());
	ASSERT_EQ(0xFF, tag[2]->id());
	ASSERT_EQ(0xFF + 3, tag[3]->id());
}

//------------------------------------------------------------------------------
TEST_F(ILBaseTagArrayTagTest, insertPtr) {
	ILBaseTagArrayTag tag(ILTag::TAG_ILTAG_ARRAY);
	ILTag * t;

	ASSERT_EQ(0, tag.count());

	t =  ILBaseTagListTagTest::createSample(0xFF, 1);
	ASSERT_TRUE(tag.insert(0, t));
	ASSERT_EQ(1, tag.count());
	ASSERT_EQ(0xFF, tag[0]->id());

	t =  ILBaseTagListTagTest::createSample(0xFF + 1, 1);
	ASSERT_TRUE(tag.insert(0, t));
	ASSERT_EQ(2, tag.count());
	ASSERT_EQ(0xFF + 1, tag[0]->id());
	ASSERT_EQ(0xFF, tag[1]->id());

	t =  ILBaseTagListTagTest::createSample(0xFF + 2, 1);
	ASSERT_TRUE(tag.insert(1, t));
	ASSERT_EQ(3, tag.count());
	ASSERT_EQ(0xFF + 1, tag[0]->id());
	ASSERT_EQ(0xFF + 2, tag[1]->id());
	ASSERT_EQ(0xFF, tag[2]->id());

	t =  ILBaseTagListTagTest::createSample(0xFF + 3, 1);
	ASSERT_TRUE(tag.insert(3, t));
	ASSERT_EQ(4, tag.count());
	ASSERT_EQ(0xFF + 1, tag[0]->id());
	ASSERT_EQ(0xFF + 2, tag[1]->id());
	ASSERT_EQ(0xFF, tag[2]->id());
	ASSERT_EQ(0xFF + 3, tag[3]->id());
}

//------------------------------------------------------------------------------
TEST_F(ILBaseTagArrayTagTest, remove) {
	ILBaseTagArrayTag tag(ILTag::TAG_ILTAG_ARRAY);

	ASSERT_EQ(0, tag.count());
	ASSERT_TRUE(tag.add(ILBaseTagListTagTest::createSample(0xFF + 0, 1)));
	ASSERT_TRUE(tag.add(ILBaseTagListTagTest::createSample(0xFF + 1, 1)));
	ASSERT_TRUE(tag.add(ILBaseTagListTagTest::createSample(0xFF + 2, 1)));
	ASSERT_TRUE(tag.add(ILBaseTagListTagTest::createSample(0xFF + 3, 1)));
	ASSERT_EQ(4, tag.count());
	ASSERT_EQ(0xFF + 0, tag[0]->id());
	ASSERT_EQ(0xFF + 1, tag[1]->id());
	ASSERT_EQ(0xFF + 2, tag[2]->id());
	ASSERT_EQ(0xFF + 3, tag[3]->id());

	ASSERT_TRUE(tag.remove(3));
	ASSERT_EQ(3, tag.count());
	ASSERT_EQ(0xFF + 0, tag[0]->id());
	ASSERT_EQ(0xFF + 1, tag[1]->id());
	ASSERT_EQ(0xFF + 2, tag[2]->id());

	ASSERT_TRUE(tag.remove(1));
	ASSERT_EQ(2, tag.count());
	ASSERT_EQ(0xFF + 0, tag[0]->id());
	ASSERT_EQ(0xFF + 2, tag[1]->id());

	ASSERT_TRUE(tag.remove(0));
	ASSERT_EQ(1, tag.count());
	ASSERT_EQ(0xFF + 2, tag[0]->id());

	ASSERT_TRUE(tag.remove(0));
	ASSERT_EQ(0, tag.count());
}

//------------------------------------------------------------------------------
TEST_F(ILBaseTagArrayTagTest, clear) {
	ILBaseTagArrayTag tag(ILTag::TAG_ILTAG_ARRAY);

	ASSERT_EQ(0, tag.count());
	ASSERT_TRUE(tag.add(ILBaseTagListTagTest::createSample(0xFF + 0, 1)));
	ASSERT_TRUE(tag.add(ILBaseTagListTagTest::createSample(0xFF + 1, 1)));
	ASSERT_TRUE(tag.add(ILBaseTagListTagTest::createSample(0xFF + 2, 1)));
	ASSERT_TRUE(tag.add(ILBaseTagListTagTest::createSample(0xFF + 3, 1)));
	ASSERT_EQ(4, tag.count());
	ASSERT_EQ(0xFF + 0, tag[0]->id());
	ASSERT_EQ(0xFF + 1, tag[1]->id());
	ASSERT_EQ(0xFF + 2, tag[2]->id());
	ASSERT_EQ(0xFF + 3, tag[3]->id());

	tag.clear();
	ASSERT_EQ(0, tag.count());
}

//------------------------------------------------------------------------------
TEST_F(ILBaseTagArrayTagTest, accessOperatorRO) {
	ILBaseTagArrayTag tag(ILTag::TAG_ILTAG_ARRAY);
	const ILBaseTagArrayTag & roTag(tag);

	ASSERT_EQ(0, tag.count());
	ASSERT_TRUE(tag.add(ILBaseTagListTagTest::createSample(0xFF + 0, 1)));
	ASSERT_TRUE(tag.add(ILBaseTagListTagTest::createSample(0xFF + 1, 1)));
	ASSERT_TRUE(tag.add(ILBaseTagListTagTest::createSample(0xFF + 2, 1)));
	ASSERT_TRUE(tag.add(ILBaseTagListTagTest::createSample(0xFF + 3, 1)));
	ASSERT_EQ(4, tag.count());
	ASSERT_EQ(0xFF + 0, roTag[0]->id());
	ASSERT_EQ(0xFF + 1, roTag[1]->id());
	ASSERT_EQ(0xFF + 2, roTag[2]->id());
	ASSERT_EQ(0xFF + 3, roTag[3]->id());
}

//------------------------------------------------------------------------------
TEST_F(ILBaseTagArrayTagTest, accessOperatorRW) {
	ILBaseTagArrayTag tag(ILTag::TAG_ILTAG_ARRAY);

	ASSERT_EQ(0, tag.count());
	ASSERT_TRUE(tag.add(ILBaseTagListTagTest::createSample(0xFF + 0, 1)));
	ASSERT_TRUE(tag.add(ILBaseTagListTagTest::createSample(0xFF + 1, 1)));
	ASSERT_TRUE(tag.add(ILBaseTagListTagTest::createSample(0xFF + 2, 1)));
	ASSERT_TRUE(tag.add(ILBaseTagListTagTest::createSample(0xFF + 3, 1)));
	ASSERT_EQ(4, tag.count());
	ASSERT_EQ(0xFF + 0, tag[0]->id());
	ASSERT_EQ(0xFF + 1, tag[1]->id());
	ASSERT_EQ(0xFF + 2, tag[2]->id());
	ASSERT_EQ(0xFF + 3, tag[3]->id());
}

//------------------------------------------------------------------------------
TEST_F(ILBaseTagArrayTagTest, serialize) {
	ILBaseTagArrayTag tag(ILTag::TAG_ILTAG_ARRAY);
	IRBuffer out;
	IRBuffer expected;

	// Create the object to be serialized
	for (int i = 0; i < 256; i++) {
		ASSERT_TRUE(tag.add(ILBaseTagListTagTest::createSample(0xFF + i, i)));
	}

	// Serialize by hand
	ASSERT_TRUE(expected.writeILInt(tag.id()));
	ASSERT_TRUE(expected.writeILInt(tag.size()));
	ASSERT_TRUE(expected.writeILInt(tag.count()));
	for (unsigned int i = 0; i < tag.count(); i++) {
		ASSERT_TRUE(tag[i]->serialize(expected));
	}

	ASSERT_TRUE(tag.serialize(out));
	ASSERT_EQ(expected.size(), out.size());
	ASSERT_EQ(0, std::memcmp(expected.roBuffer(), out.roBuffer(),
			expected.size()));
}

//------------------------------------------------------------------------------
TEST_F(ILBaseTagArrayTagTest, deserializeValue) {
	ILBaseTagArrayTag tag(ILTag::TAG_ILTAG_ARRAY);
	ILTagFactory f;
	ILTag * t;
	IRBuffer serialized;

	// Serialize by hand
	ASSERT_TRUE(serialized.writeILInt(256));
	for (int i = 0; i < 256; i++) {
		t = ILBaseTagListTagTest::createSample(0xFF + i, i);
		ASSERT_TRUE(t->serialize(serialized));
		delete t;
	}
	serialized.beginning();
	ASSERT_TRUE(tag.deserializeValue(f, serialized.roBuffer(), serialized.size()));

	ASSERT_EQ(256, tag.count());
	for (unsigned int i = 0; i < tag.count(); i++) {
		ASSERT_EQ(0xFF + i, tag[i]->id());
		ASSERT_EQ(i, tag[i]->size());
	}
}

//------------------------------------------------------------------------------
