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
#ifndef IRJSON_H_
#define IRJSON_H_

#include <string>
#include <cstdint>
#include <memory>
#include <map>
#include <vector>

namespace ircommon {
namespace json {

/**
 * Base type for all JSON objects.
 *
 * @since 2018.01.04
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
 * @note This class is not thread-safe.
 */
class IRJsonValue {
public:
	typedef enum {
		NULL_VALUE,
		STRING,
		BOOLEAN,
		INTEGER,
		DECIMAL,
		OBJECT,
		ARRAY
	} JsonType;

	/**
	 * Alias for the type std::shared_ptr<IRJsonBase>.
	 */
	typedef std::shared_ptr<IRJsonValue> SharedPointer;
private:
	/**
	 * Type ID.
	 */
	JsonType _type;
public:
	/**
	 * Creates a new instance of this class.
	 *
	 * @param[in] type The type id.
	 */
	IRJsonValue(JsonType type): _type(type) {}

	/**
	 * Disposes this instance and releases all associated resources.
	 */
	virtual ~IRJsonValue() = default;

	/**
	 * Returns the type if of this
	 *
	 * @return The type ID.
	 */
	JsonType type() const {
		return this->_type;
	}

	/**
	 * Verifies if this is a string value.
	 *
	 * @return true if it is an instance of IRJsonString or false otherwise.
	 */
	bool isString() const { return this->type() == STRING; }

	/**
	 * Verifies if this is a boolean value.
	 *
	 * @return true if it is an instance of IRJsonBoolean or false otherwise.
	 */
	bool isBoolean() const { return this->type() == BOOLEAN; }

	/**
	 * Verifies if this is an integer value.
	 *
	 * @return true if it is an instance of IRJsonInteger or false otherwise.
	 */
	bool isInteger() const { return this->type() == INTEGER; }

	/**
	 * Verifies if this is a decimal value.
	 *
	 * @return true if it is an instance of IRJsonDecimal or false otherwise.
	 */
	bool isDecimal() const { return this->type() == DECIMAL; }

	/**
	 * Verifies if this is an object value.
	 *
	 * @return true if it is an instance of IRJsonObject or false otherwise.
	 */
	bool isObject() const { return this->type() == OBJECT; }

	/**
	 * Verifies if this is an array value.
	 *
	 * @return true if it is an instance of IRJsonArray or false otherwise.
	 */
	bool isArray() const { return this->type() == ARRAY; }

	/**
	 * Verifies if this is a null value.
	 *
	 * @return true if it is an instance of IRJsonNull or false otherwise.
	 */
	bool isNull() const { return this->type() == NULL_VALUE; }

	/**
	 * Verifies if this instance has the same contents of another IRJsonBase.
	 *
	 * @param[in] v The other instance of IRJsonBase.
	 * @return true if they are equal or false otherwise.
	 * @since 2018.01.08
	 * @note The default implementation from IRJsonValue returns true if both
	 * types are the same. Subclasses must override this behavior in order to
	 * check the contents as well.
	 */
	virtual bool equals(const IRJsonValue & v) const;

	/**
	 * Verifies if this instance has the same contents of another IRJsonBase.
	 *
	 * @param[in] v The other instance of IRJsonBase.
	 * @return true if they are equal or false otherwise.
	 * @since 2018.01.08
	 */
	bool operator == (const IRJsonValue & v) const {
		return this->equals(v);
	}

	/**
	 * Returns the current value as boolean.
	 *
	 * @return The boolean value.
	 * @exception std::domain_error If if it cannot be converted to boolean.
	 */
	virtual bool asBoolean() const;

	/**
	 * Returns the current value as double.
	 *
	 * @return The double value.
	 * @exception std::domain_error If if it cannot be converted to double.
	 */
	virtual double asDecimal() const;

	/**
	 * Returns the current value as integer.
	 *
	 * @return The integer value.
	 * @exception std::domain_error If if it cannot be converted to integer.
	 */
	virtual std::uint64_t asInteger() const;

	/**
	 * Returns the current value as string.
	 *
	 * @return The string value.
	 * @exception std::domain_error If if it cannot be converted to string.
	 */
	virtual const std::string & asString() const;

