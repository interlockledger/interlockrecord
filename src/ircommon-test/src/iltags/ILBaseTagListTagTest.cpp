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
#include "ILBaseTagListTagTest.h"
#include <ircommon/iltag.h>
#include <ircommon/ilint.h>
#include <cstring>
using namespace ircommon;
using namespace ircommon::iltags;

//==============================================================================
// class ILTagListTagTest
//------------------------------------------------------------------------------
ILBaseTagListTagTest::ILBaseTagListTagTest() {
}

//------------------------------------------------------------------------------
ILBaseTagListTagTest::~ILBaseTagListTagTest() {
}

//------------------------------------------------------------------------------
void ILBaseTagListTagTest::SetUp() {
}

//------------------------------------------------------------------------------
void ILBaseTagListTagTest::TearDown() {
}

//------------------------------------------------------------------------------
ILTag * ILBaseTagListTagTest::createSample(std::uint64_t id, int size) {
	ILRawTag * tag;

	tag = new ILRawTag(id);
	for (int i = 0; i < size; i++) {
		tag->value().write(size);
	}
	return tag;
}


//------------------------------------------------------------------------------
TEST_F(ILBaseTagListTagTest,Constructor) {
	ILBaseTagListTag * tag;

	tag = new ILBaseTagListTag(ILTag::TAG_ILTAG_ARRAY);
	ASSERT_EQ(ILTag::TAG_ILTAG_ARRAY, tag->id());
	ASSERT_EQ(0, tag->size());
	ASSERT_EQ(0, tag->count());
	ASSERT_EQ(0xFFFFFFFFFFFFFFFFll, tag->maxEntries());
	delete tag;

	tag = new ILBaseTagListTag(ILTag::TAG_ILTAG_ARRAY, 10);
	ASSERT_EQ(ILTag::TAG_ILTAG_ARRAY, tag->id());
	ASSERT_EQ(0, tag->size());
	ASSERT_EQ(0, tag->count());
	ASSERT_EQ(10, tag->maxEntries());
	delete tag;
}

//------------------------------------------------------------------------------
TEST_F(ILBaseTagListTagTest, size) {
	ILBaseTagListTag tag(ILTag::TAG_ILTAG_ARRAY);
	ILTag * t;
	std::uint64_t payloadSize;

	ASSERT_EQ(0, tag.size());
	payloadSize = 0;
	for (int i = 0; i < 256; i++) {
		t =  ILBaseTagListTagTest::createSample(0xFF, 10);
		payloadSize += t->tagSize();
		tag.add(t);
		ASSERT_EQ(payloadSize, tag.size());
	}
}

//------------------------------------------------------------------------------
TEST_F(ILBaseTagListTagTest, count) {
	ILBaseTagListTag tag(ILTag::TAG_ILTAG_ARRAY);
	ILTag * t;

	ASSERT_EQ(0, tag.count());
	for (int i = 0; i < 256; i++) {
		t =  ILBaseTagListTagTest::createSample(0xFF, i);
		tag.add(t);
		ASSERT_EQ(i + 1, tag.count());
	}
}

//------------------------------------------------------------------------------
TEST_F(ILBaseTagListTagTest, add) {
	ILBaseTagListTag tag(ILTag::TAG_ILTAG_ARRAY);
	ILTag * t;

	ASSERT_EQ(0, tag.count());
	for (int i = 0; i < 16; i++) {
		t =  ILBaseTagListTagTest::createSample(0xFF + i, 1);
		ASSERT_TRUE(tag.add(ILBaseTagListTag::SharedPointer(t)));
		ASSERT_EQ(i + 1, tag.count());
		for (int j = 0; j <= i; j++) {
			ASSERT_EQ(0xFF + j, tag[j]->id());
		}
	}
}

//------------------------------------------------------------------------------
TEST_F(ILBaseTagListTagTest, addLimited) {
	ILBaseTagListTag tag(ILTag::TAG_ILTAG_ARRAY, 10);
	ILTag * t;

	ASSERT_EQ(0, tag.count());
	for (int i = 0; i < 10; i++) {
		t =  ILBaseTagListTagTest::createSample(0xFF + i, 1);
		ASSERT_TRUE(tag.add(ILBaseTagListTag::SharedPointer(t)));
		ASSERT_EQ(i + 1, tag.count());
		for (int j = 0; j <= i; j++) {
			ASSERT_EQ(0xFF + j, tag[j]->id());
		}
	}

	for (int i = 0; i < 10; i++) {
		t =  ILBaseTagListTagTest::createSample(0xFF + i, 1);
		ASSERT_FALSE(tag.add(ILBaseTagListTag::SharedPointer(t)));
		ASSERT_EQ(10, tag.count());
	}
}

