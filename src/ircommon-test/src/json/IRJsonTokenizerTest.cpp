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
#include "IRJsonTokenizerTest.h"
#include <ircommon/irjson.h>
#include <stdexcept>
using namespace ircommon::json;

//==============================================================================
// class IRJsonDummyTokenizer
//------------------------------------------------------------------------------
class IRJsonDummyTokenizer: public IRJsonTokenizer {
private:
	std::string _buff;
	std::uint64_t _pos;
	bool _got;
protected:
	virtual int getc();

	virtual void ungetc();
public:
	IRJsonDummyTokenizer(const char * s): _buff(s), _pos(0), _got(false) {
	}

	virtual ~IRJsonDummyTokenizer() = default;

	virtual bool hasMore() const;

	int getcEx() {
		return this->getc();
	}

	void ungetcEx() {
		return this->ungetc();
	}

	std::string & buffer() {
		return this->_buff;
	}

	std::uint64_t pos(){
		return this->_pos;
	}

	void setBuffer(const char * s) {
		this->_buff = s;
		this->_pos = 0;
		this->_got = false;
	}
};

//------------------------------------------------------------------------------
int IRJsonDummyTokenizer::getc() {
	int c;

	if (this->_pos < this->_buff.size()) {
		c = this->_buff[this->_pos];
		this->_pos++;
	} else {
		c = -1;
	}
	this->_got = true;
	return c;
}

//------------------------------------------------------------------------------
void IRJsonDummyTokenizer::ungetc() {

	if (this->_got) {
		if (this->_pos > 0) {
			this->_pos--;
			this->_got = false;
		}
	} else {
		throw std::logic_error("Cannot call ungetc() two consecutive times.");
	}
}

//------------------------------------------------------------------------------
bool IRJsonDummyTokenizer::hasMore() const {

	return (this->_pos < this->_buff.size());
}

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
TEST_F(IRJsonTokenizerTest, IRJsonDummyTokenizer) {
	const char * DATA = "0123456789";
	IRJsonDummyTokenizer t(DATA);

	// Quick test on all methods from IRJsonDummyTokenizer
	ASSERT_STREQ(DATA, t.buffer().c_str());
	ASSERT_EQ(0, t.pos());
	for (int i =0; i < 10; i++) {
		ASSERT_TRUE(t.hasMore());
		ASSERT_EQ(DATA[i], t.getcEx());
	}
	ASSERT_FALSE(t.hasMore());
	t.ungetcEx();
	ASSERT_EQ(DATA[9], t.getcEx());
	t.ungetcEx();
	try {
		t.ungetcEx();
		FAIL();
	} catch (std::logic_error & e){}
}

//------------------------------------------------------------------------------
TEST_F(IRJsonTokenizerTest, reset) {
	IRJsonDummyTokenizer p("");

	ASSERT_FALSE(p.reset());
}

//------------------------------------------------------------------------------
TEST_F(IRJsonTokenizerTest, value) {
	IRJsonDummyTokenizer p("1");

	ASSERT_STREQ("", p.value().c_str());
	ASSERT_EQ(IRJsonTokenizer::VAL_INT, p.next());
	ASSERT_STREQ("1", p.value().c_str());
}

