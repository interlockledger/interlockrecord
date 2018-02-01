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
	//TODO Implementation required!
	std::cout << "Implementation required!";
}


//------------------------------------------------------------------------------
TEST_F(ILTagUtilTest, sameClass) {
	ILNullTag t1;
	ILNullTag t2;
	ILRawTag t3(t2.id());
	ILRawTag t4(t2.id() + 1);

	ASSERT_TRUE(ILTagUtil::sameClass(t1, t2));
	ASSERT_TRUE(ILTagUtil::sameClass(t1, t3));
	ASSERT_TRUE(ILTagUtil::sameClass(t1, t4));
	//TODO Implementation required!
	std::cout << "Implementation required!";
}


//------------------------------------------------------------------------------

