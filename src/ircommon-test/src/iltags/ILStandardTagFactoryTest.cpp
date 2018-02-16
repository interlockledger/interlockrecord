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
#include "ILStandardTagFactoryTest.h"
#include "ILStringTagTest.h"
#include <ircommon/iltag.h>
#include <ircommon/iltagstd.h>
#include <cstring>
using namespace ircommon;
using namespace ircommon::iltags;

//==============================================================================
// class ILStandardTagFactoryTest
//------------------------------------------------------------------------------
ILStandardTagFactoryTest::ILStandardTagFactoryTest() {
}

//------------------------------------------------------------------------------
ILStandardTagFactoryTest::~ILStandardTagFactoryTest() {
}

//------------------------------------------------------------------------------
void ILStandardTagFactoryTest::SetUp() {
}

//------------------------------------------------------------------------------
void ILStandardTagFactoryTest::TearDown() {
}

//------------------------------------------------------------------------------
TEST_F(ILStandardTagFactoryTest, Constructor) {
	ILStandardTagFactory * f;

	f = new ILStandardTagFactory();
	ASSERT_FALSE(f->secure());
	ASSERT_FALSE(f->strictMode());
	delete f;

	f = new ILStandardTagFactory(false);
	ASSERT_FALSE(f->secure());
	ASSERT_FALSE(f->strictMode());
	delete f;

	f = new ILStandardTagFactory(true);
	ASSERT_TRUE(f->secure());
	ASSERT_FALSE(f->strictMode());
	delete f;

	f = new ILStandardTagFactory(false, false);
	ASSERT_FALSE(f->secure());
	ASSERT_FALSE(f->strictMode());
	delete f;

	f = new ILStandardTagFactory(false, true);
	ASSERT_FALSE(f->secure());
	ASSERT_TRUE(f->strictMode());
	delete f;

	f = new ILStandardTagFactory(true, false);
	ASSERT_TRUE(f->secure());
	ASSERT_FALSE(f->strictMode());
	delete f;

	f = new ILStandardTagFactory(true, true);
	ASSERT_TRUE(f->secure());
	ASSERT_TRUE(f->strictMode());
	delete f;
}

