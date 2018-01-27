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
#include "ILNullTagTest.h"
#include <ircommon/iltagstd.h>
using namespace ircommon;
using namespace ircommon::iltags;

//==============================================================================
// class ILNullTagTest
//------------------------------------------------------------------------------
ILNullTagTest::ILNullTagTest() {
}

//------------------------------------------------------------------------------
ILNullTagTest::~ILNullTagTest() {
}

//------------------------------------------------------------------------------
void ILNullTagTest::SetUp() {
}

//------------------------------------------------------------------------------
void ILNullTagTest::TearDown() {
}

//------------------------------------------------------------------------------
TEST_F(ILNullTagTest,Constructor) {
	ILNullTag * t;

	t = new ILNullTag();
	ASSERT_EQ(ILTag::TAG_NULL, t->id());
	delete t;
}

//------------------------------------------------------------------------------
TEST_F(ILNullTagTest, size) {
	ILNullTag t;

	ASSERT_EQ(0, t.size());
}

//------------------------------------------------------------------------------
TEST_F(ILNullTagTest, serializeValue) {
	ILNullTag t;
	IRBuffer out;

	ASSERT_TRUE(t.serialize(out));
	ASSERT_EQ(1, out.size());
	ASSERT_EQ(0, out.roBuffer()[0]);
}

//------------------------------------------------------------------------------

