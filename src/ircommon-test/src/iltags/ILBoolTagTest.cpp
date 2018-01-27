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
#include "ILBoolTagTest.h"
#include <ircommon/iltagstd.h>
using namespace ircommon;
using namespace ircommon::iltags;

//==============================================================================
// class ILBoolTagTest
//------------------------------------------------------------------------------
ILBoolTagTest::ILBoolTagTest() {
}

//------------------------------------------------------------------------------
ILBoolTagTest::~ILBoolTagTest() {
}

//------------------------------------------------------------------------------
void ILBoolTagTest::SetUp() {
}

//------------------------------------------------------------------------------
void ILBoolTagTest::TearDown() {
}

//------------------------------------------------------------------------------
TEST_F(ILBoolTagTest,Constructor) {
	ILBoolTag * t;

	t = new ILBoolTag();
	ASSERT_EQ(ILTag::TAG_BOOL, t->id());
	ASSERT_FALSE(t->value());
	delete t;
}

//------------------------------------------------------------------------------
TEST_F(ILBoolTagTest, size) {
	ILBoolTag t;

	ASSERT_EQ(1, t.size());
}

//------------------------------------------------------------------------------
TEST_F(ILBoolTagTest, serialize) {
	ILBoolTag t;
	IRBuffer out;

	ASSERT_TRUE(t.serialize(out));
	ASSERT_EQ(2, out.size());
	ASSERT_EQ(ILTag::TAG_BOOL, out.roBuffer()[0]);
	ASSERT_EQ(0, out.roBuffer()[1]);

	out.setSize(0);
	t.setValue(true);
	ASSERT_TRUE(t.serialize(out));
	ASSERT_EQ(2, out.size());
	ASSERT_EQ(ILTag::TAG_BOOL, out.roBuffer()[0]);
	ASSERT_EQ(1, out.roBuffer()[1]);
}

//------------------------------------------------------------------------------
TEST_F(ILBoolTagTest, deserializeValue) {
	ILBoolTag t;
	std::uint8_t serialized[8];
	ILTagFactory f;

	std::memset(serialized, 0, sizeof(serialized));
	t.setValue(true);
	ASSERT_TRUE(t.deserializeValue(f, serialized, 1));
	ASSERT_FALSE(t.value());

	std::memset(serialized, 0, sizeof(serialized));
	serialized[0] = 1;
	t.setValue(false);
	ASSERT_TRUE(t.deserializeValue(f, serialized, 1));
	ASSERT_TRUE(t.value());

	ASSERT_FALSE(t.deserializeValue(f, serialized, 0));
	ASSERT_FALSE(t.deserializeValue(f, serialized, 2));
}

//------------------------------------------------------------------------------

