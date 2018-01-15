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
#include <ircommon/irjson.h>
#include <stdexcept>
#include <cstdio>
#include <cctype>
#include <cstdlib>

using namespace  ircommon::json;

//==============================================================================
// Class IRJsonBase
//------------------------------------------------------------------------------
bool IRJsonValue::equals(const IRJsonValue & v) const {
	return (this->type() == v.type());
}

//------------------------------------------------------------------------------
bool IRJsonValue::asBoolean() const {
	throw std::domain_error("Not a boolean.");
}

//------------------------------------------------------------------------------
double IRJsonValue::asDecimal() const {
	throw std::domain_error("Not a decimal.");
}

//------------------------------------------------------------------------------
std::uint64_t IRJsonValue::asInteger() const {
	throw std::domain_error("Not an integer.");
}

//------------------------------------------------------------------------------
const std::string & IRJsonValue::asString() const {
	throw std::domain_error("Not a string.");
}

//------------------------------------------------------------------------------
IRJsonValue * IRJsonValue::clone() const {
	return nullptr;
}

//==============================================================================
// Class IRJsonObject
//------------------------------------------------------------------------------
void IRJsonObject::set(const std::string & name, SharedPointer value) {
	this->_map[name] = value;
}

//------------------------------------------------------------------------------
bool IRJsonObject::contains(const std::string & name) const {
	return (this->_map.find(name) != this->_map.end());
}

//------------------------------------------------------------------------------
IRJsonValue::SharedPointer & IRJsonObject::operator[](const std::string & name) {

	auto found = this->_map.find(name);
	if (found != this->_map.end()) {
		return found->second;
	} else {
		throw std::invalid_argument("Not found.");
	}
}

//------------------------------------------------------------------------------
const IRJsonValue::SharedPointer & IRJsonObject::operator[](const std::string & name) const {

	auto found = this->_map.find(name);
	if (found != this->_map.end()) {
		return found->second;
	} else {
		throw std::invalid_argument("Not found.");
	}
}

//------------------------------------------------------------------------------
void IRJsonObject::remove(const std::string & name) {
	this->_map.erase(name);
}

//------------------------------------------------------------------------------
void IRJsonObject::getAttributeNames(AttributeList & attr) const {
	for (auto pair = this->_map.begin(); pair != this->_map.end(); pair++) {
		attr.push_back(pair->first);
	}
}

//------------------------------------------------------------------------------
bool IRJsonObject::equals(const IRJsonValue & v) const {

	if (v.type() != this->type()) {
		return false;
	}

	const IRJsonObject & o = IRJsonAsObject(v);
	if (this->size() != o.size()) {
		return false;
	}

	// Compare the elements
	for(auto pair = this->_map.begin(); pair != this->_map.end(); pair++) {
		if (!o.contains(pair->first)) {
			return false;
		}
		if (!pair->second->equals(*o[pair->first])) {
			return false;
		}
	}
	return true;
}

//------------------------------------------------------------------------------
IRJsonValue * IRJsonObject::clone() const {
	IRJsonObject * o;

	o = new IRJsonObject ();
	for(auto pair = this->_map.begin(); pair != this->_map.end(); pair++) {
		o->set(pair->first, pair->second->clone());
	}
	return o;
}

//==============================================================================
// Class IRJsonArray
//------------------------------------------------------------------------------
IRJsonValue::SharedPointer & IRJsonArray::operator[](int idx) {
#ifdef NDEBUG
	return this->_values[idx];
#else
	return this->_values.at(idx);
#endif
}

//------------------------------------------------------------------------------
const IRJsonValue::SharedPointer & IRJsonArray::operator[](int idx) const {
#ifdef NDEBUG
	return this->_values[idx];
#else
	return this->_values.at(idx);
#endif
}

//------------------------------------------------------------------------------
void IRJsonArray::remove(int idx) {
	this->_values.erase(this->_values.begin() + idx);
}

//------------------------------------------------------------------------------
void IRJsonArray::insert(int idx, SharedPointer value) {
	this->_values.insert(this->_values.begin() + idx, value);
}

