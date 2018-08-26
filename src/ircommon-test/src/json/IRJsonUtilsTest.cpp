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
#include "IRJsonUtilsTest.h"
#include <ircommon/irjson.h>
using namespace ircommon::json;

//==============================================================================
// class IRJsonUtilsTest
//------------------------------------------------------------------------------
IRJsonUtilsTest::IRJsonUtilsTest() {
}

//------------------------------------------------------------------------------
IRJsonUtilsTest::~IRJsonUtilsTest() {
}

//------------------------------------------------------------------------------
void IRJsonUtilsTest::SetUp() {
}

//------------------------------------------------------------------------------
void IRJsonUtilsTest::TearDown() {
}

//------------------------------------------------------------------------------
TEST_F(IRJsonUtilsTest, IRJsonAsArray) {
	IRJsonArray arrayObj;
	IRJsonBoolean boolObj;
	IRJsonDecimal decObj;
	IRJsonInteger intObj;
	IRJsonNull nullObj;
	IRJsonObject objObj;
	IRJsonString strObj;

	try {
		IRJsonAsArray(arrayObj);
	}catch (std::invalid_argument &e){FAIL();}
	try {
		IRJsonAsArray(boolObj);
		FAIL();
	}catch (std::invalid_argument &e){}
	try {
		IRJsonAsArray(decObj);
		FAIL();
	}catch (std::invalid_argument &e){}
	try {
		IRJsonAsArray(intObj);
		FAIL();
	}catch (std::invalid_argument &e){}
	try {
		IRJsonAsArray(nullObj);
		FAIL();
	}catch (std::invalid_argument &e){}
	try {
		IRJsonAsArray(objObj);
		FAIL();
	}catch (std::invalid_argument &e){}
	try {
		IRJsonAsArray(strObj);
		FAIL();
	}catch (std::invalid_argument &e){}
}

//------------------------------------------------------------------------------
TEST_F(IRJsonUtilsTest, IRJsonAsBoolean) {
	IRJsonArray arrayObj;
	IRJsonBoolean boolObj;
	IRJsonDecimal decObj;
	IRJsonInteger intObj;
	IRJsonNull nullObj;
	IRJsonObject objObj;
	IRJsonString strObj;

	try {
		IRJsonAsBoolean(arrayObj);
		FAIL();
	}catch (std::invalid_argument &e){}
	try {
		IRJsonAsBoolean(boolObj);
	}catch (std::invalid_argument &e){FAIL();}
	try {
		IRJsonAsBoolean(decObj);
		FAIL();
	}catch (std::invalid_argument &e){}
	try {
		IRJsonAsBoolean(intObj);
		FAIL();
	}catch (std::invalid_argument &e){}
	try {
		IRJsonAsBoolean(nullObj);
		FAIL();
	}catch (std::invalid_argument &e){}
	try {
		IRJsonAsBoolean(objObj);
		FAIL();
	}catch (std::invalid_argument &e){}
	try {
		IRJsonAsBoolean(strObj);
		FAIL();
	}catch (std::invalid_argument &e){}
}

//------------------------------------------------------------------------------
TEST_F(IRJsonUtilsTest, IRJsonAsDecimal) {
	IRJsonArray arrayObj;
	IRJsonBoolean boolObj;
	IRJsonDecimal decObj;
	IRJsonInteger intObj;
	IRJsonNull nullObj;
	IRJsonObject objObj;
	IRJsonString strObj;

	try {
		IRJsonAsDecimal(arrayObj);
		FAIL();
	}catch (std::invalid_argument &e){}
	try {
		IRJsonAsDecimal(boolObj);
		FAIL();
	}catch (std::invalid_argument &e){}
	try {
		IRJsonAsDecimal(decObj);
	}catch (std::invalid_argument &e){FAIL();}
	try {
		IRJsonAsDecimal(intObj);
		FAIL();
	}catch (std::invalid_argument &e){}
	try {
		IRJsonAsDecimal(nullObj);
		FAIL();
	}catch (std::invalid_argument &e){}
	try {
		IRJsonAsDecimal(objObj);
		FAIL();
	}catch (std::invalid_argument &e){}
	try {
		IRJsonAsDecimal(strObj);
		FAIL();
	}catch (std::invalid_argument &e){}
}

