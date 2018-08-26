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
#include "IRClosingPayloadTest.h"
#include <irecordcore/irblock.h>

using namespace irecordcore;
using namespace irecordcore::block;

//==============================================================================
// class IRClosingPayloadTest
//------------------------------------------------------------------------------
IRClosingPayloadTest::IRClosingPayloadTest() {
}

//------------------------------------------------------------------------------
IRClosingPayloadTest::~IRClosingPayloadTest() {
}

//------------------------------------------------------------------------------
void IRClosingPayloadTest::SetUp() {
}

//------------------------------------------------------------------------------
void IRClosingPayloadTest::TearDown() {
}

//------------------------------------------------------------------------------
TEST_F(IRClosingPayloadTest,Constructor) {

	IRClosingPayload * cp;

	cp = new IRClosingPayload();

	ASSERT_EQ(0, cp->version());
	ASSERT_FALSE(cp->emergency());
	ASSERT_EQ(0, cp->reason());
	ASSERT_STREQ("", cp->comments().c_str());
	ASSERT_EQ(0, cp->successorId().size());

	delete cp;
}
//------------------------------------------------------------------------------

TEST_F(IRClosingPayloadTest, version) {
	IRClosingPayload cp;
	const IRClosingPayload & ccp = cp;

	ASSERT_EQ(0, cp.version());
	ASSERT_EQ(0, ccp.version());
	cp.setVersion(1);
	ASSERT_EQ(1, cp.version());
	ASSERT_EQ(1, ccp.version());
}
//------------------------------------------------------------------------------

TEST_F(IRClosingPayloadTest, emergency) {
	IRClosingPayload cp;
	const IRClosingPayload & ccp = cp;

	ASSERT_FALSE(cp.emergency());
	ASSERT_FALSE(ccp.emergency());
	cp.setEmergency(true);
	ASSERT_TRUE(cp.emergency());
	ASSERT_TRUE(ccp.emergency());
}
//------------------------------------------------------------------------------

TEST_F(IRClosingPayloadTest, reason) {
	IRClosingPayload cp;
	const IRClosingPayload & ccp = cp;

	ASSERT_EQ(0, cp.reason());
	ASSERT_EQ(0, ccp.reason());
	cp.setReason(1);
	ASSERT_EQ(1, cp.reason());
	ASSERT_EQ(1, ccp.reason());
}
//------------------------------------------------------------------------------

TEST_F(IRClosingPayloadTest, comments) {
	IRClosingPayload cp;
	const IRClosingPayload & ccp = cp;

	ASSERT_EQ("", cp.comments());
	ASSERT_EQ("", ccp.comments());
	cp.setComments("TEST");
	ASSERT_EQ("TEST", cp.comments());
	ASSERT_EQ("TEST", ccp.comments());
}
//------------------------------------------------------------------------------
