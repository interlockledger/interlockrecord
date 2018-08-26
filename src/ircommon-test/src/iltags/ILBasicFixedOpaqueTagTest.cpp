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
#include "ILBasicFixedOpaqueTagTest.h"
#include <ircommon/iltagstd.h>
#include <cstring>
using namespace ircommon;
using namespace ircommon::iltags;

//==============================================================================
// class ILBasicFixedOpaqueTagTest
//------------------------------------------------------------------------------
ILBasicFixedOpaqueTagTest::ILBasicFixedOpaqueTagTest() {
}

//------------------------------------------------------------------------------
ILBasicFixedOpaqueTagTest::~ILBasicFixedOpaqueTagTest() {
}

//------------------------------------------------------------------------------
void ILBasicFixedOpaqueTagTest::SetUp() {
}

//------------------------------------------------------------------------------
void ILBasicFixedOpaqueTagTest::TearDown() {
}

//------------------------------------------------------------------------------
TEST_F(ILBasicFixedOpaqueTagTest,Constructor) {

	auto t8 = new ILBasicFixedOpaqueTag<0xFF, 8>();
	ASSERT_EQ(0xFF, t8->id());
	ASSERT_EQ(8, t8->size());
	delete t8;

	auto t16 = new ILBasicFixedOpaqueTag<0xFE, 16>();
	ASSERT_EQ(0xFE, t16->id());
	ASSERT_EQ(16, t16->size());
	delete t16;
}

//------------------------------------------------------------------------------
TEST_F(ILBasicFixedOpaqueTagTest, size) {

	ILBasicFixedOpaqueTag<0xFF, 8> t8;
	ASSERT_EQ(8, t8.size());

	ILBasicFixedOpaqueTag<0xFF, 16> t16;
	ASSERT_EQ(16, t16.size());
}

//------------------------------------------------------------------------------
TEST_F(ILBasicFixedOpaqueTagTest, getSetValue) {
	ILBasicFixedOpaqueTag<0xFF, 8> t;
	std::uint8_t buff[16];

	for (unsigned int i = 0; i < sizeof(buff); i++) {
		buff[i] = i;
	}

	ASSERT_TRUE(t.setValue(buff, t.size()));
	ASSERT_EQ(0, std::memcmp(buff, t.value(), t.size()));

	ASSERT_FALSE(t.setValue(buff, t.size() - 1));
	ASSERT_EQ(0, std::memcmp(buff, t.value(), t.size()));

	ASSERT_FALSE(t.setValue(buff, t.size() + 1));
	ASSERT_EQ(0, std::memcmp(buff, t.value(), t.size()));
}

//------------------------------------------------------------------------------
TEST_F(ILBasicFixedOpaqueTagTest, serialize) {
	ILBasicFixedOpaqueTag<0xFF, 8> t;
	std::uint8_t buff[16];
	IRBuffer out;
	IRBuffer exp;

	for (unsigned int i = 0; i < sizeof(buff); i++) {
		buff[i] = i;
	}

	ASSERT_TRUE(t.setValue(buff, t.size()));
	ASSERT_TRUE(t.serialize(out));

	ASSERT_TRUE(exp.writeILInt(t.id()));
	ASSERT_TRUE(exp.writeILInt(t.size()));
	ASSERT_TRUE(exp.write(buff, t.size()));

	ASSERT_EQ(exp.size(), out.size());
	ASSERT_EQ(0, std::memcmp(exp.roBuffer(), out.roBuffer(), exp.size()));
}

//------------------------------------------------------------------------------
TEST_F(ILBasicFixedOpaqueTagTest, deserializeValue) {
	ILBasicFixedOpaqueTag<0xFF, 8> t;
	std::uint8_t buff[16];
	ILTagFactory f;

	for (unsigned int i = 0; i < sizeof(buff); i++) {
		buff[i] = i;
	}

	ASSERT_TRUE(t.deserializeValue(f, buff, t.size()));
	ASSERT_EQ(0, std::memcmp(buff, t.value(), t.size()));

	ASSERT_FALSE(t.deserializeValue(f, buff, t.size() - 1));
	ASSERT_EQ(0, std::memcmp(buff, t.value(), t.size()));

	ASSERT_FALSE(t.deserializeValue(f, buff, t.size() + 1));
	ASSERT_EQ(0, std::memcmp(buff, t.value(), t.size()));
}


//------------------------------------------------------------------------------