//------------------------------------------------------------------------------
TEST_F(IRJsonTokenizerTest, ignoreComment) {
	IRJsonDummyTokenizer p("");

	p.setBuffer("//\n");
	ASSERT_EQ(IRJsonTokenizer::INPUT_END, p.next());

	p.setBuffer("//");
	ASSERT_EQ(IRJsonTokenizer::INPUT_END, p.next());

	p.setBuffer("//\n1");
	ASSERT_EQ(IRJsonTokenizer::VAL_INT, p.next());
	ASSERT_STREQ("1", p.value().c_str());
	ASSERT_EQ(IRJsonTokenizer::INPUT_END, p.next());

	p.setBuffer("//\n1////\n2");
	ASSERT_EQ(IRJsonTokenizer::VAL_INT, p.next());
	ASSERT_STREQ("1", p.value().c_str());
	ASSERT_EQ(IRJsonTokenizer::VAL_INT, p.next());
	ASSERT_STREQ("2", p.value().c_str());
	ASSERT_EQ(IRJsonTokenizer::INPUT_END, p.next());

	p.setBuffer("//test me\n1");
	ASSERT_EQ(IRJsonTokenizer::VAL_INT, p.next());
	ASSERT_STREQ("1", p.value().c_str());
	ASSERT_EQ(IRJsonTokenizer::INPUT_END, p.next());

	p.setBuffer("//test me\n1//test me");
	ASSERT_EQ(IRJsonTokenizer::VAL_INT, p.next());
	ASSERT_STREQ("1", p.value().c_str());
	ASSERT_EQ(IRJsonTokenizer::INPUT_END, p.next());

	// Multi-line
	p.setBuffer("/**/");
	ASSERT_EQ(IRJsonTokenizer::INPUT_END, p.next());

	p.setBuffer("/*\n*/1");
	ASSERT_EQ(IRJsonTokenizer::VAL_INT, p.next());
	ASSERT_STREQ("1", p.value().c_str());
	ASSERT_EQ(IRJsonTokenizer::INPUT_END, p.next());

	p.setBuffer("1\n/**/");
	ASSERT_EQ(IRJsonTokenizer::VAL_INT, p.next());
	ASSERT_STREQ("1", p.value().c_str());
	ASSERT_EQ(IRJsonTokenizer::INPUT_END, p.next());

	p.setBuffer("/* test me // */1/**/");
	ASSERT_EQ(IRJsonTokenizer::VAL_INT, p.next());
	ASSERT_STREQ("1", p.value().c_str());
	ASSERT_EQ(IRJsonTokenizer::INPUT_END, p.next());

	p.setBuffer("/*");
	ASSERT_EQ(IRJsonTokenizer::INVALID, p.next());

	p.setBuffer("/* test me // */1/*");
	ASSERT_EQ(IRJsonTokenizer::VAL_INT, p.next());
	ASSERT_STREQ("1", p.value().c_str());
	ASSERT_EQ(IRJsonTokenizer::INVALID, p.next());

	p.setBuffer("/1");
	ASSERT_EQ(IRJsonTokenizer::INVALID, p.next());
}

//------------------------------------------------------------------------------
TEST_F(IRJsonTokenizerTest, ignoreSpaces) {
	IRJsonDummyTokenizer p("");

	p.setBuffer("\t\n\r ");
	ASSERT_EQ(IRJsonTokenizer::INPUT_END, p.next());

	p.setBuffer("\t\n\r 1");
	ASSERT_EQ(IRJsonTokenizer::VAL_INT, p.next());
	ASSERT_EQ(IRJsonTokenizer::INPUT_END, p.next());

	p.setBuffer("1\t\n2\r ");
	ASSERT_EQ(IRJsonTokenizer::VAL_INT, p.next());
	ASSERT_EQ(IRJsonTokenizer::VAL_INT, p.next());
	ASSERT_EQ(IRJsonTokenizer::INPUT_END, p.next());
}

