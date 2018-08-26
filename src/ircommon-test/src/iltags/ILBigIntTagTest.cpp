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
#include "ILBigIntTagTest.h"
#include <ircommon/iltagstd.h>
#include <cstring>
using namespace ircommon;
using namespace ircommon::iltags;

//==============================================================================
// class IRBigIntTagTest
//------------------------------------------------------------------------------
ILBigIntTagTest::ILBigIntTagTest() {
}

//------------------------------------------------------------------------------
ILBigIntTagTest::~ILBigIntTagTest() {
}

//------------------------------------------------------------------------------
void ILBigIntTagTest::SetUp() {
}

//------------------------------------------------------------------------------
void ILBigIntTagTest::TearDown() {
}

//------------------------------------------------------------------------------
TEST_F(ILBigIntTagTest,Constructor) {
	ILBigIntTag * t;

	t = new ILBigIntTag();
	ASSERT_EQ(ILTag::TAG_BINT, t->id());
	ASSERT_EQ(0, t->value().size());
	ASSERT_TRUE(t->value().secure());
	delete t;

	t = new ILBigIntTag(false);
	ASSERT_EQ(ILTag::TAG_BINT, t->id());
	ASSERT_EQ(0, t->value().size());
	ASSERT_FALSE(t->value().secure());
	delete t;

	t = new ILBigIntTag(true);
	ASSERT_EQ(ILTag::TAG_BINT, t->id());
	ASSERT_EQ(0, t->value().size());
	ASSERT_TRUE(t->value().secure());
	delete t;
}

//------------------------------------------------------------------------------
TEST_F(ILBigIntTagTest, serialize) {
	ILBigIntTag t;
	IRBuffer out;
	IRBuffer exp;
	std::uint8_t buff[16];

	for (unsigned int i = 0; i < sizeof(buff); i++) {
		buff[i] = i;
	}
	ASSERT_TRUE(t.value().set(buff, sizeof(buff)));
	ASSERT_TRUE(t.serialize(out));

	ASSERT_TRUE(exp.writeILInt(ILTag::TAG_BINT));
	ASSERT_TRUE(exp.writeILInt(sizeof(buff)));
	ASSERT_TRUE(exp.write(buff, sizeof(buff)));

	ASSERT_EQ(exp.size(), out.size());
	ASSERT_EQ(0, std::memcmp(exp.roBuffer(), out.roBuffer(), exp.size()));
}
//------------------------------------------------------------------------------
