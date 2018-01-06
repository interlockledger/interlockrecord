#include "irjson.h"

#include <stdexcept>
#include <cstdio>
#include <cctype>
#include <cstdlib>

using namespace  ircommon::json;

//==============================================================================
// Class IRJsonObject
//------------------------------------------------------------------------------
void IRJsonObject::set(const std::string & name, std::shared_ptr<IRJsonBase> & value) {
	this->_map[name] = value;
}

//------------------------------------------------------------------------------
bool IRJsonObject::contains(const std::string & name) const {
	return (this->_map.find(name) != this->_map.end());
}

//------------------------------------------------------------------------------
std::shared_ptr<IRJsonBase> & IRJsonObject::operator[](const std::string & name) {

	auto found = this->_map.find(name);
	if (found != this->_map.end()) {
		return found->second;
	} else {
		throw std::invalid_argument("Not found.");
	}
}

//------------------------------------------------------------------------------
const std::shared_ptr<IRJsonBase> & IRJsonObject::operator[](const std::string & name) const {

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
void IRJsonObject::getAttributeNames(std::vector<std::string> & attr) const {
	for (auto pair = this->_map.begin(); pair != this->_map.end(); pair++) {
		attr.push_back(pair->first);
	}
}

//==============================================================================
// Class IRJsonArray
//------------------------------------------------------------------------------
std::shared_ptr<IRJsonBase> & IRJsonArray::operator[](int idx) {
	return this->_values[idx];
}

//------------------------------------------------------------------------------
const std::shared_ptr<IRJsonBase> & IRJsonArray::operator[](int idx) const {
	return this->_values[idx];
}

//------------------------------------------------------------------------------
void IRJsonArray::remove(int idx) {
	this->_values.erase(this->_values.begin() + idx);
}

//------------------------------------------------------------------------------
void IRJsonArray::insert(int idx, const std::shared_ptr<IRJsonBase> & value) {
	this->_values.insert(this->_values.begin() + idx, value);
}

//------------------------------------------------------------------------------
void IRJsonArray::append(const std::shared_ptr<IRJsonBase> & value) {
	this->_values.push_back(value);
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
void IRJsonSerializer::serialize(const IRJsonBase & v, std::string & out) {

	switch(v.type()) {
	case IRJsonBase::ARRAY:
		this->serializeArray(static_cast<const IRJsonArray &>(v), out);
		break;
	case IRJsonBase::BOOLEAN:
		this->serializeBoolean(static_cast<const IRJsonBoolean &>(v), out);
		break;
	case IRJsonBase::DECIMAL:
		this->serializeDecimal(static_cast<const IRJsonDecimal &>(v), out);
		break;
	case IRJsonBase::INTEGER:
		this->serializeInteger(static_cast<const IRJsonInteger &>(v), out);
		break;
	case IRJsonBase::NULL_VALUE:
		this->serializeNull(out);
		break;
	case IRJsonBase::OBJECT:
		this->serializeObject(static_cast<const IRJsonObject &>(v), out);
		break;
	case IRJsonBase::STRING:
		this->serializeString(static_cast<const IRJsonString &>(v), out);
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
	std::vector<std::string> attr;

	v.getAttributeNames(attr);
	//this->beginLine(out);
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
	//this->endLine(out);
}

//------------------------------------------------------------------------------
void IRJsonSerializer::serializeArray(const IRJsonArray & v, std::string & out) {

	this->beginLine(out);
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
	this->endLine(out);
}

//==============================================================================
// Class IRJsonTokenizer
//------------------------------------------------------------------------------
IRJsonTokenizer::IRJsonTokenizer(const std::string & in):
		IRJsonTokenizer(in, 0, in.size()){
}

//------------------------------------------------------------------------------
IRJsonTokenizer::IRJsonTokenizer(const std::string & in, int start, int size):
		_in(in, start, size), _pos(0) {
}

//------------------------------------------------------------------------------
IRJsonTokenizer::IRJsonTokenizer(const char * in): _in(in), _pos(0) {
}

//------------------------------------------------------------------------------
IRJsonTokenizer::IRJsonTokenizer(const char * in, int size):
		_in(in, size), _pos(0) {
}

//------------------------------------------------------------------------------
int IRJsonTokenizer::getc() {

	if (this->_pos < this->_in.size()) {
		return this->_in[this->_pos++];
	} else {
		return -1;
	}
}

//------------------------------------------------------------------------------
void IRJsonTokenizer::ungetc() {

	if (this->_pos > 0) {
		this->_pos--;
	}
}

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
		do {
			c = this->getc();
		} while (c != '\n');
		return true;
	} else if (c == '*') {
		bool prefix = false;
		do {
			c = this->getc();
			switch (c) {
			case '*':
				prefix = true;
				break;
			case '/':
				if (prefix) {
					return true;
				}
				break;
			default:
				prefix = false;;
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
void IRJsonTokenizer::reset() {
	this->_pos = 0;
	this->_token.clear();
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
IRJsonTokenizer::TokenType IRJsonTokenizer::extractNumeric() {
	enum {
		ST_INT_FIRST,
		ST_INT,
		ST_FRAC_FIRST,
		ST_FRAC,
		ST_EXP_FIRST,
		ST_EXP,
		ST_END} state;
	int c;
	bool decimal;

	decimal = false;
	if ((this->_token[0] == '-') || (this->_token[0] == '+')) {
		state = ST_INT_FIRST;
	} else {
		state = ST_INT;
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
			if ((c == '-') || (c == '+') || (IRJsonTokenizer::isDigit(c))) {
				state = ST_EXP;
			} else {
				return IRJsonTokenizer::INVALID;
			}
			break;
		case ST_EXP:
			// Exponent
			if (c == -1) {
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
IRJsonTokenizer::TokenType IRJsonTokenizer::extractKeyword() {
	int c;

	do {
		c = this->getc();
		if (isKeywordChar(c)) {
			this->_token.push_back(c);
		} else if (c != -1) {
			this->ungetc();
			this->_token.pop_back();
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
			this->_token.push_back(c);
			if ((c == '-') || (c == '+') || std::isdigit(c)) {
				return this->extractNumeric();
			} else if (isKeywordChar(c)) {
				return this->extractKeyword();
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

//------------------------------------------------------------------------------