//------------------------------------------------------------------------------
TEST_F(IRJsonTokenizerTest, extractNumeric) {
	IRJsonDummyTokenizer p("");

	// Integer
	p.setBuffer("1");
	ASSERT_EQ(IRJsonTokenizer::VAL_INT, p.next());
	ASSERT_STREQ("1", p.value().c_str());
	ASSERT_EQ(IRJsonTokenizer::INPUT_END, p.next());

	p.setBuffer("11");
	ASSERT_EQ(IRJsonTokenizer::VAL_INT, p.next());
	ASSERT_STREQ("11", p.value().c_str());
	ASSERT_EQ(IRJsonTokenizer::INPUT_END, p.next());

	p.setBuffer("+11");
	ASSERT_EQ(IRJsonTokenizer::VAL_INT, p.next());
	ASSERT_STREQ("11", p.value().c_str());
	ASSERT_EQ(IRJsonTokenizer::INPUT_END, p.next());

	// Decimal
	p.setBuffer("0.1");
	ASSERT_EQ(IRJsonTokenizer::VAL_DEC, p.next());
	ASSERT_STREQ("0.1", p.value().c_str());

	p.setBuffer("-0.1");
	ASSERT_EQ(IRJsonTokenizer::VAL_DEC, p.next());
	ASSERT_STREQ("-0.1", p.value().c_str());

	p.setBuffer("+0.1");
	ASSERT_EQ(IRJsonTokenizer::VAL_DEC, p.next());
	ASSERT_STREQ("0.1", p.value().c_str());

	p.setBuffer("0.1E1");
	ASSERT_EQ(IRJsonTokenizer::VAL_DEC, p.next());
	ASSERT_STREQ("0.1E1", p.value().c_str());

	p.setBuffer("0.1E-1");
	ASSERT_EQ(IRJsonTokenizer::VAL_DEC, p.next());
	ASSERT_STREQ("0.1E-1", p.value().c_str());

	p.setBuffer("0.1E+1");
	ASSERT_EQ(IRJsonTokenizer::VAL_DEC, p.next());
	ASSERT_STREQ("0.1E1", p.value().c_str());

	p.setBuffer("0.1E12");
	ASSERT_EQ(IRJsonTokenizer::VAL_DEC, p.next());
	ASSERT_STREQ("0.1E12", p.value().c_str());

	p.setBuffer("0.1E-12");
	ASSERT_EQ(IRJsonTokenizer::VAL_DEC, p.next());
	ASSERT_STREQ("0.1E-12", p.value().c_str());

	p.setBuffer("0.1E+12");
	ASSERT_EQ(IRJsonTokenizer::VAL_DEC, p.next());
	ASSERT_STREQ("0.1E12", p.value().c_str());

	// Invalid integers
	p.setBuffer("- ");
	ASSERT_EQ(IRJsonTokenizer::INVALID, p.next());

	p.setBuffer("+ ");
	ASSERT_EQ(IRJsonTokenizer::INVALID, p.next());

	// Invalid decimals
	p.setBuffer("0.");
	ASSERT_EQ(IRJsonTokenizer::INVALID, p.next());

	p.setBuffer("0.1E");
	ASSERT_EQ(IRJsonTokenizer::INVALID, p.next());

	p.setBuffer("0.1E-");
	ASSERT_EQ(IRJsonTokenizer::INVALID, p.next());

	p.setBuffer("0.1E+");
	ASSERT_EQ(IRJsonTokenizer::INVALID, p.next());
}

//------------------------------------------------------------------------------
TEST_F(IRJsonTokenizerTest, extractKeyword) {
	IRJsonDummyTokenizer p("");

	p.setBuffer("true");
	ASSERT_EQ(IRJsonTokenizer::VAL_TRUE, p.next());
	ASSERT_EQ(IRJsonTokenizer::INPUT_END, p.next());

	p.setBuffer("false");
	ASSERT_EQ(IRJsonTokenizer::VAL_FALSE, p.next());
	ASSERT_EQ(IRJsonTokenizer::INPUT_END, p.next());

	p.setBuffer("null");
	ASSERT_EQ(IRJsonTokenizer::VAL_NULL, p.next());
	ASSERT_EQ(IRJsonTokenizer::INPUT_END, p.next());

	p.setBuffer("False");
	ASSERT_EQ(IRJsonTokenizer::INVALID, p.next());

	p.setBuffer("once");
	ASSERT_EQ(IRJsonTokenizer::INVALID, p.next());
}