//------------------------------------------------------------------------------
void IRJsonArray::append(SharedPointer value) {
	this->_values.push_back(value);
}

//------------------------------------------------------------------------------
bool IRJsonArray::equals(const IRJsonValue & v) const {

	if (v.type() != this->type()) {
		return false;
	}
	const IRJsonArray & o = IRJsonAsArray(v);
	if (this->size() != o.size()) {
		return false;
	}
	// Compare the elements
	for (int i = 0; i < this->size(); i++) {
		if (!(*this)[i]->equals(*(o[i]))) {
			return false;
		}
	}
	return true;
}

//------------------------------------------------------------------------------
IRJsonValue * IRJsonArray::clone() const {
	IRJsonArray * a;

	a = new IRJsonArray();
	for (int i = 0; i < this->size(); i++) {
		a->append((*this)[i]->clone());
	}
	return a;
}

//==============================================================================
// Class IRJsonSerializer
//------------------------------------------------------------------------------
void IRJsonSerializer::levelUp() {
	this->_level++;
}

//------------------------------------------------------------------------------
void IRJsonSerializer::levelDown() {
	this->_level--;
}

//------------------------------------------------------------------------------
void IRJsonSerializer::beginLine(std::string & out) {
	if (this->_indent) {
		out.append(this->_level, '\t');
	}
}

//------------------------------------------------------------------------------
void IRJsonSerializer::endLine(std::string & out) {
	if (this->_indent) {
		out.push_back('\n');
	}
}

//------------------------------------------------------------------------------
void IRJsonSerializer::serialize(const IRJsonValue & v, std::string & out) {

	switch(v.type()) {
	case IRJsonValue::ARRAY:
		this->serializeArray(IRJsonAsArray(v), out);
		break;
	case IRJsonValue::BOOLEAN:
		this->serializeBoolean(IRJsonAsBoolean(v), out);
		break;
	case IRJsonValue::DECIMAL:
		this->serializeDecimal(IRJsonAsDecimal(v), out);
		break;
	case IRJsonValue::INTEGER:
		this->serializeInteger(IRJsonAsInteger(v), out);
		break;
	case IRJsonValue::NULL_VALUE:
		this->serializeNull(out);
		break;
	case IRJsonValue::OBJECT:
		this->serializeObject(IRJsonAsObject(v), out);
		break;
	case IRJsonValue::STRING:
		this->serializeString(IRJsonAsString(v), out);
		break;
	}
}

//------------------------------------------------------------------------------
void IRJsonSerializer::serializeNull(std::string & out) {
	out.append("null");
}

//------------------------------------------------------------------------------
void IRJsonSerializer::serializeString(const IRJsonString & v, std::string & out) {
	this->serializeString(v.get(), out);
}

//------------------------------------------------------------------------------
void IRJsonSerializer::serializeString(const std::string & v, std::string & out) {
	char tmp[8];

	// TODO escaped unicode is not supported yet.
	out.push_back('\"');
	for (int i = 0; i < v.size(); i++) {
		int c = v[i] & 0xFF;
		switch (c) {
		case '\"':
			out.append("\\\"");
			break;
		case '\\':
			out.append("\\\\");
			break;
		case '\b':
			out.append("\\b");
			break;
		case '\f':
			out.append("\\f");
			break;
		case '\n':
			out.append("\\n");
			break;
		case '\r':
			out.append("\\r");
			break;
		case '\t':
			out.append("\\t");
			break;
		default:
			if (c > 0x21) {
				// Literal
				out.push_back(c);
			} else {
				// Use \uXXXX
				out.append("\\u");
				std::snprintf(tmp, sizeof(tmp), "%04X", c);
				out.append(tmp);
			}
			break;
		}
	}
	out.push_back('\"');
}

//------------------------------------------------------------------------------
void IRJsonSerializer::serializeInteger(const IRJsonInteger & v, std::string & out) {
	out.append(std::to_string(v.get()));
}

//------------------------------------------------------------------------------
void IRJsonSerializer::serializeDecimal(const IRJsonDecimal & v, std::string & out) {
	out.append(std::to_string(v.get()));
}

