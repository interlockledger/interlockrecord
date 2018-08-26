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
#include "IRJsonValueTest.h"
#include <ircommon/irjson.h>
using namespace ircommon::json;

#define IRJsonValueTest_TYPES_SIZE 7
static IRJsonValue::JsonType
	IRJsonValueTest_TYPES[IRJsonValueTest_TYPES_SIZE] = {
		IRJsonValue::NULL_VALUE,
		IRJsonValue::STRING,
		IRJsonValue::BOOLEAN,
		IRJsonValue::INTEGER,
		IRJsonValue::DECIMAL,
		IRJsonValue::OBJECT,
		IRJsonValue::ARRAY};


//==============================================================================
// class IRJsonValueTest
//------------------------------------------------------------------------------
IRJsonValueTest::IRJsonValueTest() {
}

//------------------------------------------------------------------------------
IRJsonValueTest::~IRJsonValueTest() {
}

//------------------------------------------------------------------------------
void IRJsonValueTest::SetUp() {
}

//------------------------------------------------------------------------------
void IRJsonValueTest::TearDown() {
}

//------------------------------------------------------------------------------
TEST_F(IRJsonValueTest, Constructor) {
	IRJsonValue * v;

	v = new IRJsonValue(IRJsonValue::ARRAY);
	ASSERT_EQ(IRJsonValue::ARRAY, v->type());
	delete v;

	v = new IRJsonValue(IRJsonValue::BOOLEAN);
	ASSERT_EQ(IRJsonValue::BOOLEAN, v->type());
	delete v;

	v = new IRJsonValue(IRJsonValue::DECIMAL);
	ASSERT_EQ(IRJsonValue::DECIMAL, v->type());
	delete v;

	v = new IRJsonValue(IRJsonValue::INTEGER);
	ASSERT_EQ(IRJsonValue::INTEGER, v->type());
	delete v;

	v = new IRJsonValue(IRJsonValue::NULL_VALUE);
	ASSERT_EQ(IRJsonValue::NULL_VALUE, v->type());
	delete v;

	v = new IRJsonValue(IRJsonValue::OBJECT);
	ASSERT_EQ(IRJsonValue::OBJECT, v->type());
	delete v;

	v = new IRJsonValue(IRJsonValue::STRING);
	ASSERT_EQ(IRJsonValue::STRING, v->type());
	delete v;
}

//------------------------------------------------------------------------------
TEST_F(IRJsonValueTest, is) {
	IRJsonValue * v;

	v = new IRJsonValue(IRJsonValue::ARRAY);
	ASSERT_TRUE(v->isArray());
	ASSERT_FALSE(v->isBoolean());
	ASSERT_FALSE(v->isDecimal());
	ASSERT_FALSE(v->isInteger());
	ASSERT_FALSE(v->isNull());
	ASSERT_FALSE(v->isObject());
	ASSERT_FALSE(v->isString());
	delete v;

	v = new IRJsonValue(IRJsonValue::BOOLEAN);
	ASSERT_FALSE(v->isArray());
	ASSERT_TRUE(v->isBoolean());
	ASSERT_FALSE(v->isDecimal());
	ASSERT_FALSE(v->isInteger());
	ASSERT_FALSE(v->isNull());
	ASSERT_FALSE(v->isObject());
	ASSERT_FALSE(v->isString());
	delete v;

	v = new IRJsonValue(IRJsonValue::DECIMAL);
	ASSERT_FALSE(v->isArray());
	ASSERT_FALSE(v->isBoolean());
	ASSERT_TRUE(v->isDecimal());
	ASSERT_FALSE(v->isInteger());
	ASSERT_FALSE(v->isNull());
	ASSERT_FALSE(v->isObject());
	ASSERT_FALSE(v->isString());
	delete v;

	v = new IRJsonValue(IRJsonValue::INTEGER);
	ASSERT_FALSE(v->isArray());
	ASSERT_FALSE(v->isBoolean());
	ASSERT_FALSE(v->isDecimal());
	ASSERT_TRUE(v->isInteger());
	ASSERT_FALSE(v->isNull());
	ASSERT_FALSE(v->isObject());
	ASSERT_FALSE(v->isString());
	delete v;

	v = new IRJsonValue(IRJsonValue::NULL_VALUE);
	ASSERT_FALSE(v->isArray());
	ASSERT_FALSE(v->isBoolean());
	ASSERT_FALSE(v->isDecimal());
	ASSERT_FALSE(v->isInteger());
	ASSERT_TRUE(v->isNull());
	ASSERT_FALSE(v->isObject());
	ASSERT_FALSE(v->isString());
	delete v;

	v = new IRJsonValue(IRJsonValue::OBJECT);
	ASSERT_FALSE(v->isArray());
	ASSERT_FALSE(v->isBoolean());
	ASSERT_FALSE(v->isDecimal());
	ASSERT_FALSE(v->isInteger());
	ASSERT_FALSE(v->isNull());
	ASSERT_TRUE(v->isObject());
	ASSERT_FALSE(v->isString());
	delete v;

	v = new IRJsonValue(IRJsonValue::STRING);
	ASSERT_FALSE(v->isArray());
	ASSERT_FALSE(v->isBoolean());
	ASSERT_FALSE(v->isDecimal());
	ASSERT_FALSE(v->isInteger());
	ASSERT_FALSE(v->isNull());
	ASSERT_FALSE(v->isObject());
	ASSERT_TRUE(v->isString());
	delete v;
}