	/**
	 * Creates a clone of this value. The clone is created by
	 * performing a deep copy of this instance.
	 *
	 * @return The clone of this value or NULL if it is not implemented.
	 */
	virtual IRJsonValue * clone() const;
};

/**
 * The template for all basic JSON values.
 *
 * @since 2018.01.04
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
 * @tparam ValueType The basic type of the value.
 * @tparam TypeID ID of the type.
 * @note This class is not thread-safe.
 */
template <class ValueType, IRJsonValue::JsonType TypeID>
class IRJsonBaseValue: public IRJsonValue {
private:
	/**
	 * The current value.
	 */
	ValueType _value;
public:
	/**
	 * Creates a new instance of this class.
	 */
	IRJsonBaseValue(): IRJsonValue(TypeID), _value(){}

	/**
	 * Creates a new instance of this class.
	 *
	 * @param[in] value The initial value.
	 */
	IRJsonBaseValue(const ValueType & value): IRJsonValue(TypeID), _value(value){}

	/**
	 * Disposes this instance and releases all associated resources.
	 */
	virtual ~IRJsonBaseValue() = default;

	/**
	 * Returns the current value.
	 */
	const ValueType & get() const {
		return this->_value;
	}

	/**
	 * Sets the current value.
	 *
	 * @param[in] value The value.
	 */
	void set(const ValueType & value) {
		this->_value = value;
	}

	/**
	 * Sets the current value.
	 *
	 * @param[in] value The value.
	 * @return A reference to self.
	 */
	IRJsonBaseValue & operator = (const ValueType & value) {
		this->set(value);
		return (*this);
	}

	virtual bool equals(const IRJsonValue & v) const {
		if (this->type() == v.type()) {
			return (this->get() == static_cast<const IRJsonBaseValue&>(v).get());
		} else {
			return false;
		}
	}

	virtual IRJsonValue * clone() const {
		return new IRJsonBaseValue(this->get());
	}

	virtual bool asBoolean() const {
		return IRJsonValue::asBoolean();
	}

	virtual double asDecimal() const {
		return IRJsonValue::asDecimal();
	}

	virtual std::uint64_t asInteger() const {
		return IRJsonValue::asInteger();
	}

	virtual const std::string & asString() const {
		return IRJsonValue::asString();
	}
};

// Explicity specialized implementations
template<>
bool IRJsonBaseValue<bool, IRJsonValue::BOOLEAN>::asBoolean() const;

template <>
const std::string &
IRJsonBaseValue<std::string, IRJsonValue::STRING>::asString() const;

template <>
std::uint64_t
IRJsonBaseValue<std::int64_t, IRJsonValue::INTEGER>::asInteger() const;

template <>
double IRJsonBaseValue<double, IRJsonValue::DECIMAL>::asDecimal() const;

/**
 * JSON string. It uses std::string as its basic type.
 *
 * @since 2018.01.04
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
 * @note This class is not thread-safe.
 */
typedef IRJsonBaseValue<std::string, IRJsonValue::STRING> IRJsonString;

/**
 * JSON integer. It uses std::int64_t as its basic type.
 *
 * @since 2018.01.04
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
 * @note This class is not thread-safe.
 */
typedef IRJsonBaseValue<std::int64_t, IRJsonValue::INTEGER> IRJsonInteger;

/**
 * JSON decimal. It uses double as its basic type.
 *
 * @since 2018.01.04
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
 * @note This class is not thread-safe.
 */
typedef IRJsonBaseValue<double, IRJsonValue::DECIMAL> IRJsonDecimal;

/**
 * JSON boolean. It uses bool as its basic type.
 *
 * @since 2018.01.04
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
 * @note This class is not thread-safe.
 */
typedef IRJsonBaseValue<bool, IRJsonValue::BOOLEAN> IRJsonBoolean;

/**
 * JSON null. It uses bool as its basic type.
 *
 * @since 2018.01.04
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
 * @note This class is not thread-safe.
 */
class IRJsonNull : public IRJsonValue {
public:
	/**
	 * Creates a new instance of this class.
	 */
	IRJsonNull(): IRJsonValue(IRJsonValue::NULL_VALUE){}

	/**
	 * Disposes this instance and releases all associated resources.
	 */
	virtual ~IRJsonNull() = default;

	virtual IRJsonValue * clone() const {
		return new IRJsonNull();
	}
};

/**
 * JSON object. The values are referenced with std::shared_ptr in order to
 * avoid possible memory leaking.
 *
 * @since 2018.01.04
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
 * @note This class is not thread-safe.
 */
class IRJsonObject: public IRJsonValue {
private:
	std::map<std::string, std::shared_ptr<IRJsonValue>> _map;
public:
	/**
	 * Alias for the type std::vector<std::string>.
	 */
	typedef std::vector<std::string> AttributeList;

