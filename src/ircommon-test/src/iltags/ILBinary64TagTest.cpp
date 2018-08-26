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
#include "ILBinary64TagTest.h"
#include <ircommon/iltagstd.h>
#include <cstring>
using namespace ircommon;
using namespace ircommon::iltags;

//==============================================================================
// class ILBinary64TagTest
//------------------------------------------------------------------------------
ILBinary64TagTest::ILBinary64TagTest() {
}

//------------------------------------------------------------------------------
ILBinary64TagTest::~ILBinary64TagTest() {
}

//------------------------------------------------------------------------------
void ILBinary64TagTest::SetUp() {
}

//------------------------------------------------------------------------------
void ILBinary64TagTest::TearDown() {
}

//------------------------------------------------------------------------------
TEST_F(ILBinary64TagTest,Constructor) {
	ILBinary64Tag * t;

	t = new ILBinary64Tag();
	ASSERT_EQ(ILTag::TAG_BINARY64, t->id());
	ASSERT_EQ(double(0), t->value());
	ASSERT_EQ(sizeof(double), t->size());
	ASSERT_EQ(typeid(double), typeid(t->value()));
	delete t;
}

//------------------------------------------------------------------------------
TEST_F(ILBinary64TagTest, serialize) {
	ILBinary64Tag t;
	IRBuffer out;
	IRBuffer exp;
	double v;

	v = -1.234567l;
	t.setValue(v);
	ASSERT_TRUE(t.serialize(out));

	ASSERT_TRUE(exp.writeILInt(ILTag::TAG_BINARY64));
	ASSERT_TRUE(exp.writeFloat(v));

	ASSERT_EQ(exp.size(), out.size());
	ASSERT_EQ(0, std::memcmp(exp.roBuffer(), out.roBuffer(), exp.size()));
}

//------------------------------------------------------------------------------