//------------------------------------------------------------------------------
void IRJsonSerializer::serializeBoolean(const IRJsonBoolean & v, std::string & out) {
	if (v.get()) {
		out.append("true");
	} else {
		out.append("false");
	}
}

//------------------------------------------------------------------------------
void IRJsonSerializer::serializeObject(const IRJsonObject & v, std::string & out) {
	IRJsonObject::AttributeList attr;

	v.getAttributeNames(attr);
	out.push_back('{');
	this->endLine(out);
	this->levelUp();
	for (int i = 0; i < attr.size(); i++) {
		this->beginLine(out);
		this->serializeString(attr[i], out);
		out.push_back(':');
		if (v[attr[i]]->isObject() || v[attr[i]]->isArray()) {
			this->levelUp();
		}
		this->serialize(*v[attr[i]], out);
		if (v[attr[i]]->isObject() || v[attr[i]]->isArray()) {
			this->levelDown();
		}
		if (i < (attr.size() - 1)) {
			out.push_back(',');
		}
		this->endLine(out);
	}
	this->levelDown();
	this->beginLine(out);
	out.push_back('}');
}

//------------------------------------------------------------------------------
void IRJsonSerializer::serializeArray(const IRJsonArray & v, std::string & out) {

	out.push_back('[');
	this->endLine(out);
	this->levelUp();
	for (int i = 0; i < v.size(); i++) {
		this->beginLine(out);
		this->serialize(*(v[i]), out);
		if (i < (v.size() - 1)) {
			out.append(1, ',');
		}
		this->endLine(out);
	}
	this->levelDown();
	this->beginLine(out);
	out.push_back(']');
}

//==============================================================================
// Class IRJsonTokenizer
//------------------------------------------------------------------------------
bool IRJsonTokenizer::isSpace(int c) {

	return (c == 0x20) || (c == 0x09) || (c == 0x0A) || (c == 0x0D);
}

//------------------------------------------------------------------------------
bool IRJsonTokenizer::isHex(int c) {

	return ((c >= '0') && (c <= '9')) ||
			((c >= 'a') && (c <= 'f')) ||
			((c >= 'A') && (c <= 'F'));
}

//------------------------------------------------------------------------------
bool IRJsonTokenizer::isDigit(int c) {

	return ((c >= '0') && (c <= '9'));
}

//------------------------------------------------------------------------------
bool IRJsonTokenizer::isKeywordChar(int c) {
	return ((c >= 'a') && (c <= 'z'));
}

//------------------------------------------------------------------------------
bool IRJsonTokenizer::ignoreComment() {
	int c;

	c = this->getc();
	if (c == '/') {
		// Single-line
		do {
			c = this->getc();
		} while ((c != '\n') && (c != -1));
		return true;
	} else if (c == '*') {
		// Multi-line
		bool endPrefix = false;
		do {
			c = this->getc();
			switch (c) {
			case '*':
				endPrefix = true;
				break;
			case '/':
				if (endPrefix) {
					return true;
				}
				break;
			default:
				endPrefix = false;
			}
		} while (c != -1);
		return false; // Premature EOF
	} else {
		return false;
	}
}

//------------------------------------------------------------------------------
void IRJsonTokenizer::ignoreSpaces() {
	int c;

	do {
		c = this->getc();
	} while (IRJsonTokenizer::isSpace(c));
	if (c != -1) {
		this->ungetc();
	}
}

//------------------------------------------------------------------------------
bool IRJsonTokenizer::reset() {
	this->_token.clear();
	return false;
}

