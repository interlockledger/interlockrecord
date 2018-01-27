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

