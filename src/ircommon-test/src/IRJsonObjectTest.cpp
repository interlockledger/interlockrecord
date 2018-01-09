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
	o->set("bool", new IRJsonBoolean(true));
	o->set("int", new IRJsonInteger(1));
	o->set("dec", new IRJsonDecimal(2));
	o->set("null", new IRJsonNull());
	return o;
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
	ASSERT_EQ(4, o->size());
	delete o;

	o = IRJsonObjectTest::createObject();
	ASSERT_EQ(IRJsonValue::OBJECT, o->type());
	o->set("obj2", IRJsonObjectTest::createObject());
	ASSERT_EQ(5, o->size());
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

