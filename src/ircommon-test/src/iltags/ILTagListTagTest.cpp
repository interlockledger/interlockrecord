/*
 * Copyright (c) 2017-2018, Open Communications Security
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the <organization> nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL OPEN COMMUNICATIONS SECURITY BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include "ILTagListTagTest.h"
#include <ircommon/iltag.h>
#include <ircommon/ilint.h>
#include <cstring>
using namespace ircommon;
using namespace ircommon::iltags;

//==============================================================================
// class ILTagListTagTest
//------------------------------------------------------------------------------
ILTagListTagTest::ILTagListTagTest() {
}

//------------------------------------------------------------------------------
ILTagListTagTest::~ILTagListTagTest() {
}

//------------------------------------------------------------------------------
void ILTagListTagTest::SetUp() {
}

//------------------------------------------------------------------------------
void ILTagListTagTest::TearDown() {
}

//------------------------------------------------------------------------------
ILTag * ILTagListTagTest::createSample(std::uint64_t id, int size) {
	ILRawTag * tag;

	tag = new ILRawTag(id);
	for (int i = 0; i < size; i++) {
		tag->value().write(size);
	}
	return tag;
}


//------------------------------------------------------------------------------
TEST_F(ILTagListTagTest,Constructor) {
	ILTagListTag * tag;

	tag = new ILTagListTag(ILTag::TAG_ILTAG_ARRAY);
	ASSERT_EQ(ILTag::TAG_ILTAG_ARRAY, tag->id());
	ASSERT_EQ(ILInt::size(tag->count()), tag->size());
	ASSERT_EQ(0, tag->count());
	delete tag;
}

//------------------------------------------------------------------------------
TEST_F(ILTagListTagTest, size) {
	ILTagListTag tag(ILTag::TAG_ILTAG_ARRAY);
	ILTag * t;
	std::uint64_t payloadSize;

	ASSERT_EQ(ILInt::size(tag.count()), tag.size());
	payloadSize = 0;
	for (int i = 0; i < 256; i++) {
		t =  ILTagListTagTest::createSample(0xFF, 10);
		payloadSize += t->tagSize();
		tag.add(t);
		ASSERT_EQ(ILInt::size(tag.count()) + payloadSize, tag.size());
	}
}

//------------------------------------------------------------------------------
TEST_F(ILTagListTagTest, count) {
	ILTagListTag tag(ILTag::TAG_ILTAG_ARRAY);
	ILTag * t;

	ASSERT_EQ(0, tag.count());
	for (int i = 0; i < 256; i++) {
		t =  ILTagListTagTest::createSample(0xFF, i);
		tag.add(t);
		ASSERT_EQ(i + 1, tag.count());
	}
}

//------------------------------------------------------------------------------
TEST_F(ILTagListTagTest, add) {
	ILTagListTag tag(ILTag::TAG_ILTAG_ARRAY);
	ILTag * t;

	ASSERT_EQ(0, tag.count());
	for (int i = 0; i < 16; i++) {
		t =  ILTagListTagTest::createSample(0xFF + i, 1);
		ASSERT_TRUE(tag.add(ILTagListTag::SharedPointer(t)));
		ASSERT_EQ(i + 1, tag.count());
		for (int j = 0; j <= i; j++) {
			ASSERT_EQ(0xFF + j, tag[j]->id());
		}
	}
}

//------------------------------------------------------------------------------
TEST_F(ILTagListTagTest, addPtr) {
	ILTagListTag tag(ILTag::TAG_ILTAG_ARRAY);
	ILTag * t;

	ASSERT_EQ(0, tag.count());
	for (int i = 0; i < 16; i++) {
		t =  ILTagListTagTest::createSample(0xFF + i, 1);
		ASSERT_TRUE(tag.add(t));
		ASSERT_EQ(i + 1, tag.count());
		for (int j = 0; j <= i; j++) {
			ASSERT_EQ(0xFF + j, tag[j]->id());
		}
	}
}

//------------------------------------------------------------------------------
TEST_F(ILTagListTagTest, insert) {
	ILTagListTag tag(ILTag::TAG_ILTAG_ARRAY);
	ILTag * t;

	ASSERT_EQ(0, tag.count());

	t =  ILTagListTagTest::createSample(0xFF, 1);
	ASSERT_TRUE(tag.insert(0, ILTagListTag::SharedPointer(t)));
	ASSERT_EQ(1, tag.count());
	ASSERT_EQ(0xFF, tag[0]->id());

	t =  ILTagListTagTest::createSample(0xFF + 1, 1);
	ASSERT_TRUE(tag.insert(0, ILTagListTag::SharedPointer(t)));
	ASSERT_EQ(2, tag.count());
	ASSERT_EQ(0xFF + 1, tag[0]->id());
	ASSERT_EQ(0xFF, tag[1]->id());

	t =  ILTagListTagTest::createSample(0xFF + 2, 1);
	ASSERT_TRUE(tag.insert(1, ILTagListTag::SharedPointer(t)));
	ASSERT_EQ(3, tag.count());
	ASSERT_EQ(0xFF + 1, tag[0]->id());
	ASSERT_EQ(0xFF + 2, tag[1]->id());
	ASSERT_EQ(0xFF, tag[2]->id());

	t =  ILTagListTagTest::createSample(0xFF + 3, 1);
	ASSERT_TRUE(tag.insert(3, ILTagListTag::SharedPointer(t)));
	ASSERT_EQ(4, tag.count());
	ASSERT_EQ(0xFF + 1, tag[0]->id());
	ASSERT_EQ(0xFF + 2, tag[1]->id());
	ASSERT_EQ(0xFF, tag[2]->id());
	ASSERT_EQ(0xFF + 3, tag[3]->id());
}

//------------------------------------------------------------------------------
TEST_F(ILTagListTagTest, insertPtr) {
	ILTagListTag tag(ILTag::TAG_ILTAG_ARRAY);
	ILTag * t;

	ASSERT_EQ(0, tag.count());

	t =  ILTagListTagTest::createSample(0xFF, 1);
	ASSERT_TRUE(tag.insert(0, t));
	ASSERT_EQ(1, tag.count());
	ASSERT_EQ(0xFF, tag[0]->id());

	t =  ILTagListTagTest::createSample(0xFF + 1, 1);
	ASSERT_TRUE(tag.insert(0, t));
	ASSERT_EQ(2, tag.count());
	ASSERT_EQ(0xFF + 1, tag[0]->id());
	ASSERT_EQ(0xFF, tag[1]->id());

	t =  ILTagListTagTest::createSample(0xFF + 2, 1);
	ASSERT_TRUE(tag.insert(1, t));
	ASSERT_EQ(3, tag.count());
	ASSERT_EQ(0xFF + 1, tag[0]->id());
	ASSERT_EQ(0xFF + 2, tag[1]->id());
	ASSERT_EQ(0xFF, tag[2]->id());

	t =  ILTagListTagTest::createSample(0xFF + 3, 1);
	ASSERT_TRUE(tag.insert(3, t));
	ASSERT_EQ(4, tag.count());
	ASSERT_EQ(0xFF + 1, tag[0]->id());
	ASSERT_EQ(0xFF + 2, tag[1]->id());
	ASSERT_EQ(0xFF, tag[2]->id());
	ASSERT_EQ(0xFF + 3, tag[3]->id());
}

//------------------------------------------------------------------------------
TEST_F(ILTagListTagTest, remove) {
	ILTagListTag tag(ILTag::TAG_ILTAG_ARRAY);
	ILTag * t;

	ASSERT_EQ(0, tag.count());
	ASSERT_TRUE(tag.add(ILTagListTagTest::createSample(0xFF + 0, 1)));
	ASSERT_TRUE(tag.add(ILTagListTagTest::createSample(0xFF + 1, 1)));
	ASSERT_TRUE(tag.add(ILTagListTagTest::createSample(0xFF + 2, 1)));
	ASSERT_TRUE(tag.add(ILTagListTagTest::createSample(0xFF + 3, 1)));
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
TEST_F(ILTagListTagTest, clear) {
	ILTagListTag tag(ILTag::TAG_ILTAG_ARRAY);
	ILTag * t;

	ASSERT_EQ(0, tag.count());
	ASSERT_TRUE(tag.add(ILTagListTagTest::createSample(0xFF + 0, 1)));
	ASSERT_TRUE(tag.add(ILTagListTagTest::createSample(0xFF + 1, 1)));
	ASSERT_TRUE(tag.add(ILTagListTagTest::createSample(0xFF + 2, 1)));
	ASSERT_TRUE(tag.add(ILTagListTagTest::createSample(0xFF + 3, 1)));
	ASSERT_EQ(4, tag.count());
	ASSERT_EQ(0xFF + 0, tag[0]->id());
	ASSERT_EQ(0xFF + 1, tag[1]->id());
	ASSERT_EQ(0xFF + 2, tag[2]->id());
	ASSERT_EQ(0xFF + 3, tag[3]->id());

	tag.clear();
	ASSERT_EQ(0, tag.count());
}

//------------------------------------------------------------------------------
TEST_F(ILTagListTagTest, accessOperatorRO) {
	ILTagListTag tag(ILTag::TAG_ILTAG_ARRAY);
	const ILTagListTag & roTag(tag);
	ILTag * t;

	ASSERT_EQ(0, tag.count());
	ASSERT_TRUE(tag.add(ILTagListTagTest::createSample(0xFF + 0, 1)));
	ASSERT_TRUE(tag.add(ILTagListTagTest::createSample(0xFF + 1, 1)));
	ASSERT_TRUE(tag.add(ILTagListTagTest::createSample(0xFF + 2, 1)));
	ASSERT_TRUE(tag.add(ILTagListTagTest::createSample(0xFF + 3, 1)));
	ASSERT_EQ(4, tag.count());
	ASSERT_EQ(0xFF + 0, roTag[0]->id());
	ASSERT_EQ(0xFF + 1, roTag[1]->id());
	ASSERT_EQ(0xFF + 2, roTag[2]->id());
	ASSERT_EQ(0xFF + 3, roTag[3]->id());
}

//------------------------------------------------------------------------------
TEST_F(ILTagListTagTest, accessOperatorRW) {
	ILTagListTag tag(ILTag::TAG_ILTAG_ARRAY);
	ILTag * t;

	ASSERT_EQ(0, tag.count());
	ASSERT_TRUE(tag.add(ILTagListTagTest::createSample(0xFF + 0, 1)));
	ASSERT_TRUE(tag.add(ILTagListTagTest::createSample(0xFF + 1, 1)));
	ASSERT_TRUE(tag.add(ILTagListTagTest::createSample(0xFF + 2, 1)));
	ASSERT_TRUE(tag.add(ILTagListTagTest::createSample(0xFF + 3, 1)));
	ASSERT_EQ(4, tag.count());
	ASSERT_EQ(0xFF + 0, tag[0]->id());
	ASSERT_EQ(0xFF + 1, tag[1]->id());
	ASSERT_EQ(0xFF + 2, tag[2]->id());
	ASSERT_EQ(0xFF + 3, tag[3]->id());
}

//------------------------------------------------------------------------------
TEST_F(ILTagListTagTest, serialize) {
	ILTagListTag tag(ILTag::TAG_ILTAG_ARRAY);
	ILTag * t;
	IRBuffer out;
	IRBuffer expected;

	// Create the object to be serialized
	for (int i = 0; i < 256; i++) {
		ASSERT_TRUE(tag.add(ILTagListTagTest::createSample(0xFF + i, i)));
	}

	// Serialize by hand
	ASSERT_TRUE(expected.writeILInt(tag.id()));
	ASSERT_TRUE(expected.writeILInt(tag.size()));
	ASSERT_TRUE(expected.writeILInt(tag.count()));
	for (int i = 0; i < tag.count(); i++) {
		ASSERT_TRUE(tag[i]->serialize(expected));
	}

	ASSERT_TRUE(tag.serialize(out));
	ASSERT_EQ(expected.size(), out.size());
	ASSERT_EQ(0, std::memcmp(expected.roBuffer(), out.roBuffer(),
			expected.size()));
}

//------------------------------------------------------------------------------
TEST_F(ILTagListTagTest, deserializeValue) {
	ILTagListTag tag(ILTag::TAG_ILTAG_ARRAY);
	ILTagFactory f;
	ILTag * t;
	IRBuffer serialized;

	// Serialize by hand
	ASSERT_TRUE(serialized.writeILInt(256));
	for (int i = 0; i < 256; i++) {
		t = ILTagListTagTest::createSample(0xFF + i, i);
		ASSERT_TRUE(t->serialize(serialized));
		delete t;
	}
	serialized.beginning();
	ASSERT_TRUE(tag.deserializeValue(f, serialized.roBuffer(), serialized.size()));

	ASSERT_EQ(256, tag.count());
	for (int i = 0; i < tag.count(); i++) {
		ASSERT_EQ(0xFF + i, tag[i]->id());
		ASSERT_EQ(i, tag[i]->size());
	}
}

//------------------------------------------------------------------------------

