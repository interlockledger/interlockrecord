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
	 */
	virtual bool decodeCore(const char * src, int srcSize,
			std::uint8_t * dst, int & dstSize) const = 0;

	/**
	 * Computes the size of the encoded data without the padding.
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
	 * encode(const void *,int,std::string&) in order to add the padding to the
	 * end of the encoded data.
	 *
	 * @param[in,out] dst The encoded data.
	 * @param[in] encodedSize The number of characters already in the output.
	 * @note The default implementation does nothing.
	 */
	virtual void addPadding(std::string & dst, int encodedSize) const;
public:
	IRCodec();

	virtual ~IRCodec();

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
	 * Decodes the binary value.
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

class IRBase2NCodec {
private:
	IRAlphabet * _alphabet;
protected:
	/**
	 * Implements the actual encoding. This method is called if and only if
	 * all parameters are valid.
	 *
	 * @param[in] src The source data. It will never be NULL.
	 * @param[in] srcSize The size of source.
	 */
	virtual void encodeCore(const std::uint8_t * src, int srcSize,
			std::string & dst) const;

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
	 */
	virtual bool decodeCore(const char * src, int srcSize,
			std::uint8_t * dst, int & dstSize) const;

	/**
	 * Verifies if a given character must be ignored or not.
	 *
	 * @param[in] c The character to be tested.
	 * @return true if the character must be ignored or false otherwise.
	 */
	virtual bool isIgnored(int c) const;
public:
	/**
	 * Creates a new instance of this class.
	 *
	 * @param[in] alphabet the alphabet to be used. This contructor will claim
	 * the ownership of this instance.
	 * @param[in] blockSize The size of the padding block. use zero to disable
	 * the padding.
	 */
	IRBase2NCodec(IRAlphabet * alphabet, int blockSize = 0, int paddingChar = 0);

	virtual ~IRBase2NCodec();

	virtual int getEncodedSize(int srcSize) const = 0;

	virtual int getDecodedSize(int srcSize) const = 0;

};

} //namespace ircommon

#endif /* __IRCOMMON_IRCODEC_H__ */