//------------------------------------------------------------------------------
TEST_F(ILStandardTagFactoryTest, createFalseFalse) {
	ILStandardTagFactory f(false, false);
	ILTag * t;

	t = f.create(ILTag::TAG_NULL);
	ASSERT_TRUE(t != nullptr);
	ASSERT_EQ(typeid(ILNullTag), typeid(*t));
	delete t;

	t = f.create(ILTag::TAG_BOOL);
	ASSERT_TRUE(t != nullptr);
	ASSERT_EQ(typeid(ILBoolTag), typeid(*t));
	delete t;

	t = f.create(ILTag::TAG_INT8);
	ASSERT_TRUE(t != nullptr);
	ASSERT_EQ(typeid(ILInt8Tag), typeid(*t));
	delete t;

	t = f.create(ILTag::TAG_UINT8);
	ASSERT_TRUE(t != nullptr);
	ASSERT_EQ(typeid(ILUInt8Tag), typeid(*t));
	delete t;

	t = f.create(ILTag::TAG_INT16);
	ASSERT_TRUE(t != nullptr);
	ASSERT_EQ(typeid(ILInt16Tag), typeid(*t));
	delete t;

	t = f.create(ILTag::TAG_UINT16);
	ASSERT_TRUE(t != nullptr);
	ASSERT_EQ(typeid(ILUInt16Tag), typeid(*t));
	delete t;

	t = f.create(ILTag::TAG_INT32);
	ASSERT_TRUE(t != nullptr);
	ASSERT_EQ(typeid(ILInt32Tag), typeid(*t));
	delete t;

	t = f.create(ILTag::TAG_UINT32);
	ASSERT_TRUE(t != nullptr);
	ASSERT_EQ(typeid(ILUInt32Tag), typeid(*t));
	delete t;

	t = f.create(ILTag::TAG_INT64);
	ASSERT_TRUE(t != nullptr);
	ASSERT_EQ(typeid(ILInt64Tag), typeid(*t));
	delete t;

	t = f.create(ILTag::TAG_UINT64);
	ASSERT_TRUE(t != nullptr);
	ASSERT_EQ(typeid(ILUInt64Tag), typeid(*t));
	delete t;

	t = f.create(ILTag::TAG_ILINT64);
	ASSERT_TRUE(t != nullptr);
	ASSERT_EQ(typeid(ILILIntTag), typeid(*t));
	delete t;

	t = f.create(ILTag::TAG_BINARY32);
	ASSERT_TRUE(t != nullptr);
	ASSERT_EQ(typeid(ILBinary32Tag), typeid(*t));
	delete t;

	t = f.create(ILTag::TAG_BINARY64);
	ASSERT_TRUE(t != nullptr);
	ASSERT_EQ(typeid(ILBinary64Tag), typeid(*t));
	delete t;

	t = f.create(ILTag::TAG_BINARY128);
	ASSERT_TRUE(t != nullptr);
	ASSERT_EQ(typeid(ILBinary128Tag), typeid(*t));
	delete t;

	t = f.create(ILTag::TAG_BYTE_ARRAY);
	ASSERT_TRUE(t != nullptr);
	ASSERT_EQ(typeid(ILByteArrayTag), typeid(*t));
	ASSERT_FALSE(static_cast<ILByteArrayTag*>(t)->secure());
	delete t;

	t = f.create(ILTag::TAG_STRING);
	ASSERT_TRUE(t != nullptr);
	ASSERT_EQ(typeid(ILStringTag), typeid(*t));
	delete t;

	t = f.create(ILTag::TAG_BINT);
	ASSERT_TRUE(t != nullptr);
	ASSERT_EQ(typeid(ILBigIntTag), typeid(*t));
	ASSERT_FALSE(static_cast<ILBigIntTag*>(t)->secure());
	delete t;

	t = f.create(ILTag::TAG_BDEC);
	ASSERT_TRUE(t != nullptr);
	ASSERT_EQ(typeid(ILBigDecimalTag), typeid(*t));
	ASSERT_FALSE(static_cast<ILBigDecimalTag*>(t)->integral().secure());
	delete t;

	t = f.create(ILTag::TAG_ILINT64_ARRAY);
	ASSERT_TRUE(t != nullptr);
	ASSERT_EQ(typeid(ILILIntArrayTag), typeid(*t));
	delete t;

	t = f.create(ILTag::TAG_ILTAG_ARRAY);
	ASSERT_TRUE(t != nullptr);
	ASSERT_EQ(typeid(ILTagArrayTag), typeid(*t));
	delete t;

	t = f.create(ILTag::TAG_ILTAG_SEQ);
	ASSERT_TRUE(t != nullptr);
	ASSERT_EQ(typeid(ILTagSeqTag), typeid(*t));
	delete t;

	// Reserved tags
	t = f.create(14);
	ASSERT_TRUE(t != nullptr);
	ASSERT_EQ(typeid(ILRawTag), typeid(*t));
	ASSERT_FALSE(static_cast<ILRawTag*>(t)->secure());
	delete t;

	t = f.create(15);
	ASSERT_TRUE(t != nullptr);
	ASSERT_EQ(typeid(ILRawTag), typeid(*t));
	ASSERT_FALSE(static_cast<ILRawTag*>(t)->secure());
	delete t;

	for (int i = 23; i < 32; i++) {
		t = f.create(i);
		ASSERT_TRUE(t != nullptr);
		ASSERT_EQ(typeid(ILRawTag), typeid(*t));
		ASSERT_FALSE(static_cast<ILRawTag*>(t)->secure());
		delete t;
	}

	// Other tags
	for (int i = 32; i < 256; i++) {
		t = f.create(i);
		ASSERT_TRUE(t != nullptr);
		ASSERT_EQ(typeid(ILRawTag), typeid(*t));
		ASSERT_FALSE(static_cast<ILRawTag*>(t)->secure());
		delete t;
	}
}

