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
#include "ILTagUtilTest.h"
#include <ircommon/ilint.h>
#include <ircommon/iltag.h>
#include <ircommon/iltagstd.h>

using namespace ircommon;
using namespace ircommon::iltags;

//==============================================================================
// class ILTagUtilTest
//------------------------------------------------------------------------------
ILTagUtilTest::ILTagUtilTest() {
}

//------------------------------------------------------------------------------
ILTagUtilTest::~ILTagUtilTest() {
}

//------------------------------------------------------------------------------
void ILTagUtilTest::SetUp() {
}

//------------------------------------------------------------------------------
void ILTagUtilTest::TearDown() {
}

//------------------------------------------------------------------------------
TEST_F(ILTagUtilTest, sameID) {
	ILNullTag t1;
	ILNullTag t2;
	ILRawTag t3(t2.id());
	ILRawTag t4(t2.id() + 1);

	ASSERT_TRUE(ILTagUtil::sameID(t1, t2));
	ASSERT_TRUE(ILTagUtil::sameID(t1, t3));
	ASSERT_FALSE(ILTagUtil::sameID(t1, t4));
}

//------------------------------------------------------------------------------
TEST_F(ILTagUtilTest, sameClass) {
	ILNullTag t1;
	ILNullTag t2;
	ILRawTag t3(t2.id());
	ILRawTag t4(t2.id() + 1);

	// Same classes
	ASSERT_TRUE(ILTagUtil::sameClass(t1, t1));
	ASSERT_TRUE(ILTagUtil::sameClass(t1, t2));
	ASSERT_TRUE(ILTagUtil::sameClass(t2, t1));

	// Distinct classes
	ASSERT_FALSE(ILTagUtil::sameClass(t1, t3));
	ASSERT_FALSE(ILTagUtil::sameClass(t3, t1));

    // Same classes but distinct IDs
	ASSERT_TRUE(ILTagUtil::sameClass(t3, t4));
	ASSERT_TRUE(ILTagUtil::sameClass(t4, t3));
}

//------------------------------------------------------------------------------
TEST_F(ILTagUtilTest, equals) {
	ILNullTag t1;
	ILNullTag t2;
	ILInt8Tag t3;
	ILInt8Tag t4;
	ILRawTag t5(t4.id());
    ILRawTag t6(123);
    ILRawTag t7(124);

	t3.setValue(0);
	t4.setValue(1);
	t5.value().write(0);

	// Same classes
	ASSERT_TRUE(ILTagUtil::equals(t1, t1));
    ASSERT_TRUE(ILTagUtil::equals(t1, t2));
    ASSERT_TRUE(ILTagUtil::equals(t2, t1));
    ASSERT_TRUE(ILTagUtil::equals(t3, t3));

    // Distinct classes, same value
    ASSERT_TRUE(ILTagUtil::equals(t3, t5));

    // Same classes, distinct values
    ASSERT_FALSE(ILTagUtil::equals(t3, t4));
    ASSERT_FALSE(ILTagUtil::equals(t4, t3));
    ASSERT_FALSE(ILTagUtil::equals(t6, t7));
    ASSERT_FALSE(ILTagUtil::equals(t7, t6));

    // Distinct classes, distinct value
    ASSERT_FALSE(ILTagUtil::equals(t1, t3));
    ASSERT_FALSE(ILTagUtil::equals(t3, t1));
}

