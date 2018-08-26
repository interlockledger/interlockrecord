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
#ifndef __IRCOMMON_IRALPHAB_H__
#define __IRCOMMON_IRALPHAB_H__

#include <stdexcept>

namespace ircommon {
namespace codec {

// This implementation is loosely based on the original code from
// https://github.com/opencs/ocsbincodec-c

//------------------------------------------------------------------------------
/**
 * This class implements the interface of an alphabet suitable to be used by
 * text-to-binary codecs.
 *
 * <p>By contract, this class is expected to be immutable once created.
 * Furthermore, all methods with the exception of the constructor and the
 * destructor must be thread safe.</p>
 *
 * @since 2017.12.28
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
 */
class IRAlphabet{
private:
	int _size;
public:
	/**
	 * Creates a new instance of this class with a given size.
	 *
	 * @param[in] size The size of the alphabet. It must be greater than 1.
	 * @except std::invalid_argument If size is invalid
	 */
	IRAlphabet(int size);

	/**
	 * Disposes this instance and releases all associated resources.
	 */
	virtual ~IRAlphabet() = default;

	/**
	 * Returns the size of this alphabet.
	 *
	 * @return The size of this alphabet.
	 */
	int size() const {
		return this->_size;
	}

	/**
	 * Returns the value of the character.
	 *
	 * @param[in] c The character.
	 * @return The value of the character or -1 if the character is invalid.
	 */
	virtual int getValue(int c) const = 0;

	/**
	 * Returns the alphabet character.
	 *
	 * @param[in] v The value.
	 * @return The character.
	 */
	virtual int getChar(int v) const = 0;
};

//------------------------------------------------------------------------------
/**
 * This class implements a generic alphabet suitable to be used by
 * text-to-binary codecs. This implementation allows the use any string as the
 * map.
 *
 * @since 2017.12.28
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
 */
class IRGenericAlphabet: public IRAlphabet {
private:
	char * _map;
public:
	/**
	 * Creates a new instance of this class.
	 *
	 * @param[in] map The map of characters. All characters must be distinct.
	 * @param[in] mapSize The size of the map.
	 */
	IRGenericAlphabet(const char * map, int mapSize);

	/**
	 * Disposes this instance and releases all associated resources.
	 */
	virtual ~IRGenericAlphabet();

	/**
	 * Returns the value of the character.
	 *
	 * @param[in] c The character.
	 * @return The value of the character or -1 if the character is invalid.
	 * @note This method always performs a sequential scan on the mapping.
	 */
	virtual int getValue(int c) const;

	/**
	 * Returns the alphabet character.
	 *
	 * @param[in] v The value.
	 * @return The character.
	 */
	virtual int getChar(int v) const;
};

//------------------------------------------------------------------------------
/**
 * This class implements the binary alphabet suitable to be used by
 * text-to-binary codecs. This implementation allows the use any string as the
 * map.
 *
 * @since 2017.12.28
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
 */
class IRBinaryAlphabet: public IRAlphabet {
private:
	/**
	 * The map.
	 */
	char _map[2];
public:
	/**
	 * Creates a new instance of this class.
	 *
	 * @param[in] f Character for false.
	 * @param[in] t Character for true.
	 * @except std::invalid_argument If f is equal to t.
	 */
	IRBinaryAlphabet(char f = '0', char t = '1');

	/**
	 * Disposes this instance and releases all associated resources.
	 */
	virtual ~IRBinaryAlphabet() = default;

	/**
	 * Returns the value of the character.
	 *
	 * @param[in] c The character.
	 * @return The value of the character or -1 if the character is invalid.
	 */
	virtual int getValue(int c) const;

	/**
	 * Returns the alphabet character.
	 *
	 * @param[in] v The value.
	 * @return The character.
	 */
	virtual int getChar(int v) const;
};

//------------------------------------------------------------------------------
/**
 * This class implements an hexadecimal alphabet suitable to be used by
 * text-to-binary codecs. This implementation allows the use any string as the
 * map.
 *
 * <p>This implementation allows the output of upper case or lower case mapping
 * but will always accept both cases on decoding.</p>
 *
 * @since 2017.12.28
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
 */
class IRHexAlphabet: public IRAlphabet {
private:
	/**
	 * The map.
	 */
	const char * _map;
public:
	/**
	 * Creates a new instance of this class.
	 *
	 * @param[in] lower If true, the output will be in lower case, otherwise
	 * the output will be in upper case.
	 */
	IRHexAlphabet(bool lower = false);

