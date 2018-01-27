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
#include "ILBasicIntTagTest.h"
#include <ircommon/iltagstd.h>
#include <cstring>
using namespace ircommon;
using namespace ircommon::iltags;


//==============================================================================
// class ILBasicTagTest
//------------------------------------------------------------------------------
ILBasicIntTagTest::ILBasicIntTagTest() {
}

//------------------------------------------------------------------------------
ILBasicIntTagTest::~ILBasicIntTagTest() {
}

//------------------------------------------------------------------------------
void ILBasicIntTagTest::SetUp() {
}

//------------------------------------------------------------------------------
void ILBasicIntTagTest::TearDown() {
}

//------------------------------------------------------------------------------
TEST_F(ILBasicIntTagTest,Constructor) {

	auto u8 = new ILBasicIntTag<std::uint8_t, 0xFF>();
	ASSERT_EQ(0xFF, u8->id());
	ASSERT_EQ(typeid(std::uint8_t), typeid(u8->value()));
	ASSERT_EQ(sizeof(std::uint8_t), u8->size());
	ASSERT_EQ(0, u8->value());
	delete u8;

	auto s8 = new ILBasicIntTag<std::int8_t, 0xFE>();
	ASSERT_EQ(0xFE, s8->id());
	ASSERT_EQ(typeid(std::int8_t), typeid(s8->value()));
	ASSERT_EQ(sizeof(std::int8_t), s8->size());
	ASSERT_EQ(0, s8->value());
	delete s8;

	auto u16 = new ILBasicIntTag<std::uint16_t, 0xFF>();
	ASSERT_EQ(0xFF, u16->id());
	ASSERT_EQ(typeid(std::uint16_t), typeid(u16->value()));
	ASSERT_EQ(sizeof(std::uint16_t), u16->size());
	ASSERT_EQ(0, u16->value());
	delete u16;

	auto s16 = new ILBasicIntTag<std::int16_t, 0xFE>();
	ASSERT_EQ(0xFE, s16->id());
	ASSERT_EQ(typeid(std::int16_t), typeid(s16->value()));
	ASSERT_EQ(sizeof(std::int16_t), s16->size());
	ASSERT_EQ(0, s16->value());
	delete s16;

	auto u32 = new ILBasicIntTag<std::uint32_t, 0xFF>();
	ASSERT_EQ(0xFF, u32->id());
	ASSERT_EQ(typeid(std::uint32_t), typeid(u32->value()));
	ASSERT_EQ(sizeof(std::uint32_t), u32->size());
	ASSERT_EQ(0, u32->value());
	delete u32;

	auto s32 = new ILBasicIntTag<std::int32_t, 0xFE>();
	ASSERT_EQ(0xFE, s32->id());
	ASSERT_EQ(typeid(std::int32_t), typeid(s32->value()));
	ASSERT_EQ(sizeof(std::int32_t), s32->size());
	ASSERT_EQ(0, s32->value());
	delete s32;

	auto u64 = new ILBasicIntTag<std::uint64_t, 0xFF>();
	ASSERT_EQ(0xFF, u64->id());
	ASSERT_EQ(typeid(std::uint64_t), typeid(u64->value()));
	ASSERT_EQ(sizeof(std::uint64_t), u64->size());
	ASSERT_EQ(0, u64->value());
	delete u64;

	auto s64 = new ILBasicIntTag<std::int64_t, 0xFE>();
	ASSERT_EQ(0xFE, s64->id());
	ASSERT_EQ(typeid(std::int64_t), typeid(s64->value()));
	ASSERT_EQ(sizeof(std::int64_t), s64->size());
	ASSERT_EQ(0, s64->value());
	delete s64;
}

//------------------------------------------------------------------------------
TEST_F(ILBasicIntTagTest, size) {

	ILBasicIntTag<std::int8_t, 0xFF> s8;
	ILBasicIntTag<std::uint8_t, 0xFF> u8;
	ASSERT_EQ(sizeof(std::int8_t), s8.size());
	ASSERT_EQ(sizeof(std::uint8_t), u8.size());

	ILBasicIntTag<std::int16_t, 0xFF> s16;
	ILBasicIntTag<std::uint16_t, 0xFF> u16;
	ASSERT_EQ(sizeof(std::int16_t), s16.size());
	ASSERT_EQ(sizeof(std::uint16_t), u16.size());

	ILBasicIntTag<std::int32_t, 0xFF> s32;
	ILBasicIntTag<std::uint32_t, 0xFF> u32;
	ASSERT_EQ(sizeof(std::int32_t), s32.size());
	ASSERT_EQ(sizeof(std::uint32_t), u32.size());

	ILBasicIntTag<std::int64_t, 0xFF> s64;
	ILBasicIntTag<std::uint64_t, 0xFF> u64;
	ASSERT_EQ(sizeof(std::int64_t), s64.size());
	ASSERT_EQ(sizeof(std::uint64_t), u64.size());
}

