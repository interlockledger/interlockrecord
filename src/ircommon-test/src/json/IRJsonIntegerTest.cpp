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
#include "IRJsonIntegerTest.h"
#include <ircommon/irjson.h>
using namespace ircommon::json;

//==============================================================================
// class IRJsonIntegerTest
//------------------------------------------------------------------------------
IRJsonIntegerTest::IRJsonIntegerTest() {
}

//------------------------------------------------------------------------------
IRJsonIntegerTest::~IRJsonIntegerTest() {
}

//------------------------------------------------------------------------------
void IRJsonIntegerTest::SetUp() {
}

//------------------------------------------------------------------------------
void IRJsonIntegerTest::TearDown() {
}

//------------------------------------------------------------------------------
TEST_F(IRJsonIntegerTest,Constructor) {
	IRJsonInteger * i;

	i = new IRJsonInteger();
	ASSERT_EQ(IRJsonValue::INTEGER, i->type());
	ASSERT_EQ(0, i->get());
	delete i;

	i = new IRJsonInteger(123456789012ll);
	ASSERT_EQ(IRJsonValue::INTEGER, i->type());
	ASSERT_EQ(123456789012ll, i->get());
	delete i;
}

//------------------------------------------------------------------------------
TEST_F(IRJsonIntegerTest,getSet) {
	IRJsonInteger i;

	ASSERT_EQ(0, i.get());
	i.set(123456789012ll);
	ASSERT_EQ(123456789012ll, i.get());
}

//------------------------------------------------------------------------------
TEST_F(IRJsonIntegerTest, as) {
	IRJsonInteger i;

	try{
		i.asBoolean();
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
	ASSERT_EQ(0, i.asInteger());
}

//------------------------------------------------------------------------------
TEST_F(IRJsonIntegerTest, equals) {
	IRJsonInteger a(1);
	IRJsonInteger b(1);
	IRJsonInteger c(2);

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

