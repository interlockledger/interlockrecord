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
#include "IRJsonStringTokenizerTest.h"
#include <ircommon/irjson.h>
using namespace ircommon::json;

//==============================================================================
// class IRJsonStringTokenizerTest
//------------------------------------------------------------------------------
IRJsonStringTokenizerTest::IRJsonStringTokenizerTest() {
}

//------------------------------------------------------------------------------
IRJsonStringTokenizerTest::~IRJsonStringTokenizerTest() {
}

//------------------------------------------------------------------------------
void IRJsonStringTokenizerTest::SetUp() {
}

//------------------------------------------------------------------------------
void IRJsonStringTokenizerTest::TearDown() {
}

//------------------------------------------------------------------------------
TEST_F(IRJsonStringTokenizerTest,Constructor) {
	IRJsonStringTokenizer * t;
	std::string s = "12345";

	t = new IRJsonStringTokenizer(s);
	ASSERT_EQ(IRJsonTokenizer::VAL_INT, t->next());
	ASSERT_STREQ(s.c_str(), t->value().c_str());
	delete t;

	t = new IRJsonStringTokenizer(s, 1, 3);
	ASSERT_EQ(IRJsonTokenizer::VAL_INT, t->next());
	ASSERT_STREQ("234", t->value().c_str());
	delete t;

	t = new IRJsonStringTokenizer(s.c_str());
	ASSERT_EQ(IRJsonTokenizer::VAL_INT, t->next());
	ASSERT_STREQ(s.c_str(), t->value().c_str());
	delete t;

	t = new IRJsonStringTokenizer(s.c_str(), 3);
	ASSERT_EQ(IRJsonTokenizer::VAL_INT, t->next());
	ASSERT_STREQ("123", t->value().c_str());
	delete t;
}

//------------------------------------------------------------------------------
TEST_F(IRJsonStringTokenizerTest,reset) {
	IRJsonStringTokenizer t("12345");

	ASSERT_EQ(IRJsonTokenizer::VAL_INT, t.next());
	ASSERT_EQ(IRJsonTokenizer::INPUT_END, t.next());
	ASSERT_FALSE(t.hasMore());
	ASSERT_TRUE(t.reset());
	ASSERT_TRUE(t.hasMore());
	ASSERT_EQ(IRJsonTokenizer::VAL_INT , t.next());
	ASSERT_EQ(IRJsonTokenizer::INPUT_END, t.next());
}

//------------------------------------------------------------------------------
TEST_F(IRJsonStringTokenizerTest,hasMore) {
	IRJsonStringTokenizer t0("");
	IRJsonStringTokenizer t("12345 12345");

	ASSERT_FALSE(t0.hasMore());

	ASSERT_TRUE(t.hasMore());
	ASSERT_EQ(IRJsonTokenizer::VAL_INT, t.next());
	ASSERT_TRUE(t.hasMore());
	ASSERT_EQ(IRJsonTokenizer::VAL_INT, t.next());
	ASSERT_FALSE(t.hasMore());
	ASSERT_EQ(IRJsonTokenizer::INPUT_END, t.next());
	ASSERT_FALSE(t.hasMore());
}

//------------------------------------------------------------------------------
TEST_F(IRJsonStringTokenizerTest, position) {
	IRJsonStringTokenizer t("12345 12345");

	ASSERT_EQ(0, t.position());
	ASSERT_EQ(IRJsonTokenizer::VAL_INT, t.next());
	ASSERT_EQ(5, t.position());
	ASSERT_EQ(IRJsonTokenizer::VAL_INT, t.next());
	ASSERT_EQ(11, t.position());
}
//------------------------------------------------------------------------------