//------------------------------------------------------------------------------
IRJsonTokenizer::TokenType IRJsonTokenizer::extractString() {
	enum {
		ST_LITERAL,
		ST_ESCAPED,
		ST_UC,
		ST_END
	} state;
	std::string hex;
	int c;

	// TODO Deal with other planes later
	state = ST_LITERAL;
	do {
		c = this->getc();
		if (c == -1) {
			return IRJsonTokenizer::INVALID;
		}
		switch (state) {
		case ST_LITERAL:
			if (c == '\\') {
				state = ST_ESCAPED;
			} else if (c == '\"') {
				state = ST_END;
			} else {
				this->_token.push_back(c);
			}
			break;
		case ST_ESCAPED:
			int literal;
			switch (c) {
			case '\"':
				literal = '\"';
				break;
			case '\\':
				literal = '\\';
				break;
			case '/':
				literal = '/';
				break;
			case 'b':
				literal = '\b';
				break;
			case 'f':
				literal = '\f';
				break;
			case 'n':
				literal = '\n';
				break;
			case 'r':
				literal = '\r';
				break;
			case 't':
				literal = '\t';
				break;
			case 'u':
				state = ST_UC;
				break;
			default:
				return IRJsonTokenizer::INVALID;
			}
			if (state == ST_ESCAPED) {
				this->_token.push_back(literal);
				state = ST_LITERAL;
			}
			break;
		case ST_UC:
			if (IRJsonTokenizer::isHex(c)) {
				hex.push_back(c);
				if (hex.size() == 4) {
					this->unicodeToUTF8(std::stoi(hex, 0, 16), this->_token);
					state = ST_LITERAL;
				}
			} else {
				return IRJsonTokenizer::INVALID;
			}
			break;
		}
	} while (state != ST_END);
	return IRJsonTokenizer::VAL_STRING;
}

//------------------------------------------------------------------------------
IRJsonTokenizer::TokenType IRJsonTokenizer::extractNumeric(int initialChar) {
	enum {
		ST_INT_FIRST,
		ST_INT,
		ST_FRAC_FIRST,
		ST_FRAC,
		ST_EXP_FIRST,
		ST_EXP_FIRST_DIGIT,
		ST_EXP,
		ST_END} state;
	int c;
	bool decimal;

	decimal = false;
	switch (initialChar) {
	case '-':
		this->_token.push_back(initialChar);
		state = ST_INT_FIRST;
		break;
	case '+':
		state = ST_INT_FIRST;
		break;
	default:
		this->_token.push_back(initialChar);
		state = ST_INT;
		break;
	}
	do {
		c = this->getc();
		this->_token.push_back(c);
		switch (state) {
		case ST_INT_FIRST:
			if (IRJsonTokenizer::isDigit(c)){
				state = ST_INT;
			} else {
				return IRJsonTokenizer::INVALID;
			}
			break;
		case ST_INT:
			// Integral part
			switch (c) {
			case -1:
				this->_token.pop_back();
				state = ST_END;
				break;
			case '.':
				state = ST_FRAC_FIRST;
				decimal = true;
				break;
			case 'E':
			case 'e':
				state = ST_EXP_FIRST;
				decimal = true;
				break;
			default:
				if (!IRJsonTokenizer::isDigit(c)) {
					this->ungetc();
					this->_token.pop_back();
					state = ST_END;
				}
			}
			break;
		case ST_FRAC_FIRST:
			if (IRJsonTokenizer::isDigit(c)){
				state = ST_FRAC;
			} else {
				return IRJsonTokenizer::INVALID;
			}
			break;
		case ST_FRAC:
			if (c == -1) {
				this->_token.pop_back();
				state = ST_END;
			} else if ((c == 'e') || (c == 'E')) {
				state = ST_EXP_FIRST;
			} else if (!IRJsonTokenizer::isDigit(c)) {
				this->ungetc();
				this->_token.pop_back();
				state = ST_END;
			}
			break;
		case ST_EXP_FIRST:
			if (IRJsonTokenizer::isDigit(c)) {
				state = ST_EXP;
			} else if (c == '-') {
				state = ST_EXP_FIRST_DIGIT;
			} else if (c == '+') {
				this->_token.pop_back();
				state = ST_EXP_FIRST_DIGIT;
			} else {
				return IRJsonTokenizer::INVALID;
			}
			break;
		case ST_EXP_FIRST_DIGIT:
			if (IRJsonTokenizer::isDigit(c)) {
				state = ST_EXP;
			} else {
				return IRJsonTokenizer::INVALID;
			}
			break;
		case ST_EXP:
			// Exponent
			if (c == -1) {
				this->_token.pop_back();
				state = ST_END;
			} else if (!IRJsonTokenizer::isDigit(c)) {
				this->ungetc();
				this->_token.pop_back();
				state = ST_END;
			}
			break;
		}
	} while (state != ST_END);

	if (decimal) {
		return IRJsonTokenizer::VAL_DEC;
	} else {
		return IRJsonTokenizer::VAL_INT;
	}
}

