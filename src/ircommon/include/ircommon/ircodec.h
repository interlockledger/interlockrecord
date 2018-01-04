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
#ifndef __IRCOMMON_IRCODEC_H__
#define __IRCOMMON_IRCODEC_H__

#include <ircommon/iralphab.h>
#include <string>
#include <memory>
#include <cstdint>

namespace ircommon {

/**
 * This is the base class for all binary-to-text encoders. This code is loosely
 * based on the code from https://github.com/opencs/ocsbincodec-c.
 *
 * @since 2017.12.28
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
 */
class IRCodec {
protected:
	/**
	 * Implements the actual encoding. This method is called if and only if
	 * all parameters are valid.
	 *
	 * @param[in] src The source data. It will never be NULL.
	 * @param[in] srcSize The size of source.
	 * @note This method should not handle the padding, just the encoding.
	 */
	virtual void encodeCore(const std::uint8_t * src, int srcSize,
			std::string & dst) const = 0;

	/**
	 * Implements the actual decoder. This method is called if and only if
	 * all parameters are valid.
	 *
	 * @param[in] src The source data. It will never be NULL.
	 * @param[in] srcSize The size of src.
	 * @param[out] dst The destination buffer. Its size will always be equal or
	 * greater than getDecodedSize(srcSize).
	 * @param[out] dstSize The actual size of the output.
	 * @return true on success or false otherwise.
	 * @note This method should not handle the padding, just the decoding.
	 */
	virtual bool decodeCore(const char * src, int srcSize,
			std::uint8_t * dst, int & dstSize) const = 0;

	/**
	 * Computes the size of the encoded data without the padding. It is called
	 * by IRCodec::decode(const std::string&,int,int,void*,int&) in order to
	 * determine the actual size of the data without the padding.
	 *
	 * @param[in] src The encoded data.
	 * @param[in] srcSize The size of the encoded data.
	 * @return The new srcSize without the padding or -1 if the padding is
	 * invalid.
	 * @note The default implementation always return srcSize.
	 */
	virtual int removePadding(const char * src, int srcSize) const;

	/**
	 * Adds the padding if necessary. This method is called by
	 * IRCodec::encode(const void *,int,std::string&) in order to add the
	 * padding to the end of the encoded data.
	 *
	 * @param[in,out] dst The encoded data.
	 * @param[in] encodedSize The number of characters already in the output.
	 * @note The default implementation does nothing.
	 */
	virtual void addPadding(std::string & dst, int encodedSize) const;
public:
	IRCodec() = default;

	virtual ~IRCodec() = default;

	virtual int getEncodedSize(int srcSize) const = 0;

	virtual int getDecodedSize(int srcSize) const = 0;

	/**
	 * Encodes the binary value.
	 *
	 * @param[in] src The binary value.
	 * @param[in] srcSize Size of src in bytes.
	 * @param[out] dst The output string. The encoded value will be appended to
	 * this string.
	 * @return The number of characters added to dst.
	 */
	virtual int encode(const void * src, int srcSize, std::string & dst) const;

	/**
	 * Decodes the binary value.
	 *
	 * @param[in] src The encoded data.
	 * @param[in] srcStart Offset of the encoded data inside src.
	 * @param[in] srcSize Number of characters of the encoded data.
	 * @param[out] dst The buffer that will receive the data. It must have at
	 * least the same number of bytes returned by getDecodedSize(int).
	 * @param[int,out] dstSize On input, it is the number of bytes available in
	 * dst. On output, it is the actual size of the data.
	 * @return true on success or false otherwise.
	 */
	virtual bool decode(const std::string & src, int srcStart, int srcSize,
			void * dst, int & dstSize) const;

