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