//------------------------------------------------------------------------------
IRJsonTokenizer::TokenType IRJsonTokenizer::extractKeyword(int initialChar) {
	int c;

	this->_token.push_back(initialChar);
	do {
		c = this->getc();
		if (isKeywordChar(c)) {
			this->_token.push_back(c);
		} else if (c != -1) {
			this->ungetc();
			c = -1;
		}
	} while (c != -1);

	if (this->_token == "true") {
		return IRJsonTokenizer::VAL_TRUE;
	} else if (this->_token == "false") {
		return IRJsonTokenizer::VAL_FALSE;
	} else if (this->_token == "null") {
		return IRJsonTokenizer::VAL_NULL;
	} else {
		return IRJsonTokenizer::INVALID;
	}
}

//------------------------------------------------------------------------------
IRJsonTokenizer::TokenType IRJsonTokenizer::next() {
	int c;

	this->_token.clear();
	do {
		this->ignoreSpaces();
		c = this->getc();
		switch (c) {
		case -1:
			return IRJsonTokenizer::INPUT_END;
		case '/':
			if (!this->ignoreComment()) {
				return IRJsonTokenizer::INVALID;
			}
			break;
		case '{':
			return IRJsonTokenizer::OBJ_BEGIN;
			break;
		case '}':
			return IRJsonTokenizer::OBJ_END;
		case '[':
			return IRJsonTokenizer::ARRAY_BEGIN;
		case ']':
			return IRJsonTokenizer::ARRAY_END;
		case ':':
			return IRJsonTokenizer::NAME_SEP;
		case ',':
			return IRJsonTokenizer::VALUE_SEP;
		case '"':
			return this->extractString();
		default:
			if ((c == '-') || (c == '+') || std::isdigit(c)) {
				return this->extractNumeric(c);
			} else if (isKeywordChar(c)) {
				return this->extractKeyword(c);
			}
			return IRJsonTokenizer::INVALID;
		}
	} while (true);
}

//------------------------------------------------------------------------------
void IRJsonTokenizer::unicodeToUTF8(int c, std::string & out) {

	if ((c >= 0) && (c <= 0x7F)) {
		out.push_back(c);
	} else if ((c >= 0x80) && (c <= 0x7FF)) {
		out.push_back(char(0b11000000 | (c >> 6)));
		out.push_back(char(0b10000000 | (c & 0b00111111)));
	} else if ((c >= 0x800) && (c <= 0xFFFF)) {
		out.push_back(char(0b11100000 | (c >> 12)));
		out.push_back(char(0b10000000 | ((c >> 6) & 0b00111111)));
		out.push_back(char(0b10000000 | (c & 0b00111111)));
	} else if ((c >= 0x10000) && (c <= 0x10FFFF)) {
		out.push_back(char(0b11110000 | (c >> 18)));
		out.push_back(char(0b10000000 | ((c >> 12) & 0b00111111)));
		out.push_back(char(0b10000000 | ((c >> 6) & 0b00111111)));
		out.push_back(char(0b10000000 | (c & 0b00111111)));
	}
}

//------------------------------------------------------------------------------
std::string IRJsonTokenizer::tokenToName(IRJsonTokenizer::TokenType token) {

	switch (token) {
	case OBJ_BEGIN:
		return "OBJ_BEGIN";
	case OBJ_END:
		return "OBJ_END";
	case ARRAY_BEGIN:
		return "ARRAY_BEGIN";
	case ARRAY_END:
		return "ARRAY_END";
	case NAME_SEP:
		return "NAME_SEP";
	case VALUE_SEP:
		return "VALUE_SEP";
	case VAL_STRING:
		return "VAL_STRING";
	case VAL_TRUE:
		return "VAL_TRUE";
	case VAL_FALSE:
		return "VAL_FALSE";
	case VAL_INT:
		return "VAL_INT";
	case VAL_DEC:
		return "VAL_DEC";
	case VAL_NULL:
		return "VAL_NULL";
	case INVALID:
		return "INVALID";
	case INPUT_END:
		return "INPUT_END";
	default:
		return "????";
	}
}

