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
#include "IRBaseType16RawTagTest.h"
#include <irecordcore/irtags.h>
#include <cstring>
#include "../crypto/CryptoSamples.h"

using namespace irecordcore;
using namespace irecordcore::tags;
using namespace ircommon;
using namespace ircommon::iltags;

//==============================================================================
// class IRBaseType16RawTagTest
//------------------------------------------------------------------------------
IRBaseType16RawTagTest::IRBaseType16RawTagTest() {
}

//------------------------------------------------------------------------------
IRBaseType16RawTagTest::~IRBaseType16RawTagTest() {
}

//------------------------------------------------------------------------------
void IRBaseType16RawTagTest::SetUp() {
}

//------------------------------------------------------------------------------
void IRBaseType16RawTagTest::TearDown() {
}

//------------------------------------------------------------------------------
TEST_F(IRBaseType16RawTagTest,Constructor) {
	IRBaseType16RawTag * bt16rt;

	bt16rt = new IRBaseType16RawTag(0xFF, false);
	ASSERT_EQ(0xFF, bt16rt->id());
	ASSERT_FALSE(bt16rt->value().secure());
	delete bt16rt;

	bt16rt = new IRBaseType16RawTag(0xFFFF, true);
	ASSERT_EQ(0xFFFF, bt16rt->id());
	ASSERT_TRUE(bt16rt->value().secure());
	delete bt16rt;
}

//------------------------------------------------------------------------------
TEST_F(IRBaseType16RawTagTest, Size) {
	IRBaseType16RawTag bt16rt(0xFF, false);

	ASSERT_EQ(2, bt16rt.size());
	ASSERT_TRUE(bt16rt.value().write(0));
	ASSERT_EQ(2 + 1, bt16rt.size());
	ASSERT_TRUE(bt16rt.value().setSize(0));
	ASSERT_EQ(2, bt16rt.size());
	ASSERT_TRUE(bt16rt.value().setSize(32));
	ASSERT_EQ(2 + 32, bt16rt.size());
}

//------------------------------------------------------------------------------
TEST_F(IRBaseType16RawTagTest, deserializeValue) {
	IRBaseType16RawTag bt16rt(0xFF, false);
	IRBuffer serialized;
	ILStandardTagFactory f;

	// Empty
	ASSERT_TRUE(serialized.writeInt((std::uint16_t)0xFACA));
	ASSERT_TRUE(bt16rt.deserializeValue(f, serialized.roBuffer(), serialized.size()));
	ASSERT_EQ(0xFACA, bt16rt.value().type());
	ASSERT_EQ(0, bt16rt.value().size());

	// With value
	serialized.setSize(0);
	ASSERT_TRUE(serialized.writeInt((std::uint16_t)0xCACA));
	ASSERT_TRUE(serialized.write(CRYPTOSAMPLES_SAMPLE, sizeof(CRYPTOSAMPLES_SAMPLE)));
	ASSERT_TRUE(bt16rt.deserializeValue(f, serialized.roBuffer(), serialized.size()));
	ASSERT_EQ(0xCACA, bt16rt.value().type());
	ASSERT_EQ(sizeof(CRYPTOSAMPLES_SAMPLE), bt16rt.value().size());
	ASSERT_EQ(0, 
		std::memcmp(bt16rt.value().roBuffer(), CRYPTOSAMPLES_SAMPLE, sizeof(CRYPTOSAMPLES_SAMPLE)));

	// Fail
	serialized.setSize(0);
	ASSERT_FALSE(bt16rt.deserializeValue(f, serialized.roBuffer(), serialized.size()));

	serialized.setSize(1);
	ASSERT_FALSE(bt16rt.deserializeValue(f, serialized.roBuffer(), serialized.size()));
}

/*
//------------------------------------------------------------------------------
TEST_F(IRBaseType16RawTagTest, value) {

	IRBaseType16RawTag bt16rt(0xFF, false);

	bt16rt.value.setType(0x1234);
	ASSERT_EQ(0x1234, bt16rt.value());


}
*/

//------------------------------------------------------------------------------
TEST_F(IRBaseType16RawTagTest, serialize) {
	IRBaseType16RawTag bt16rt(0xFF, false);
	IRBuffer serialized;
	IRBuffer expected;

	// Empty
	ASSERT_TRUE(bt16rt.serialize(serialized));
	ASSERT_TRUE(expected.writeILInt(0xFF));
	ASSERT_TRUE(expected.writeILInt(2));
	ASSERT_TRUE(expected.writeInt((std::uint16_t)0));
	ASSERT_EQ(expected.size(), serialized.size());
	ASSERT_EQ(0,
		std::memcmp(expected.roBuffer(), serialized.roBuffer(), expected.size()));

	// With content
	serialized.setSize(0);
	expected.setSize(0);
	bt16rt.value().setType(0x1234);
	ASSERT_TRUE(bt16rt.value().write(CRYPTOSAMPLES_SAMPLE, sizeof(CRYPTOSAMPLES_SAMPLE)));
	ASSERT_TRUE(bt16rt.serialize(serialized));
	ASSERT_TRUE(expected.writeILInt(0xFF));
	ASSERT_TRUE(expected.writeILInt(2 + sizeof(CRYPTOSAMPLES_SAMPLE)));
	ASSERT_TRUE(expected.writeInt((std::uint16_t)0x1234));
	ASSERT_TRUE(expected.write(CRYPTOSAMPLES_SAMPLE, sizeof(CRYPTOSAMPLES_SAMPLE)));
	ASSERT_EQ(expected.size(), serialized.size());
	ASSERT_EQ(0,
		std::memcmp(expected.roBuffer(), serialized.roBuffer(), expected.size()));
}

//------------------------------------------------------------------------------




