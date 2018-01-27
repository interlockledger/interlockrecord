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
#include "ILBasicFloatTagTest.h"
#include <ircommon/iltagstd.h>
#include <cstring>
using namespace ircommon;
using namespace ircommon::iltags;

//==============================================================================
// class ILBasicFloatTagTest
//------------------------------------------------------------------------------
ILBasicFloatTagTest::ILBasicFloatTagTest() {
}

//------------------------------------------------------------------------------
ILBasicFloatTagTest::~ILBasicFloatTagTest() {
}

//------------------------------------------------------------------------------
void ILBasicFloatTagTest::SetUp() {
}

//------------------------------------------------------------------------------
void ILBasicFloatTagTest::TearDown() {
}

//------------------------------------------------------------------------------
TEST_F(ILBasicFloatTagTest,Constructor) {

	auto f = new ILBasicFloatTag<float, 0xFF>();
	ASSERT_EQ(0xFF, f->id());
	ASSERT_EQ(typeid(float), typeid(f->value()));
	ASSERT_EQ(sizeof(float), f->size());
	ASSERT_EQ(0, f->value());
	delete f;

	auto d = new ILBasicFloatTag<double, 0xFE>();
	ASSERT_EQ(0xFE, d->id());
	ASSERT_EQ(typeid(double), typeid(d->value()));
	ASSERT_EQ(sizeof(double), d->size());
	ASSERT_EQ(0, d->value());
	delete d;
}

//------------------------------------------------------------------------------
TEST_F(ILBasicFloatTagTest, size) {

	ILBasicFloatTag<float, 0xFF> f;
	ASSERT_EQ(sizeof(float), f.size());

	ILBasicFloatTag<double, 0xFE> d;
	ASSERT_EQ(sizeof(double), d.size());
}

//------------------------------------------------------------------------------
TEST_F(ILBasicFloatTagTest, getSetValue) {


	ILBasicFloatTag<float, 0xFF> f;
	ASSERT_EQ(0, f.value());
	float fv = 1.2345;
	f.setValue(fv);
	ASSERT_EQ(fv, f.value());
	fv = -1.2345;
	f.setValue(fv);
	ASSERT_EQ(fv, f.value());

	ILBasicFloatTag<double, 0xFF> d;
	ASSERT_EQ(0, d.value());
	double dv = 1.2345l;
	d.setValue(dv);
	ASSERT_EQ(dv, d.value());
	dv = -1.2345l;
	d.setValue(dv);
	ASSERT_EQ(dv, d.value());
}

//------------------------------------------------------------------------------
TEST_F(ILBasicFloatTagTest, serializeFloat) {
	float v;
	ILBasicFloatTag<float, 0xFF> t;
	IRBuffer out;
	IRBuffer exp;

	v = 1.2345;
	t.setValue(v);
	ASSERT_TRUE(t.serialize(out));

	ASSERT_TRUE(exp.writeILInt(0xFF));
	ASSERT_TRUE(exp.writeILInt(sizeof(v)));
	ASSERT_TRUE(exp.writeFloat(v));

	ASSERT_EQ(exp.size(), out.size());
	ASSERT_EQ(0, std::memcmp(exp.roBuffer(), out.roBuffer(), exp.size()));
}

//------------------------------------------------------------------------------
TEST_F(ILBasicFloatTagTest, serializeDouble) {
	double v;
	ILBasicFloatTag<double, 0xFF> t;
	IRBuffer out;
	IRBuffer exp;

	v = 1.2345l;
	t.setValue(v);
	ASSERT_TRUE(t.serialize(out));

	ASSERT_TRUE(exp.writeILInt(0xFF));
	ASSERT_TRUE(exp.writeILInt(sizeof(v)));
	ASSERT_TRUE(exp.writeFloat(v));

	ASSERT_EQ(exp.size(), out.size());
	ASSERT_EQ(0, std::memcmp(exp.roBuffer(), out.roBuffer(), exp.size()));
}

//------------------------------------------------------------------------------
TEST_F(ILBasicFloatTagTest, deserializeValueFloat) {
	float v;
	ILBasicFloatTag<float, 0xFF> t;
	ILTagFactory f;
	IRBuffer src;

	v = 1.2345;
	ASSERT_TRUE(src.writeFloat(v));

	ASSERT_TRUE(t.deserializeValue(f, src.roBuffer(), src.size()));
	ASSERT_EQ(v, t.value());

	ASSERT_FALSE(t.deserializeValue(f, src.roBuffer(), src.size() - 1));
	ASSERT_TRUE(src.write(0));
	ASSERT_FALSE(t.deserializeValue(f, src.roBuffer(), src.size()));
}

//------------------------------------------------------------------------------
TEST_F(ILBasicFloatTagTest, deserializeValueDouble) {
	double v;
	ILBasicFloatTag<double, 0xFF> t;
	ILTagFactory f;
	IRBuffer src;

	v = 1.2345l;
	ASSERT_TRUE(src.writeFloat(v));

	ASSERT_TRUE(t.deserializeValue(f, src.roBuffer(), src.size()));
	ASSERT_EQ(v, t.value());

	ASSERT_FALSE(t.deserializeValue(f, src.roBuffer(), src.size() - 1));
	ASSERT_TRUE(src.write(0));
	ASSERT_FALSE(t.deserializeValue(f, src.roBuffer(), src.size()));
}

//------------------------------------------------------------------------------


