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

	/**
	 * Returns the size of the encoded value based on the first encoded byte.
	 *
	 * @param[in] prefix The value of the first byte.
	 * @return The number bytes of te encoded data.
	 * @since 2018.01.22
	 */
	inline static int encodedSize(int prefix) {
		if (prefix < ILINT_BASE) {
			return 1;
		} else {
			return 2 + (prefix & 0x07);
		}
	}

	/**
	 * Decodes the ILInt values.
	 *
	 * @param[in] inp The value to be decoded.
	 * @param[in] inpSize The size of inp.
	 * @param[out] v The output value.
	 * @return The number of bytes read from inp or 0 in case of failure.
	 * @since 2018.01.27
	 */
	static int decode(const void * inp, int inpSize, uint64_t & v) {
		return decode(inp, inpSize, &v);
	}
};

} //namespace ircommon

#endif //__ILCOMMON_ILINT_H__

