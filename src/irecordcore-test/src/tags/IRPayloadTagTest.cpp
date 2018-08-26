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
#include "IRPayloadTagTest.h"
#include <irecordcore/irtags.h>

using namespace irecordcore;
using namespace irecordcore::tags;

//==============================================================================
// class IRPayloadTagTest
//------------------------------------------------------------------------------
IRPayloadTagTest::IRPayloadTagTest() {
}

//------------------------------------------------------------------------------
IRPayloadTagTest::~IRPayloadTagTest() {
}

//------------------------------------------------------------------------------
void IRPayloadTagTest::SetUp() {
}

//------------------------------------------------------------------------------
void IRPayloadTagTest::TearDown() {
}

//------------------------------------------------------------------------------
TEST_F(IRPayloadTagTest,Constructor) {

	IRPayloadTag * ptag;

	ptag = new IRPayloadTag();
	ASSERT_NE(TAG_HASH, ptag->id());
	ASSERT_EQ(TAG_PAYLOAD, ptag->id());

	delete ptag;

}
//------------------------------------------------------------------------------

