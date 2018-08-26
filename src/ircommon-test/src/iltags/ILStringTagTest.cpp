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
#include "ILStringTagTest.h"
#include <ircommon/iltag.h>
#include <ircommon/iltagstd.h>
#include <cstring>
using namespace ircommon;
using namespace ircommon::iltags;

//==============================================================================
// class ILStringTagTest
//------------------------------------------------------------------------------
const static char * ILStringTagTest_SAMPLE = "The truth points to itself.";

//------------------------------------------------------------------------------
ILStringTagTest::ILStringTagTest() {
}

//------------------------------------------------------------------------------
ILStringTagTest::~ILStringTagTest() {
}

//------------------------------------------------------------------------------
void ILStringTagTest::SetUp() {
}

//------------------------------------------------------------------------------
void ILStringTagTest::TearDown() {
}

//------------------------------------------------------------------------------
TEST_F(ILStringTagTest,Constructor) {
	ILStringTag * t;

	t = new ILStringTag();
	ASSERT_EQ(ILTag::TAG_STRING, t->id());
	ASSERT_EQ(0, t->value().size());
	delete t;
}

//------------------------------------------------------------------------------
TEST_F(ILStringTagTest, size) {
	ILStringTag t;

	for (unsigned int size = 0; size < std::strlen(ILStringTagTest_SAMPLE); size++) {
		t.setValue(ILStringTagTest_SAMPLE, size);
		ASSERT_EQ(size, t.size());
	}
}

//------------------------------------------------------------------------------
TEST_F(ILStringTagTest, getSetValueString) {
	ILStringTag t;
	std::string s;

	s = ILStringTagTest_SAMPLE;
	t.setValue(s);
	ASSERT_STREQ(ILStringTagTest_SAMPLE, t.value().c_str());
}

//------------------------------------------------------------------------------
TEST_F(ILStringTagTest, getSetValueCStr) {
	ILStringTag t;

	t.setValue(ILStringTagTest_SAMPLE);
	ASSERT_STREQ(ILStringTagTest_SAMPLE, t.value().c_str());
}

//------------------------------------------------------------------------------
TEST_F(ILStringTagTest, getSetValueCStrInt) {
	ILStringTag t;
	std::string s;

	for (unsigned int size = 0; size < std::strlen(ILStringTagTest_SAMPLE); size++) {
		t.setValue(ILStringTagTest_SAMPLE, size);
		s.assign(ILStringTagTest_SAMPLE, size);
		ASSERT_STREQ(s.c_str(), t.value().c_str());
	}
}

//------------------------------------------------------------------------------
TEST_F(ILStringTagTest, serialize) {
	ILStringTag t;
	IRBuffer out;
	IRBuffer exp;

	// Empty
	ASSERT_TRUE(t.serialize(out));

	ASSERT_TRUE(exp.writeILInt(ILTag::TAG_STRING));
	ASSERT_TRUE(exp.writeILInt(0));
	ASSERT_EQ(exp.size(), out.size());
	ASSERT_EQ(0, std::memcmp(exp.roBuffer(), out.roBuffer(), exp.size()));

	// Non-empty
	out.setSize(0);
	exp.setSize(0);
	t.setValue(ILStringTagTest_SAMPLE);
	ASSERT_TRUE(t.serialize(out));

	ASSERT_TRUE(exp.writeILInt(ILTag::TAG_STRING));
	ASSERT_TRUE(exp.writeILInt(std::strlen(ILStringTagTest_SAMPLE)));
	ASSERT_TRUE(exp.write(ILStringTagTest_SAMPLE,
			std::strlen(ILStringTagTest_SAMPLE)));

	ASSERT_EQ(exp.size(), out.size());
	ASSERT_EQ(0, std::memcmp(exp.roBuffer(), out.roBuffer(), exp.size()));
}

//------------------------------------------------------------------------------
TEST_F(ILStringTagTest, deserializeValue) {
	ILStringTag t;
	ILTagFactory f;

	// Empty
	ASSERT_TRUE(t.deserializeValue(f, ILStringTagTest_SAMPLE, 0));
	ASSERT_STREQ("", t.value().c_str());

	// Non-empty
	ASSERT_TRUE(t.deserializeValue(f, ILStringTagTest_SAMPLE,
			std::strlen(ILStringTagTest_SAMPLE)));
	ASSERT_STREQ(ILStringTagTest_SAMPLE, t.value().c_str());
}
//------------------------------------------------------------------------------

