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

