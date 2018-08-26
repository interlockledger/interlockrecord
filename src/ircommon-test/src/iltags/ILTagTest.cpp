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
#include "ILTagTest.h"
#include <cstring>
#include <ircommon/ilint.h>
#include <ircommon/iltag.h>
using namespace ircommon;
using namespace ircommon::iltags;

//==============================================================================
// class ILDummyTag
//------------------------------------------------------------------------------
class ILDummyTag: public ILTag{
protected:
	std::uint8_t _value;
	virtual bool serializeValue(ircommon::IRBuffer & out) const;
public:
	ILDummyTag(std::uint64_t id):ILTag(id),_value(0) {}
	virtual ~ILDummyTag() = default;
	virtual std::uint64_t size() const;
	virtual bool deserializeValue(const ILTagFactory & factory,
			const void * buff, std::uint64_t size);

	std::uint8_t get() const {
		return this->_value;
	}

	void set(std::uint8_t v) {
		this->_value = v;
	}
};

//------------------------------------------------------------------------------
bool ILDummyTag::serializeValue(ircommon::IRBuffer & out) const {
	return out.write(this->get());
}

//------------------------------------------------------------------------------
std::uint64_t ILDummyTag::size() const {
	return 1;
}

//------------------------------------------------------------------------------
bool ILDummyTag::deserializeValue(const ILTagFactory & factory,
		const void * buff, std::uint64_t size) {

	if (size != 1) {
		return false;
	}
	this->_value = *((const char *)buff);
	return true;
}

//==============================================================================
// class ILTagTest
//------------------------------------------------------------------------------
ILTagTest::ILTagTest() {
}

//------------------------------------------------------------------------------
ILTagTest::~ILTagTest() {
}

//------------------------------------------------------------------------------
void ILTagTest::SetUp() {
}

//------------------------------------------------------------------------------
void ILTagTest::TearDown() {
}

//------------------------------------------------------------------------------
TEST_F(ILTagTest, Constructor) {
	ILDummyTag * t;

	t = new ILDummyTag(0);
	ASSERT_EQ(0, t->id());
	delete t;

	t = new ILDummyTag(100);
	ASSERT_EQ(100, t->id());
	delete t;
}

//------------------------------------------------------------------------------
TEST_F(ILTagTest, id) {
	ILDummyTag * t;

	for (int i = 0; i < 100; i++) {
		t = new ILDummyTag(i);
		ASSERT_EQ(i, t->id());
		delete t;
	}
}

//------------------------------------------------------------------------------
TEST_F(ILTagTest, size) {
	ILDummyTag t(1);

	ASSERT_EQ(1, t.size());
}

//------------------------------------------------------------------------------
TEST_F(ILTagTest, tagSize) {

	ILDummyTag t1(1);
	ASSERT_EQ(2, t1.tagSize());

	ILDummyTag t2(0xFFFFFFFF);
	ASSERT_EQ(ILInt::size(0xFFFFFFFF) + 1 + 1, t2.tagSize());
}

//------------------------------------------------------------------------------
TEST_F(ILTagTest, serializeImplicit) {
	IRBuffer out;
	IRBuffer exp;

	ILDummyTag t1(1);
	t1.set(0);
	out.setSize(0);
	ASSERT_TRUE(t1.serialize(out));
	ASSERT_TRUE(exp.writeILInt(1));
	ASSERT_TRUE(exp.write(0));
	ASSERT_EQ(exp.size(), out.size());
	ASSERT_EQ(0, std::memcmp(exp.roBuffer(), out.roBuffer(), exp.size()));
}

//------------------------------------------------------------------------------
TEST_F(ILTagTest, serializeExplicit) {
	IRBuffer out;
	IRBuffer exp;

	ILDummyTag t1(0xFF);
	t1.set(0);
	out.setSize(0);
	ASSERT_TRUE(t1.serialize(out));
	ASSERT_TRUE(exp.writeILInt(0xFF));
	ASSERT_TRUE(exp.writeILInt(1));
	ASSERT_TRUE(exp.write(0));
	ASSERT_EQ(exp.size(), out.size());
	ASSERT_EQ(0, std::memcmp(exp.roBuffer(), out.roBuffer(), exp.size()));
}

//------------------------------------------------------------------------------
TEST_F(ILTagTest, deserializeValue) {
	std::uint8_t buff[8];
	ILTagFactory factory;

	std::memset(buff, 0xFF, sizeof(buff));
	ILDummyTag t1(0xFF);
	ASSERT_TRUE(t1.deserializeValue(factory, buff, 1));
	ASSERT_EQ(0xFF, t1.get());

	ASSERT_FALSE(t1.deserializeValue(factory, buff, 0));
	ASSERT_FALSE(t1.deserializeValue(factory, buff, 2));
}

