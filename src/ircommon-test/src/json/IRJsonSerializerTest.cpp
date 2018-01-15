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

