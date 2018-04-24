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
#include "IRBlockSigTagTest.h"
#include <irecordcore/irtags.h>


using namespace irecordcore;
using namespace irecordcore::tags;
using namespace ircommon;
using namespace ircommon::iltags;


//==============================================================================
// class IRBlockSigTagTest
//------------------------------------------------------------------------------
IRBlockSigTagTest::IRBlockSigTagTest() {
}

//------------------------------------------------------------------------------
IRBlockSigTagTest::~IRBlockSigTagTest() {
}

//------------------------------------------------------------------------------
void IRBlockSigTagTest::SetUp() {
}

//------------------------------------------------------------------------------
void IRBlockSigTagTest::TearDown() {
}

//------------------------------------------------------------------------------
TEST_F(IRBlockSigTagTest,Constructor) {

	IRBlockSigTag * bstag;

	bstag = new IRBlockSigTag();
	ASSERT_EQ(TAG_BLOCK_SIG, bstag->id());
	ASSERT_EQ((1 + 2) + (1 + 1 + 2), bstag->size());
	delete bstag;
}

//------------------------------------------------------------------------------
TEST_F(IRBlockSigTagTest, Size) {
	IRBlockSigTag bstag;

	ASSERT_EQ((1 + 2) + (1 + 1 + 2), bstag.size());
	bstag.signature().value().set("SIGNATURE",9);
	ASSERT_EQ((1 + 2) + (1 + 1 + 2) + 9, bstag.size());
}

//------------------------------------------------------------------------------
TEST_F(IRBlockSigTagTest, serialize) {
	IRBlockSigTag bstag;
	IRBuffer serialized;
	IRBuffer expected;
	ILStandardTagFactory f;

	// Empty
	ASSERT_TRUE(bstag.serialize(serialized));

	ASSERT_TRUE(expected.writeILInt(TAG_BLOCK_SIG));
	ASSERT_TRUE(expected.writeILInt((1 + 2) + (1 + 1 + 2)));
	
	ASSERT_TRUE(expected.writeILInt(ircommon::iltags::ILTag::TAG_UINT16));
	ASSERT_TRUE(expected.writeInt((std::uint16_t)0));

	ASSERT_TRUE(expected.writeILInt(TAG_SIG));
	ASSERT_TRUE(expected.writeILInt(2));
	ASSERT_TRUE(expected.writeInt((std::uint16_t)0));

	ASSERT_EQ(serialized.size(), expected.size());
	ASSERT_EQ(0, std::memcmp(serialized.roBuffer(), expected.roBuffer(), expected.size()));
	
	// Non empty
	serialized.setSize(0);
	expected.setSize(0);

	bstag.parentHashType().setValue(0xCACA);
	bstag.signature().value().setType(0xfaca);
	bstag.signature().value().set("SIGNATURE", 9);

	ASSERT_TRUE(bstag.serialize(serialized));

	ASSERT_TRUE(expected.writeILInt(TAG_BLOCK_SIG));
	ASSERT_TRUE(expected.writeILInt((1 + 2) + (1 + 1 + 2 + 9)));

	ASSERT_TRUE(expected.writeILInt(ircommon::iltags::ILTag::TAG_UINT16));
	ASSERT_TRUE(expected.writeInt((std::uint16_t)0xCACA));

	ASSERT_TRUE(expected.writeILInt(TAG_SIG));
	ASSERT_TRUE(expected.writeILInt(2 + 9));
	ASSERT_TRUE(expected.writeInt((std::uint16_t)0xFACA));
	ASSERT_TRUE(expected.write("SIGNATURE", 9));

	ASSERT_EQ(serialized.size(), expected.size());
	ASSERT_EQ(0, std::memcmp(serialized.roBuffer(), expected.roBuffer(), expected.size()));

}


//------------------------------------------------------------------------------
TEST_F(IRBlockSigTagTest, deserializeValue) {
	IRBlockSigTag bstag;
	IRBuffer serialized;
	ILStandardTagFactory f;

	//ILUInt16Tag:
	ASSERT_TRUE(serialized.writeILInt(ILTag::TAG_UINT16));
	ASSERT_TRUE(serialized.writeInt((std::uint16_t)0xCACA));
	
	//IRSigTag:
	//Tag
	ASSERT_TRUE(serialized.writeILInt(IRTagType::TAG_SIG));
	//Size (ULInt)
	ASSERT_TRUE(serialized.writeILInt(2 + 9));
	//Payload (2 bytes) 
	ASSERT_TRUE(serialized.writeInt((std::uint16_t)0xFACA));
	ASSERT_TRUE(serialized.write("SIGNATURE", 9));

	ASSERT_TRUE(bstag.deserializeValue(f, serialized.roBuffer(), serialized.size()));

	ASSERT_EQ(0xCACA, bstag.parentHashType().value());
	ASSERT_EQ(0xFACA, bstag.signature().value().type());
	ASSERT_EQ(9, bstag.signature().value().size());
	ASSERT_EQ(0, std::memcmp(
		bstag.signature().value().roBuffer(), "SIGNATURE", 9));

}



//------------------------------------------------------------------------------
TEST_F(IRBlockSigTagTest, parentHashType) {


}

//------------------------------------------------------------------------------
TEST_F(IRBlockSigTagTest, signature) {


}