	/**
	 * Creates a new instance of this class.
	 */
	IRJsonObject():IRJsonValue(IRJsonValue::OBJECT){}

	/**
	 * Disposes this instance and releases all associated resources.
	 */
	virtual ~IRJsonObject() = default;

	/**
	 * Sets the value of an attribute.
	 *
	 * @param[in] name The name of the attribute.
	 * @param[in] value The value.
	 */
	void set(const std::string & name, SharedPointer value);

	/**
	 * Sets the value of an attribute.
	 *
	 * @param[in] name The name of the attribute.
	 * @param[in] value The value. This method will claim the ownership of this
	 * instance.
	 * @since 2018.01.09
	 */
	void set(const std::string & name, IRJsonValue * value) {
		this->set(name, SharedPointer(value));
	}

	/**
	 * Verifies if a given attribute exists.
	 *
	 * @param[in] name The name of the attribute.
	 * @return true if it exists or false otherwise.
	 */
	bool contains(const std::string & name) const;

	/**
	 * Returns the number of attributes of this object.
	 *
	 * @return The number of attributes.
	 */
	int size() const {
		return this->_map.size();
	}

	/**
	 * Grants read and write access to a given attribute.
	 *
	 * @param[in] name The name of the attribute.
	 * @return a shared_ptr to the attribute.
	 * @except std::invalid_argument If the name is not present.
	 */
	SharedPointer & operator[](const std::string & name);

	/**
	 * Grants read access to a given attribute.
	 *
	 * @param[in] name The name of the attribute.
	 * @return a shared_ptr to the attribute.
	 * @except std::invalid_argument If the name is not present.
	 */
	const SharedPointer & operator[](const std::string & name) const;

	/**
	 * Removes the attribute with a given name.
	 *
	 * @param[in] name The name of the attribute.
	 */
	void remove(const std::string & name);

	/**
	 * Returns a list of the attribute names.
	 *
	 * @param[out] attr The list of attribute names.
	 * @note The list of attributes are inserted into attr.
	 */
	void getAttributeNames(AttributeList & attr) const;

	virtual bool equals(const IRJsonValue & v) const;

	virtual IRJsonValue * clone() const;
};

/**
 * JSON array. The values are referenced with std::shared_ptr in order to
 * avoid possible memory leaking.
 *
 * @since 2018.01.04
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
 * @note This class is not thread-safe.
 */
class IRJsonArray: public IRJsonValue {
private:
	std::vector<SharedPointer> _values;
public:
	/**
	 * Creates a new instance of this class.
	 */
	IRJsonArray() : IRJsonValue(IRJsonValue::ARRAY) {}

	/**
	 * Disposes this instance and releases all associated resources.
	 */
	virtual ~IRJsonArray() = default;

	/**
	 * Returns the size of this array.
	 * @return The size of this array.
	 */
	int size() const {
		return this->_values.size();
	}

	/**
	 * Allows read/write access to the elements of this array.
	 *
	 * @param[in] idx The index of the element.
	 * @return A reference to the given element.
	 * @note This operator does not check the bounds of the index.
	 */
	SharedPointer & operator[](int idx);

	/**
	 * Allows read-only access to the elements of this array.
	 *
	 * @param[in] idx The index of the element.
	 * @return A read-only reference to the given element.
	 * @note This operator does not check the bounds of the index.
	 */
	const SharedPointer & operator[](int idx) const;

	/**
	 * Removes the element at a given index.
	 *
	 * @param[in] idx The index of the element.
	 */
	void remove(int idx);

	/**
	 * Inserts a new element into a given position.
	 *
	 * @param[in] idx The index of the element.
	 * @param[in] value The value to be added.
	 */
	void insert(int idx, SharedPointer value);

	/**
	 * Inserts a new element into a given position.
	 *
	 * @param[in] idx The index of the element.
	 * @param[in] value The value to be added. This method will claim the
	 * ownership of this instance.
	 * @since 2018.01.09
	 */
	void insert(int idx, IRJsonValue * value) {
		this->insert(idx, SharedPointer(value));
	}

	/**
	 * Inserts a new element into the end of the array.
	 *
	 * @param[in] value The value to be added.
	 */
	void append(SharedPointer value);