//------------------------------------------------------------------------------
TEST_F(ILBasicIntTagTest, getSetValue) {

	ILBasicIntTag<std::int8_t, 0xFF> s8;
	s8.setValue(-1);
	ASSERT_EQ(-1, s8.value());
	s8.setValue(0);
	ASSERT_EQ(0, s8.value());

	ILBasicIntTag<std::int8_t, 0xFF> u8;
	u8.setValue(~0);
	ASSERT_EQ(~0, u8.value());
	u8.setValue(0);
	ASSERT_EQ(0, u8.value());

	ILBasicIntTag<std::int16_t, 0xFF> s16;
	s16.setValue(-1);
	ASSERT_EQ(-1, s16.value());
	s16.setValue(0);
	ASSERT_EQ(0, s16.value());

	ILBasicIntTag<std::int16_t, 0xFF> u16;
	u16.setValue(~0);
	ASSERT_EQ(~0, u16.value());
	u16.setValue(0);
	ASSERT_EQ(0, u16.value());

	ILBasicIntTag<std::int32_t, 0xFF> s32;
	s32.setValue(-1);
	ASSERT_EQ(-1, s32.value());
	s32.setValue(0);
	ASSERT_EQ(0, s32.value());

	ILBasicIntTag<std::int32_t, 0xFF> u32;
	u32.setValue(~0);
	ASSERT_EQ(~0, u32.value());
	u32.setValue(0);
	ASSERT_EQ(0, u32.value());

	ILBasicIntTag<std::int64_t, 0xFF> s64;
	s64.setValue(-1);
	ASSERT_EQ(-1, s64.value());
	s64.setValue(0);
	ASSERT_EQ(0, s64.value());

	ILBasicIntTag<std::int64_t, 0xFF> u64;
	u64.setValue(~0);
	ASSERT_EQ(~0, u64.value());
	u64.setValue(0);
	ASSERT_EQ(0, u64.value());
}

//------------------------------------------------------------------------------
TEST_F(ILBasicIntTagTest, serialize8) {
	std::int8_t v;
	ILBasicIntTag<std::int8_t, 0xFF> t;
	IRBuffer out;
	IRBuffer exp;

	v = 0xAF;
	t.setValue(v);
	ASSERT_TRUE(t.serialize(out));

	ASSERT_TRUE(exp.writeILInt(0xFF));
	ASSERT_TRUE(exp.writeILInt(sizeof(v)));
	ASSERT_TRUE(exp.writeInt(v));

	ASSERT_EQ(exp.size(), out.size());
	ASSERT_EQ(0, std::memcmp(exp.roBuffer(), out.roBuffer(), exp.size()));
}

//------------------------------------------------------------------------------
TEST_F(ILBasicIntTagTest, serialize8u) {
	std::uint8_t v;
	ILBasicIntTag<std::uint8_t, 0xFF> t;
	IRBuffer out;
	IRBuffer exp;

	v = 0xAF;
	t.setValue(v);
	ASSERT_TRUE(t.serialize(out));

	ASSERT_TRUE(exp.writeILInt(0xFF));
	ASSERT_TRUE(exp.writeILInt(sizeof(v)));
	ASSERT_TRUE(exp.writeInt(v));

	ASSERT_EQ(exp.size(), out.size());
	ASSERT_EQ(0, std::memcmp(exp.roBuffer(), out.roBuffer(), exp.size()));
}

//------------------------------------------------------------------------------
TEST_F(ILBasicIntTagTest, serialize16) {
	std::int16_t v;
	ILBasicIntTag<std::int16_t, 0xFF> t;
	IRBuffer out;
	IRBuffer exp;

	v = 0xAF01;
	t.setValue(v);
	ASSERT_TRUE(t.serialize(out));

	ASSERT_TRUE(exp.writeILInt(0xFF));
	ASSERT_TRUE(exp.writeILInt(sizeof(v)));
	ASSERT_TRUE(exp.writeInt(v));

	ASSERT_EQ(exp.size(), out.size());
	ASSERT_EQ(0, std::memcmp(exp.roBuffer(), out.roBuffer(), exp.size()));
}

