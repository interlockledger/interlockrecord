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
#include "IRBlockHeaderTest.h"
#include <irecordcore/irblock.h>

using namespace irecordcore;
using namespace irecordcore::block;

//==============================================================================
// class IRBlockHeaderTest
//------------------------------------------------------------------------------
IRBlockHeaderTest::IRBlockHeaderTest() {
}

//------------------------------------------------------------------------------
IRBlockHeaderTest::~IRBlockHeaderTest() {
}

//------------------------------------------------------------------------------
void IRBlockHeaderTest::SetUp() {
}

//------------------------------------------------------------------------------
void IRBlockHeaderTest::TearDown() {
}

//------------------------------------------------------------------------------
TEST_F(IRBlockHeaderTest,Constructor) {

	IRBlockHeader * bh;

	bh = new IRBlockHeader();

	ASSERT_EQ(0, bh->version());
	ASSERT_EQ(IR_ROOT_RECORD_TYPE, bh->recordType());
	ASSERT_EQ(0, bh->instanceID().size());
	ASSERT_EQ(0, bh->blockSerial());
	ASSERT_EQ(0, bh->blockOffset());
	ASSERT_EQ(0, bh->parentBlockOffset());
	ASSERT_EQ(0, bh->applicationID());
	ASSERT_EQ(0, bh->timestamp());

	delete bh;
}
//------------------------------------------------------------------------------

TEST_F(IRBlockHeaderTest, blockSerial) {
	IRBlockHeader bh;
	const IRBlockHeader & cbh = bh;

	ASSERT_EQ(0, bh.blockSerial());
	ASSERT_EQ(0, cbh.blockSerial());
	bh.setBlockSerial(1);
	ASSERT_EQ(1, bh.blockSerial());
	ASSERT_EQ(1, cbh.blockSerial());
}
//------------------------------------------------------------------------------

TEST_F(IRBlockHeaderTest, blockOffset) {
	IRBlockHeader bo;
	const IRBlockHeader & cbo = bo;

	ASSERT_EQ(0, bo.blockOffset());
	ASSERT_EQ(0, cbo.blockOffset());
	bo.setBlockOffset(1);
	ASSERT_EQ(1, bo.blockOffset());
	ASSERT_EQ(1, cbo.blockOffset());
}
//------------------------------------------------------------------------------

TEST_F(IRBlockHeaderTest, parentBlockOffset) {
	IRBlockHeader pbo;
	const IRBlockHeader & cpbo = pbo;

	ASSERT_EQ(0, pbo.parentBlockOffset());
	ASSERT_EQ(0, cpbo.parentBlockOffset());
	pbo.setParentBlockOffset(1);
	ASSERT_EQ(1, pbo.parentBlockOffset());
	ASSERT_EQ(1, cpbo.parentBlockOffset());
}
//------------------------------------------------------------------------------

TEST_F(IRBlockHeaderTest, applicationID) {
	IRBlockHeader aid;
	const IRBlockHeader & caid = aid;

	ASSERT_EQ(0, aid.applicationID());
	ASSERT_EQ(0, caid.applicationID());
	aid.setApplicationID(1);
	ASSERT_EQ(1, aid.applicationID());
	ASSERT_EQ(1, caid.applicationID());
}
//------------------------------------------------------------------------------

TEST_F(IRBlockHeaderTest, timestamp) {
	IRBlockHeader ts;
	const IRBlockHeader & cts = ts;

	ASSERT_EQ(0, ts.timestamp());
	ASSERT_EQ(0, cts.timestamp());
	ts.setTimestamp(1);
	ASSERT_EQ(1, ts.timestamp());
	ASSERT_EQ(1, cts.timestamp());
}