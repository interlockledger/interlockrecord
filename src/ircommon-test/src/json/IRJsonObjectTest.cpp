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
#include "IRJsonObjectTest.h"
#include <set>

//==============================================================================
// class IRJsonObjectTest
//------------------------------------------------------------------------------
IRJsonObjectTest::IRJsonObjectTest() {
}

//------------------------------------------------------------------------------
IRJsonObjectTest::~IRJsonObjectTest() {
}

//------------------------------------------------------------------------------
void IRJsonObjectTest::SetUp() {
}

//------------------------------------------------------------------------------
void IRJsonObjectTest::TearDown() {
}

//------------------------------------------------------------------------------
IRJsonObject  * IRJsonObjectTest::createObject() {
	IRJsonObject * o;

	o = new IRJsonObject();
	o->set("array", new IRJsonArray());
	o->set("bool", new IRJsonBoolean(true));
	o->set("int", new IRJsonInteger(1));
	o->set("dec", new IRJsonDecimal(2));
	o->set("null", new IRJsonNull());
	o->set("object", new IRJsonObject());
	o->set("string", new IRJsonString("s"));
	return o;
}

//------------------------------------------------------------------------------
TEST_F(IRJsonObjectTest,createObject) {
	IRJsonObject * o;

	o = IRJsonObjectTest::createObject();
	ASSERT_EQ(IRJsonValue::OBJECT, o->type());
	ASSERT_EQ(7, o->size());
	ASSERT_TRUE((*o)["array"]->isArray());
	ASSERT_EQ(0, IRJsonAsArray(*(*o)["array"]).size());

	ASSERT_TRUE((*o)["bool"]->isBoolean());
	ASSERT_TRUE((*o)["bool"]->asBoolean());

	ASSERT_TRUE((*o)["int"]->isInteger());
	ASSERT_EQ(1, (*o)["int"]->asInteger());

	ASSERT_TRUE((*o)["dec"]->isDecimal());
	ASSERT_EQ(2, (*o)["dec"]->asDecimal());

	ASSERT_TRUE((*o)["null"]->isNull());

	ASSERT_TRUE((*o)["object"]->isObject());
	ASSERT_EQ(0, IRJsonAsObject(*(*o)["object"]).size());

	ASSERT_TRUE((*o)["string"]->isString());
	ASSERT_STREQ("s", (*o)["string"]->asString().c_str());
	delete o;
}


//------------------------------------------------------------------------------
TEST_F(IRJsonObjectTest,Constructor) {
	IRJsonObject * o;

	o = new IRJsonObject();
	ASSERT_EQ(IRJsonValue::OBJECT, o->type());
	ASSERT_EQ(0, o->size());
	delete o;

	o = IRJsonObjectTest::createObject();
	ASSERT_EQ(IRJsonValue::OBJECT, o->type());
	ASSERT_EQ(7, o->size());
	delete o;

	o = IRJsonObjectTest::createObject();
	ASSERT_EQ(IRJsonValue::OBJECT, o->type());
	o->set("obj2", IRJsonObjectTest::createObject());
	ASSERT_EQ(8, o->size());
	delete o;
}

//------------------------------------------------------------------------------
TEST_F(IRJsonObjectTest, is) {
	IRJsonObject o;

	ASSERT_FALSE(o.isArray());
	ASSERT_FALSE(o.isBoolean());
	ASSERT_FALSE(o.isDecimal());
	ASSERT_FALSE(o.isInteger());
	ASSERT_FALSE(o.isNull());
	ASSERT_TRUE(o.isObject());
	ASSERT_FALSE(o.isString());
}

//------------------------------------------------------------------------------
TEST_F(IRJsonObjectTest, as) {
	IRJsonObject o;

	try{
		o.asBoolean();
		FAIL();
	} catch(std::domain_error & e){}
	try{
		o.asInteger();
		FAIL();
	} catch(std::domain_error & e){}
	try{
		o.asString();
		FAIL();
	} catch(std::domain_error & e){}
	try{
		o.asDecimal();
		FAIL();
	} catch(std::domain_error & e){}
}

