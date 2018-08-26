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
#include "IRContextDisposeTest.h"
#include <irecord/irecord.h>

//==============================================================================
// class IRContextDisposeTest
//------------------------------------------------------------------------------
IRContextDisposeTest::IRContextDisposeTest() {
}

//------------------------------------------------------------------------------
IRContextDisposeTest::~IRContextDisposeTest() {
}

//------------------------------------------------------------------------------
void IRContextDisposeTest::SetUp() {
}

//------------------------------------------------------------------------------
void IRContextDisposeTest::TearDown() {
}

//------------------------------------------------------------------------------
TEST_F(IRContextDisposeTest, FunctionExits) {
	int retval;

	retval = IRClose(0, 0, 0, 0, NULL, 0, NULL);
	ASSERT_EQ(IRE_NOT_IMPLEMENTED, retval);
	//TODO Implementation required!
	std::cout << "Implementation required!";
}
//------------------------------------------------------------------------------

