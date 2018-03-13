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
#include "ILBasicFixedOpaqueTagTest.h"
#include <ircommon/iltagstd.h>
#include <cstring>
using namespace ircommon;
using namespace ircommon::iltags;

//==============================================================================
// class ILBasicFixedOpaqueTagTest
//------------------------------------------------------------------------------
ILBasicFixedOpaqueTagTest::ILBasicFixedOpaqueTagTest() {
}

//------------------------------------------------------------------------------
ILBasicFixedOpaqueTagTest::~ILBasicFixedOpaqueTagTest() {
}

//------------------------------------------------------------------------------
void ILBasicFixedOpaqueTagTest::SetUp() {
}

//------------------------------------------------------------------------------
void ILBasicFixedOpaqueTagTest::TearDown() {
}

//------------------------------------------------------------------------------
TEST_F(ILBasicFixedOpaqueTagTest,Constructor) {

	auto t8 = new ILBasicFixedOpaqueTag<0xFF, 8>();
	ASSERT_EQ(0xFF, t8->id());
	ASSERT_EQ(8, t8->size());
	delete t8;

	auto t16 = new ILBasicFixedOpaqueTag<0xFE, 16>();
	ASSERT_EQ(0xFE, t16->id());
	ASSERT_EQ(16, t16->size());
	delete t16;
}

//------------------------------------------------------------------------------
TEST_F(ILBasicFixedOpaqueTagTest, size) {

	ILBasicFixedOpaqueTag<0xFF, 8> t8;
	ASSERT_EQ(8, t8.size());

	ILBasicFixedOpaqueTag<0xFF, 16> t16;
	ASSERT_EQ(16, t16.size());
}

//------------------------------------------------------------------------------
TEST_F(ILBasicFixedOpaqueTagTest, getSetValue) {
	ILBasicFixedOpaqueTag<0xFF, 8> t;
	std::uint8_t buff[16];

	for (unsigned int i = 0; i < sizeof(buff); i++) {
		buff[i] = i;
	}

	ASSERT_TRUE(t.setValue(buff, t.size()));
	ASSERT_EQ(0, std::memcmp(buff, t.value(), t.size()));

	ASSERT_FALSE(t.setValue(buff, t.size() - 1));
	ASSERT_EQ(0, std::memcmp(buff, t.value(), t.size()));

	ASSERT_FALSE(t.setValue(buff, t.size() + 1));
	ASSERT_EQ(0, std::memcmp(buff, t.value(), t.size()));
}

//------------------------------------------------------------------------------
TEST_F(ILBasicFixedOpaqueTagTest, serialize) {
	ILBasicFixedOpaqueTag<0xFF, 8> t;
	std::uint8_t buff[16];
	IRBuffer out;
	IRBuffer exp;

	for (unsigned int i = 0; i < sizeof(buff); i++) {
		buff[i] = i;
	}

	ASSERT_TRUE(t.setValue(buff, t.size()));
	ASSERT_TRUE(t.serialize(out));

	ASSERT_TRUE(exp.writeILInt(t.id()));
	ASSERT_TRUE(exp.writeILInt(t.size()));
	ASSERT_TRUE(exp.write(buff, t.size()));

	ASSERT_EQ(exp.size(), out.size());
	ASSERT_EQ(0, std::memcmp(exp.roBuffer(), out.roBuffer(), exp.size()));
}

//------------------------------------------------------------------------------
TEST_F(ILBasicFixedOpaqueTagTest, deserializeValue) {
	ILBasicFixedOpaqueTag<0xFF, 8> t;
	std::uint8_t buff[16];
	ILTagFactory f;

	for (unsigned int i = 0; i < sizeof(buff); i++) {
		buff[i] = i;
	}

	ASSERT_TRUE(t.deserializeValue(f, buff, t.size()));
	ASSERT_EQ(0, std::memcmp(buff, t.value(), t.size()));

	ASSERT_FALSE(t.deserializeValue(f, buff, t.size() - 1));
	ASSERT_EQ(0, std::memcmp(buff, t.value(), t.size()));

	ASSERT_FALSE(t.deserializeValue(f, buff, t.size() + 1));
	ASSERT_EQ(0, std::memcmp(buff, t.value(), t.size()));
}


//------------------------------------------------------------------------------

