
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
	void set(const std::string & name, std::shared_ptr<IRJsonBase> & value);

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
	IRJsonArray() : IRJsonBase(IRJsonBase::ARRAY) {}

	virtual ~IRJsonArray() = default;

	int size() const {
		return this->_values.size();
	}

	std::shared_ptr<IRJsonBase> & operator[](int idx);

	const std::shared_ptr<IRJsonBase> & operator[](int idx) const;

	void remove(int idx);

	void insert(int idx, const std::shared_ptr<IRJsonBase> & value);

	void append(const std::shared_ptr<IRJsonBase> & value);
};

class IRJsonSerializer {
protected:
	bool _indent;

	int _level;

	void levelUp();
	void levelDown();
	void beginLine(std::string & out);
	void endLine(std::string & out);
	void serializeNull(std::string & out);
	void serializeString(std::string & out, const IRJsonString & v);
	void serializeString(std::string & out, const std::string & v);
	void serializeInteger(std::string & out, const IRJsonInteger & v);
	void serializeDecimal(std::string & out, const IRJsonDecimal & v);
	void serializeBoolean(std::string & out, const IRJsonBoolean & v);
	void serializeObject(std::string & out, const IRJsonObject & v);
	void serializeArray(std::string & out, const IRJsonArray & v);
public:
	IRJsonSerializer(bool indent = false): _indent(indent), _level(0) {}

	virtual ~IRJsonSerializer() = default;

	void serialize(std::string & out, const IRJsonBase & v);
};

/**
 * JSON tokenizer.
 *
 * @since 2018.01.04
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
 */
class IRJsonTokenizer {
public:
	typedef enum {
		OBJ_BEGIN,
		OBJ_END,
		ARRAY_BEGIN,
		ARRAY_END,
		NAME_SEP,
		VALUE_SEP,
		VAL_STRING,
		VAL_TRUE,
		VAL_FALSE,
		VAL_INT,
		VAL_DEC,
		VAL_NULL,
		INVALID,
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
	IRJsonTokenizer(const std::string & in);

	IRJsonTokenizer(const char * in);

	IRJsonTokenizer(const char * in, int size);

	IRJsonTokenizer(const std::string & in, int start, int size);

	virtual ~IRJsonTokenizer() = default;

	int position() const {
		return this->_pos;
	}

	void reset();

	TokenType next();

	const std::string value() const {
		return this->_token;
	}

	/**
	 * Converts a unicode point into its UTF-8 representation.
	 *
	 * @param[out] out The output string.
	 * @param[in] c The unicode point from U+0000 to U+10FFFF.
	 */
	static void unicodeToUTF8(std::string & out, int c);
};

} //namespace json
} // namespace ircommon

#endif /* IRJSON_H_ */
