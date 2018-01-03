/*
 * Copyright (c) 2017, Open Communications Security
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
#ifndef __IRCOMMON_IRALPHAB_H__
#define __IRCOMMON_IRALPHAB_H__

#include <stdexcept>

namespace ircommon {

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

} //namespace ircommon

#endif /* __IRCOMMON_IRALPHAB_H__ */
