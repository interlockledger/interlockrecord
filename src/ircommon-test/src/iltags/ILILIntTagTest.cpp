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
#include "ILILIntTagTest.h"
#include <ircommon/iltagstd.h>
#include <ircommon/ilint.h>
#include <cstring>
using namespace ircommon;
using namespace ircommon::iltags;

//==============================================================================
// class ILILIntTagTest
//------------------------------------------------------------------------------
ILILIntTagTest::ILILIntTagTest() {
}

//------------------------------------------------------------------------------
ILILIntTagTest::~ILILIntTagTest() {
}

//------------------------------------------------------------------------------
void ILILIntTagTest::SetUp() {
}

//------------------------------------------------------------------------------
void ILILIntTagTest::TearDown() {
}

//------------------------------------------------------------------------------
TEST_F(ILILIntTagTest,Constructor) {
	ILILIntTag * t;

	t = new ILILIntTag();
	ASSERT_EQ(ILTag::TAG_ILINT64, t->id());
	ASSERT_EQ(0, t->value());
	ASSERT_EQ(1, t->size());
	delete t;
}

//------------------------------------------------------------------------------
TEST_F(ILILIntTagTest, getSetValue) {
	ILILIntTag t;

	ASSERT_EQ(0, t.value());

	std::uint64_t v = 0xFF;
	for (int i = 0; i < 8; i++) {
		t.setValue(v);
		ASSERT_EQ(v, t.value());
		v = (v << 8) | 0xFF;
	}
}

//------------------------------------------------------------------------------
TEST_F(ILILIntTagTest, size) {
	ILILIntTag t;

	ASSERT_EQ(0, t.value());

	std::uint64_t v = 0xFF;
	for (int i = 0; i < 8; i++) {
		t.setValue(v);
		ASSERT_EQ(ILInt::size(v), t.size());
		v = (v << 8) | 0xFF;
	}
}

//------------------------------------------------------------------------------
TEST_F(ILILIntTagTest, serialize) {
	ILILIntTag t;
	IRBuffer out;
	IRBuffer exp;

	ASSERT_EQ(0, t.value());
	ASSERT_TRUE(t.serialize(out));
	ASSERT_TRUE(exp.writeILInt(ILTag::TAG_ILINT64));
	ASSERT_TRUE(exp.writeILInt(0));
	ASSERT_EQ(exp.size(), out.size());
	ASSERT_EQ(0, std::memcmp(exp.roBuffer(), out.roBuffer(), exp.size()));

	std::uint64_t v = 0xFF;
	for (int i = 0; i < 8; i++) {
		out.setSize(0);
		exp.setSize(0);

		t.setValue(v);

		ASSERT_TRUE(t.serialize(out));
		ASSERT_TRUE(exp.writeILInt(ILTag::TAG_ILINT64));
		ASSERT_TRUE(exp.writeILInt(v));
		ASSERT_EQ(exp.size(), out.size());
		ASSERT_EQ(0, std::memcmp(exp.roBuffer(), out.roBuffer(), exp.size()));
		v = (v << 8) | 0xFF;
	}
}

//------------------------------------------------------------------------------
TEST_F(ILILIntTagTest, deserializeValue) {
	ILILIntTag t;
	IRBuffer src;
	ILTagFactory f;

	ASSERT_TRUE(src.writeILInt(0));
	t.setValue(1);
	ASSERT_TRUE(t.deserializeValue(f, src.roBuffer(), src.size()));
	ASSERT_EQ(0, t.value());

	std::uint64_t v = 0xFF;
	for (int i = 0; i < 8; i++) {
		src.setSize(0);
		ASSERT_TRUE(src.writeILInt(v));
		ASSERT_TRUE(t.deserializeValue(f, src.roBuffer(), src.size()));
		ASSERT_EQ(v, t.value());
		v = (v << 8) | 0xFF;
	}

	ASSERT_FALSE(t.deserializeValue(f, src.roBuffer(), src.size() - 1));
	src.write(0);
	ASSERT_FALSE(t.deserializeValue(f, src.roBuffer(), src.size()));
}

//------------------------------------------------------------------------------