//------------------------------------------------------------------------------
TEST_F(ILBasicIntTagTest, serialize16u) {
	std::uint16_t v;
	ILBasicIntTag<std::uint16_t, 0xFF> t;
	IRBuffer out;
	IRBuffer exp;

	v = 0xAF01;
	t.setValue(v);
	ASSERT_TRUE(t.serialize(out));

	ASSERT_TRUE(exp.writeILInt(0xFF));
	ASSERT_TRUE(exp.writeILInt(sizeof(v)));
	ASSERT_TRUE(exp.writeInt(v));

	ASSERT_EQ(exp.size(), out.size());
	ASSERT_EQ(0, std::memcmp(exp.roBuffer(), out.roBuffer(), exp.size()));
}

//------------------------------------------------------------------------------
TEST_F(ILBasicIntTagTest, serialize32) {
	std::int32_t v;
	ILBasicIntTag<std::int32_t, 0xFF> t;
	IRBuffer out;
	IRBuffer exp;

	v = 0xAF01;
	t.setValue(v);
	ASSERT_TRUE(t.serialize(out));

	ASSERT_TRUE(exp.writeILInt(0xFF));
	ASSERT_TRUE(exp.writeILInt(sizeof(v)));
	ASSERT_TRUE(exp.writeInt(v));

	ASSERT_EQ(exp.size(), out.size());
	ASSERT_EQ(0, std::memcmp(exp.roBuffer(), out.roBuffer(), exp.size()));
}

//------------------------------------------------------------------------------
TEST_F(ILBasicIntTagTest, serialize32u) {
	std::uint32_t v;
	ILBasicIntTag<std::uint32_t, 0xFF> t;
	IRBuffer out;
	IRBuffer exp;

	v = 0xAF01;
	t.setValue(v);
	ASSERT_TRUE(t.serialize(out));

	ASSERT_TRUE(exp.writeILInt(0xFF));
	ASSERT_TRUE(exp.writeILInt(sizeof(v)));
	ASSERT_TRUE(exp.writeInt(v));

	ASSERT_EQ(exp.size(), out.size());
	ASSERT_EQ(0, std::memcmp(exp.roBuffer(), out.roBuffer(), exp.size()));
}
//------------------------------------------------------------------------------
TEST_F(ILBasicIntTagTest, serialize64) {
	std::int64_t v;
	ILBasicIntTag<std::int64_t, 0xFF> t;
	IRBuffer out;
	IRBuffer exp;

	v = 0xAF01;
	t.setValue(v);
	ASSERT_TRUE(t.serialize(out));

	ASSERT_TRUE(exp.writeILInt(0xFF));
	ASSERT_TRUE(exp.writeILInt(sizeof(v)));
	ASSERT_TRUE(exp.writeInt(v));

	ASSERT_EQ(exp.size(), out.size());
	ASSERT_EQ(0, std::memcmp(exp.roBuffer(), out.roBuffer(), exp.size()));
}

//------------------------------------------------------------------------------
TEST_F(ILBasicIntTagTest, serialize64u) {
	std::uint64_t v;
	ILBasicIntTag<std::uint64_t, 0xFF> t;
	IRBuffer out;
	IRBuffer exp;

	v = 0xAF01;
	t.setValue(v);
	ASSERT_TRUE(t.serialize(out));

	ASSERT_TRUE(exp.writeILInt(0xFF));
	ASSERT_TRUE(exp.writeILInt(sizeof(v)));
	ASSERT_TRUE(exp.writeInt(v));

	ASSERT_EQ(exp.size(), out.size());
	ASSERT_EQ(0, std::memcmp(exp.roBuffer(), out.roBuffer(), exp.size()));
}

//------------------------------------------------------------------------------
TEST_F(ILBasicIntTagTest, deserializeValue8) {
	std::int8_t v;
	ILBasicIntTag<std::int8_t, 0xFF> t;
	IRBuffer src;
	ILTagFactory f;

	v = 0xAF;
	ASSERT_TRUE(src.writeInt(v));

	ASSERT_TRUE(t.deserializeValue(f, src.roBuffer(), src.size()));
	ASSERT_EQ(v, t.value());

	ASSERT_FALSE(t.deserializeValue(f, src.roBuffer(), src.size() - 1));
	ASSERT_TRUE(src.write(0));
	ASSERT_FALSE(t.deserializeValue(f, src.roBuffer(), src.size() + 1));
}

//------------------------------------------------------------------------------
TEST_F(ILBasicIntTagTest, deserializeValue8u) {
	std::uint8_t v;
	ILBasicIntTag<std::uint8_t, 0xFF> t;
	IRBuffer src;
	ILTagFactory f;

	v = 0xAF;
	ASSERT_TRUE(src.writeInt(v));

	ASSERT_TRUE(t.deserializeValue(f, src.roBuffer(), src.size()));
	ASSERT_EQ(v, t.value());

	ASSERT_FALSE(t.deserializeValue(f, src.roBuffer(), src.size() - 1));
	ASSERT_TRUE(src.write(0));
	ASSERT_FALSE(t.deserializeValue(f, src.roBuffer(), src.size() + 1));
}