//------------------------------------------------------------------------------
TEST_F(IRJsonUtilsTest, IRJsonAsInteger) {
	IRJsonArray arrayObj;
	IRJsonBoolean boolObj;
	IRJsonDecimal decObj;
	IRJsonInteger intObj;
	IRJsonNull nullObj;
	IRJsonObject objObj;
	IRJsonString strObj;

	try {
		IRJsonAsInteger(arrayObj);
		FAIL();
	}catch (std::invalid_argument &e){}
	try {
		IRJsonAsInteger(boolObj);
		FAIL();
	}catch (std::invalid_argument &e){}
	try {
		IRJsonAsInteger(decObj);
		FAIL();
	}catch (std::invalid_argument &e){}
	try {
		IRJsonAsInteger(intObj);
	}catch (std::invalid_argument &e){FAIL();}
	try {
		IRJsonAsInteger(nullObj);
		FAIL();
	}catch (std::invalid_argument &e){}
	try {
		IRJsonAsInteger(objObj);
		FAIL();
	}catch (std::invalid_argument &e){}
	try {
		IRJsonAsInteger(strObj);
		FAIL();
	}catch (std::invalid_argument &e){}
}

//------------------------------------------------------------------------------
TEST_F(IRJsonUtilsTest, IRJsonAsNull) {
	IRJsonArray arrayObj;
	IRJsonBoolean boolObj;
	IRJsonDecimal decObj;
	IRJsonInteger intObj;
	IRJsonNull nullObj;
	IRJsonObject objObj;
	IRJsonString strObj;

	try {
		IRJsonAsNull(arrayObj);
		FAIL();
	}catch (std::invalid_argument &e){}
	try {
		IRJsonAsNull(boolObj);
		FAIL();
	}catch (std::invalid_argument &e){}
	try {
		IRJsonAsNull(decObj);
		FAIL();
	}catch (std::invalid_argument &e){}
	try {
		IRJsonAsNull(intObj);
		FAIL();
	}catch (std::invalid_argument &e){}
	try {
		IRJsonAsNull(nullObj);
	}catch (std::invalid_argument &e){FAIL();}
	try {
		IRJsonAsNull(objObj);
		FAIL();
	}catch (std::invalid_argument &e){}
	try {
		IRJsonAsNull(strObj);
		FAIL();
	}catch (std::invalid_argument &e){}
}

//------------------------------------------------------------------------------
TEST_F(IRJsonUtilsTest, IRJsonAsObject) {
	IRJsonArray arrayObj;
	IRJsonBoolean boolObj;
	IRJsonDecimal decObj;
	IRJsonInteger intObj;
	IRJsonNull nullObj;
	IRJsonObject objObj;
	IRJsonString strObj;

	try {
		IRJsonAsObject(arrayObj);
		FAIL();
	}catch (std::invalid_argument &e){}
	try {
		IRJsonAsObject(boolObj);
		FAIL();
	}catch (std::invalid_argument &e){}
	try {
		IRJsonAsObject(decObj);
		FAIL();
	}catch (std::invalid_argument &e){}
	try {
		IRJsonAsObject(intObj);
		FAIL();
	}catch (std::invalid_argument &e){}
	try {
		IRJsonAsObject(nullObj);
		FAIL();
	}catch (std::invalid_argument &e){}
	try {
		IRJsonAsObject(objObj);
	}catch (std::invalid_argument &e){FAIL();}
	try {
		IRJsonAsObject(strObj);
		FAIL();
	}catch (std::invalid_argument &e){}
}

//------------------------------------------------------------------------------
TEST_F(IRJsonUtilsTest, IRJsonAsString) {
	IRJsonArray arrayObj;
	IRJsonBoolean boolObj;
	IRJsonDecimal decObj;
	IRJsonInteger intObj;
	IRJsonNull nullObj;
	IRJsonObject objObj;
	IRJsonString strObj;

	try {
		IRJsonAsString(arrayObj);
		FAIL();
	}catch (std::invalid_argument &e){}
	try {
		IRJsonAsString(boolObj);
		FAIL();
	}catch (std::invalid_argument &e){}
	try {
		IRJsonAsString(decObj);
		FAIL();
	}catch (std::invalid_argument &e){}
	try {
		IRJsonAsString(intObj);
		FAIL();
	}catch (std::invalid_argument &e){}
	try {
		IRJsonAsString(nullObj);
		FAIL();
	}catch (std::invalid_argument &e){}
	try {
		IRJsonAsString(objObj);
		FAIL();
	}catch (std::invalid_argument &e){}
	try {
		IRJsonAsString(strObj);
	}catch (std::invalid_argument &e){FAIL();}
}
//------------------------------------------------------------------------------

