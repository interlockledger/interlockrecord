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
#include "ILTagFactoryTest.h"
#include <ircommon/iltag.h>
#include <ircommon/iltagstd.h>
#include <ircommon/ilint.h>
#include <cstring>
using namespace ircommon;
using namespace ircommon::iltags;

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
	ASSERT_FALSE(f->strictMode());
	delete f;

	f = new ILTagFactory(false);
	ASSERT_FALSE(f->secure());
	ASSERT_FALSE(f->strictMode());
	delete f;

	f = new ILTagFactory(true);
	ASSERT_TRUE(f->secure());
	ASSERT_FALSE(f->strictMode());
	delete f;

	f = new ILTagFactory(false, false);
	ASSERT_FALSE(f->secure());
	ASSERT_FALSE(f->strictMode());
	delete f;

	f = new ILTagFactory(true, false);
	ASSERT_TRUE(f->secure());
	ASSERT_FALSE(f->strictMode());
	delete f;

	f = new ILTagFactory(false, true);
	ASSERT_FALSE(f->secure());
	ASSERT_TRUE(f->strictMode());
	delete f;

	f = new ILTagFactory(true, true);
	ASSERT_TRUE(f->secure());
	ASSERT_TRUE(f->strictMode());
	delete f;
}

//------------------------------------------------------------------------------
TEST_F(ILTagFactoryTest, create) {
	ILTagFactory f;

	f.setSecure(false);
	f.setStrictMode(false);
	for (int tagId = 0; tagId < 256; tagId++) {
		ILTag * tag = f.create(tagId);
		ASSERT_TRUE(tag != nullptr);
		ASSERT_EQ(tagId, tag->id());
		ASSERT_EQ(typeid(*tag), typeid(ILRawTag));
		ASSERT_FALSE(static_cast<ILRawTag*>(tag)->secure());
		delete tag;
	}

	f.setSecure(false);
	f.setStrictMode(true);
	for (int tagId = 0; tagId < 256; tagId++) {
		ASSERT_EQ(nullptr, f.create(tagId));
	}

	f.setSecure(true);
	f.setStrictMode(false);
	for (int tagId = 0; tagId < 256; tagId++) {
		ILTag * tag = f.create(tagId);
		ASSERT_TRUE(tag != nullptr);
		ASSERT_EQ(tagId, tag->id());
		ASSERT_EQ(typeid(*tag), typeid(ILRawTag));
		ASSERT_TRUE(static_cast<ILRawTag*>(tag)->secure());
		delete tag;
	}

	f.setSecure(true);
	f.setStrictMode(true);
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
	ILTagFactory f;
	IRBuffer b;
	std::uint8_t buff[256];
	ILTag * t;
	ILRawTag * r;

	for (unsigned int i = 0; i < sizeof(buff); i++) {
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
TEST_F(ILTagFactoryTest, deserializeStrict) {
	ILTagFactory f;
	IRBuffer b;
	std::uint8_t buff[256];
	ILTag * t;

	f.setStrictMode(true);

	for (unsigned int i = 0; i < sizeof(buff); i++) {
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
			ASSERT_TRUE(f.deserialize(b) == nullptr);

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
			ASSERT_TRUE(f.deserialize(b) == nullptr);

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
	ASSERT_TRUE(f.deserialize(b) == nullptr);

	std::uint64_t exp = 0xFF;
	for (int i = 1; i < 9; i++) {
		// TAG_ILINT64
		b.setSize(0);
		b.writeILInt(ILTag::TAG_ILINT64);
		b.writeILInt(exp);
		b.beginning();
		ASSERT_TRUE(f.deserialize(b) == nullptr);

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
TEST_F(ILTagFactoryTest, strictMode) {
	ILTagFactory f;

	ASSERT_FALSE(f.strictMode());

	f.setStrictMode(true);
	ASSERT_TRUE(f.strictMode());

	f.setStrictMode(false);
	ASSERT_FALSE(f.strictMode());
}

//------------------------------------------------------------------------------
TEST_F(ILTagFactoryTest, deserializeIRBufferILTag) {
	ILTagFactory f;
	IRBuffer out;
	ILInt64Tag uint64Tag;
	ILInt32Tag uint32Tag;
	ILStringTag stringTag;
	std::string s;

	// Implicity
	ASSERT_TRUE(out.writeILInt(ILTag::TAG_INT64));
	ASSERT_TRUE(out.writeInt(std::uint64_t(0xFACADA)));

	out.beginning();
	ASSERT_TRUE(f.deserialize(out, uint64Tag));
	ASSERT_EQ(0xFACADA, uint64Tag.value());

	out.beginning();
	ASSERT_FALSE(f.deserialize(out, uint32Tag));
	out.beginning();
	ASSERT_FALSE(f.deserialize(out, stringTag));

	// Full tag
	s = "And so it begins.";
	out.beginning();
	ASSERT_TRUE(out.writeILInt(ILTag::TAG_STRING));
	ASSERT_TRUE(out.writeILInt(s.size()));
	ASSERT_TRUE(out.write(s.c_str(), s.size()));

	out.beginning();
	ASSERT_TRUE(f.deserialize(out, stringTag));
	ASSERT_STREQ(s.c_str(), stringTag.value().c_str());

	out.beginning();
	ASSERT_FALSE(f.deserialize(out, uint32Tag));
	out.beginning();
	ASSERT_FALSE(f.deserialize(out, uint64Tag));
}

//------------------------------------------------------------------------------