//------------------------------------------------------------------------------
TEST_F(ILBaseTagListTagTest, addPtr) {
	ILBaseTagListTag tag(ILTag::TAG_ILTAG_ARRAY);
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
TEST_F(ILBaseTagListTagTest, addPtrLimited) {
	ILBaseTagListTag tag(ILTag::TAG_ILTAG_ARRAY, 10);
	ILTag * t;

	ASSERT_EQ(0, tag.count());
	for (int i = 0; i < 10; i++) {
		t =  ILBaseTagListTagTest::createSample(0xFF + i, 1);
		ASSERT_TRUE(tag.add(t));
		ASSERT_EQ(i + 1, tag.count());
		for (int j = 0; j <= i; j++) {
			ASSERT_EQ(0xFF + j, tag[j]->id());
		}
	}
	for (int i = 0; i < 10; i++) {
		t =  ILBaseTagListTagTest::createSample(0xFF + i, 1);
		ASSERT_FALSE(tag.add(t));
		ASSERT_EQ(10, tag.count());
		delete t;
	}
}

//------------------------------------------------------------------------------
TEST_F(ILBaseTagListTagTest, insert) {
	ILBaseTagListTag tag(ILTag::TAG_ILTAG_ARRAY);
	ILTag * t;

	ASSERT_EQ(0, tag.count());

	t =  ILBaseTagListTagTest::createSample(0xFF, 1);
	ASSERT_TRUE(tag.insert(0, ILBaseTagListTag::SharedPointer(t)));
	ASSERT_EQ(1, tag.count());
	ASSERT_EQ(0xFF, tag[0]->id());

	t =  ILBaseTagListTagTest::createSample(0xFF + 1, 1);
	ASSERT_TRUE(tag.insert(0, ILBaseTagListTag::SharedPointer(t)));
	ASSERT_EQ(2, tag.count());
	ASSERT_EQ(0xFF + 1, tag[0]->id());
	ASSERT_EQ(0xFF, tag[1]->id());

	t =  ILBaseTagListTagTest::createSample(0xFF + 2, 1);
	ASSERT_TRUE(tag.insert(1, ILBaseTagListTag::SharedPointer(t)));
	ASSERT_EQ(3, tag.count());
	ASSERT_EQ(0xFF + 1, tag[0]->id());
	ASSERT_EQ(0xFF + 2, tag[1]->id());
	ASSERT_EQ(0xFF, tag[2]->id());

	t =  ILBaseTagListTagTest::createSample(0xFF + 3, 1);
	ASSERT_TRUE(tag.insert(3, ILBaseTagListTag::SharedPointer(t)));
	ASSERT_EQ(4, tag.count());
	ASSERT_EQ(0xFF + 1, tag[0]->id());
	ASSERT_EQ(0xFF + 2, tag[1]->id());
	ASSERT_EQ(0xFF, tag[2]->id());
	ASSERT_EQ(0xFF + 3, tag[3]->id());
}

//------------------------------------------------------------------------------
TEST_F(ILBaseTagListTagTest, insertLimited) {
	ILBaseTagListTag tag(ILTag::TAG_ILTAG_ARRAY, 4);
	ILTag * t;

	ASSERT_EQ(0, tag.count());

	// Insert beyond the bounds
	t =  ILBaseTagListTagTest::createSample(0xFF, 1);
	ASSERT_FALSE(tag.insert(5, ILBaseTagListTag::SharedPointer(t)));
	ASSERT_EQ(0, tag.count());

	// Normal insertions
	t =  ILBaseTagListTagTest::createSample(0xFF, 1);
	ASSERT_TRUE(tag.insert(0, ILBaseTagListTag::SharedPointer(t)));
	ASSERT_EQ(1, tag.count());
	ASSERT_EQ(0xFF, tag[0]->id());

	t =  ILBaseTagListTagTest::createSample(0xFF + 1, 1);
	ASSERT_TRUE(tag.insert(0, ILBaseTagListTag::SharedPointer(t)));
	ASSERT_EQ(2, tag.count());
	ASSERT_EQ(0xFF + 1, tag[0]->id());
	ASSERT_EQ(0xFF, tag[1]->id());

	t =  ILBaseTagListTagTest::createSample(0xFF + 2, 1);
	ASSERT_TRUE(tag.insert(1, ILBaseTagListTag::SharedPointer(t)));
	ASSERT_EQ(3, tag.count());
	ASSERT_EQ(0xFF + 1, tag[0]->id());
	ASSERT_EQ(0xFF + 2, tag[1]->id());
	ASSERT_EQ(0xFF, tag[2]->id());

	t =  ILBaseTagListTagTest::createSample(0xFF + 3, 1);
	ASSERT_TRUE(tag.insert(3, ILBaseTagListTag::SharedPointer(t)));
	ASSERT_EQ(4, tag.count());
	ASSERT_EQ(0xFF + 1, tag[0]->id());
	ASSERT_EQ(0xFF + 2, tag[1]->id());
	ASSERT_EQ(0xFF, tag[2]->id());
	ASSERT_EQ(0xFF + 3, tag[3]->id());

	// At the beginning
	t =  ILBaseTagListTagTest::createSample(0xFF, 1);
	ASSERT_FALSE(tag.insert(0, ILBaseTagListTag::SharedPointer(t)));
	ASSERT_EQ(4, tag.count());
}


//------------------------------------------------------------------------------
TEST_F(ILBaseTagListTagTest, insertPtr) {
	ILBaseTagListTag tag(ILTag::TAG_ILTAG_ARRAY);
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
TEST_F(ILBaseTagListTagTest, insertPtrLimited) {
	ILBaseTagListTag tag(ILTag::TAG_ILTAG_ARRAY, 4);
	ILTag * t;

	ASSERT_EQ(0, tag.count());

	// Insert beyond the bounds
	t =  ILBaseTagListTagTest::createSample(0xFF, 1);
	ASSERT_FALSE(tag.insert(5, t));
	ASSERT_EQ(0, tag.count());
	delete t;

	// Normal insertions
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

	// Insert beyond the bounds
	t =  ILBaseTagListTagTest::createSample(0xFF, 1);
	ASSERT_FALSE(tag.insert(0, t));
	ASSERT_EQ(4, tag.count());
	delete t;
}

//------------------------------------------------------------------------------
TEST_F(ILBaseTagListTagTest, remove) {
	ILBaseTagListTag tag(ILTag::TAG_ILTAG_ARRAY);
	ILTag * t;

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
TEST_F(ILBaseTagListTagTest, clear) {
	ILBaseTagListTag tag(ILTag::TAG_ILTAG_ARRAY);
	ILTag * t;

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
TEST_F(ILBaseTagListTagTest, accessOperatorRO) {
	ILBaseTagListTag tag(ILTag::TAG_ILTAG_ARRAY);
	const ILBaseTagListTag & roTag(tag);
	ILTag * t;

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
TEST_F(ILBaseTagListTagTest, accessOperatorRW) {
	ILBaseTagListTag tag(ILTag::TAG_ILTAG_ARRAY);
	ILTag * t;

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
TEST_F(ILBaseTagListTagTest, serialize) {
	ILBaseTagListTag tag(ILTag::TAG_ILTAG_ARRAY);
	ILTag * t;
	IRBuffer out;
	IRBuffer expected;

	// Create the object to be serialized
	for (int i = 0; i < 256; i++) {
		ASSERT_TRUE(tag.add(ILBaseTagListTagTest::createSample(0xFF + i, i)));
	}

	// Serialize by hand
	ASSERT_TRUE(expected.writeILInt(tag.id()));
	ASSERT_TRUE(expected.writeILInt(tag.size()));
	for (int i = 0; i < tag.count(); i++) {
		ASSERT_TRUE(tag[i]->serialize(expected));
	}

	ASSERT_TRUE(tag.serialize(out));
	ASSERT_EQ(expected.size(), out.size());
	ASSERT_EQ(0, std::memcmp(expected.roBuffer(), out.roBuffer(),
			expected.size()));
}

//------------------------------------------------------------------------------
TEST_F(ILBaseTagListTagTest, deserializeValue) {
	ILBaseTagListTag tag(ILTag::TAG_ILTAG_ARRAY);
	ILTagFactory f;
	ILTag * t;
	IRBuffer serialized;

	// Serialize by hand
	for (int i = 0; i < 256; i++) {
		t = ILBaseTagListTagTest::createSample(0xFF + i, i);
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
TEST_F(ILBaseTagListTagTest, get) {
	ILBaseTagListTag tag(ILTag::TAG_ILTAG_ARRAY);
	const ILBaseTagListTag & ctag = tag;

	for (int i = 0; i < 10; i++) {
		ASSERT_TRUE(tag.add(ILBaseTagListTagTest::createSample(0xFF + i, i)));
	}

	for (int i = 0; i < 10; i++) {
		ASSERT_EQ(0xFF + i, tag.get(i)->id());
	}
	try {
		tag.get(10);
		FAIL();
	}catch(std::out_of_range & e){}

	for (int i = 0; i < 10; i++) {
		ASSERT_EQ(0xFF + i, ctag.get(i)->id());
	}
	try {
		ctag.get(10);
		FAIL();
	}catch(std::out_of_range & e){}
}

//------------------------------------------------------------------------------
TEST_F(ILBaseTagListTagTest, maxEntries) {

	for (int i = 1; i < 10; i++) {
		ILBaseTagListTag tag(ILTag::TAG_ILTAG_ARRAY, i);
		ASSERT_EQ(i, tag.maxEntries());
	}
}

//------------------------------------------------------------------------------
TEST_F(ILBaseTagListTagTest, isFull) {
	ILBaseTagListTag tag(ILTag::TAG_ILTAG_ARRAY, 10);

	for (int i = 0; i < 10; i++) {
		ASSERT_FALSE(tag.isFull());
		ASSERT_TRUE(tag.add(ILBaseTagListTagTest::createSample(0xFF + i, i)));
	}
	ASSERT_TRUE(tag.isFull());
}
//------------------------------------------------------------------------------