	/**
	 * Disposes this instance and releases all associated resources.
	 */
	virtual ~IRHexAlphabet();

	/**
	 * Returns the value of the character.
	 *
	 * @param[in] c The character.
	 * @return The value of the character or -1 if the character is invalid.
	 */
	virtual int getValue(int c) const;

	/**
	 * Returns the alphabet character.
	 *
	 * @param[in] v The value.
	 * @return The character.
	 */
	virtual int getChar(int v) const;
};

//------------------------------------------------------------------------------
/**
 * This class implements an Base32 (RFC4648) alphabet suitable to be used by
 * text-to-binary codecs. This implementation allows the use any string as the
 * map.
 *
 * <p>This implementation allows the output of upper case or lower case mapping
 * but will always accept both cases on decoding.</p>
 *
 * @since 2017.12.28
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
 */
class IRBase32Alphabet: public IRAlphabet {
private:
	/**
	 * Flag that indicates the use of the extended hex instead of the normal
	 * alphabet.
	 */
	bool _extendedHex;
	/**
	 * The current mapping.
	 */
	const char * _map;
public:
	enum {
		/**
		 * Size of the default padding block size for Base32 (RFC4648).
		 */
		DEFAULT_PADDING = 8,
		/**
		 * Size of the default padding character for base32 (RFC4648).
		 */
		DEFAULT_PADDING_CHAR = '='
	};

	/**
	 * Creates a new instance of this class.
	 *
	 * @param[in] extendedHex If true, it will use the Extended Hex alphabet
	 * defined by the RFC4648.
	 */
	IRBase32Alphabet(bool lower = false, bool extendedHex = false);

	/**
	 * Disposes this instance and releases all associated resources.
	 */
	virtual ~IRBase32Alphabet();

	/**
	 * Returns the value of the character.
	 *
	 * @param[in] c The character.
	 * @return The value of the character or -1 if the character is invalid.
	 */
	virtual int getValue(int c) const;

	/**
	 * Returns the alphabet character.
	 *
	 * @param[in] v The value.
	 * @return The character.
	 */
	virtual int getChar(int v) const;
};

//------------------------------------------------------------------------------
/**
 * This class implements an Base64 (RFC4648) alphabet suitable to be used by
 * text-to-binary codecs. This implementation allows the use any string as the
 * map.
 *
 * <p>This implementation allows the output of upper case or lower case mapping
 * but will always accept both cases on decoding.</p>
 *
 * @since 2017.12.28
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
 */
class IRBase64Alphabet: public IRAlphabet {
private:
	char _map[64];
public:
	enum {
		/**
		 * Size of the default padding block size for Base64 (RFC4648).
		 */
		DEFAULT_PADDING = 4,
		/**
		 * Size of the default padding character for base64 (RFC4648).
		 */
		DEFAULT_PADDING_CHAR = '='
	};

	/**
	 * Creates a new instance of this class.
	 *
	 * @param[in] url If true, it will use the URL safe alphabet
	 * defined by the RFC4648.
	 */
	IRBase64Alphabet(bool url = false);

	/**
	 * Creates a new instance of this class.
	 *
	 * @param[in] s62 The character for the value 62.
	 * @param[in] s63 The character for the value 63.
	 */
	IRBase64Alphabet(int s62, int s63);

	/**
	 * Disposes this instance and releases all associated resources.
	 */
	virtual ~IRBase64Alphabet();

	/**
	 * Returns the value of the character.
	 *
	 * @param[in] c The character.
	 * @return The value of the character or -1 if the character is invalid.
	 */
	virtual int getValue(int c) const;

	/**
	 * Returns the alphabet character.
	 *
	 * @param[in] v The value.
	 * @return The character.
	 */
	virtual int getChar(int v) const;
};

} // namespace codec
} //namespace ircommon

#endif /* __IRCOMMON_IRALPHAB_H__ */
