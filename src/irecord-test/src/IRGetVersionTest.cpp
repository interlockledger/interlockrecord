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