//------------------------------------------------------------------------------
TEST_F(ILStandardTagFactoryTest, createTrueFalse) {
	ILStandardTagFactory f(true, false);
	ILTag * t;

	t = f.create(ILTag::TAG_NULL);
	ASSERT_TRUE(t != nullptr);
	ASSERT_EQ(typeid(ILNullTag), typeid(*t));
	delete t;

	t = f.create(ILTag::TAG_BOOL);
	ASSERT_TRUE(t != nullptr);
	ASSERT_EQ(typeid(ILBoolTag), typeid(*t));
	delete t;

	t = f.create(ILTag::TAG_INT8);
	ASSERT_TRUE(t != nullptr);
	ASSERT_EQ(typeid(ILInt8Tag), typeid(*t));
	delete t;

	t = f.create(ILTag::TAG_UINT8);
	ASSERT_TRUE(t != nullptr);
	ASSERT_EQ(typeid(ILUInt8Tag), typeid(*t));
	delete t;

	t = f.create(ILTag::TAG_INT16);
	ASSERT_TRUE(t != nullptr);
	ASSERT_EQ(typeid(ILInt16Tag), typeid(*t));
	delete t;

	t = f.create(ILTag::TAG_UINT16);
	ASSERT_TRUE(t != nullptr);
	ASSERT_EQ(typeid(ILUInt16Tag), typeid(*t));
	delete t;

	t = f.create(ILTag::TAG_INT32);
	ASSERT_TRUE(t != nullptr);
	ASSERT_EQ(typeid(ILInt32Tag), typeid(*t));
	delete t;

	t = f.create(ILTag::TAG_UINT32);
	ASSERT_TRUE(t != nullptr);
	ASSERT_EQ(typeid(ILUInt32Tag), typeid(*t));
	delete t;

	t = f.create(ILTag::TAG_INT64);
	ASSERT_TRUE(t != nullptr);
	ASSERT_EQ(typeid(ILInt64Tag), typeid(*t));
	delete t;

	t = f.create(ILTag::TAG_UINT64);
	ASSERT_TRUE(t != nullptr);
	ASSERT_EQ(typeid(ILUInt64Tag), typeid(*t));
	delete t;

	t = f.create(ILTag::TAG_ILINT64);
	ASSERT_TRUE(t != nullptr);
	ASSERT_EQ(typeid(ILILIntTag), typeid(*t));
	delete t;

	t = f.create(ILTag::TAG_BINARY32);
	ASSERT_TRUE(t != nullptr);
	ASSERT_EQ(typeid(ILBinary32Tag), typeid(*t));
	delete t;

	t = f.create(ILTag::TAG_BINARY64);
	ASSERT_TRUE(t != nullptr);
	ASSERT_EQ(typeid(ILBinary64Tag), typeid(*t));
	delete t;

	t = f.create(ILTag::TAG_BINARY128);
	ASSERT_TRUE(t != nullptr);
	ASSERT_EQ(typeid(ILBinary128Tag), typeid(*t));
	delete t;

	t = f.create(ILTag::TAG_BYTE_ARRAY);
	ASSERT_TRUE(t != nullptr);
	ASSERT_EQ(typeid(ILByteArrayTag), typeid(*t));
	ASSERT_TRUE(static_cast<ILByteArrayTag*>(t)->secure());
	delete t;

	t = f.create(ILTag::TAG_STRING);
	ASSERT_TRUE(t != nullptr);
	ASSERT_EQ(typeid(ILStringTag), typeid(*t));
	delete t;

	t = f.create(ILTag::TAG_BINT);
	ASSERT_TRUE(t != nullptr);
	ASSERT_EQ(typeid(ILBigIntTag), typeid(*t));
	ASSERT_TRUE(static_cast<ILBigIntTag*>(t)->secure());
	delete t;

	t = f.create(ILTag::TAG_BDEC);
	ASSERT_TRUE(t != nullptr);
	ASSERT_EQ(typeid(ILBigDecimalTag), typeid(*t));
	ASSERT_TRUE(static_cast<ILBigDecimalTag*>(t)->integral().secure());
	delete t;

	t = f.create(ILTag::TAG_ILINT64_ARRAY);
	ASSERT_TRUE(t != nullptr);
	ASSERT_EQ(typeid(ILILIntArrayTag), typeid(*t));
	delete t;

	t = f.create(ILTag::TAG_ILTAG_ARRAY);
	ASSERT_TRUE(t != nullptr);
	ASSERT_EQ(typeid(ILTagArrayTag), typeid(*t));
	delete t;

	t = f.create(ILTag::TAG_ILTAG_SEQ);
	ASSERT_TRUE(t != nullptr);
	ASSERT_EQ(typeid(ILTagSeqTag), typeid(*t));
	delete t;

	// Reserved tags
	t = f.create(14);
	ASSERT_TRUE(t != nullptr);
	ASSERT_EQ(typeid(ILRawTag), typeid(*t));
	ASSERT_TRUE(static_cast<ILRawTag*>(t)->secure());
	delete t;

	t = f.create(15);
	ASSERT_TRUE(t != nullptr);
	ASSERT_EQ(typeid(ILRawTag), typeid(*t));
	ASSERT_TRUE(static_cast<ILRawTag*>(t)->secure());
	delete t;

	for (int i = 23; i < 32; i++) {
		t = f.create(i);
		ASSERT_TRUE(t != nullptr);
		ASSERT_EQ(typeid(ILRawTag), typeid(*t));
		ASSERT_TRUE(static_cast<ILRawTag*>(t)->secure());
		delete t;
	}

	// Other tags
	for (int i = 32; i < 256; i++) {
		t = f.create(i);
		ASSERT_TRUE(t != nullptr);
		ASSERT_EQ(typeid(ILRawTag), typeid(*t));
		ASSERT_TRUE(static_cast<ILRawTag*>(t)->secure());
		delete t;
	}
}

