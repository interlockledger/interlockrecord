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
#include "IRJsonBooleanTest.h"
#include <ircommon/irjson.h>
using namespace ircommon::json;

//==============================================================================
// class IRJsonBooleanTest
//------------------------------------------------------------------------------
IRJsonBooleanTest::IRJsonBooleanTest() {
}

//------------------------------------------------------------------------------
IRJsonBooleanTest::~IRJsonBooleanTest() {
}

//------------------------------------------------------------------------------
void IRJsonBooleanTest::SetUp() {
}

//------------------------------------------------------------------------------
void IRJsonBooleanTest::TearDown() {
}

//------------------------------------------------------------------------------
TEST_F(IRJsonBooleanTest,Constructor) {
	IRJsonBoolean * i;

	i = new IRJsonBoolean();
	ASSERT_EQ(IRJsonValue::BOOLEAN, i->type());
	ASSERT_FALSE(i->get());
	delete i;

	i = new IRJsonBoolean(false);
	ASSERT_EQ(IRJsonValue::BOOLEAN, i->type());
	ASSERT_FALSE(i->get());
	delete i;

	i = new IRJsonBoolean(true);
	ASSERT_EQ(IRJsonValue::BOOLEAN, i->type());
	ASSERT_TRUE(i->get());
	delete i;
}

//------------------------------------------------------------------------------
TEST_F(IRJsonBooleanTest,getSet) {
	IRJsonBoolean i;

	ASSERT_FALSE(i.get());
	i.set(true);
	ASSERT_TRUE(i.get());
}

//------------------------------------------------------------------------------
TEST_F(IRJsonBooleanTest, as) {
	IRJsonBoolean i;

	try{
		i.asInteger();
		FAIL();
	} catch(std::domain_error & e){}
	try{
		i.asDecimal();
		FAIL();
	} catch(std::domain_error & e){}
	try{
		i.asString();
		FAIL();
	} catch(std::domain_error & e){}
	ASSERT_FALSE(i.asBoolean());
	i.set(true);
	ASSERT_TRUE(i.asBoolean());
}

//------------------------------------------------------------------------------
TEST_F(IRJsonBooleanTest, equals) {
	IRJsonBoolean a(true);
	IRJsonBoolean b(true);
	IRJsonBoolean c(false);

	ASSERT_TRUE(a.equals(a));
	ASSERT_TRUE(a.equals(b));
	ASSERT_FALSE(a.equals(c));

	ASSERT_FALSE(a.equals(IRJsonArray()));
	ASSERT_FALSE(a.equals(IRJsonBoolean()));
	ASSERT_FALSE(a.equals(IRJsonDecimal()));
	ASSERT_FALSE(a.equals(IRJsonInteger()));
	ASSERT_FALSE(a.equals(IRJsonNull()));
	ASSERT_FALSE(a.equals(IRJsonObject()));
	ASSERT_FALSE(a.equals(IRJsonString()));
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------