//------------------------------------------------------------------------------
TEST_F(IRJsonTokenizerTest, extractString) {
	IRJsonDummyTokenizer p("");

	p.setBuffer("\"once\"");
	ASSERT_EQ(IRJsonTokenizer::VAL_STRING, p.next());
	ASSERT_STREQ("once", p.value().c_str());

	p.setBuffer("\"once\\\"\"");
	ASSERT_EQ(IRJsonTokenizer::VAL_STRING, p.next());
	ASSERT_STREQ("once\"", p.value().c_str());

	p.setBuffer("\"once\\\"\"");
	ASSERT_EQ(IRJsonTokenizer::VAL_STRING, p.next());
	ASSERT_STREQ("once\"", p.value().c_str());

	// Escaping
	p.setBuffer("\"\\\"\\\\\\/\\b\\f\\n\\r\\t\"");
	ASSERT_EQ(IRJsonTokenizer::VAL_STRING, p.next());
	ASSERT_STREQ("\"\\/\b\f\n\r\t", p.value().c_str());

	// UTF-8
	p.setBuffer("\"\\u0024\\u00A2\\u20ac\"");
	ASSERT_EQ(IRJsonTokenizer::VAL_STRING, p.next());
	ASSERT_STREQ("\x024\x0C2\x0A2\x0E2\x082\x0AC", p.value().c_str());

	// Failed strings
	p.setBuffer("\"");
	ASSERT_EQ(IRJsonTokenizer::INVALID, p.next());

	p.setBuffer("\"\\l\"");
	ASSERT_EQ(IRJsonTokenizer::INVALID, p.next());

	p.setBuffer("\"\\u123Q\"");
	ASSERT_EQ(IRJsonTokenizer::INVALID, p.next());
}

//------------------------------------------------------------------------------
TEST_F(IRJsonTokenizerTest, operators) {
	IRJsonDummyTokenizer p("");

	p.setBuffer("{ } [ ] : ,");
	ASSERT_EQ(IRJsonTokenizer::OBJ_BEGIN, p.next());
	ASSERT_EQ(IRJsonTokenizer::OBJ_END, p.next());
	ASSERT_EQ(IRJsonTokenizer::ARRAY_BEGIN, p.next());
	ASSERT_EQ(IRJsonTokenizer::ARRAY_END, p.next());
	ASSERT_EQ(IRJsonTokenizer::NAME_SEP, p.next());
	ASSERT_EQ(IRJsonTokenizer::VALUE_SEP, p.next());
	ASSERT_EQ(IRJsonTokenizer::INPUT_END, p.next());
}

//------------------------------------------------------------------------------
TEST_F(IRJsonTokenizerTest, mixed) {
	IRJsonDummyTokenizer p("");

	p.setBuffer("{\"a\":12,\"b\":[-12.3 ,+12.3E1,null,false,true]}");
	ASSERT_EQ(IRJsonTokenizer::OBJ_BEGIN, p.next());

	ASSERT_EQ(IRJsonTokenizer::VAL_STRING, p.next());
	ASSERT_STREQ("a", p.value().c_str());

	ASSERT_EQ(IRJsonTokenizer::NAME_SEP, p.next());

	ASSERT_EQ(IRJsonTokenizer::VAL_INT, p.next());
	ASSERT_STREQ("12", p.value().c_str());

	ASSERT_EQ(IRJsonTokenizer::VALUE_SEP, p.next());

	ASSERT_EQ(IRJsonTokenizer::VAL_STRING, p.next());
	ASSERT_STREQ("b", p.value().c_str());

	ASSERT_EQ(IRJsonTokenizer::NAME_SEP, p.next());

	ASSERT_EQ(IRJsonTokenizer::ARRAY_BEGIN, p.next());

	ASSERT_EQ(IRJsonTokenizer::VAL_DEC, p.next());
	ASSERT_STREQ("-12.3", p.value().c_str());

	ASSERT_EQ(IRJsonTokenizer::VALUE_SEP, p.next());

	ASSERT_EQ(IRJsonTokenizer::VAL_DEC, p.next());
	ASSERT_STREQ("12.3E1", p.value().c_str());

	ASSERT_EQ(IRJsonTokenizer::VALUE_SEP, p.next());

	ASSERT_EQ(IRJsonTokenizer::VAL_NULL, p.next());

	ASSERT_EQ(IRJsonTokenizer::VALUE_SEP, p.next());

	ASSERT_EQ(IRJsonTokenizer::VAL_FALSE, p.next());

	ASSERT_EQ(IRJsonTokenizer::VALUE_SEP, p.next());

	ASSERT_EQ(IRJsonTokenizer::VAL_TRUE, p.next());

	ASSERT_EQ(IRJsonTokenizer::ARRAY_END, p.next());

	ASSERT_EQ(IRJsonTokenizer::OBJ_END, p.next());

	ASSERT_EQ(IRJsonTokenizer::INPUT_END, p.next());
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