//------------------------------------------------------------------------------
TEST_F(ILStandardTagFactoryTest, createFalseTrue) {
	ILStandardTagFactory f(false, true);
	ILTag * t;

	t = f.create(ILTag::TAG_NULL);
	ASSERT_TRUE(t != nullptr);
	ASSERT_EQ(typeid(ILNullTag), typeid(*t));
	delete t;

	t = f.create(ILTag::TAG_BOOL);
	ASSERT_TRUE(t != nullptr);
	ASSERT_EQ(typeid(ILBoolTag), typeid(*t));
	delete t;

	t = f.create(ILTag::TAG_INT8);
	ASSERT_TRUE(t != nullptr);
	ASSERT_EQ(typeid(ILInt8Tag), typeid(*t));
	delete t;

	t = f.create(ILTag::TAG_UINT8);
	ASSERT_TRUE(t != nullptr);
	ASSERT_EQ(typeid(ILUInt8Tag), typeid(*t));
	delete t;

	t = f.create(ILTag::TAG_INT16);
	ASSERT_TRUE(t != nullptr);
	ASSERT_EQ(typeid(ILInt16Tag), typeid(*t));
	delete t;

	t = f.create(ILTag::TAG_UINT16);
	ASSERT_TRUE(t != nullptr);
	ASSERT_EQ(typeid(ILUInt16Tag), typeid(*t));
	delete t;

	t = f.create(ILTag::TAG_INT32);
	ASSERT_TRUE(t != nullptr);
	ASSERT_EQ(typeid(ILInt32Tag), typeid(*t));
	delete t;

	t = f.create(ILTag::TAG_UINT32);
	ASSERT_TRUE(t != nullptr);
	ASSERT_EQ(typeid(ILUInt32Tag), typeid(*t));
	delete t;

	t = f.create(ILTag::TAG_INT64);
	ASSERT_TRUE(t != nullptr);
	ASSERT_EQ(typeid(ILInt64Tag), typeid(*t));
	delete t;

	t = f.create(ILTag::TAG_UINT64);
	ASSERT_TRUE(t != nullptr);
	ASSERT_EQ(typeid(ILUInt64Tag), typeid(*t));
	delete t;

	t = f.create(ILTag::TAG_ILINT64);
	ASSERT_TRUE(t != nullptr);
	ASSERT_EQ(typeid(ILILIntTag), typeid(*t));
	delete t;

	t = f.create(ILTag::TAG_BINARY32);
	ASSERT_TRUE(t != nullptr);
	ASSERT_EQ(typeid(ILBinary32Tag), typeid(*t));
	delete t;

	t = f.create(ILTag::TAG_BINARY64);
	ASSERT_TRUE(t != nullptr);
	ASSERT_EQ(typeid(ILBinary64Tag), typeid(*t));
	delete t;

	t = f.create(ILTag::TAG_BINARY128);
	ASSERT_TRUE(t != nullptr);
	ASSERT_EQ(typeid(ILBinary128Tag), typeid(*t));
	delete t;

	t = f.create(ILTag::TAG_BYTE_ARRAY);
	ASSERT_TRUE(t != nullptr);
	ASSERT_EQ(typeid(ILByteArrayTag), typeid(*t));
	ASSERT_FALSE(static_cast<ILByteArrayTag*>(t)->secure());
	delete t;

	t = f.create(ILTag::TAG_STRING);
	ASSERT_TRUE(t != nullptr);
	ASSERT_EQ(typeid(ILStringTag), typeid(*t));
	delete t;

	t = f.create(ILTag::TAG_BINT);
	ASSERT_TRUE(t != nullptr);
	ASSERT_EQ(typeid(ILBigIntTag), typeid(*t));
	ASSERT_FALSE(static_cast<ILBigIntTag*>(t)->secure());
	delete t;

	t = f.create(ILTag::TAG_BDEC);
	ASSERT_TRUE(t != nullptr);
	ASSERT_EQ(typeid(ILBigDecimalTag), typeid(*t));
	ASSERT_FALSE(static_cast<ILBigDecimalTag*>(t)->integral().secure());
	delete t;

	t = f.create(ILTag::TAG_ILINT64_ARRAY);
	ASSERT_TRUE(t != nullptr);
	ASSERT_EQ(typeid(ILILIntArrayTag), typeid(*t));
	delete t;

	t = f.create(ILTag::TAG_ILTAG_ARRAY);
	ASSERT_TRUE(t != nullptr);
	ASSERT_EQ(typeid(ILTagArrayTag), typeid(*t));
	delete t;

	t = f.create(ILTag::TAG_ILTAG_SEQ);
	ASSERT_TRUE(t != nullptr);
	ASSERT_EQ(typeid(ILTagSeqTag), typeid(*t));
	delete t;

	// Reserved tags
	t = f.create(14);
	ASSERT_TRUE(t == nullptr);

	t = f.create(15);
	ASSERT_TRUE(t == nullptr);

	for (int i = 23; i < 32; i++) {
		t = f.create(i);
		ASSERT_TRUE(t == nullptr);
	}

	// Other tags
	for (int i = 32; i < 256; i++) {
		t = f.create(i);
		ASSERT_TRUE(t == nullptr);
	}
}