//------------------------------------------------------------------------------
TEST_F(IRJsonValueTest, equals) {
	IRJsonValue * a;
	IRJsonValue * b;

	for (int i = 0; i < IRJsonValueTest_TYPES_SIZE; i++) {
		a = new IRJsonValue(IRJsonValueTest_TYPES[i]);
		for (int j = 0; j < IRJsonValueTest_TYPES_SIZE; j++) {
			b = new IRJsonValue(IRJsonValueTest_TYPES[j]);
			if (i == j) {
				ASSERT_TRUE(a->equals(*b));
			} else {
				ASSERT_FALSE(a->equals(*b));
			}
			delete b;
		}
		delete a;
	}
}

//------------------------------------------------------------------------------
TEST_F(IRJsonValueTest, asBoolean) {
	IRJsonValue * v;

	for (int i = 0; i < IRJsonValueTest_TYPES_SIZE; i++) {
		v = new IRJsonValue(IRJsonValueTest_TYPES[i]);
		try {
			v->asBoolean();
			FAIL();
		} catch (std::domain_error & e){}
		delete v;
	}
}

//------------------------------------------------------------------------------
TEST_F(IRJsonValueTest, asDecimal) {
	IRJsonValue * v;

	for (int i = 0; i < IRJsonValueTest_TYPES_SIZE; i++) {
		v = new IRJsonValue(IRJsonValueTest_TYPES[i]);
		try {
			v->asDecimal();
			FAIL();
		} catch (std::domain_error & e){}
		delete v;
	}
}

//------------------------------------------------------------------------------
TEST_F(IRJsonValueTest, asInteger) {
	IRJsonValue * v;

	for (int i = 0; i < IRJsonValueTest_TYPES_SIZE; i++) {
		v = new IRJsonValue(IRJsonValueTest_TYPES[i]);
		try {
			v->asInteger();
			FAIL();
		} catch (std::domain_error & e){}
		delete v;
	}
}

//------------------------------------------------------------------------------
TEST_F(IRJsonValueTest, asString) {
	IRJsonValue * v;

	for (int i = 0; i < IRJsonValueTest_TYPES_SIZE; i++) {
		v = new IRJsonValue(IRJsonValueTest_TYPES[i]);
		try {
			v->asString();
			FAIL();
		} catch (std::domain_error & e){}
		delete v;
	}
}

//------------------------------------------------------------------------------