	/**
	 * Inserts a new element into the end of the array.
	 *
	 * @param[in] value The value to be added. This method will claim the
	 * ownership of this instance.
	 * @since 2018.01.09
	 */
	void append(IRJsonValue * value) {
		this->append(SharedPointer(value));
	}

	virtual bool equals(const IRJsonValue & v) const;

	virtual IRJsonValue * clone() const;
};

/**
 * JSON serializer. It follows the JSON syntax defined by RFC8259.
 *
 * @since 2018.01.04
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
 * @note This class is not thread-safe.
 */
class IRJsonSerializer {
protected:
	bool _indent;

	int _level;

	void levelUp();
	void levelDown();
	void beginLine(std::string & out);
	void endLine(std::string & out);
	void serializeNull(std::string & out);
	void serializeString(const IRJsonString & v, std::string & out);
	void serializeString(const std::string & v, std::string & out);
	void serializeInteger(const IRJsonInteger & v, std::string & out);
	void serializeDecimal(const IRJsonDecimal & v, std::string & out);
	void serializeBoolean(const IRJsonBoolean & v, std::string & out);
	void serializeObject(const IRJsonObject & v, std::string & out);
	void serializeArray(const IRJsonArray & v, std::string & out);
public:
	/**
	 * Creates a new instance of this class.
	 */
	IRJsonSerializer(bool indent = false): _indent(indent), _level(0) {}

	/**
	 * Disposes this instance and releases all associated resources.
	 */
	virtual ~IRJsonSerializer() = default;

	/**
	 * Serializes a given JSON object.
	 * @param[in] v The JSON object.
	 * @param[out] out The string that will hold the output.
	 */
	void serialize(const IRJsonValue & v, std::string & out);

	/**
	 * Returns the indent flag.
	 *
	 * @return true if this serializer will indent the result or false otherwise.
	 */
	bool indent() const {
		return this->_indent;
	}
};

/**
 * JSON abstract tokenizer. Subclasses of this class must be able to parse a
 * character source and split it to tokens it using the JSON syntax defined by
 * RFC8259.
 *
 * @since 2018.01.04
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
 * @note This class is not thread-safe.
 */
class IRJsonTokenizer {
public:
	typedef enum {
		/**
		 * Token '{'.
		 */
		OBJ_BEGIN,
		/**
		 * Token '}'.
		 */
		OBJ_END,
		/**
		 * Token '['.
		 */
		ARRAY_BEGIN,
		/**
		 * Token ']'.
		 */
		ARRAY_END,
		/**
		 * Token ':'.
		 */
		NAME_SEP,
		/**
		 * Token ','.
		 */
		VALUE_SEP,
		/**
		 * Token string value.
		 */
		VAL_STRING,
		/**
		 * Token "true".
		 */
		VAL_TRUE,
		/**
		 * Token "false".
		 */
		VAL_FALSE,
		/**
		 * Token integer value.
		 */
		VAL_INT,
		/**
		 * Token decimal value.
		 */
		VAL_DEC,
		/**
		 * Token "null".
		 */
		VAL_NULL,
		/**
		 * Invalid token. It marks a parser error.
		 */
		INVALID,
		/**
		 * Token that marks the end of the data.
		 */
		INPUT_END
	} TokenType;
private:
	/**
	 * The token value.
	 */
	std::string _token;

	/**
	 * Consumes the comments.
	 *
	 * @return true on success or false it the comment is corrupted.
	 */
	bool ignoreComment();

	/**
	 * Consumes the spaces between tokens.
	 */
	void ignoreSpaces();

	/**
	 * Extracts a string value from the input. The initial '"' must be already
	 * consumed from the input.
	 *
	 * @return VAL_STRING on success or INVALID if the string is indeed invalid.
	 * @note The actual value of the string is added to the field _token.
	 */
	TokenType extractString();

	/**
	 * Extracts a numeric value from the input. The initial numeric character
	 * must be already consumed from the input.
	 *
	 * @return VAL_INT or VAL_DEC on success or INVALID if the numeric value is
	 * invalid.
	 * @note The actual value of the token will be added to the field _token.
	 */
	TokenType extractNumeric(int initialChar);

