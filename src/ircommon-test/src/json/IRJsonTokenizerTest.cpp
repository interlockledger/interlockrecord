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
#include "IRJsonTokenizerTest.h"
#include <ircommon/irjson.h>
using namespace ircommon::json;

//==============================================================================
// class IRJsonTokenizerTest
//------------------------------------------------------------------------------
IRJsonTokenizerTest::IRJsonTokenizerTest() {
}

//------------------------------------------------------------------------------
IRJsonTokenizerTest::~IRJsonTokenizerTest() {
}

//------------------------------------------------------------------------------
void IRJsonTokenizerTest::SetUp() {
}

//------------------------------------------------------------------------------
void IRJsonTokenizerTest::TearDown() {
}

//------------------------------------------------------------------------------
TEST_F(IRJsonTokenizerTest, unicodeToUTF8) {
	std::string out;

	out.clear();
	IRJsonTokenizer::unicodeToUTF8(0x24, out);
	ASSERT_STREQ("\x24", out.c_str());

	out.clear();
	IRJsonTokenizer::unicodeToUTF8(0xA2, out);
	ASSERT_STREQ("\xC2\xA2", out.c_str());

	out.clear();
	IRJsonTokenizer::unicodeToUTF8(0x20AC, out);
	ASSERT_STREQ("\xE2\x82\xAC", out.c_str());

	out.clear();
	IRJsonTokenizer::unicodeToUTF8(0x10348, out);
	ASSERT_STREQ("\xF0\x90\x8D\x88", out.c_str());
}

//------------------------------------------------------------------------------
TEST_F(IRJsonTokenizerTest, tokenToName) {

	ASSERT_STREQ("ARRAY_BEGIN", IRJsonTokenizer::tokenToName(IRJsonTokenizer::ARRAY_BEGIN).c_str());
	ASSERT_STREQ("ARRAY_END", IRJsonTokenizer::tokenToName(IRJsonTokenizer::ARRAY_END).c_str());
	ASSERT_STREQ("INPUT_END", IRJsonTokenizer::tokenToName(IRJsonTokenizer::INPUT_END).c_str());
	ASSERT_STREQ("INVALID", IRJsonTokenizer::tokenToName(IRJsonTokenizer::INVALID).c_str());
	ASSERT_STREQ("NAME_SEP", IRJsonTokenizer::tokenToName(IRJsonTokenizer::NAME_SEP).c_str());
	ASSERT_STREQ("OBJ_BEGIN", IRJsonTokenizer::tokenToName(IRJsonTokenizer::OBJ_BEGIN).c_str());
	ASSERT_STREQ("OBJ_END", IRJsonTokenizer::tokenToName(IRJsonTokenizer::OBJ_END).c_str());
	ASSERT_STREQ("VALUE_SEP", IRJsonTokenizer::tokenToName(IRJsonTokenizer::VALUE_SEP).c_str());
	ASSERT_STREQ("VAL_DEC", IRJsonTokenizer::tokenToName(IRJsonTokenizer::VAL_DEC).c_str());
	ASSERT_STREQ("VAL_FALSE", IRJsonTokenizer::tokenToName(IRJsonTokenizer::VAL_FALSE).c_str());
	ASSERT_STREQ("VAL_INT", IRJsonTokenizer::tokenToName(IRJsonTokenizer::VAL_INT).c_str());
	ASSERT_STREQ("VAL_NULL", IRJsonTokenizer::tokenToName(IRJsonTokenizer::VAL_NULL).c_str());
	ASSERT_STREQ("VAL_STRING", IRJsonTokenizer::tokenToName(IRJsonTokenizer::VAL_STRING).c_str());
	ASSERT_STREQ("VAL_TRUE", IRJsonTokenizer::tokenToName(IRJsonTokenizer::VAL_TRUE).c_str());
	ASSERT_STREQ("????", IRJsonTokenizer::tokenToName((IRJsonTokenizer::TokenType)-1).c_str());
}

//------------------------------------------------------------------------------
TEST_F(IRJsonTokenizerTest, isSpace) {

	for (int c = 0; c < 256; c++) {
		switch (c) {
		case 0x20:
		case 0x09:
		case 0x0A:
		case 0x0D:
			ASSERT_TRUE(IRJsonTokenizer::isSpace(c));
			break;
		default:
			ASSERT_FALSE(IRJsonTokenizer::isSpace(c));
		}
	}
}

//------------------------------------------------------------------------------
TEST_F(IRJsonTokenizerTest, isHex) {

	for (int c = 0; c < 256; c++) {
		if (((c >= '0') && (c <= '9')) ||
				((c >= 'A') && (c <= 'F')) ||
				((c >= 'a') && (c <= 'f'))) {
			ASSERT_TRUE(IRJsonTokenizer::isHex(c));
		} else {
			ASSERT_FALSE(IRJsonTokenizer::isHex(c));
		}
	}
}

//------------------------------------------------------------------------------
TEST_F(IRJsonTokenizerTest, isDigit) {

	for (int c = 0; c < 256; c++) {
		if ((c >= '0') && (c <= '9')) {
			ASSERT_TRUE(IRJsonTokenizer::isDigit(c));
		} else {
			ASSERT_FALSE(IRJsonTokenizer::isDigit(c));
		}
	}
}

//------------------------------------------------------------------------------
TEST_F(IRJsonTokenizerTest, isKeywordChar) {

	for (int c = 0; c < 256; c++) {
		if ((c >= 'a') && (c <= 'z')) {
			ASSERT_TRUE(IRJsonTokenizer::isKeywordChar(c));
		} else {
			ASSERT_FALSE(IRJsonTokenizer::isKeywordChar(c));
		}
	}
}
//------------------------------------------------------------------------------
