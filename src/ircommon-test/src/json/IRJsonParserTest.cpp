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
#include "IRJsonParserTest.h"
#include "IRJsonSerializerTest.h"
#include <ircommon/irjson.h>
using namespace ircommon::json;

//==============================================================================
// class IRJsonParserTest
//------------------------------------------------------------------------------
IRJsonParserTest::IRJsonParserTest() {
}

//------------------------------------------------------------------------------
IRJsonParserTest::~IRJsonParserTest() {
}

//------------------------------------------------------------------------------
void IRJsonParserTest::SetUp() {
}

//------------------------------------------------------------------------------
void IRJsonParserTest::TearDown() {
}

//------------------------------------------------------------------------------
TEST_F(IRJsonParserTest,Constructor) {
	IRJsonParser * p;

	p = new IRJsonParser(new IRJsonStringTokenizer(""));
	ASSERT_FALSE(p->hasMore());
	delete p;

	p = new IRJsonParser(new IRJsonStringTokenizer("123456"));
	ASSERT_TRUE(p->hasMore());
	delete p;
}

//------------------------------------------------------------------------------
TEST_F(IRJsonParserTest, hasMore) {
	IRJsonParser p0(new IRJsonStringTokenizer(""));
	IRJsonParser p1(new IRJsonStringTokenizer("1234"));

	ASSERT_FALSE(p0.hasMore());
	ASSERT_TRUE(p1.hasMore());
}

//------------------------------------------------------------------------------
TEST_F(IRJsonParserTest, reset) {
	IRJsonParser p0(new IRJsonStringTokenizer(""));
	IRJsonParser p1(new IRJsonStringTokenizer("{}"));
	IRJsonObject * o;

	ASSERT_FALSE(p0.hasMore());
	ASSERT_TRUE(p0.reset());

	ASSERT_TRUE(p1.hasMore());
	o = p1.parseObject();
	ASSERT_TRUE(o != NULL);
	ASSERT_FALSE(p1.hasMore());
	delete o;
	ASSERT_TRUE(p1.reset());
	ASSERT_TRUE(p1.hasMore());
	o = p1.parseObject();
	ASSERT_TRUE(o != NULL);
	ASSERT_FALSE(p1.hasMore());
}

//------------------------------------------------------------------------------
TEST_F(IRJsonParserTest, ParseEmptyString) {
	IRJsonParser p(new IRJsonStringTokenizer(""));
	IRJsonObject * o;

	ASSERT_FALSE(p.hasMore());
	o = p.parseObject();
	ASSERT_TRUE(o == nullptr);
}

//------------------------------------------------------------------------------
TEST_F(IRJsonParserTest, ParseEmptyObject) {
	IRJsonParser p(new IRJsonStringTokenizer("{}"));
	IRJsonObject * o;

	o = p.parseObject();
	ASSERT_TRUE(o != nullptr);
	ASSERT_EQ(0, o->size());
	delete o;
}

//------------------------------------------------------------------------------
TEST_F(IRJsonParserTest, ParseMultipleObject) {
	IRJsonParser p(new IRJsonStringTokenizer("{}{}"));
	IRJsonObject * o;

	o = p.parseObject();
	ASSERT_TRUE(o != nullptr);
	ASSERT_EQ(0, o->size());
	delete o;

	o = p.parseObject();
	ASSERT_TRUE(o != nullptr);
	ASSERT_EQ(0, o->size());
	delete o;

	o = p.parseObject();
	ASSERT_TRUE(o == nullptr);
}

//------------------------------------------------------------------------------
TEST_F(IRJsonParserTest, Parse1) {
	IRJsonSerializer s(false);
	std::string serialized;
	IRJsonObject * src;
	IRJsonObject * dst;

	src = IRJsonSerializerTest::createComplexObject();
	s.serialize(*src, serialized);

	IRJsonParser p(new IRJsonStringTokenizer(serialized));
	dst = p.parseObject();
	ASSERT_TRUE(dst != nullptr);
	ASSERT_TRUE(src->equals(*dst));
	delete src;
	delete dst;
}

//------------------------------------------------------------------------------
TEST_F(IRJsonParserTest, Parse2) {
	IRJsonSerializer s(true);
	std::string serialized;
	IRJsonObject * src;
	IRJsonObject * dst;

	src = IRJsonSerializerTest::createComplexObject();
	s.serialize(*src, serialized);

	IRJsonParser p(new IRJsonStringTokenizer(serialized));
	dst = p.parseObject();
	ASSERT_TRUE(dst != nullptr);
	ASSERT_TRUE(src->equals(*dst));
	delete src;
	delete dst;
}

