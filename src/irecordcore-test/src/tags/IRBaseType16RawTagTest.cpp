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
#include "IRBaseType16RawTagTest.h"
#include <irecordcore/irtags.h>
#include <cstring>
#include "../crypto/CryptoSamples.h"

using namespace irecordcore;
using namespace irecordcore::tags;
using namespace ircommon;
using namespace ircommon::iltags;

//==============================================================================
// class IRBaseType16RawTagTest
//------------------------------------------------------------------------------
IRBaseType16RawTagTest::IRBaseType16RawTagTest() {
}

//------------------------------------------------------------------------------
IRBaseType16RawTagTest::~IRBaseType16RawTagTest() {
}

//------------------------------------------------------------------------------
void IRBaseType16RawTagTest::SetUp() {
}

//------------------------------------------------------------------------------
void IRBaseType16RawTagTest::TearDown() {
}

//------------------------------------------------------------------------------
TEST_F(IRBaseType16RawTagTest,Constructor) {
	IRBaseType16RawTag * bt16rt;

	bt16rt = new IRBaseType16RawTag(0xFF, false);
	ASSERT_EQ(0xFF, bt16rt->id());
	ASSERT_FALSE(bt16rt->value().secure());
	delete bt16rt;

	bt16rt = new IRBaseType16RawTag(0xFFFF, true);
	ASSERT_EQ(0xFFFF, bt16rt->id());
	ASSERT_TRUE(bt16rt->value().secure());
	delete bt16rt;
}

//------------------------------------------------------------------------------
TEST_F(IRBaseType16RawTagTest, Size) {
	IRBaseType16RawTag bt16rt(0xFF, false);

	ASSERT_EQ(2, bt16rt.size());
	ASSERT_TRUE(bt16rt.value().write(0));
	ASSERT_EQ(2 + 1, bt16rt.size());
	ASSERT_TRUE(bt16rt.value().setSize(0));
	ASSERT_EQ(2, bt16rt.size());
	ASSERT_TRUE(bt16rt.value().setSize(32));
	ASSERT_EQ(2 + 32, bt16rt.size());
}

//------------------------------------------------------------------------------
TEST_F(IRBaseType16RawTagTest, deserializeValue) {
	IRBaseType16RawTag bt16rt(0xFF, false);
	IRBuffer serialized;
	ILStandardTagFactory f;

	// Empty
	ASSERT_TRUE(serialized.writeInt((std::uint16_t)0xFACA));
	ASSERT_TRUE(bt16rt.deserializeValue(f, serialized.roBuffer(), serialized.size()));
	ASSERT_EQ(0xFACA, bt16rt.value().type());
	ASSERT_EQ(0, bt16rt.value().size());

	// With value
	serialized.setSize(0);
	ASSERT_TRUE(serialized.writeInt((std::uint16_t)0xCACA));
	ASSERT_TRUE(serialized.write(CRYPTOSAMPLES_SAMPLE, sizeof(CRYPTOSAMPLES_SAMPLE)));
	ASSERT_TRUE(bt16rt.deserializeValue(f, serialized.roBuffer(), serialized.size()));
	ASSERT_EQ(0xCACA, bt16rt.value().type());
	ASSERT_EQ(sizeof(CRYPTOSAMPLES_SAMPLE), bt16rt.value().size());
	ASSERT_EQ(0, 
		std::memcmp(bt16rt.value().roBuffer(), CRYPTOSAMPLES_SAMPLE, sizeof(CRYPTOSAMPLES_SAMPLE)));

	// Fail
	serialized.setSize(0);
	ASSERT_FALSE(bt16rt.deserializeValue(f, serialized.roBuffer(), serialized.size()));

	serialized.setSize(1);
	ASSERT_FALSE(bt16rt.deserializeValue(f, serialized.roBuffer(), serialized.size()));
}


//------------------------------------------------------------------------------
TEST_F(IRBaseType16RawTagTest, value) {

	IRBaseType16RawTag bt16rt(0xFF, false);
	IRBuffer bfValue;

	bt16rt.value().setType(0x1234);
	ASSERT_TRUE(bt16rt.value().write(CRYPTOSAMPLES_KEY128, sizeof(CRYPTOSAMPLES_KEY128)));
	ASSERT_TRUE(bfValue.write(CRYPTOSAMPLES_KEY128, sizeof(CRYPTOSAMPLES_KEY128)));
	ASSERT_EQ(bfValue.size(), bt16rt.value().size());
}


//------------------------------------------------------------------------------
TEST_F(IRBaseType16RawTagTest, serialize) {
	IRBaseType16RawTag bt16rt(0xFF, false);
	IRBuffer serialized;
	IRBuffer expected;

	// Empty
	ASSERT_TRUE(bt16rt.serialize(serialized));
	ASSERT_TRUE(expected.writeILInt(0xFF));
	ASSERT_TRUE(expected.writeILInt(2));
	ASSERT_TRUE(expected.writeInt((std::uint16_t)0));
	ASSERT_EQ(expected.size(), serialized.size());
	ASSERT_EQ(0,
		std::memcmp(expected.roBuffer(), serialized.roBuffer(), expected.size()));

	// With content
	serialized.setSize(0);
	expected.setSize(0);
	bt16rt.value().setType(0x1234);
	ASSERT_TRUE(bt16rt.value().write(CRYPTOSAMPLES_SAMPLE, sizeof(CRYPTOSAMPLES_SAMPLE)));
	ASSERT_TRUE(bt16rt.serialize(serialized));
	ASSERT_TRUE(expected.writeILInt(0xFF));
	ASSERT_TRUE(expected.writeILInt(2 + sizeof(CRYPTOSAMPLES_SAMPLE)));
	ASSERT_TRUE(expected.writeInt((std::uint16_t)0x1234));
	ASSERT_TRUE(expected.write(CRYPTOSAMPLES_SAMPLE, sizeof(CRYPTOSAMPLES_SAMPLE)));
	ASSERT_EQ(expected.size(), serialized.size());
	ASSERT_EQ(0,
		std::memcmp(expected.roBuffer(), serialized.roBuffer(), expected.size()));
}

//------------------------------------------------------------------------------