//------------------------------------------------------------------------------
TEST_F(IRJsonObjectTest, setShared) {
	IRJsonObject o;

	o.set("v1", IRJsonValue::SharedPointer(new IRJsonBoolean()));
	ASSERT_TRUE(o["v1"]->isBoolean());
	ASSERT_EQ(1, o.size());

	o.set("v2", std::make_shared<IRJsonInteger>());
	ASSERT_TRUE(o["v1"]->isBoolean());
	ASSERT_TRUE(o["v2"]->isInteger());
	ASSERT_EQ(2, o.size());

	o.set("v2", std::make_shared<IRJsonDecimal>());
	ASSERT_TRUE(o["v1"]->isBoolean());
	ASSERT_TRUE(o["v2"]->isDecimal());
	ASSERT_EQ(2, o.size());
}

//------------------------------------------------------------------------------
TEST_F(IRJsonObjectTest, setPtr) {
	IRJsonObject o;

	o.set("v1", new IRJsonBoolean());
	ASSERT_TRUE(o["v1"]->isBoolean());
	ASSERT_EQ(1, o.size());

	o.set("v2", new IRJsonInteger());
	ASSERT_TRUE(o["v1"]->isBoolean());
	ASSERT_TRUE(o["v2"]->isInteger());
	ASSERT_EQ(2, o.size());

	o.set("v2", new IRJsonDecimal());
	ASSERT_TRUE(o["v1"]->isBoolean());
	ASSERT_TRUE(o["v2"]->isDecimal());
	ASSERT_EQ(2, o.size());
}

//------------------------------------------------------------------------------
TEST_F(IRJsonObjectTest, contains) {
	IRJsonObject o;

	o.set("v1", new IRJsonBoolean());
	ASSERT_TRUE(o.contains("v1"));
	ASSERT_FALSE(o.contains("v2"));
	ASSERT_FALSE(o.contains("v3"));

	o.set("v2", new IRJsonBoolean());
	ASSERT_TRUE(o.contains("v1"));
	ASSERT_TRUE(o.contains("v2"));
	ASSERT_FALSE(o.contains("v3"));

	o.set("v3", new IRJsonBoolean());
	ASSERT_TRUE(o.contains("v1"));
	ASSERT_TRUE(o.contains("v2"));
	ASSERT_TRUE(o.contains("v3"));
}

//------------------------------------------------------------------------------
TEST_F(IRJsonObjectTest, size) {
	IRJsonObject o;

	ASSERT_EQ(0, o.size());
	o.set("v1", new IRJsonBoolean());
	ASSERT_EQ(1, o.size());

	o.set("v2", new IRJsonBoolean());
	ASSERT_EQ(2, o.size());

	o.set("v3", new IRJsonBoolean());
	ASSERT_EQ(3, o.size());
}

//------------------------------------------------------------------------------
TEST_F(IRJsonObjectTest, AccessOperatorRW) {
	IRJsonObject o;

	o.set("v1", new IRJsonBoolean());
	ASSERT_TRUE(o["v1"]->isBoolean());

	o.set("v2", new IRJsonInteger());
	ASSERT_TRUE(o["v2"]->isInteger());

	o["v1"] = IRJsonValue::SharedPointer(new IRJsonString("s"));
	ASSERT_TRUE(o["v1"]->isString());

	try {
		o["v6"] = IRJsonValue::SharedPointer(new IRJsonString("s"));
		FAIL();
	} catch (std::invalid_argument & e){}
}

//------------------------------------------------------------------------------
TEST_F(IRJsonObjectTest, AccessOperatorR) {
	IRJsonObject o;
	const IRJsonObject & co = o;

	o.set("v1", new IRJsonBoolean());
	ASSERT_TRUE(co["v1"]->isBoolean());

	o.set("v2", new IRJsonInteger());
	ASSERT_TRUE(co["v2"]->isInteger());

	try {
		co["v6"];
		FAIL();
	} catch (std::invalid_argument & e){}
}

