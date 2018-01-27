/*
 * Copyright (c) 2017-2018, Open Communications Security
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
#ifndef _IRCOMMON_IRFP_H_
#define _IRCOMMON_IRFP_H_

namespace ircommon {

/**
 * This static class implements a few utilities that can be used to manipulate
 * IEEE754 values.
 *
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
 * @since 2018.01.19
 */
class IRFloatingPoint {
private:
	/**
	 * Static flag that caches the result of the big endian test.
	 */
	static bool _bigEndian;

	/**
	 * Static flag that caches the result of the little endian test.
	 */
	static bool _littleEndian;

	/**
	 * Static flag that caches the result of the IEEE754 test.
	 */
	static bool _IEEE754;

	static bool IsBigEndian();

	static bool IsLittleEndian();

	static bool IsIEEE754();
public:
	/**
	 * Indicates that the FPU unit works with big endian floating points.
	 *
	 * @return true If it is big endian or false otherwise.
	 */
	static bool BigEndian() {
		return IRFloatingPoint::_bigEndian;
	}

	/**
	 * Indicates that the FPU unit works with little endian floating points.
	 *
	 * @return true If it is little endian or false otherwise.
	 */
	static bool LittleEndian() {
		return IRFloatingPoint::_littleEndian;
	}

	/**
	 * Indicates if the FPU is compatible with IEEE754.
	 *
	 * @return true If it is compatible with IEEE754 or false otherwise.
	 */
	static bool IEEE754() {
		return IRFloatingPoint::_IEEE754;
	}

	/**
	 * Converts the buffer into a IEEE754 single precision (Big Endian).
	 *
	 * @param[in] bigEndian Assume big endian if true or little endian
	 * otherwise.
	 * @param[in] buff The input buffer. Must have at least 4 bytes.
	 * @return The floating point value.
	 */
	static float toSingle(bool bigEndian, const void * buff);

	/**
	 * Converts the buffer into a IEEE754 double precision.
	 *
	 * @param[in] bigEndian Assume big endian if true or little endian
	 * otherwise.
	 * @param[in] buff The input buffer. Must have at least 8 bytes.
	 * @return The floating point value.
	 */
	static double toDouble(bool bigEndian, const void * buff);

	/**
	 * Converts the given float value into a IEEE754 single precision.
	 *
	 * @param[in] bigEndian Assume big endian if true or little endian
	 * otherwise.
	 * @param[in] v The value to be converted.
	 * @param[out] buff The buffer that will receive the value. Must have at
	 * least 4 bytes.
	 */
	static void toBytes(bool bigEndian, float v, void * buff);

	/**
	 * Converts the given float value into a IEEE754 double precision.
	 *
	 * @param[in] bigEndian Assume big endian if true or little endian
	 * otherwise.
	 * @param[in] v The value to be converted.
	 * @param[out] buff The buffer that will receive the value. Must have at
	 * least 8 bytes.
	 */
	static void toBytes(bool bigEndian, double v, void * buff);

	/**
	 * Converts the buffer into a IEEE754 single precision.
	 *
	 * @param[in] bigEndian Assume big endian if true or little endian
	 * otherwise.
	 * @param[in] buff The input buffer. Must have at least 4 bytes.
	 * @param[out] v The value.
	 * @since 2018.01.27
	 */
	static void toFloat(bool bigEndian, const void * buff, float & v) {
		v = toSingle(bigEndian, buff);
	}

	/**
	 * Converts the buffer into a IEEE754 double precision.
	 *
	 * @param[in] bigEndian Assume big endian if true or little endian
	 * otherwise.
	 * @param[in] buff The input buffer. Must have at least 4 bytes.
	 * @param[out] v The value.
	 * @since 2018.01.27
	 */
	static void toFloat(bool bigEndian, const void * buff, double & v) {
		v = toDouble(bigEndian, buff);
	}
};

}

#endif /* _IRCOMMON_IRFP_H_ */