//==============================================================================
// Class IRJsonTokenizer
//------------------------------------------------------------------------------
IRJsonStringTokenizer::IRJsonStringTokenizer(const std::string & in):
		IRJsonStringTokenizer(in, 0, in.size()){
}

//------------------------------------------------------------------------------
IRJsonStringTokenizer::IRJsonStringTokenizer(const std::string & in, int start, int size):
		_in(in, start, size), _pos(0) {
}

//------------------------------------------------------------------------------
IRJsonStringTokenizer::IRJsonStringTokenizer(const char * in): _in(in), _pos(0) {
}

//------------------------------------------------------------------------------
IRJsonStringTokenizer::IRJsonStringTokenizer(const char * in, int size):
		_in(in, size), _pos(0) {
}

//------------------------------------------------------------------------------
bool IRJsonStringTokenizer::reset() {
	IRJsonTokenizer::reset(); // Force the cleanup of the token string
	this->_pos = 0;
	return true;
}

//------------------------------------------------------------------------------
int IRJsonStringTokenizer::getc() {

	if (this->_pos < this->_in.size()) {
		return this->_in[this->_pos++];
	} else {
		return -1;
	}
}

//------------------------------------------------------------------------------
void IRJsonStringTokenizer::ungetc() {

	if (this->_pos > 0) {
		this->_pos--;
	}
}

//------------------------------------------------------------------------------
bool IRJsonStringTokenizer::hasMore() const {
	return (this->_pos < this->_in.size());
}

//==============================================================================
// Class IRJsonParser
//------------------------------------------------------------------------------
IRJsonParser::IRJsonParser(IRJsonTokenizer * tokenizer): _tokenizer(tokenizer) {

}

//------------------------------------------------------------------------------
IRJsonParser::IRJsonParser(const std::string & in):
		_tokenizer(new IRJsonStringTokenizer(in)) {
}

//------------------------------------------------------------------------------
IRJsonParser::~IRJsonParser() {
	if (this->_tokenizer) {
		delete this->_tokenizer;
	}
}

//------------------------------------------------------------------------------
IRJsonValue * IRJsonParser::parsePartialAny(IRJsonTokenizer::TokenType type) {

	switch (type) {
	case IRJsonTokenizer::OBJ_BEGIN:
		return this->parsePartialObject();
	case IRJsonTokenizer::ARRAY_BEGIN:
		return this->parsePartialArray();
	case IRJsonTokenizer::VAL_NULL:
		return new IRJsonNull();
	case IRJsonTokenizer::VAL_TRUE:
		return new IRJsonBoolean(true);
	case IRJsonTokenizer::VAL_FALSE:
		return new IRJsonBoolean(false);
	case IRJsonTokenizer::VAL_STRING:
		return new IRJsonString(this->_tokenizer->value());
	case IRJsonTokenizer::VAL_INT:
		return new IRJsonInteger(
				std::stol(this->_tokenizer->value()));
	case IRJsonTokenizer::VAL_DEC:
		return new IRJsonDecimal(
				std::stod(this->_tokenizer->value()));
	default:
		return nullptr;
	}
}

//------------------------------------------------------------------------------
IRJsonValue *  IRJsonParser::parseAny() {
	return this->parsePartialAny(this->_tokenizer->next());
}

