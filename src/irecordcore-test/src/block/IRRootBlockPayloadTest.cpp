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