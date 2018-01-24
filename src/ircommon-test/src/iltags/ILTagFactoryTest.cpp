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
#include "ILTagFactoryTest.h"
#include <ircommon/iltag.h>
#include <ircommon/ilint.h>
#include <cstring>
using namespace ircommon;
using namespace ircommon::iltags;

//==============================================================================
// class ILTagFactoryTest
//------------------------------------------------------------------------------
class ILDummyTagFactory: public ILTagFactory{
public:
	ILDummyTagFactory(): ILTagFactory(false) {}

	virtual ~ILDummyTagFactory() = default;

	virtual ILTag * create(std::uint64_t tagId) const;
};

//------------------------------------------------------------------------------
ILTag * ILDummyTagFactory::create(std::uint64_t tagId) const {
	return new ILRawTag(tagId);
}

//==============================================================================
// class ILTagFactoryTest
//------------------------------------------------------------------------------
ILTagFactoryTest::ILTagFactoryTest() {
}

//------------------------------------------------------------------------------
ILTagFactoryTest::~ILTagFactoryTest() {
}

//------------------------------------------------------------------------------
void ILTagFactoryTest::SetUp() {
}

//------------------------------------------------------------------------------
void ILTagFactoryTest::TearDown() {
}

//------------------------------------------------------------------------------
TEST_F(ILTagFactoryTest,Constructor) {
	ILTagFactory * f;

	f = new ILTagFactory();
	ASSERT_FALSE(f->secure());
	delete f;

	f = new ILTagFactory(false);
	ASSERT_FALSE(f->secure());
	delete f;

	f = new ILTagFactory(true);
	ASSERT_TRUE(f->secure());
	delete f;
}

//------------------------------------------------------------------------------
TEST_F(ILTagFactoryTest, create) {
	ILTagFactory f;

	for (int tagId = 0; tagId < 256; tagId++) {
		ASSERT_EQ(nullptr, f.create(tagId));
	}
}

//------------------------------------------------------------------------------
TEST_F(ILTagFactoryTest, secure) {
	ILTagFactory f(false);
	ILTagFactory sf(true);

	ASSERT_FALSE(f.secure());
	ASSERT_TRUE(sf.secure());
}

//------------------------------------------------------------------------------
TEST_F(ILTagFactoryTest, deserialize) {
	ILDummyTagFactory f;
	IRBuffer b;
	std::uint8_t buff[256];
	ILTag * t;
	ILRawTag * r;

	for (int i = 0; i < sizeof(buff); i++) {
		buff[i] = i;
	}

	// Empty
	b.setSize(0);
	t = f.deserialize(b);
	ASSERT_TRUE(t == nullptr);

	// Implicity tags
	for (int tagId = 0; tagId < 16; tagId++) {
		if (tagId != ILTag::TAG_ILINT64) {
			b.setSize(0);
			b.writeILInt(tagId);
			b.write(buff, ILTag::getImplicitValueSize(tagId));

			b.beginning();
			t = f.deserialize(b);
			ASSERT_EQ(b.size(), b.position());

			ASSERT_TRUE(t != nullptr);
			ASSERT_EQ(tagId, t->id());
			ASSERT_EQ(ILTag::getImplicitValueSize(tagId), t->size());
			r = static_cast<ILRawTag *>(t);
			ASSERT_EQ(0, std::memcmp(buff, r->value().roBuffer(), t->size()));
			delete t;

			// Incomplete
			b.setSize(b.size() - 1);
			b.beginning();
			t = f.deserialize(b);
			ASSERT_TRUE(t == nullptr);
		}
	}

	// Explicit tags
	for (int tagId = 16; tagId < 256; tagId++) {
		if (tagId != ILTag::TAG_ILINT64) {
			b.setSize(0);
			b.writeILInt(tagId);
			b.writeILInt(tagId);
			b.write(buff, tagId);

			b.beginning();
			t = f.deserialize(b);
			ASSERT_EQ(b.size(), b.position());

			ASSERT_TRUE(t != nullptr);
			ASSERT_EQ(tagId, t->id());
			ASSERT_EQ(tagId, t->size());
			r = static_cast<ILRawTag *>(t);
			ASSERT_EQ(0, std::memcmp(buff, r->value().roBuffer(), t->size()));
			delete t;

			// Incomplete
			b.setSize(b.size() - 1);
			b.beginning();
			t = f.deserialize(b);
			ASSERT_TRUE(t == nullptr);
		}
	}

	// TAG_ILINT64
	b.setSize(0);
	b.writeILInt(ILTag::TAG_ILINT64);
	b.writeILInt(0);
	b.beginning();
	t = f.deserialize(b);
	ASSERT_EQ(b.size(), b.position());
	ASSERT_TRUE(t != nullptr);

	ASSERT_EQ(ILTag::TAG_ILINT64, t->id());
	ASSERT_EQ(1, t->size());
	r = static_cast<ILRawTag *>(t);
	ASSERT_EQ(0, std::memcmp(buff, r->value().roBuffer(), t->size()));
	delete t;

	std::uint64_t exp = 0xFF;
	for (int i = 1; i < 9; i++) {
		// TAG_ILINT64
		b.setSize(0);
		b.writeILInt(ILTag::TAG_ILINT64);
		b.writeILInt(exp);
		b.beginning();
		t = f.deserialize(b);
		ASSERT_EQ(b.size(), b.position());
		ASSERT_TRUE(t != nullptr);

		ASSERT_EQ(ILTag::TAG_ILINT64, t->id());
		ASSERT_EQ(ILInt::size(exp), t->size());
		r = static_cast<ILRawTag *>(t);
		std::uint64_t v;
		ASSERT_TRUE(ILInt::decode(r->value().roBuffer(), t->size(), &v));
		ASSERT_EQ(exp, v);
		delete t;

		// Fail
		// Incomplete
		b.setSize(b.size() - 1);
		b.beginning();
		t = f.deserialize(b);
		ASSERT_TRUE(t == nullptr);

		exp = (exp << 8) | 0xFF;
	}

}