//------------------------------------------------------------------------------
TEST_F(ILBasicIntTagTest, deserializeValue16) {
	std::int16_t v;
	ILBasicIntTag<std::int16_t, 0xFF> t;
	IRBuffer src;
	ILTagFactory f;

	v = 0xAF;
	ASSERT_TRUE(src.writeInt(v));

	ASSERT_TRUE(t.deserializeValue(f, src.roBuffer(), src.size()));
	ASSERT_EQ(v, t.value());

	ASSERT_FALSE(t.deserializeValue(f, src.roBuffer(), src.size() - 1));
	ASSERT_TRUE(src.write(0));
	ASSERT_FALSE(t.deserializeValue(f, src.roBuffer(), src.size() + 1));
}

//------------------------------------------------------------------------------
TEST_F(ILBasicIntTagTest, deserializeValue16u) {
	std::uint16_t v;
	ILBasicIntTag<std::uint16_t, 0xFF> t;
	IRBuffer src;
	ILTagFactory f;

	v = 0xAF;
	ASSERT_TRUE(src.writeInt(v));

	ASSERT_TRUE(t.deserializeValue(f, src.roBuffer(), src.size()));
	ASSERT_EQ(v, t.value());

	ASSERT_FALSE(t.deserializeValue(f, src.roBuffer(), src.size() - 1));
	ASSERT_TRUE(src.write(0));
	ASSERT_FALSE(t.deserializeValue(f, src.roBuffer(), src.size() + 1));
}

//------------------------------------------------------------------------------
TEST_F(ILBasicIntTagTest, deserializeValue32) {
	std::int32_t v;
	ILBasicIntTag<std::int32_t, 0xFF> t;
	IRBuffer src;
	ILTagFactory f;

	v = 0xAF;
	ASSERT_TRUE(src.writeInt(v));

	ASSERT_TRUE(t.deserializeValue(f, src.roBuffer(), src.size()));
	ASSERT_EQ(v, t.value());

	ASSERT_FALSE(t.deserializeValue(f, src.roBuffer(), src.size() - 1));
	ASSERT_TRUE(src.write(0));
	ASSERT_FALSE(t.deserializeValue(f, src.roBuffer(), src.size() + 1));
}

//------------------------------------------------------------------------------
TEST_F(ILBasicIntTagTest, deserializeValue32u) {
	std::uint32_t v;
	ILBasicIntTag<std::uint32_t, 0xFF> t;
	IRBuffer src;
	ILTagFactory f;

	v = 0xAF;
	ASSERT_TRUE(src.writeInt(v));

	ASSERT_TRUE(t.deserializeValue(f, src.roBuffer(), src.size()));
	ASSERT_EQ(v, t.value());

	ASSERT_FALSE(t.deserializeValue(f, src.roBuffer(), src.size() - 1));
	ASSERT_TRUE(src.write(0));
	ASSERT_FALSE(t.deserializeValue(f, src.roBuffer(), src.size() + 1));
}

//------------------------------------------------------------------------------
TEST_F(ILBasicIntTagTest, deserializeValue64) {
	std::int64_t v;
	ILBasicIntTag<std::int64_t, 0xFF> t;
	IRBuffer src;
	ILTagFactory f;

	v = 0xAF;
	ASSERT_TRUE(src.writeInt(v));

	ASSERT_TRUE(t.deserializeValue(f, src.roBuffer(), src.size()));
	ASSERT_EQ(v, t.value());

	ASSERT_FALSE(t.deserializeValue(f, src.roBuffer(), src.size() - 1));
	ASSERT_TRUE(src.write(0));
	ASSERT_FALSE(t.deserializeValue(f, src.roBuffer(), src.size() + 1));
}

//------------------------------------------------------------------------------
TEST_F(ILBasicIntTagTest, deserializeValue64u) {
	std::uint64_t v;
	ILBasicIntTag<std::uint64_t, 0xFF> t;
	IRBuffer src;
	ILTagFactory f;

	v = 0xAF;
	ASSERT_TRUE(src.writeInt(v));

	ASSERT_TRUE(t.deserializeValue(f, src.roBuffer(), src.size()));
	ASSERT_EQ(v, t.value());

	ASSERT_FALSE(t.deserializeValue(f, src.roBuffer(), src.size() - 1));
	ASSERT_TRUE(src.write(0));
	ASSERT_FALSE(t.deserializeValue(f, src.roBuffer(), src.size() + 1));
}

//------------------------------------------------------------------------------