//------------------------------------------------------------------------------
TEST_F(ILTagTest, isImplicit) {

	for (int i = 0; i < 16; i++) {
		ILDummyTag t(i);
		ASSERT_TRUE(t.isImplicit());
	}
	for (int i = 16; i < 32; i++) {
		ILDummyTag t(i);
		ASSERT_FALSE(t.isImplicit());
	}
	for (int i = 32; i < 100; i++) {
		ILDummyTag t(i);
		ASSERT_FALSE(t.isImplicit());
	}
}

//------------------------------------------------------------------------------
TEST_F(ILTagTest, isImplicitInt) {

	for (int i = 0; i < 16; i++) {
		ASSERT_TRUE(ILTag::isImplicit(i));
	}
	for (int i = 16; i < 32; i++) {
		ASSERT_FALSE(ILTag::isImplicit(i));
	}
	for (int i = 32; i < 100; i++) {
		ASSERT_FALSE(ILTag::isImplicit(i));
	}
}

//------------------------------------------------------------------------------
TEST_F(ILTagTest, isStandard) {

	for (int i = 0; i < 32; i++) {
		ILDummyTag t(i);
		ASSERT_TRUE(t.isStandard());
	}
	for (int i = 32; i < 100; i++) {
		ILDummyTag t(i);
		ASSERT_FALSE(t.isStandard());
	}
}

//------------------------------------------------------------------------------
TEST_F(ILTagTest, isStandardInt) {

	for (int i = 0; i < 32; i++) {
		ASSERT_TRUE(ILTag::isStandard(i));
	}
	for (int i = 32; i < 100; i++) {
		ASSERT_FALSE(ILTag::isStandard(i));
	}
}

//------------------------------------------------------------------------------
TEST_F(ILTagTest, getImplicitValueSize) {

	ASSERT_EQ(0, ILTag::getImplicitValueSize(ILTag::TAG_NULL));
	ASSERT_EQ(1, ILTag::getImplicitValueSize(ILTag::TAG_BOOL));
	ASSERT_EQ(1, ILTag::getImplicitValueSize(ILTag::TAG_INT8));
	ASSERT_EQ(1, ILTag::getImplicitValueSize(ILTag::TAG_UINT8));
	ASSERT_EQ(2, ILTag::getImplicitValueSize(ILTag::TAG_INT16));
	ASSERT_EQ(2, ILTag::getImplicitValueSize(ILTag::TAG_UINT16));
	ASSERT_EQ(4, ILTag::getImplicitValueSize(ILTag::TAG_INT32));
	ASSERT_EQ(4, ILTag::getImplicitValueSize(ILTag::TAG_UINT32));
	ASSERT_EQ(8, ILTag::getImplicitValueSize(ILTag::TAG_INT64));
	ASSERT_EQ(8, ILTag::getImplicitValueSize(ILTag::TAG_UINT64));
	ASSERT_EQ(0, ILTag::getImplicitValueSize(ILTag::TAG_ILINT64));
	ASSERT_EQ(4, ILTag::getImplicitValueSize(ILTag::TAG_BINARY32));
	ASSERT_EQ(8, ILTag::getImplicitValueSize(ILTag::TAG_BINARY64));
	ASSERT_EQ(16, ILTag::getImplicitValueSize(ILTag::TAG_BINARY128));
}

//------------------------------------------------------------------------------
TEST_F(ILTagTest, CONSTANTS) {

	ASSERT_EQ(0, ILTag::TAG_NULL);
	ASSERT_EQ(1, ILTag::TAG_BOOL);
	ASSERT_EQ(2, ILTag::TAG_INT8);
	ASSERT_EQ(3, ILTag::TAG_UINT8);
	ASSERT_EQ(4, ILTag::TAG_INT16);
	ASSERT_EQ(5, ILTag::TAG_UINT16);
	ASSERT_EQ(6, ILTag::TAG_INT32);
	ASSERT_EQ(7, ILTag::TAG_UINT32);
	ASSERT_EQ(8, ILTag::TAG_INT64);
	ASSERT_EQ(9, ILTag::TAG_UINT64);
	ASSERT_EQ(10, ILTag::TAG_ILINT64);
	ASSERT_EQ(11, ILTag::TAG_BINARY32);
	ASSERT_EQ(12, ILTag::TAG_BINARY64);
	ASSERT_EQ(13, ILTag::TAG_BINARY128);

	ASSERT_EQ(16, ILTag::TAG_BYTE_ARRAY);
	ASSERT_EQ(17, ILTag::TAG_STRING);
	ASSERT_EQ(18, ILTag::TAG_BINT);
	ASSERT_EQ(19, ILTag::TAG_BDEC);
	ASSERT_EQ(20, ILTag::TAG_ILINT64_ARRAY);
	ASSERT_EQ(21, ILTag::TAG_ILTAG_ARRAY);
	ASSERT_EQ(22, ILTag::TAG_ILTAG_SEQ);
	ASSERT_EQ(23, ILTag::TAG_RANGE);
	ASSERT_EQ(24, ILTag::TAG_VERSION);
}

//------------------------------------------------------------------------------