//------------------------------------------------------------------------------
TEST_F(ILTagFactoryTest, extractTagHeader) {
	IRBuffer b;
	std::uint64_t rTagId;
	std::uint64_t rTagSize;

	// No data
	b.setSize(0);
	ASSERT_FALSE(ILTagFactory::extractTagHeader(b, rTagId, rTagSize));

	// Basic
	for (int tagId = 0; tagId < 16; tagId++) {
		if (tagId != ILTag::TAG_ILINT64) {
			b.setSize(0);
			b.writeILInt(tagId);
			b.beginning();
			ASSERT_TRUE(ILTagFactory::extractTagHeader(b, rTagId, rTagSize));
			ASSERT_EQ(b.size(), b.position());
			ASSERT_EQ(tagId, rTagId);
			ASSERT_EQ(ILTag::getImplicitValueSize(tagId), rTagSize);
			// No bytes left
			ASSERT_FALSE(ILTagFactory::extractTagHeader(b, rTagId, rTagSize));
		}
	}

	// TAG_ILINT64
	for (std::uint64_t size = 0xF7; size <= 0xFF; size++) {
		b.setSize(0);
		b.writeILInt(ILTag::TAG_ILINT64);
		b.write(size);
		b.beginning();
		ASSERT_TRUE(ILTagFactory::extractTagHeader(b, rTagId, rTagSize));
		ASSERT_EQ(1, b.position());
		ASSERT_EQ(ILTag::TAG_ILINT64, rTagId);
		ASSERT_EQ((size - 0xF8 + 2), rTagSize);
		// No bytes left
		b.setSize(1);
		b.beginning();
		ASSERT_FALSE(ILTagFactory::extractTagHeader(b, rTagId, rTagSize));
	}

	// Generic
	for (int tagId = 16; tagId < 256; tagId++) {
		if (tagId != ILTag::TAG_ILINT64) {
			b.setSize(0);
			b.writeILInt(tagId);
			b.writeILInt(tagId + 1);
			b.beginning();
			ASSERT_TRUE(ILTagFactory::extractTagHeader(b, rTagId, rTagSize));
			ASSERT_EQ(tagId, rTagId);
			ASSERT_EQ(tagId + 1, rTagSize);

			// Incomplete size
			b.setSize(b.size() - 1);
			b.beginning();
			ASSERT_FALSE(ILTagFactory::extractTagHeader(b, rTagId, rTagSize));

			// No size
			b.setSize(0);
			b.writeILInt(tagId);
			b.beginning();
			ASSERT_FALSE(ILTagFactory::extractTagHeader(b, rTagId, rTagSize));

			// Incomplete ID
			b.setSize(b.size() - 1);
			b.beginning();
			ASSERT_FALSE(ILTagFactory::extractTagHeader(b, rTagId, rTagSize));
		}
	}
}

//------------------------------------------------------------------------------

