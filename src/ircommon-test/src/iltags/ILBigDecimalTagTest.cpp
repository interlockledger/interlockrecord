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
#include "ILBigDecimalTagTest.h"
#include <ircommon/iltagstd.h>
#include <cstring>
using namespace ircommon;
using namespace ircommon::iltags;

//==============================================================================
// class IRBigDecimalTagTest
//------------------------------------------------------------------------------
ILBigDecimalTagTest::ILBigDecimalTagTest() {
}

//------------------------------------------------------------------------------
ILBigDecimalTagTest::~ILBigDecimalTagTest() {
}

//------------------------------------------------------------------------------
void ILBigDecimalTagTest::SetUp() {
}

//------------------------------------------------------------------------------
void ILBigDecimalTagTest::TearDown() {
}

//------------------------------------------------------------------------------
TEST_F(ILBigDecimalTagTest,Constructor) {
	ILBigDecimalTag * t;

	t = new ILBigDecimalTag();
	ASSERT_EQ(ILTag::TAG_BDEC, t->id());
	ASSERT_EQ(0, t->scale());
	ASSERT_EQ(0, t->integral().size());
	ASSERT_FALSE(t->integral().secure());
	delete t;

	t = new ILBigDecimalTag(false);
	ASSERT_EQ(ILTag::TAG_BDEC, t->id());
	ASSERT_EQ(0, t->scale());
	ASSERT_EQ(0, t->integral().size());
	ASSERT_FALSE(t->integral().secure());
	delete t;

	t = new ILBigDecimalTag(true);
	ASSERT_EQ(ILTag::TAG_BDEC, t->id());
	ASSERT_EQ(0, t->scale());
	ASSERT_EQ(0, t->integral().size());
	ASSERT_TRUE(t->integral().secure());
	delete t;
}

//------------------------------------------------------------------------------
TEST_F(ILBigDecimalTagTest, size) {
	ILBigDecimalTag t;
	std::uint8_t buff[32];

	for (unsigned int i = 0; i < sizeof(buff); i++) {
		buff[i] = i;
	}

	for (unsigned int i = 0; i < sizeof(buff); i++) {
		ASSERT_TRUE(t.setIntegral(buff, i));
		ASSERT_EQ(sizeof(std::int32_t) + i, t.size());
	}
}

//------------------------------------------------------------------------------
TEST_F(ILBigDecimalTagTest, serialize) {
	ILBigDecimalTag t;
	std::uint8_t buff[32];
	IRBuffer out;
	IRBuffer exp;

	for (unsigned int i = 0; i < sizeof(buff); i++) {
		buff[i] = i;
	}

	for (unsigned int i = 0; i < sizeof(buff); i++) {
		out.setSize(0);
		exp.setSize(0);

		ASSERT_TRUE(t.setIntegral(buff, i));
		t.setScale(i);
		ASSERT_TRUE(t.serialize(out));

		ASSERT_TRUE(exp.writeILInt(ILTag::TAG_BDEC));
		ASSERT_TRUE(exp.writeILInt(t.size()));
		ASSERT_TRUE(exp.writeInt(t.scale()));
		ASSERT_TRUE(exp.write(t.integral().roBuffer(), t.integral().size()));

		ASSERT_EQ(exp.size(), out.size());
		ASSERT_EQ(0, std::memcmp(exp.roBuffer(), out.roBuffer(), exp.size()));
	}
}

//------------------------------------------------------------------------------
TEST_F(ILBigDecimalTagTest, deserializeValue) {
	ILBigDecimalTag t;
	std::uint8_t buff[32];
	IRBuffer exp;
	ILTagFactory f;

	for (unsigned int i = 0; i < sizeof(buff); i++) {
		buff[i] = i;
	}

	for (unsigned int i = 0; i < sizeof(buff); i++) {
		exp.setSize(0);
		ASSERT_TRUE(exp.writeInt((std::int32_t)i));
		ASSERT_TRUE(exp.write(t.integral().roBuffer(), t.integral().size()));

		ASSERT_TRUE(t.deserializeValue(f, exp.roBuffer(), exp.size()));
		ASSERT_EQ(i, t.scale());
		ASSERT_EQ(0, std::memcmp(buff, t.integral().roBuffer(),
				t.integral().size()));
	}
}
//------------------------------------------------------------------------------

