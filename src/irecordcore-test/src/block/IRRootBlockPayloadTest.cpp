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
#include "IRRootBlockPayloadTest.h"
#include <irecordcore/irblock.h>

using namespace irecordcore;
using namespace irecordcore::block;

//==============================================================================
// class IRRootBlockPayloadTest
//------------------------------------------------------------------------------
IRRootBlockPayloadTest::IRRootBlockPayloadTest() {
}

//------------------------------------------------------------------------------
IRRootBlockPayloadTest::~IRRootBlockPayloadTest() {
}

//------------------------------------------------------------------------------
void IRRootBlockPayloadTest::SetUp() {
}

//------------------------------------------------------------------------------
void IRRootBlockPayloadTest::TearDown() {
}

//------------------------------------------------------------------------------
TEST_F(IRRootBlockPayloadTest,Constructor) {

	IRRootBlockPayload * rbp;

	rbp = new IRRootBlockPayload();

	ASSERT_EQ(0, rbp->version());
	ASSERT_EQ(0, rbp->networkID());
	ASSERT_EQ(0, rbp->emergencyKey().size());
	ASSERT_EQ(0, rbp->creationTimestamp());
	ASSERT_STREQ("", rbp->friendlyName().c_str());
	ASSERT_STREQ("", rbp->ownerName().c_str());
	ASSERT_STREQ("", rbp->comments().c_str());
	ASSERT_EQ(0, rbp->parentId().size());

	delete rbp;
}
//------------------------------------------------------------------------------

TEST_F(IRRootBlockPayloadTest, version) {
	IRRootBlockPayload rbp;
	const IRRootBlockPayload & crbp = rbp;

	ASSERT_EQ(0, rbp.version());
	ASSERT_EQ(0, crbp.version());
	rbp.setVersion(1);
	ASSERT_EQ(1, rbp.version());
	ASSERT_EQ(1, crbp.version());
}
//------------------------------------------------------------------------------

TEST_F(IRRootBlockPayloadTest, networkID) {
	IRRootBlockPayload rbp;
	const IRRootBlockPayload & crbp = rbp;

	ASSERT_EQ(0, rbp.networkID());
	ASSERT_EQ(0, crbp.networkID());
	rbp.setNetworkID(1);
	ASSERT_EQ(1, rbp.networkID());
	ASSERT_EQ(1, crbp.networkID());
}
//------------------------------------------------------------------------------

TEST_F(IRRootBlockPayloadTest, creationTimestamp) {
	IRRootBlockPayload rbp;
	const IRRootBlockPayload & crbp = rbp;

	ASSERT_EQ(0, rbp.creationTimestamp());
	ASSERT_EQ(0, crbp.creationTimestamp());
	rbp.setCreationTimestamp(1);
	ASSERT_EQ(1, rbp.creationTimestamp());
	ASSERT_EQ(1, crbp.creationTimestamp());
}
//------------------------------------------------------------------------------

TEST_F(IRRootBlockPayloadTest, friendlyName) {
	IRRootBlockPayload rbp;
	const IRRootBlockPayload & crbp = rbp;

	ASSERT_EQ("", rbp.friendlyName());
	ASSERT_EQ("", crbp.friendlyName());
	rbp.setFriendlyName("TEST");
	ASSERT_EQ("TEST", rbp.friendlyName());
	ASSERT_EQ("TEST", crbp.friendlyName());
}
//------------------------------------------------------------------------------

TEST_F(IRRootBlockPayloadTest, ownerName) {
	IRRootBlockPayload rbp;
	const IRRootBlockPayload & crbp = rbp;

	ASSERT_EQ("", rbp.ownerName());
	ASSERT_EQ("", crbp.ownerName());
	rbp.setOwnerName("TEST");
	ASSERT_EQ("TEST", rbp.ownerName());
	ASSERT_EQ("TEST", crbp.ownerName());
}
//------------------------------------------------------------------------------

TEST_F(IRRootBlockPayloadTest, comments) {
	IRRootBlockPayload rbp;
	const IRRootBlockPayload & crbp = rbp;

	ASSERT_EQ("", rbp.comments());
	ASSERT_EQ("", crbp.comments());
	rbp.setComments("TEST");
	ASSERT_EQ("TEST", rbp.comments());
	ASSERT_EQ("TEST", crbp.comments());
}
//------------------------------------------------------------------------------
