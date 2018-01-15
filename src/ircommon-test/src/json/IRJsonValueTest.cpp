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