//------------------------------------------------------------------------------
TEST_F(ILStandardTagFactoryTest, createTrueTrue) {
	ILStandardTagFactory f(true, true);
	ILTag * t;

	t = f.create(ILTag::TAG_NULL);
	ASSERT_TRUE(t != nullptr);
	ASSERT_EQ(typeid(ILNullTag), typeid(*t));
	delete t;

	t = f.create(ILTag::TAG_BOOL);
	ASSERT_TRUE(t != nullptr);
	ASSERT_EQ(typeid(ILBoolTag), typeid(*t));
	delete t;

	t = f.create(ILTag::TAG_INT8);
	ASSERT_TRUE(t != nullptr);
	ASSERT_EQ(typeid(ILInt8Tag), typeid(*t));
	delete t;

	t = f.create(ILTag::TAG_UINT8);
	ASSERT_TRUE(t != nullptr);
	ASSERT_EQ(typeid(ILUInt8Tag), typeid(*t));
	delete t;

	t = f.create(ILTag::TAG_INT16);
	ASSERT_TRUE(t != nullptr);
	ASSERT_EQ(typeid(ILInt16Tag), typeid(*t));
	delete t;

	t = f.create(ILTag::TAG_UINT16);
	ASSERT_TRUE(t != nullptr);
	ASSERT_EQ(typeid(ILUInt16Tag), typeid(*t));
	delete t;

	t = f.create(ILTag::TAG_INT32);
	ASSERT_TRUE(t != nullptr);
	ASSERT_EQ(typeid(ILInt32Tag), typeid(*t));
	delete t;

	t = f.create(ILTag::TAG_UINT32);
	ASSERT_TRUE(t != nullptr);
	ASSERT_EQ(typeid(ILUInt32Tag), typeid(*t));
	delete t;

	t = f.create(ILTag::TAG_INT64);
	ASSERT_TRUE(t != nullptr);
	ASSERT_EQ(typeid(ILInt64Tag), typeid(*t));
	delete t;

	t = f.create(ILTag::TAG_UINT64);
	ASSERT_TRUE(t != nullptr);
	ASSERT_EQ(typeid(ILUInt64Tag), typeid(*t));
	delete t;

	t = f.create(ILTag::TAG_ILINT64);
	ASSERT_TRUE(t != nullptr);
	ASSERT_EQ(typeid(ILILIntTag), typeid(*t));
	delete t;

	t = f.create(ILTag::TAG_BINARY32);
	ASSERT_TRUE(t != nullptr);
	ASSERT_EQ(typeid(ILBinary32Tag), typeid(*t));
	delete t;

	t = f.create(ILTag::TAG_BINARY64);
	ASSERT_TRUE(t != nullptr);
	ASSERT_EQ(typeid(ILBinary64Tag), typeid(*t));
	delete t;

	t = f.create(ILTag::TAG_BINARY128);
	ASSERT_TRUE(t != nullptr);
	ASSERT_EQ(typeid(ILBinary128Tag), typeid(*t));
	delete t;

	t = f.create(ILTag::TAG_BYTE_ARRAY);
	ASSERT_TRUE(t != nullptr);
	ASSERT_EQ(typeid(ILByteArrayTag), typeid(*t));
	ASSERT_TRUE(static_cast<ILByteArrayTag*>(t)->secure());
	delete t;

	t = f.create(ILTag::TAG_STRING);
	ASSERT_TRUE(t != nullptr);
	ASSERT_EQ(typeid(ILStringTag), typeid(*t));
	delete t;

	t = f.create(ILTag::TAG_BINT);
	ASSERT_TRUE(t != nullptr);
	ASSERT_EQ(typeid(ILBigIntTag), typeid(*t));
	ASSERT_TRUE(static_cast<ILBigIntTag*>(t)->secure());
	delete t;

	t = f.create(ILTag::TAG_BDEC);
	ASSERT_TRUE(t != nullptr);
	ASSERT_EQ(typeid(ILBigDecimalTag), typeid(*t));
	ASSERT_TRUE(static_cast<ILBigDecimalTag*>(t)->integral().secure());
	delete t;

	t = f.create(ILTag::TAG_ILINT64_ARRAY);
	ASSERT_TRUE(t != nullptr);
	ASSERT_EQ(typeid(ILILIntArrayTag), typeid(*t));
	delete t;

	t = f.create(ILTag::TAG_ILTAG_ARRAY);
	ASSERT_TRUE(t != nullptr);
	ASSERT_EQ(typeid(ILTagArrayTag), typeid(*t));
	delete t;

	t = f.create(ILTag::TAG_ILTAG_SEQ);
	ASSERT_TRUE(t != nullptr);
	ASSERT_EQ(typeid(ILTagSeqTag), typeid(*t));
	delete t;

	// Reserved tags
	t = f.create(14);
	ASSERT_TRUE(t == nullptr);

	t = f.create(15);
	ASSERT_TRUE(t == nullptr);

	for (int i = 23; i < 32; i++) {
		t = f.create(i);
		ASSERT_TRUE(t == nullptr);
	}

	// Other tags
	for (int i = 32; i < 256; i++) {
		t = f.create(i);
		ASSERT_TRUE(t == nullptr);
	}
}
//------------------------------------------------------------------------------