//------------------------------------------------------------------------------
TEST_F(IRJsonParserTest, ParseExampleRFC) {
	IRJsonObject * dst;

	IRJsonParser p(new IRJsonStringTokenizer(
			"/* Example from RFC7159 */\n"
			"{\n"
			"   \"Image\": {\n"
			"      \"Width\":  800,\n"
			"      \"Height\": 600,\n"
			"      \"Title\":  \"View from 15th Floor\",\n"
			"      // A single line comment\n"
			"      \"Thumbnail\": {\n"
			"         \"Url\":    \"http://www.example.com/image/481989943\",\n"
			"         \"Height\": 125.0,\n"
			"         \"Width\":  100.0E0\n"
			"         },\n"
			"      \"Animated\" : false,\n"
			"      \"IDs\": [116, 943, null, true]\n"
			"   }\n"
			"}\n"));
	dst = p.parseObject();
	ASSERT_TRUE(dst != nullptr);

	ASSERT_TRUE(dst->isObject());

	ASSERT_TRUE((*dst)["Image"]->isObject());
	const IRJsonObject & imageObj = IRJsonAsObject(*(*dst)["Image"]);
	ASSERT_EQ(6, imageObj.size());

	ASSERT_TRUE(imageObj["Height"]->isInteger());
	ASSERT_EQ(600, imageObj["Height"]->asInteger());

	ASSERT_TRUE(imageObj["Width"]->isInteger());
	ASSERT_EQ(800, imageObj["Width"]->asInteger());

	ASSERT_TRUE(imageObj["Title"]->isString());
	ASSERT_STREQ("View from 15th Floor", imageObj["Title"]->asString().c_str());

	ASSERT_TRUE(imageObj["Thumbnail"]->isObject());
	const IRJsonObject & thumbnailObj = IRJsonAsObject(*imageObj["Thumbnail"]);
	ASSERT_EQ(3, thumbnailObj.size());

	ASSERT_TRUE(thumbnailObj["Url"]->isString());
	ASSERT_STREQ("http://www.example.com/image/481989943", thumbnailObj["Url"]->asString().c_str());

	ASSERT_TRUE(thumbnailObj["Height"]->isDecimal());
	ASSERT_EQ(125.0, thumbnailObj["Height"]->asDecimal());

	ASSERT_TRUE(thumbnailObj["Width"]->isDecimal());
	ASSERT_EQ(100.0, thumbnailObj["Width"]->asDecimal());

	ASSERT_TRUE(imageObj["Animated"]->isBoolean());
	ASSERT_FALSE(imageObj["Animated"]->asBoolean());

	ASSERT_TRUE(imageObj["IDs"]->isArray());
	const IRJsonArray & idsArray = IRJsonAsArray(*imageObj["IDs"]);
	ASSERT_EQ(4, idsArray.size());

	ASSERT_TRUE(idsArray[0]->isInteger());
	ASSERT_EQ(116, idsArray[0]->asInteger());

	ASSERT_TRUE(idsArray[1]->isInteger());
	ASSERT_EQ(943, idsArray[1]->asInteger());

	ASSERT_TRUE(idsArray[2]->isNull());

	ASSERT_TRUE(idsArray[3]->isBoolean());
	ASSERT_TRUE(idsArray[3]->asBoolean());

	delete dst;
}

