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
#include "IRJsonStringTest.h"
#include <ircommon/irjson.h>
using namespace ircommon::json;

//==============================================================================
// class IRJsonStringTest
//------------------------------------------------------------------------------
IRJsonStringTest::IRJsonStringTest() {
}

//------------------------------------------------------------------------------
IRJsonStringTest::~IRJsonStringTest() {
}

//------------------------------------------------------------------------------
void IRJsonStringTest::SetUp() {
}

//------------------------------------------------------------------------------
void IRJsonStringTest::TearDown() {
}

//------------------------------------------------------------------------------
TEST_F(IRJsonStringTest,Constructor) {
	IRJsonString * s;

	s = new IRJsonString();
	ASSERT_EQ(IRJsonValue::STRING, s->type());
	ASSERT_STREQ("", s->get().c_str());
	delete s;

	s = new IRJsonString("value");
	ASSERT_EQ(IRJsonValue::STRING, s->type());
	ASSERT_STREQ("value", s->get().c_str());
	delete s;
}

//------------------------------------------------------------------------------
TEST_F(IRJsonStringTest,getSet) {
	IRJsonString s("value");

	ASSERT_STREQ("value", s.get().c_str());
	s.set("21");
	ASSERT_STREQ("21", s.get().c_str());
}

//------------------------------------------------------------------------------
TEST_F(IRJsonStringTest, as) {
	IRJsonString s("value");

	try{
		s.asBoolean();
		FAIL();
	} catch(std::domain_error & e){}
	try{
		s.asDecimal();
		FAIL();
	} catch(std::domain_error & e){}
	try{
		s.asInteger();
		FAIL();
	} catch(std::domain_error & e){}
	ASSERT_STREQ("value", s.asString().c_str());
}

//------------------------------------------------------------------------------
TEST_F(IRJsonStringTest, equals) {
	IRJsonString a("value");
	IRJsonString b("value");
	IRJsonString c("value2");

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

