
#ifndef IRJSON_H_
#define IRJSON_H_

#include <string>
#include <cstdint>
#include <memory>
#include <map>
#include <vector>
#include <istream>

namespace ircommon {
namespace json {

/**
 * Base type for all JSON objects.
 *
 * @since 2018.01.04
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
 */
class IRJsonBase {
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
	IRJsonBase(JsonType type): _type(type) {}

	/**
	 * Disposes this instance and releases all associated resources.
	 */
	virtual ~IRJsonBase() = default;

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
};

/**
 * The template for all basic JSON values.
 *
 * @since 2018.01.04
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
 * @tparam ValueType The basic type of the value.
 * @tparam TypeID ID of the type.
 */
template <class ValueType, IRJsonBase::JsonType TypeID>
class IRJsonValue: public IRJsonBase {
private:
	/**
	 * The current value.
	 */
	ValueType _value;
public:
	/**
	 * Creates a new instance of this class.
	 */
	IRJsonValue(): IRJsonBase(TypeID), _value(){}

	/**
	 * Creates a new instance of this class.
	 *
	 * @param[in] value The initial value.
	 */
	IRJsonValue(const ValueType & value): IRJsonBase(TypeID), _value(value){}

	/**
	 * Disposes this instance and releases all associated resources.
	 */
	virtual ~IRJsonValue() = default;

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
	IRJsonValue & operator = (const ValueType & value) {
		this->set(value);
		return (*this);
	}
};

/**
 * JSON string. It uses std::string as its basic type.
 *
 * @since 2018.01.04
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
 */
typedef IRJsonValue<std::string, IRJsonBase::STRING> IRJsonString;

/**
 * JSON integer. It uses std::int64_t as its basic type.
 *
 * @since 2018.01.04
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
 */
typedef IRJsonValue<std::int64_t, IRJsonBase::INTEGER> IRJsonInteger;

/**
 * JSON decimal. It uses double as its basic type.
 *
 * @since 2018.01.04
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
 */
typedef IRJsonValue<double, IRJsonBase::DECIMAL> IRJsonDecimal;

/**
 * JSON boolean. It uses bool as its basic type.
 *
 * @since 2018.01.04
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
 */
typedef IRJsonValue<bool, IRJsonBase::BOOLEAN> IRJsonBoolean;

/**
 * JSON null. It uses bool as its basic type.
 *
 * @since 2018.01.04
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
 */
class IRJsonNull : public IRJsonBase {
public:
	/**
	 * Creates a new instance of this class.
	 */
	IRJsonNull(): IRJsonBase(IRJsonBase::NULL_VALUE){}

	/**
	 * Disposes this instance and releases all associated resources.
	 */
	virtual ~IRJsonNull() = default;
};

/**
 * JSON object. The values are referenced with std::shared_ptr in order to
 * avoid possible memory leaking.
 *
 * @since 2018.01.04
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
 */
class IRJsonObject: public IRJsonBase {
private:
	std::map<std::string, std::shared_ptr<IRJsonBase>> _map;
public:
	/**
	 * Creates a new instance of this class.
	 */
	IRJsonObject():IRJsonBase(IRJsonBase::OBJECT){}

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
	void set(const std::string & name, std::shared_ptr<IRJsonBase> value);

	/**
	 * Verifies if a given attribute exists.
	 *
	 * @param[in] name The name of the attribute.
	 * @return true if it exists or false otherwise.
	 */
	bool contains(const std::string & name) const;

	/**
	 * Grants read and write access to a given attribute.
	 *
	 * @param[in] name The name of the attribute.
	 * @return a shared_ptr to the attribute.
	 * @except std::invalid_argument If the name is not present.
	 */
	std::shared_ptr<IRJsonBase> & operator[](const std::string & name);

