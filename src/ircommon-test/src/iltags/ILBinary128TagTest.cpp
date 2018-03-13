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
#include "ILBinary128TagTest.h"
#include "ILBigDecimalTagTest.h"
#include <ircommon/iltagstd.h>
#include <cstring>
using namespace ircommon;
using namespace ircommon::iltags;

//==============================================================================
// class ILBinary128TagTest
//------------------------------------------------------------------------------
ILBinary128TagTest::ILBinary128TagTest() {
}

//------------------------------------------------------------------------------
ILBinary128TagTest::~ILBinary128TagTest() {
}

//------------------------------------------------------------------------------
void ILBinary128TagTest::SetUp() {
}

//------------------------------------------------------------------------------
void ILBinary128TagTest::TearDown() {
}

//------------------------------------------------------------------------------
TEST_F(ILBinary128TagTest,Constructor) {
	ILBinary128Tag * t;

	t = new ILBinary128Tag();
	ASSERT_EQ(ILTag::TAG_BINARY128, t->id());
	ASSERT_EQ(16, t->size());
	delete t;
}

//------------------------------------------------------------------------------
TEST_F(ILBinary128TagTest, serialize) {
	ILBinary128Tag t;
	IRBuffer out;
	IRBuffer exp;
	std::uint8_t buff[16];

	for (unsigned int i = 0; i < sizeof(buff); i++) {
		buff[i] = i;
	}
	ASSERT_TRUE(t.setValue(buff, sizeof(buff)));
	ASSERT_TRUE(t.serialize(out));

	ASSERT_TRUE(exp.writeILInt(ILTag::TAG_BINARY128));
	ASSERT_TRUE(exp.write(buff, sizeof(buff)));

	ASSERT_EQ(exp.size(), out.size());
	ASSERT_EQ(0, std::memcmp(exp.roBuffer(), out.roBuffer(), exp.size()));
}

//------------------------------------------------------------------------------