//------------------------------------------------------------------------------
TEST_F(IRJsonObjectTest, remove) {
	IRJsonObject o;

	o.set("v1", new IRJsonBoolean());
	o.set("v2", new IRJsonBoolean());
	o.set("v3", new IRJsonBoolean());
	ASSERT_EQ(3, o.size());
	ASSERT_TRUE(o.contains("v1"));
	ASSERT_TRUE(o.contains("v2"));
	ASSERT_TRUE(o.contains("v3"));

	o.remove("v3");
	ASSERT_EQ(2, o.size());
	ASSERT_TRUE(o.contains("v1"));
	ASSERT_TRUE(o.contains("v2"));
	ASSERT_FALSE(o.contains("v3"));
}

//------------------------------------------------------------------------------
TEST_F(IRJsonObjectTest, getAttributeNames) {
	IRJsonObject o;
	IRJsonObject::AttributeList attr;

	o.set("v1", new IRJsonBoolean());
	o.set("v2", new IRJsonBoolean());
	o.set("v3", new IRJsonBoolean());
	ASSERT_EQ(3, o.size());

	o.getAttributeNames(attr);
	ASSERT_EQ(o.size(), attr.size());

	std::set<std::string> attrNames;
	for (auto a = attr.begin(); a != attr.end(); a++) {
		attrNames.insert(*a);
	}
	ASSERT_EQ(attr.size(), attrNames.size());
	ASSERT_TRUE(attrNames.find("v1") != attrNames.end());
	ASSERT_TRUE(attrNames.find("v2") != attrNames.end());
	ASSERT_TRUE(attrNames.find("v3") != attrNames.end());
	ASSERT_FALSE(attrNames.find("v4") != attrNames.end());
}

//------------------------------------------------------------------------------
TEST_F(IRJsonObjectTest, equals) {
	IRJsonObject a;
	IRJsonObject b;
	IRJsonObject c;
	IRJsonObject d;

	a.set("v1", new IRJsonArray());
	a.set("v2", new IRJsonBoolean(true));
	a.set("v3", new IRJsonDecimal(1));
	a.set("v4", new IRJsonInteger(2));
	a.set("v5", new IRJsonNull());
	a.set("v6", IRJsonObjectTest::createObject());
	a.set("v7", new IRJsonString());
	ASSERT_TRUE(a.equals(a));

	b.set("v1", new IRJsonArray());
	b.set("v2", new IRJsonBoolean(true));
	b.set("v3", new IRJsonDecimal(1));
	b.set("v4", new IRJsonInteger(2));
	b.set("v5", new IRJsonNull());
	b.set("v6", IRJsonObjectTest::createObject());
	b.set("v7", new IRJsonString());
	ASSERT_TRUE(a.equals(b));

	c.set("v1", new IRJsonArray());
	c.set("v2", new IRJsonBoolean(true));
	c.set("v3", new IRJsonDecimal(1));
	c.set("v4", new IRJsonInteger(2));
	c.set("v5", new IRJsonNull());
	c.set("v6", IRJsonObjectTest::createObject());
	c.set("v7", new IRJsonString("q"));
	ASSERT_FALSE(a.equals(c));

	d.set("v1", new IRJsonArray());
	d.set("v2", new IRJsonBoolean(true));
	d.set("v3", new IRJsonDecimal(1));
	d.set("v4", new IRJsonInteger(2));
	d.set("v5", new IRJsonNull());
	d.set("v6", IRJsonObjectTest::createObject());
	ASSERT_FALSE(a.equals(d));
}

//------------------------------------------------------------------------------
TEST_F(IRJsonObjectTest, clone) {
	IRJsonObject a;
	IRJsonObject * b;

	a.set("v1", new IRJsonArray());
	a.set("v2", new IRJsonBoolean(true));
	a.set("v3", new IRJsonDecimal(1));
	a.set("v4", new IRJsonInteger(2));
	a.set("v5", new IRJsonNull());
	a.set("v6", IRJsonObjectTest::createObject());
	a.set("v7", new IRJsonString());

	b = (IRJsonObject*)a.clone();
	ASSERT_TRUE(b != nullptr);
	ASSERT_TRUE(&a != b);
	ASSERT_TRUE(a == *b);
	delete b;
}
//------------------------------------------------------------------------------

