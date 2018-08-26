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
#include "IRRecordTypeTest.h"
#include <irecordcore/irblock.h>
using namespace irecordcore::block;

//==============================================================================
// class IRRecordTypeTest
//------------------------------------------------------------------------------
IRRecordTypeTest::IRRecordTypeTest() {
}

//------------------------------------------------------------------------------
IRRecordTypeTest::~IRRecordTypeTest() {
}

//------------------------------------------------------------------------------
void IRRecordTypeTest::SetUp() {
}

//------------------------------------------------------------------------------
void IRRecordTypeTest::TearDown() {
}

//------------------------------------------------------------------------------
TEST_F(IRRecordTypeTest,Constructor) {

	ASSERT_EQ(0, IR_ROOT_RECORD_TYPE);
	ASSERT_EQ(1, IR_DATA_RECORD_TYPE);
	ASSERT_EQ(2, IR_CLOSING_RECORD_TYPE);
	ASSERT_EQ(3, IR_EMERGENCY_CLOSING_RECORD_TYPE);

}

//------------------------------------------------------------------------------
