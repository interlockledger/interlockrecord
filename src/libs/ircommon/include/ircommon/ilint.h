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
#ifndef __ILCOMMON_ILINT_H__
#define __ILCOMMON_ILINT_H__

#include <cstdint>

namespace ircommon {

/**
 * This class implements an ILInt value.
 *
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
 * @since 2017.10.13
 */
class ILInt {
private:
	std::uint64_t _value;
public:
	enum {
		/**
		 * LInt base value. All values larger then or equal to will use more
		 * than 1 byte to be encoded.
		 */
		ILINT_BASE = 0xF8
	};

	ILInt(std::uint64_t value);

	ILInt(const ILInt & value);

	virtual ~ILInt();

	const std::uint64_t value() const {
		return this->_value;
	}

	void setValue(std::uint64_t value) {
		this->_value = value;
	}

	/**
	 * Returns the number of bytes required to encode this value.
	 *
	 * @return The number of bytes required to store the value.
	 */
	int size() const {
		return size(this->_value);
	}

	/**
	 * Returns the number of bytes required to encode the given value.
	 *
	 * @param[in] v The value to be encoded.
	 * @return The number of bytes required to store the value.
	 */
	static int size(uint64_t v);

	/**
	 * Encodes the value v into the ILInt value.
	 *
	 * @param[out] out The output buffer.
	 * @param[in] outSize The number of bytes in out.
	 * @return The number of bytes used or 0 in case of failure.
	 */
	int encode(void * out, int outSize) const {
		return encode(this->_value, out, outSize);
	}

	/**
	 * Encodes the value v into the ILInt value.
	 *
	 * @param[in] v The value.
	 * @param[out] out The output buffer.
	 * @param[in] outSize The number of bytes in out.
	 * @return The number of bytes used or 0 in case of failure.
	 */
	static int encode(uint64_t v, void * out, int outSize);

	/**
	 * Decodes the ILInt values.
	 *
	 * @param[in] inp The value to be decoded.
	 * @param[in] inpSize The size of inp.
	 * @return The number of bytes read from inp or 0 in case of failure.
	 */
	int decode(const void * inp, int inpSize);

	/**
	 * Decodes the ILInt values.
	 *
	 * @param[in] inp The value to be decoded.
	 * @param[in] inpSize The size of inp.
	 * @param[out] v The output value.
	 * @return The number of bytes read from inp or 0 in case of failure.
	 */
	static int decode(const void * inp, int inpSize, uint64_t * v);

	ILInt & operator=(const ILInt & v) {
		this->_value = v._value;
		return *this;
	}

	ILInt & operator=(std::uint64_t & v) {
		this->_value = v;
		return *this;
	}

	operator std::uint64_t() const {
		return this->value();
	}

};

} //namespace ircommon

#endif //__ILCOMMON_ILINT_H__

