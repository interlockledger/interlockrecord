/*
 * Copyright (c) 2017-2018 InterlockLedger Network
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
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


