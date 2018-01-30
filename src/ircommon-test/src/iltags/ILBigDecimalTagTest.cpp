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
#include "ILBigDecimalTagTest.h"
#include <ircommon/iltagstd.h>
#include <cstring>
using namespace ircommon;
using namespace ircommon::iltags;

//==============================================================================
// class IRBigDecimalTagTest
//------------------------------------------------------------------------------
ILBigDecimalTagTest::ILBigDecimalTagTest() {
}

//------------------------------------------------------------------------------
ILBigDecimalTagTest::~ILBigDecimalTagTest() {
}

//------------------------------------------------------------------------------
void ILBigDecimalTagTest::SetUp() {
}

//------------------------------------------------------------------------------
void ILBigDecimalTagTest::TearDown() {
}

//------------------------------------------------------------------------------
TEST_F(ILBigDecimalTagTest,Constructor) {
	ILBigDecimalTag * t;

	t = new ILBigDecimalTag();
	ASSERT_EQ(ILTag::TAG_BDEC, t->id());
	ASSERT_EQ(0, t->scale());
	ASSERT_EQ(0, t->integral().size());
	ASSERT_FALSE(t->integral().secure());
	delete t;

	t = new ILBigDecimalTag(false);
	ASSERT_EQ(ILTag::TAG_BDEC, t->id());
	ASSERT_EQ(0, t->scale());
	ASSERT_EQ(0, t->integral().size());
	ASSERT_FALSE(t->integral().secure());
	delete t;

	t = new ILBigDecimalTag(true);
	ASSERT_EQ(ILTag::TAG_BDEC, t->id());
	ASSERT_EQ(0, t->scale());
	ASSERT_EQ(0, t->integral().size());
	ASSERT_TRUE(t->integral().secure());
	delete t;
}

//------------------------------------------------------------------------------
TEST_F(ILBigDecimalTagTest, size) {
	ILBigDecimalTag t;
	std::uint8_t buff[32];

	for (int i = 0; i < sizeof(buff); i++) {
		buff[i] = i;
	}

	for (int i = 0; i < sizeof(buff); i++) {
		ASSERT_TRUE(t.setIntegral(buff, i));
		ASSERT_EQ(sizeof(std::int32_t) + i, t.size());
	}
}

//------------------------------------------------------------------------------
TEST_F(ILBigDecimalTagTest, serialize) {
	ILBigDecimalTag t;
	std::uint8_t buff[32];
	IRBuffer out;
	IRBuffer exp;

	for (int i = 0; i < sizeof(buff); i++) {
		buff[i] = i;
	}

	for (int i = 0; i < sizeof(buff); i++) {
		out.setSize(0);
		exp.setSize(0);

		ASSERT_TRUE(t.setIntegral(buff, i));
		t.setScale(i);
		ASSERT_TRUE(t.serialize(out));

		ASSERT_TRUE(exp.writeILInt(ILTag::TAG_BDEC));
		ASSERT_TRUE(exp.writeILInt(t.size()));
		ASSERT_TRUE(exp.writeInt(t.scale()));
		ASSERT_TRUE(exp.write(t.integral().roBuffer(), t.integral().size()));

		ASSERT_EQ(exp.size(), out.size());
		ASSERT_EQ(0, std::memcmp(exp.roBuffer(), out.roBuffer(), exp.size()));
	}
}

//------------------------------------------------------------------------------
TEST_F(ILBigDecimalTagTest, deserializeValue) {
	ILBigDecimalTag t;
	std::uint8_t buff[32];
	IRBuffer exp;
	ILTagFactory f;

	for (int i = 0; i < sizeof(buff); i++) {
		buff[i] = i;
	}

	for (int i = 0; i < sizeof(buff); i++) {
		exp.setSize(0);
		ASSERT_TRUE(exp.writeInt((std::int32_t)i));
		ASSERT_TRUE(exp.write(t.integral().roBuffer(), t.integral().size()));

		ASSERT_TRUE(t.deserializeValue(f, exp.roBuffer(), exp.size()));
		ASSERT_EQ(i, t.scale());
		ASSERT_EQ(0, std::memcmp(buff, t.integral().roBuffer(),
				t.integral().size()));
	}
}
//------------------------------------------------------------------------------

