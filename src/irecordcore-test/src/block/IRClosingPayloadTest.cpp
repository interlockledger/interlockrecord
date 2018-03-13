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