	/**
	 * Extracts a keyword value from the input. The initial character must be
	 * already consumed from the input.
	 *
	 * @return VAL_NULL, VAL_TRUE or VAL_FALSE on success or INVALID if the
	 * keyword is invalid.
	 * @note The actual value of the token will be added to the field _token.
	 */
	TokenType extractKeyword(int initialChar);
protected:
	/**
	 * Reads the next character from the input.
	 *
	 * @return The character read or -1 if the end of data is reached.
	 */
	virtual int getc() = 0;
	/**
	 * Returns the last character read from the input back into it. Only the
	 * last character read from the input with getc() is supposed to be
	 * returned.
	 *
	 * <p>The behavior of this method in undefined if getc() was not called at
	 * least once before it.</p>
	 */
	virtual void ungetc() = 0;
public:
	/**
	 * Creates a new instance of this class.
	 */
	IRJsonTokenizer() = default;

	/**
	 * Disposes this instance and releases all associated resources.
	 */
	virtual ~IRJsonTokenizer() = default;

	/**
	 * Verifies if there is more data to be processed.
	 *
	 * @return true if there is more data or false otherwise.
	 */
	virtual bool hasMore() const = 0;

	/**
	 * Resets this instance. Not all implementations of this class is supposed
	 * to support this method.
	 *
	 * @return true on success or false otherwise.
	 */
	virtual bool reset();

	/**
	 * Extracts the next token.
	 *
	 * @return The type of the token found.
	 */
	TokenType next();

	/**
	 * Returns the actual value of the last token read. It is used only if the
	 * last token is a string or a numeric value.
	 *
	 * @return The value of the token.
	 */
	const std::string value() const {
		return this->_token;
	}

	/**
	 * Converts a unicode point into its UTF-8 representation.
	 *
	 * @param[out] out The output string.
	 * @param[in] c The unicode point from U+0000 to U+10FFFF.
	 */
	static void unicodeToUTF8(int c, std::string & out);

	/**
	 * This is a debugging helper that translates the token type to its name.
	 *
	 * @return A string with the name of the token.
	 */
	static std::string tokenToName(TokenType token);

	/**
	 * Verifies if a given character is a space according to the RFC8259.
	 *
	 * @return true if the character is a space or false otherwise.
	 */
	static bool isSpace(int c);

	/**
	 * Verifies if a given character is an hexadecimal digit according to the
	 * RFC8259.
	 *
	 * @return true if the character is a hexadecimal digit or false otherwise.
	 */
	static bool isHex(int c);

	/**
	 * Verifies if a given character is a decimal digit according to the
	 * RFC8259.
	 *
	 * @return true if the character is a decimal digit or false otherwise.
	 */
	static bool isDigit(int c);

	/**
	 * Verifies if a given character is a valid keyword character according to
	 * the RFC8259.
	 *
	 * @return true if the character is a valid keyword  character or false
	 * otherwise.
	 * @note Only lower case letters from 'a' to 'z' are considered keyword
	 * characters.
	 */
	static bool isKeywordChar(int c);
};

/**
 * This class implements a IRJsonTokenizer that read characters from a string.
 *
 * @since 2018.01.07
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
 * @note This class is not thread-safe.
 */
class IRJsonStringTokenizer: public IRJsonTokenizer {
private:
	std::string _in;
	std::uint64_t _pos;
protected:
	virtual int getc();
	virtual void ungetc();
public:
	/**
	 * Creates a new instance of this class.
	 * @param[in] in The input string that will be parsed.
	 */
	IRJsonStringTokenizer(const std::string & in);

	/**
	 * Creates a new instance of this class.
	 *
	 * @param[in] in The input string that will be parsed.
	 */
	IRJsonStringTokenizer(const char * in);

	/**
	 * Creates a new instance of this class.
	 *
	 * @param[in] in The input string that will be parsed.
	 * @param[in] size The number of characters inside in.
	 */
	IRJsonStringTokenizer(const char * in, int size);

	/**
	 * Creates a new instance of this class.
	 *
	 * @param[in] in The input string that will be parsed.
	 * @param[in] start The starting point.
	 * @param[in] size The number of characters to be used.
	 */
	IRJsonStringTokenizer(const std::string & in, int start, int size);

	/**
	 * Position of the reading point.
	 *
	 * @return The current reading point.
	 */
	std::uint64_t position() const {
		return this->_pos;
	}

	virtual bool reset();

	virtual bool hasMore() const;
};


/**
 * JSON parser. It parses a JSON string and returns a IRJsonObject that
 * represents its contents.
 *
 * @since 2018.01.07
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
 * @note This class is not thread-safe.
 */
class IRJsonParser {
private:
	IRJsonTokenizer * _tokenizer;

