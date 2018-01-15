/*
 * Copyright (c) 2017, Open Communications Security
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
#include "IRGetVersionTest.h"
#include <irecord/irecord.h>
#include <cstring>

//==============================================================================
// class IRGetVersionTest
//------------------------------------------------------------------------------
IRGetVersionTest::IRGetVersionTest() {
}

//------------------------------------------------------------------------------
IRGetVersionTest::~IRGetVersionTest() {
}

//------------------------------------------------------------------------------
void IRGetVersionTest::SetUp() {
}

//------------------------------------------------------------------------------
void IRGetVersionTest::TearDown() {
}

//------------------------------------------------------------------------------
TEST_F(IRGetVersionTest,IRGetVersion) {
	int retval;
	char version[32];
	int versionSize;

	retval = IRGetVersion(NULL, NULL);
	ASSERT_EQ(IRE_INVALID_PARAM_01, retval);

	retval = IRGetVersion(NULL, version);
	ASSERT_EQ(IRE_INVALID_PARAM_01, retval);

	versionSize = sizeof(version);
	retval = IRGetVersion(&versionSize, NULL);
	ASSERT_EQ(IRE_BUFFER_TOO_SHORT, retval);

	versionSize = 0;
	retval = IRGetVersion(&versionSize, version);
	ASSERT_EQ(IRE_BUFFER_TOO_SHORT, retval);
	ASSERT_LT(0, versionSize);

	versionSize--;
	retval = IRGetVersion(&versionSize, version);
	ASSERT_EQ(IRE_BUFFER_TOO_SHORT, retval);
	ASSERT_LT(0, versionSize);

	versionSize = sizeof(version);
	retval = IRGetVersion(&versionSize, version);
	ASSERT_EQ(IRE_SUCCESS, retval);
	ASSERT_EQ(std::strlen(version) + 1, versionSize);

	// Exact size
	versionSize = 0;
	retval = IRGetVersion(&versionSize, version);
	ASSERT_EQ(IRE_BUFFER_TOO_SHORT, retval);
	ASSERT_GE(sizeof(version), versionSize);
	retval = IRGetVersion(&versionSize, version);
	ASSERT_EQ(IRE_SUCCESS, retval);
	ASSERT_EQ(std::strlen(version) + 1, versionSize);
}

//------------------------------------------------------------------------------
TEST_F(IRGetVersionTest,IRGetVersionInt) {
	int retval;
	int major;
	int minor;

	retval = IRGetVersionInt(NULL, NULL);
	ASSERT_EQ(IRE_GET_INVALID_PARAM(0), retval);

	retval = IRGetVersionInt(&major, NULL);
	ASSERT_EQ(IRE_GET_INVALID_PARAM(1), retval);

	major = -1;
	minor = -1;
	retval = IRGetVersionInt(&major, &minor);
	ASSERT_EQ(IRE_SUCCESS, retval);
	ASSERT_LT(-1, major);
	ASSERT_LT(-1, minor);
}
//------------------------------------------------------------------------------

