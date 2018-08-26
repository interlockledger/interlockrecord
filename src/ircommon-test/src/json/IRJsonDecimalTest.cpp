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
#include "IRJsonDecimalTest.h"
#include <ircommon/irjson.h>
using namespace ircommon::json;

//==============================================================================
// class IRJsonDecimalTest
//------------------------------------------------------------------------------
IRJsonDecimalTest::IRJsonDecimalTest() {
}

//------------------------------------------------------------------------------
IRJsonDecimalTest::~IRJsonDecimalTest() {
}

//------------------------------------------------------------------------------
void IRJsonDecimalTest::SetUp() {
}

//------------------------------------------------------------------------------
void IRJsonDecimalTest::TearDown() {
}

//------------------------------------------------------------------------------
TEST_F(IRJsonDecimalTest,Constructor) {
	IRJsonDecimal * i;

	i = new IRJsonDecimal();
	ASSERT_EQ(IRJsonValue::DECIMAL, i->type());
	ASSERT_EQ(0, i->get());
	delete i;

	i = new IRJsonDecimal(1.2);
	ASSERT_EQ(IRJsonValue::DECIMAL, i->type());
	ASSERT_EQ(1.2, i->get());
	delete i;
}

//------------------------------------------------------------------------------
TEST_F(IRJsonDecimalTest,getSet) {
	IRJsonDecimal i;

	ASSERT_EQ(0, i.get());
	i.set(1.2);
	ASSERT_EQ(1.2, i.get());
}

//------------------------------------------------------------------------------
TEST_F(IRJsonDecimalTest, as) {
	IRJsonDecimal i;

	try{
		i.asBoolean();
		FAIL();
	} catch(std::domain_error & e){}
	try{
		i.asInteger();
		FAIL();
	} catch(std::domain_error & e){}
	try{
		i.asString();
		FAIL();
	} catch(std::domain_error & e){}
	ASSERT_EQ(0, i.asDecimal());
}

//------------------------------------------------------------------------------
TEST_F(IRJsonDecimalTest, equals) {
	IRJsonDecimal a(1.1);
	IRJsonDecimal b(1.1);
	IRJsonDecimal c(1.2);

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
//------------------------------------------------------------------------------