	/**
	 * Parses a partial JSON object. The token OBJ_BEGIN should be the last read
	 * from the tokenizer.
	 *
	 * @return The array read or if the data is not correct.
	 */
	IRJsonObject * parsePartialObject();

	/**
	 * Parses a partial JSON array. The token ARRAY_BEGIN should be the last
	 * read from the tokenizer.
	 *
	 * @return The array read or if the data is not correct.
	 */
	IRJsonArray * parsePartialArray();

	/**
	 * Parses the input looking for any type of object. The initial token should
	 * be already acquired from the tokenizer and the value of the token, if
	 * any, should be stored inside it.
	 *
	 * @return An instance of a IRJsonObject on success or null otherwise.
	 */
	IRJsonValue * parsePartialAny(IRJsonTokenizer::TokenType type);

	/**
	 * Parses the input looking for any type of JSON object. It returns the
	 * first element found if any.
	 *
	 * @return An instance of a IRJsonObject on success or null otherwise.
	 */
	virtual IRJsonValue * parseAny();
public:
	/**
	 * Creates a new instance of this class.
	 * @param[in] tokenizer The tokenizer to be used.
	 * @note This instance will claim the ownership of this tokenizer.
	 */
	IRJsonParser(IRJsonTokenizer * tokenizer);

	/**
	 * Creates a new instance of this class.
	 * @param[in] in The input data.
	 */
	IRJsonParser(const std::string & in);

	/**
	 * Disposes this instance and releases all associated resources.
	 */
	virtual ~IRJsonParser();

	/**
	 * Determines if there is more data to be parsed.
	 *
	 * @return true if there is more data to be parsed or false otherwise.
	 */
	bool hasMore() const {
		return this->_tokenizer->hasMore();
	}

	/**
	 * Restarts the parser and make it ready to be reused.
	 *
	 * @return true if the operation is supported by the underlying tokenizer or
	 * false otherwise.
	 */
	bool reset(){
		return this->_tokenizer->reset();
	}

	/**
	 * Parses the input looking for complete object.
	 *
	 * @return An instance of a IRJsonObject on success or null otherwise.
	 */
	virtual IRJsonObject * parseObject();
};

/**
 * Returns a reference to the given IRJsonBase as an IRJsonNull.
 *
 * @return The reference.
 * @exception std::invalid_argument If v cannot be converted to the desired type.
 * @since 2018.01.08
 */
const IRJsonNull & IRJsonAsNull(const IRJsonValue & v);

/**
 * Returns a reference to the given IRJsonBase as an IRJsonBoolean.
 *
 * @return The reference.
 * @exception std::invalid_argument If v cannot be converted to the desired type.
 * @since 2018.01.08
 */
const IRJsonBoolean & IRJsonAsBoolean(const IRJsonValue & v);

/**
 * Returns a reference to the given IRJsonBase as an IRJsonString.
 *
 * @return The reference.
 * @exception std::invalid_argument If v cannot be converted to the desired type.
 * @since 2018.01.08
 */
const IRJsonString & IRJsonAsString(const IRJsonValue & v);

/**
 * Returns a reference to the given IRJsonBase as an IRJsonDecimal.
 *
 * @return The reference.
 * @exception std::invalid_argument If v cannot be converted to the desired type.
 * @since 2018.01.08
 */
const IRJsonDecimal & IRJsonAsDecimal(const IRJsonValue & v);

/**
 * Returns a reference to the given IRJsonBase as an IRJsonInteger.
 *
 * @return The reference.
 * @exception std::invalid_argument If v cannot be converted to the desired type.
 * @since 2018.01.08
 */
const IRJsonInteger & IRJsonAsInteger(const IRJsonValue & v);

/**
 * Returns a reference to the given IRJsonBase as an IRJsonObject.
 *
 * @return The reference.
 * @exception std::invalid_argument If v cannot be converted to the desired type.
 * @since 2018.01.08
 */
const IRJsonObject & IRJsonAsObject(const IRJsonValue & v);

/**
 * Returns a reference to the given IRJsonBase as an IRJsonArray.
 *
 * @return The reference.
 * @exception std::invalid_argument If v cannot be converted to the desired type.
 * @since 2018.01.08
 */
const IRJsonArray & IRJsonAsArray(const IRJsonValue & v);

} //namespace json
} // namespace ircommon

#endif /* IRJSON_H_ */
