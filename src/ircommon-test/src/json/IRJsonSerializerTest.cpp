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
#include "IRJsonSerializerTest.h"

//==============================================================================
// class IRJsonSerializerTest
//------------------------------------------------------------------------------
IRJsonSerializerTest::IRJsonSerializerTest() {
}

//------------------------------------------------------------------------------
IRJsonSerializerTest::~IRJsonSerializerTest() {
}

//------------------------------------------------------------------------------
void IRJsonSerializerTest::SetUp() {
}

//------------------------------------------------------------------------------
void IRJsonSerializerTest::TearDown() {
}

//------------------------------------------------------------------------------
IRJsonObject * IRJsonSerializerTest::createComplexObject() {
	IRJsonSerializer s;
	IRJsonObject * o;
	IRJsonArray * a;

	o = IRJsonObjectTest::createObject();
	o->set("object", IRJsonObjectTest::createObject());
	o->set("array", IRJsonArrayTest::createArray());
	a = IRJsonArrayTest::createArray();
	a->append(IRJsonObjectTest::createObject());
	o->set("complexArray", a);

	return o;
}

//------------------------------------------------------------------------------
TEST_F(IRJsonSerializerTest,Constructor) {
	IRJsonSerializer * s;

	s = new IRJsonSerializer();
	ASSERT_FALSE(s->indent());
	delete s;

	s = new IRJsonSerializer(false);
	ASSERT_FALSE(s->indent());
	delete s;

	s = new IRJsonSerializer(true);
	ASSERT_TRUE(s->indent());
	delete s;
}

//------------------------------------------------------------------------------
TEST_F(IRJsonSerializerTest, SerializeUnindented) {
	IRJsonSerializer s;
	IRJsonObject * o;
	std::string out;

	out.clear();
	o = new IRJsonObject();
	s.serialize(*o, out);
	delete o;
	ASSERT_STREQ("{}",
			out.c_str());

	out.clear();
	o = IRJsonObjectTest::createObject();
	s.serialize(*o, out);
	delete o;
	ASSERT_STREQ("{\"array\":[],\"bool\":true,\"dec\":2.000000,\"int\":1,\"null"
			"\":null,\"object\":{},\"string\":\"s\"}",
			out.c_str());

	out.clear();
	o = IRJsonSerializerTest::createComplexObject();
	s.serialize(*o, out);
	delete o;
	ASSERT_STREQ("{\"array\":[[],true,1,2.000000,null,{},\"s\"],\"bool\":true,"
			"\"complexArray\":[[],true,1,2.000000,null,{},\"s\",{\"array\":[],"
			"\"bool\":true,\"dec\":2.000000,\"int\":1,\"null\":null,\"object\""
			":{},\"string\":\"s\"}],\"dec\":2.000000,\"int\":1,\"null\":null,"
			"\"object\":{\"array\":[],\"bool\":true,\"dec\":2.000000,\"int\":1,"
			"\"null\":null,\"object\":{},\"string\":\"s\"},\"string\":\"s\"}",
			out.c_str());
}

//------------------------------------------------------------------------------
TEST_F(IRJsonSerializerTest, SerializeIndented) {
	IRJsonSerializer s(true);
	IRJsonObject * o;
	std::string out;

	out.clear();
	o = new IRJsonObject();
	s.serialize(*o, out);
	delete o;
	ASSERT_STREQ("{\n}",
			out.c_str());

	out.clear();
	o = IRJsonObjectTest::createObject();
	s.serialize(*o, out);
	delete o;
	ASSERT_STREQ(
			"{\n"
			"\t\"array\":[\n"
			"\t\t],\n"
			"\t\"bool\":true,\n"
			"\t\"dec\":2.000000,\n"
			"\t\"int\":1,\n"
			"\t\"null\":null,\n"
			"\t\"object\":{\n"
			"\t\t},\n"
			"\t\"string\":\"s\"\n"
			"}"	,out.c_str());

	out.clear();
	o = IRJsonSerializerTest::createComplexObject();
	s.serialize(*o, out);
	delete o;
	ASSERT_STREQ("{\n"
			"\t\"array\":[\n"
			"\t\t\t[\n"
			"\t\t\t],\n"
			"\t\t\ttrue,\n"
			"\t\t\t1,\n"
			"\t\t\t2.000000,\n"
			"\t\t\tnull,\n"
			"\t\t\t{\n"
			"\t\t\t},\n"
			"\t\t\t\"s\"\n"
			"\t\t],\n"
			"\t\"bool\":true,\n"
			"\t\"complexArray\":[\n"
			"\t\t\t[\n"
			"\t\t\t],\n"
			"\t\t\ttrue,\n"
			"\t\t\t1,\n"
			"\t\t\t2.000000,\n"
			"\t\t\tnull,\n"
			"\t\t\t{\n"
			"\t\t\t},\n"
			"\t\t\t\"s\",\n"
			"\t\t\t{\n"
			"\t\t\t\t\"array\":[\n"
			"\t\t\t\t\t],\n"
			"\t\t\t\t\"bool\":true,\n"
			"\t\t\t\t\"dec\":2.000000,\n"
			"\t\t\t\t\"int\":1,\n"
			"\t\t\t\t\"null\":null,\n"
			"\t\t\t\t\"object\":{\n"
			"\t\t\t\t\t},\n"
			"\t\t\t\t\"string\":\"s\"\n"
			"\t\t\t}\n"
			"\t\t],\n"
			"\t\"dec\":2.000000,\n"
			"\t\"int\":1,\n"
			"\t\"null\":null,\n"
			"\t\"object\":{\n"
			"\t\t\t\"array\":[\n"
			"\t\t\t\t],\n"
			"\t\t\t\"bool\":true,\n"
			"\t\t\t\"dec\":2.000000,\n"
			"\t\t\t\"int\":1,\n"
			"\t\t\t\"null\":null,\n"
			"\t\t\t\"object\":{\n"
			"\t\t\t\t},\n"
			"\t\t\t\"string\":\"s\"\n"
			"\t\t},\n"
			"\t\"string\":\"s\"\n"
			"}", out.c_str());
}
//------------------------------------------------------------------------------

