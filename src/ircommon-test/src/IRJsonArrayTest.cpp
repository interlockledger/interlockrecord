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
#include "IRJsonArrayTest.h"
#include "IRJsonObjectTest.h"

//==============================================================================
// class IRJsonArrayTest
//------------------------------------------------------------------------------
IRJsonArrayTest::IRJsonArrayTest() {
}

//------------------------------------------------------------------------------
IRJsonArrayTest::~IRJsonArrayTest() {
}

//------------------------------------------------------------------------------
void IRJsonArrayTest::SetUp() {
}

//------------------------------------------------------------------------------
void IRJsonArrayTest::TearDown() {
}

//------------------------------------------------------------------------------
IRJsonArray * IRJsonArrayTest::createArray() {
	IRJsonArray * a;

	a = new IRJsonArray();
	a->append(new IRJsonArray());
	a->append(new IRJsonBoolean(true));
	a->append(new IRJsonInteger(1));
	a->append(new IRJsonDecimal(2));
	a->append(new IRJsonNull());
	a->append(new IRJsonObject());
	a->append(new IRJsonString("s"));
	return a;
}

//------------------------------------------------------------------------------
TEST_F(IRJsonArrayTest,createArray) {
	IRJsonArray * a;

	a = IRJsonArrayTest::createArray();
	ASSERT_EQ(7, a->size());

	ASSERT_TRUE((*a)[0]->isArray());
	ASSERT_EQ(0, IRJsonAsArray(*(*a)[0]).size());

	ASSERT_TRUE((*a)[1]->isBoolean());
	ASSERT_TRUE((*a)[1]->asBoolean());

	ASSERT_TRUE((*a)[2]->isInteger());
	ASSERT_EQ(1, (*a)[2]->asInteger());

	ASSERT_TRUE((*a)[3]->isDecimal());
	ASSERT_EQ(2, (*a)[3]->asDecimal());

	ASSERT_TRUE((*a)[4]->isNull());

	ASSERT_TRUE((*a)[5]->isObject());
	ASSERT_EQ(0, IRJsonAsObject(*((*a)[5])).size());

	ASSERT_TRUE((*a)[6]->isString());
	ASSERT_STREQ("s", (*a)[6]->asString().c_str());
	delete a;
}


//------------------------------------------------------------------------------
TEST_F(IRJsonArrayTest,Constructor) {
	IRJsonArray * a;

	a = new IRJsonArray();
	ASSERT_EQ(IRJsonValue::ARRAY, a->type());
	delete a;

	a = IRJsonArrayTest::createArray();
	ASSERT_EQ(IRJsonValue::ARRAY, a->type());
	ASSERT_EQ(7, a->size());
	delete a;

	a = IRJsonArrayTest::createArray();
	ASSERT_EQ(IRJsonValue::ARRAY, a->type());
	a->append(IRJsonArrayTest::createArray());
	ASSERT_EQ(8, a->size());
	delete a;

}
//------------------------------------------------------------------------------