//------------------------------------------------------------------------------
TEST_F(IRJsonParserTest, ParseExample2) {
	IRJsonObject * dst;

	IRJsonParser p(new IRJsonStringTokenizer(
		"/* Example from RFC7159 */\n"
		"{\n"
		"	\"results\": \n"
		"	[\n"
		"	{ \n"
		"		\"gender\":\"female\",\n"
		"		\"name\" : \n"
		"		{\n"
		"			\"title\":\"miss\",\n"
		"			\"first\" : \"mildred\",\n"
		"			\"last\" : \"campbell\",\n"
		"		},\n"
		"		\"location\" : \n"
		"		{\n"
		"			\"street\":\"5076 hillcrest rd\",\n"
		"			\"city\" : \"bendigo\",\n"
		"			\"state\" : \"northern territory\",\n"
		"			\"postcode\" : 6626 \n"
		"		},\n"
		"		\"email\" : \"mildred.campbell@example.com\",\n"
		"		\"login\" : \n"
		"		{\n"
		"			\"username\":\"crazycat503\",\n"
		"			\"password\" : \"dharma\",\n"
		"			\"salt\" : \"RFWp21AU\",\n"
		"			\"md5\" : \"3582c43162268360b5ef301f875695e6\",\n"
		"			\"sha1\" : \"e0b404c85a1ad365050fd9920376274b08f14454\",\n"
		"			\"sha256\" : \"4f443959dd9d44a3c511a29ccf976aa17739cf3a4efce3cf0d894fa5178ac5c6\"\n"
		"		},\n"
		"		\"dob\":\"1975-07-29 13:26:50\",\n"
		"		\"registered\" : \"2003-08-01 11:44:07\",\n"
		"		\"phone\" : \"08-7802-4454\",\n"
		"		\"cell\" : \"0449-211-200\",\n"
		"		\"id\" : \n"
		"		{\n"
		"			\"name\":\"TFN\",\n"
		"			\"value\" : \"892538135\"\n"
		"		},\n"
		"		\"picture\" : \n"
		"		{\n"
		"			\"large\":\"https://randomuser.me/api/portraits/women/76.jpg\",\n"
		"			\"medium\" : \"https://randomuser.me/api/portraits/med/women/76.jpg\",\n"
		"			\"thumbnail\" : \"https://randomuser.me/api/portraits/thumb/women/76.jpg\"\n"
		"		},\n"
		"		\"nat\" : \"AU\"\n"
		"	}\n"
		"	],\n"
		"	\"info\":\n"
		"	{\n"
		"		\"seed\":\"38b33240cdf129f5\",\n"
		"		\"results\" : 25,\n"
		"		\"page\" : 1,\n"
		"		\"version\" : \"1.1\"\n"
		"	}\n"
		"}\n"));

	dst = p.parseObject();
	ASSERT_TRUE(dst != nullptr);

	ASSERT_TRUE(dst->isObject());

	ASSERT_TRUE((*dst)["results"]->isArray());
	const IRJsonArray & resultsArr = IRJsonAsArray(*(*dst)["results"]);

	ASSERT_EQ(1, resultsArr.size());

	ASSERT_TRUE(resultsArr[0]->isObject());

	const IRJsonObject & resultsObj = IRJsonAsObject(*(resultsArr[0]));

	ASSERT_TRUE(resultsObj["gender"]->isString());

	/*

	ASSERT_TRUE(imageObj["Height"]->isInteger());
	ASSERT_EQ(600, imageObj["Height"]->asInteger());

	ASSERT_TRUE(imageObj["Width"]->isInteger());
	ASSERT_EQ(800, imageObj["Width"]->asInteger());

	ASSERT_TRUE(imageObj["Title"]->isString());
	ASSERT_STREQ("View from 15th Floor", imageObj["Title"]->asString().c_str());

	ASSERT_TRUE(imageObj["Thumbnail"]->isObject());
	const IRJsonObject & thumbnailObj = IRJsonAsObject(*imageObj["Thumbnail"]);
	ASSERT_EQ(3, thumbnailObj.size());

	ASSERT_TRUE(thumbnailObj["Url"]->isString());
	ASSERT_STREQ("http://www.example.com/image/481989943", thumbnailObj["Url"]->asString().c_str());

	ASSERT_TRUE(thumbnailObj["Height"]->isDecimal());
	ASSERT_EQ(125.0, thumbnailObj["Height"]->asDecimal());

	ASSERT_TRUE(thumbnailObj["Width"]->isDecimal());
	ASSERT_EQ(100.0, thumbnailObj["Width"]->asDecimal());

	ASSERT_TRUE(imageObj["Animated"]->isBoolean());
	ASSERT_FALSE(imageObj["Animated"]->asBoolean());

	ASSERT_TRUE(imageObj["IDs"]->isArray());
	const IRJsonArray & idsArray = IRJsonAsArray(*imageObj["IDs"]);
	ASSERT_EQ(4, idsArray.size());

	ASSERT_TRUE(idsArray[0]->isInteger());
	ASSERT_EQ(116, idsArray[0]->asInteger());

	ASSERT_TRUE(idsArray[1]->isInteger());
	ASSERT_EQ(943, idsArray[1]->asInteger());

	ASSERT_TRUE(idsArray[2]->isNull());

	ASSERT_TRUE(idsArray[3]->isBoolean());
	ASSERT_TRUE(idsArray[3]->asBoolean());

	*/

	delete dst;
}
//------------------------------------------------------------------------------



