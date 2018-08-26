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
TEST_F(IRJsonArrayTest, is) {
	IRJsonArray a;

	ASSERT_TRUE(a.isArray());
	ASSERT_FALSE(a.isBoolean());
	ASSERT_FALSE(a.isDecimal());
	ASSERT_FALSE(a.isInteger());
	ASSERT_FALSE(a.isNull());
	ASSERT_FALSE(a.isObject());
	ASSERT_FALSE(a.isString());
}

//------------------------------------------------------------------------------
TEST_F(IRJsonArrayTest, as) {
	IRJsonArray a;

	try{
		a.asBoolean();
		FAIL();
	} catch(std::domain_error & e){}
	try{
		a.asInteger();
		FAIL();
	} catch(std::domain_error & e){}
	try{
		a.asString();
		FAIL();
	} catch(std::domain_error & e){}
	try{
		a.asDecimal();
		FAIL();
	} catch(std::domain_error & e){}
}

//------------------------------------------------------------------------------
TEST_F(IRJsonArrayTest, appendShared) {
	IRJsonArray a;

	a.append(IRJsonValue::SharedPointer(new IRJsonBoolean()));
	ASSERT_TRUE(a[0]->isBoolean());
	ASSERT_EQ(1, a.size());

	a.append(std::make_shared<IRJsonInteger>());
	ASSERT_TRUE(a[0]->isBoolean());
	ASSERT_TRUE(a[1]->isInteger());
	ASSERT_EQ(2, a.size());

	a.append(std::make_shared<IRJsonDecimal>());
	ASSERT_TRUE(a[0]->isBoolean());
	ASSERT_TRUE(a[1]->isInteger());
	ASSERT_TRUE(a[2]->isDecimal());
	ASSERT_EQ(3, a.size());
}

//------------------------------------------------------------------------------
TEST_F(IRJsonArrayTest, appendPtr) {
	IRJsonArray a;

	a.append(new IRJsonBoolean());
	ASSERT_TRUE(a[0]->isBoolean());
	ASSERT_EQ(1, a.size());

	a.append(new IRJsonInteger());
	ASSERT_TRUE(a[0]->isBoolean());
	ASSERT_TRUE(a[1]->isInteger());
	ASSERT_EQ(2, a.size());

	a.append(new IRJsonDecimal());
	ASSERT_TRUE(a[0]->isBoolean());
	ASSERT_TRUE(a[1]->isInteger());
	ASSERT_TRUE(a[2]->isDecimal());
	ASSERT_EQ(3, a.size());
}

//------------------------------------------------------------------------------
TEST_F(IRJsonArrayTest, insertShared) {
	IRJsonArray a;

	a.insert(0, IRJsonValue::SharedPointer(new IRJsonBoolean()));
	ASSERT_TRUE(a[0]->isBoolean());
	ASSERT_EQ(1, a.size());

	a.insert(0, std::make_shared<IRJsonInteger>());
	ASSERT_TRUE(a[0]->isInteger());
	ASSERT_TRUE(a[1]->isBoolean());
	ASSERT_EQ(2, a.size());

	a.insert(1, std::make_shared<IRJsonDecimal>());
	ASSERT_TRUE(a[0]->isInteger());
	ASSERT_TRUE(a[1]->isDecimal());
	ASSERT_TRUE(a[2]->isBoolean());
	ASSERT_EQ(3, a.size());

	a.insert(3, std::make_shared<IRJsonString>());
	ASSERT_TRUE(a[0]->isInteger());
	ASSERT_TRUE(a[1]->isDecimal());
	ASSERT_TRUE(a[2]->isBoolean());
	ASSERT_TRUE(a[3]->isString());
	ASSERT_EQ(4, a.size());
}