	/**
	 * Decodes the binary value. It is a convenience method that calls
	 * IRCodec::decode(const std::string&,int,int,void*,int&).
	 *
	 * @param[in] src The encoded data.
	 * @param[out] dst The buffer that will receive the data. It must have at
	 * least the same number of bytes returned by getDecodedSize(int).
	 * @param[int,out] dstSize On input, it is the number of bytes available in
	 * dst. On output, it is the actual size of the data.
	 * @return true on success or false otherwise.
	 */
	virtual bool decode(const std::string & src, void * dst, int & dstSize) const {
		return this->decode(src, 0, src.size(), dst, dstSize);
	}
};

/**
 * This class implements a Base 2^n codec. It can encode/decode data using any
 * 2^n base such as binary, hexadecimal and other encodings schemes described in
 * RFC4648 such as Base 32 and Base 64.
 *
 * @note In order to determine if a given character is a space or not, this
 * class calls the function isspace() from STL using std::locale::classic() as
 * locale.
 *
 * @since 2017.12.28
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
 */
class IRBase2NCodec : public IRCodec {
private:
	std::shared_ptr<IRAlphabet> _alphabet;
	int _blockSize;
	int _paddingChar;
	int _clearMask;
	int _charSize;
	bool _ignoreSpaces;
protected:
	virtual void encodeCore(const std::uint8_t * src, int srcSize,
			std::string & dst) const;

	virtual bool decodeCore(const char * src, int srcSize,
			std::uint8_t * dst, int & dstSize) const;

	virtual int removePadding(const char * src, int srcSize) const;

	virtual void addPadding(std::string & dst, int encodedSize) const;

	/**
	 * Verifies if a given character must be ignored or not.
	 *
	 * @param[in] c The character to be tested.
	 * @return true if the character must be ignored or false otherwise.
	 */
	virtual bool isIgnored(int c) const;
public:
	/**
	 * Creates a new instance of this class. This class will only accept
	 * alphabets with 2, 4, 8, 16, 32, 64 or 128 characters.
	 *
	 * @param[in] alphabet the alphabet to be used. It must be passed as a
	 * std::shared_ptr in order to allow the sharing of this instance among
	 * multiple instances.
	 * @param[in] blockSize The size of the padding block. Use zero to disable
	 * the padding.
	 * @param[in] paddingChar Character that should be used as padding.
	 * @param[in] ignoreSpaces Flag that determines if this instance will ignore
	 * space characters while decoding.
	 * @exception std::invalid_argument If the alphabet size is not valid.
	 */
	IRBase2NCodec(const std::shared_ptr<IRAlphabet> & alphabet, int blockSize = 0,
			int paddingChar = '=', bool ignoreSpaces = false);

	/**
	 * Disposes this instance and releases all associated resources. The
	 * instance of alphabet used by this class will also be disposed.
	 */
	virtual ~IRBase2NCodec() = default;

	virtual int getEncodedSize(int srcSize) const;

	virtual int getDecodedSize(int srcSize) const;

	/**
	 * The size of the padding block. Zero or negative values indicates that the
	 * padding should not be used.
	 */
	int blockSize() const {
		return this->_blockSize;
	}

	/**
	 * Size of the characters in bits.
	 */
	int characterSize() const {
		return this->_charSize;
	}

	/**
	 * The padding character.
	 */
	int paddingCharacter() const {
		return this->_paddingChar;
	}

	/**
	 * Verifies if this instance ignores space characters. It is false by
	 * default.
	 *
	 * @return true if the spaces are ignored or false otherwise.
	 */
	bool ignoreSpaces() const {
		return this->_ignoreSpaces;
	}

	/**
	 * The value of the clear mask. It always have the least characterSize()
	 * bits set to 1.
	 */
	int clearMask() const {
		return this->_clearMask;
	}

	/**
	 * The alphabet used by this instance.
	 */
	const IRAlphabet & alphabet() const {
		return *(this->_alphabet);
	}

	/**
	 * Allow access to the shared pointer to the inner alphabet.
	 */
	const std::shared_ptr<IRAlphabet> & sharedAlphabet() const {
		return this->_alphabet;
	}
};

} //namespace ircommon

#endif /* __IRCOMMON_IRCODEC_H__ */
