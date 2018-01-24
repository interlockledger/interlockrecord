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
#include "ILRawTagTest.h"
#include <ircommon/iltag.h>
#include <cstring>
using namespace ircommon;
using namespace ircommon::iltags;

//==============================================================================
// class ILRawTagTest
//------------------------------------------------------------------------------
ILRawTagTest::ILRawTagTest() {
}

//------------------------------------------------------------------------------
ILRawTagTest::~ILRawTagTest() {
}

//------------------------------------------------------------------------------
void ILRawTagTest::SetUp() {
}

//------------------------------------------------------------------------------
void ILRawTagTest::TearDown() {
}

//------------------------------------------------------------------------------
TEST_F(ILRawTagTest,Constructor) {
	ILRawTag * t;

	t = new ILRawTag(ILTag::TAG_BYTE_ARRAY);
	ASSERT_EQ(ILTag::TAG_BYTE_ARRAY, t->id());
	ASSERT_FALSE(t->secure());
	ASSERT_EQ(0, t->value().size());
	ASSERT_EQ(IRBuffer::DEFAULT_INCREMENT, t->value().increment());
	delete t;

	t = new ILRawTag(0xFF, false);
	ASSERT_EQ(0xFF, t->id());
	ASSERT_FALSE(t->secure());
	ASSERT_EQ(0, t->value().size());
	ASSERT_EQ(IRBuffer::DEFAULT_INCREMENT, t->value().increment());
	delete t;

	t = new ILRawTag(0xFF, true);
	ASSERT_EQ(0xFF, t->id());
	ASSERT_TRUE(t->secure());
	ASSERT_EQ(0, t->value().size());
	ASSERT_EQ(IRBuffer::DEFAULT_INCREMENT, t->value().increment());
	delete t;

	t = new ILRawTag(0xFF, false, 32);
	ASSERT_EQ(0xFF, t->id());
	ASSERT_FALSE(t->secure());
	ASSERT_EQ(0, t->value().size());
	ASSERT_EQ(32, t->value().increment());
	delete t;

	t = new ILRawTag(0xFF, true, 32);
	ASSERT_EQ(0xFF, t->id());
	ASSERT_TRUE(t->secure());
	ASSERT_EQ(0, t->value().size());
	ASSERT_EQ(32, t->value().increment());
	delete t;
}

//------------------------------------------------------------------------------
TEST_F(ILRawTagTest, size) {
	ILRawTag t(0xFF);

	for (std::uint64_t size = 0; size < 1024; size++) {
		ASSERT_TRUE(t.value().setSize(size));
		ASSERT_EQ(size, t.size());
	}
}

//------------------------------------------------------------------------------
TEST_F(ILRawTagTest, deserializeValue) {
	ILTagFactory f;
	ILRawTag t(0xFF);
	std::uint8_t exp[512];

	std::memset(exp, 0xFA, sizeof(exp));
	ASSERT_TRUE(t.deserializeValue(f, exp, sizeof(exp)));
	ASSERT_EQ(sizeof(exp), t.size());
	ASSERT_EQ(0, std::memcmp(exp, t.value().roBuffer(), t.size()));
}

//------------------------------------------------------------------------------
TEST_F(ILRawTagTest, serialize) {
	ILTagFactory f;
	ILRawTag t(0xFF);
	IRBuffer exp;
	IRBuffer out;

	exp.writeILInt(0xFF);
	exp.writeILInt(0);
	ASSERT_TRUE(t.serialize(out));
	ASSERT_EQ(exp.size(), out.size());
	ASSERT_EQ(0, std::memcmp(exp.roBuffer(), out.roBuffer(), out.size()));

	exp.setSize(0);
	exp.writeILInt(0xFF);
	exp.writeILInt(256);
	t.value().setSize(0);
	for (int i = 0; i < 256; i++) {
		t.value().write(i);
		exp.write(i);
	}
	out.setSize(0);
	ASSERT_TRUE(t.serialize(out));
	ASSERT_EQ(exp.size(), out.size());
	ASSERT_EQ(0, std::memcmp(exp.roBuffer(), out.roBuffer(), out.size()));
}

//------------------------------------------------------------------------------
TEST_F(ILRawTagTest, value) {
	ILRawTag t(0xFF);
	const ILRawTag & rot = t;

	ASSERT_EQ(0, t.value().size());
	ASSERT_TRUE(t.value().write(1));
	ASSERT_EQ(1, rot.value().size());
}

//------------------------------------------------------------------------------
TEST_F(ILRawTagTest, secure) {

	ILRawTag t1(0xFF, false);
	ASSERT_EQ(t1.value().secure(), t1.secure());
	ASSERT_FALSE(t1.secure());

	ILRawTag t2(0xFF, true);
	ASSERT_EQ(t2.value().secure(), t2.secure());
	ASSERT_TRUE(t2.secure());
}
//------------------------------------------------------------------------------