//------------------------------------------------------------------------------
TEST_F(IRJsonArrayTest, insertPtr) {
	IRJsonArray a;

	a.insert(0, new IRJsonBoolean());
	ASSERT_TRUE(a[0]->isBoolean());
	ASSERT_EQ(1, a.size());

	a.insert(0, new IRJsonInteger());
	ASSERT_TRUE(a[0]->isInteger());
	ASSERT_TRUE(a[1]->isBoolean());
	ASSERT_EQ(2, a.size());

	a.insert(1, new IRJsonDecimal());
	ASSERT_TRUE(a[0]->isInteger());
	ASSERT_TRUE(a[1]->isDecimal());
	ASSERT_TRUE(a[2]->isBoolean());
	ASSERT_EQ(3, a.size());

	a.insert(3, new IRJsonString());
	ASSERT_TRUE(a[0]->isInteger());
	ASSERT_TRUE(a[1]->isDecimal());
	ASSERT_TRUE(a[2]->isBoolean());
	ASSERT_TRUE(a[3]->isString());
	ASSERT_EQ(4, a.size());
}

//------------------------------------------------------------------------------
TEST_F(IRJsonArrayTest, size) {
	IRJsonArray a;

	for (int i = 0; i < 10; i++) {
		ASSERT_EQ(i, a.size());
		a.append(new IRJsonBoolean());
		ASSERT_EQ(i + 1, a.size());
	}
}

//------------------------------------------------------------------------------
TEST_F(IRJsonArrayTest, AccessOperatorRW) {
	IRJsonArray a;

	a.append(new IRJsonBoolean());
	a.append(new IRJsonInteger());
	a.append(new IRJsonDecimal());
	ASSERT_TRUE(a[0]->isBoolean());
	ASSERT_TRUE(a[1]->isInteger());
	ASSERT_TRUE(a[2]->isDecimal());

	a[1] = IRJsonValue::SharedPointer(new IRJsonString());
	ASSERT_TRUE(a[0]->isBoolean());
	ASSERT_TRUE(a[1]->isString());
	ASSERT_TRUE(a[2]->isDecimal());
}

//------------------------------------------------------------------------------
TEST_F(IRJsonArrayTest, AccessOperatorRO) {
	IRJsonArray a;
	IRJsonArray & ra = a;

	a.append(new IRJsonBoolean());
	a.append(new IRJsonInteger());
	a.append(new IRJsonDecimal());

	ASSERT_TRUE(ra[0]->isBoolean());
	ASSERT_TRUE(ra[1]->isInteger());
	ASSERT_TRUE(ra[2]->isDecimal());
}

//------------------------------------------------------------------------------
TEST_F(IRJsonArrayTest, Remove) {
	IRJsonArray a;

	a.append(new IRJsonBoolean());
	a.append(new IRJsonInteger());
	a.append(new IRJsonDecimal());
	a.append(new IRJsonString());

	ASSERT_EQ(4, a.size());
	ASSERT_TRUE(a[0]->isBoolean());
	ASSERT_TRUE(a[1]->isInteger());
	ASSERT_TRUE(a[2]->isDecimal());
	ASSERT_TRUE(a[3]->isString());

	a.remove(0);
	ASSERT_EQ(3, a.size());
	ASSERT_TRUE(a[0]->isInteger());
	ASSERT_TRUE(a[1]->isDecimal());
	ASSERT_TRUE(a[2]->isString());

	a.remove(1);
	ASSERT_EQ(2, a.size());
	ASSERT_TRUE(a[0]->isInteger());
	ASSERT_TRUE(a[1]->isString());

	a.remove(1);
	ASSERT_EQ(1, a.size());
	ASSERT_TRUE(a[0]->isInteger());

	a.remove(0);
	ASSERT_EQ(0, a.size());
}

//------------------------------------------------------------------------------
TEST_F(IRJsonArrayTest, Equals) {
	IRJsonArray * a;
	IRJsonArray * b;
	IRJsonArray * c;

	a = IRJsonArrayTest::createArray();
	b = IRJsonArrayTest::createArray();
	c = IRJsonArrayTest::createArray();
	(*c)[4] = IRJsonValue::SharedPointer(new IRJsonArray());

	ASSERT_TRUE(a->equals(*a));
	ASSERT_TRUE(a->equals(*b));
	ASSERT_FALSE(a->equals(*c));

	ASSERT_TRUE((*a) ==(*a));
	ASSERT_TRUE((*a) == (*b));
	ASSERT_FALSE((*a) == (*c));

	delete a;
	delete b;
	delete c;
}
//------------------------------------------------------------------------------