//------------------------------------------------------------------------------
IRJsonObject * IRJsonParser::parsePartialObject() {
	bool hasMore;
	bool error;
	IRJsonTokenizer::TokenType type;
	IRJsonObject * out;
	std::string name;

	hasMore = true;
	error = true;
	out = new IRJsonObject();
	do {
		type = this->_tokenizer->next();
		if (type ==  IRJsonTokenizer::OBJ_END) {
			error = false;
			hasMore = false;
		} else if (type ==  IRJsonTokenizer::VAL_STRING) {
			name = this->_tokenizer->value();
			type = this->_tokenizer->next();
			if (type ==  IRJsonTokenizer::NAME_SEP) {
				IRJsonValue * value = this->parseAny();
				if (value) {
					out->set(name, std::shared_ptr<IRJsonValue>(value));
					type = this->_tokenizer->next();
					if (type == IRJsonTokenizer::OBJ_END) {
						error = false;
						hasMore = false;
					} else if (type != IRJsonTokenizer::VALUE_SEP) {
						hasMore = false;
					}
				} else {
					hasMore = false;
				}
			} else {
				hasMore = false;
			}
		} else {
			hasMore = false;
		}
	} while (hasMore);

	if (!error) {
		return out;
	} else {
		delete out;
		return nullptr;
	}
}

//------------------------------------------------------------------------------
IRJsonArray * IRJsonParser::parsePartialArray() {
	bool hasMore;
	bool error;
	IRJsonTokenizer::TokenType type;
	IRJsonArray * out;
	std::string name;

	hasMore = true;
	error = true;
	out = new IRJsonArray();
	do {
		type = this->_tokenizer->next();
		if (type ==  IRJsonTokenizer::ARRAY_END) {
			error = false;
			hasMore = false;
		} else {
			IRJsonValue * value = this->parsePartialAny(type);
			if (value) {
				out->append(std::shared_ptr<IRJsonValue>(value));
				type = this->_tokenizer->next();
				if (type == IRJsonTokenizer::ARRAY_END) {
					error = false;
					hasMore = false;
				} else if (type != IRJsonTokenizer::VALUE_SEP) {
					hasMore = false;
				}
			} else {
				hasMore = false;
			}
		}
	} while (hasMore);

	if (!error) {
		return out;
	} else {
		delete out;
		return nullptr;
	}
}

//------------------------------------------------------------------------------
IRJsonObject * IRJsonParser::parseObject() {
	IRJsonTokenizer::TokenType type;

	type = this->_tokenizer->next();
	if (type == IRJsonTokenizer::OBJ_BEGIN) {
		return this->parsePartialObject();
	} else {
		return nullptr;
	}
}

//==============================================================================
// Utilities
//------------------------------------------------------------------------------
template <class OutputType, IRJsonValue::JsonType TypeID>
const OutputType & IRJsonAs(const IRJsonValue & v) {
	if (v.type() != TypeID) {
		throw std::invalid_argument("Invalid type.");
	} else {
		return static_cast<const OutputType &>(v);
	}
}

namespace ircommon {
namespace json {

//------------------------------------------------------------------------------
const IRJsonNull & IRJsonAsNull(const IRJsonValue & v) {
	return IRJsonAs<IRJsonNull, IRJsonValue::NULL_VALUE>(v);
}

//------------------------------------------------------------------------------
const IRJsonBoolean & IRJsonAsBoolean(const IRJsonValue & v) {
	return IRJsonAs<IRJsonBoolean, IRJsonValue::BOOLEAN>(v);
}

//------------------------------------------------------------------------------
const IRJsonString & IRJsonAsString(const IRJsonValue & v) {
	return IRJsonAs<IRJsonString, IRJsonValue::STRING>(v);
}

//------------------------------------------------------------------------------
const IRJsonDecimal & IRJsonAsDecimal(const IRJsonValue & v){
	return IRJsonAs<IRJsonDecimal, IRJsonValue::DECIMAL>(v);
}

//------------------------------------------------------------------------------
const IRJsonInteger & IRJsonAsInteger(const IRJsonValue & v){
	return IRJsonAs<IRJsonInteger, IRJsonValue::INTEGER>(v);
}

//------------------------------------------------------------------------------
const IRJsonObject & IRJsonAsObject(const IRJsonValue & v){
	return IRJsonAs<IRJsonObject, IRJsonValue::OBJECT>(v);
}

//------------------------------------------------------------------------------
const IRJsonArray & IRJsonAsArray(const IRJsonValue & v){
	return IRJsonAs<IRJsonArray, IRJsonValue::ARRAY>(v);
}

//------------------------------------------------------------------------------

} //namespace json
} // namespace ircommon

//------------------------------------------------------------------------------
