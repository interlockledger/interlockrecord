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