	/**
	 * Grants read access to a given attribute.
	 *
	 * @param[in] name The name of the attribute.
	 * @return a shared_ptr to the attribute.
	 * @except std::invalid_argument If the name is not present.
	 */
	const std::shared_ptr<IRJsonBase> & operator[](const std::string & name) const;

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
	void getAttributeNames(std::vector<std::string> & attr) const;
};

/**
 * JSON array. The values are referenced with std::shared_ptr in order to
 * avoid possible memory leaking.
 *
 * @since 2018.01.04
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
 */
class IRJsonArray: public IRJsonBase {
private:
	std::vector<std::shared_ptr<IRJsonBase>> _values;
public:
	/**
	 * Creates a new instance of this class.
	 */
	IRJsonArray() : IRJsonBase(IRJsonBase::ARRAY) {}

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
	 */
	std::shared_ptr<IRJsonBase> & operator[](int idx);

	/**
	 * Allows read-only access to the elements of this array.
	 *
	 * @param[in] idx The index of the element.
	 * @return A read-only reference to the given element.
	 */
	const std::shared_ptr<IRJsonBase> & operator[](int idx) const;

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
	void insert(int idx, const std::shared_ptr<IRJsonBase> value);

	/**
	 * Inserts a new element into the end of the array.
	 *
	 * @param[in] value The value to be added.
	 */
	void append(const std::shared_ptr<IRJsonBase> value);
};

/**
 * JSON serializer. It follows the JSON syntax defined by RFC8259.
 *
 * @since 2018.01.04
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
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
	void serialize(const IRJsonBase & v, std::string & out);
};

/**
 * JSON tokenizer. It tokenizes a string using the JSON syntax defined by
 * RFC8259.
 *
 * @since 2018.01.04
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
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
	std::string _token;
	std::string _in;
	int _pos;

	int getc();
	void ungetc();

	static bool isSpace(int c);

	static bool isHex(int c);

	static bool isDigit(int c);

	static bool isKeywordChar(int c);

	bool ignoreComment();

	void ignoreSpaces();

	TokenType extractString();

	TokenType extractNumeric();

	TokenType extractKeyword();
public:
	/**
	 * Creates a new instance of this class.
	 * @param[in] in The input string that will be parsed.
	 */
	IRJsonTokenizer(const std::string & in);

	/**
	 * Creates a new instance of this class.
	 *
	 * @param[in] in The input string that will be parsed.
	 */
	IRJsonTokenizer(const char * in);

	/**
	 * Creates a new instance of this class.
	 *
	 * @param[in] in The input string that will be parsed.
	 * @param[in] size The number of characters inside in.
	 */
	IRJsonTokenizer(const char * in, int size);

	/**
	 * Creates a new instance of this class.
	 *
	 * @param[in] in The input string that will be parsed.
	 * @param[in] start The starting point.
	 * @param[in] size The number of characters to be used.
	 */
	IRJsonTokenizer(const std::string & in, int start, int size);

	/**
	 * Disposes this instance and releases all associated resources.
	 */
	virtual ~IRJsonTokenizer() = default;

	/**
	 * Position of the reading point.
	 *
	 * @return The current reading point.
	 */
	int position() const {
		return this->_pos;
	}

	/**
	 * Verifies if there is more data to be processed.
	 *
	 * @return true if there is more data or false otherwise.
	 */
	bool hasMore() const {
		return (this->_pos == this->_in.size());
	}

	/**
	 * Resets this instance.
	 */
	void reset();

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
};

class IRJsonParser {
private:
	IRJsonTokenizer * _tokenizer;

	IRJsonObject * parsePartialObject();

	IRJsonArray * parsePartialArray();

	IRJsonBase * parsePartialAny(IRJsonTokenizer::TokenType type);
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

	virtual ~IRJsonParser();

	bool hasMore() const {
		return this->_tokenizer->hasMore();
	}

	void reset(){
		this->_tokenizer->reset();
	}

	virtual IRJsonObject * parseObject();

	virtual IRJsonBase * parseAny();
};

} //namespace json
} // namespace ircommon

#endif /* IRJSON_H_ */
