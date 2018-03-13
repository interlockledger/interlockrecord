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
#include "ILUInt64TagTest.h"
#include <ircommon/iltagstd.h>
#include <ircommon/ilint.h>
#include <cstring>
using namespace ircommon;
using namespace ircommon::iltags;

//==============================================================================
// class ILUInt64TagTest
//------------------------------------------------------------------------------
ILUInt64TagTest::ILUInt64TagTest() {
}

//------------------------------------------------------------------------------
ILUInt64TagTest::~ILUInt64TagTest() {
}

//------------------------------------------------------------------------------
void ILUInt64TagTest::SetUp() {
}

//------------------------------------------------------------------------------
void ILUInt64TagTest::TearDown() {
}

//------------------------------------------------------------------------------
TEST_F(ILUInt64TagTest,Constructor) {
	ILUInt64Tag * t;

	t = new ILUInt64Tag();
	ASSERT_EQ(ILTag::TAG_UINT64, t->id());
	ASSERT_EQ(0, t->value());
	ASSERT_EQ(sizeof(std::int64_t), t->size());
	delete t;
}

//------------------------------------------------------------------------------
TEST_F(ILUInt64TagTest, serialize) {
	ILUInt64Tag t;
	IRBuffer out;
	IRBuffer exp;
	std::uint64_t v;

	v = 0;
	for (unsigned int i = 0; i < sizeof(v); i++) {
		v = (v << 8) | i;
	}
	t.setValue(v);
	ASSERT_TRUE(t.serialize(out));

	ASSERT_TRUE(exp.writeILInt(ILTag::TAG_UINT64));
	ASSERT_TRUE(exp.writeInt(v));
	ASSERT_EQ(exp.size(), out.size());
	ASSERT_EQ(0, std::memcmp(exp.roBuffer(), out.roBuffer(), exp.size()));
}

//------------------------------------------------------------------------------
TEST_F(ILUInt64TagTest, deserializeValue) {
	ILUInt64Tag t;
	IRBuffer src;
	std::uint64_t v;
	ILTagFactory f;

	v = 0;
	for (unsigned int i = 0; i < sizeof(v); i++) {
		v = (v << 8) | i;
	}
	ASSERT_TRUE(src.writeInt(v));

	ASSERT_TRUE(t.deserializeValue(f, src.roBuffer(), src.size()));
	ASSERT_EQ(v, t.value());

	ASSERT_FALSE(t.deserializeValue(f, src.roBuffer(), src.size() - 1));
	src.write(0);
	ASSERT_FALSE(t.deserializeValue(f, src.roBuffer(), src.size()));
}

//------------------------------------------------------------------------------

