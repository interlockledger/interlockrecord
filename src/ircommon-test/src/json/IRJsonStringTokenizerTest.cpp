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
	IRJsonStringTokenizer t("12345 12345");

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


