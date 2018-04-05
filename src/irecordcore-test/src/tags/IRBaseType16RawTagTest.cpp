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
#include "IRBaseType16RawTagTest.h"
#include <irecordcore/irtags.h>

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
	IRBaseType16RawTag * bt16rt;

	bt16rt = new IRBaseType16RawTag(0xFF, false);
	ASSERT_EQ(0xFF, bt16rt->size);
	delete bt16rt;
}
//------------------------------------------------------------------------------




