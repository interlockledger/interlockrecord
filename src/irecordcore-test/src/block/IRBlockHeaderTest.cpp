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

TEST_F(IRBlockHeaderTest, version) {
	IRBlockHeader bh;
	const IRBlockHeader & cbh = bh;

	ASSERT_EQ(0, bh.version());
	ASSERT_EQ(0, cbh.version());
	bh.setVersion(1);
	ASSERT_EQ(1, bh.version());
	ASSERT_EQ(1, cbh.version());
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
