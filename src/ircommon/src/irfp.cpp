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
#include <cstdint>
#include <ircommon/irfp.h>
using namespace ircommon;

/**
 * Value of PI as a floating point.
 */
#define IRFloatingPoint_FLOAT_PI 3.1415927410f

//==============================================================================
// Class IRFloatingPoint
//------------------------------------------------------------------------------
bool IRFloatingPoint::_bigEndian = IRFloatingPoint::IsBigEndian();

//------------------------------------------------------------------------------
bool IRFloatingPoint::_littleEndian = IRFloatingPoint::IsLittleEndian();

//------------------------------------------------------------------------------
bool IRFloatingPoint::_IEEE754 = IRFloatingPoint::IsIEEE754();

//------------------------------------------------------------------------------
bool IRFloatingPoint::IsBigEndian() {
	float f = 0;
	std::uint8_t * p;

	p = (std::uint8_t *)&f;
	p[0] = 0x40;
	p[1] = 0x49;
	p[2] = 0x0f;
	p[3] = 0xdb;
	return (f == IRFloatingPoint_FLOAT_PI);
}

//------------------------------------------------------------------------------
bool IRFloatingPoint::IsLittleEndian() {
	float f = 0;
	std::uint8_t * p;

	p = (std::uint8_t *)&f;
	p[3] = 0x40;
	p[2] = 0x49;
	p[1] = 0x0f;
	p[0] = 0xdb;
	return (f == IRFloatingPoint_FLOAT_PI);
}

//------------------------------------------------------------------------------
bool IRFloatingPoint::IsIEEE754() {
	return (IRFloatingPoint::IsBigEndian() != IRFloatingPoint::IsLittleEndian());
}

//------------------------------------------------------------------------------
float IRFloatingPoint::toSingle(bool bigEndian, const void * buff) {
	float f = 0;

	if (IRFloatingPoint::BigEndian() == bigEndian) {
		f = *((const float *)buff);
	} else {
		std::uint8_t * dst = (std::uint8_t *)&f;
		const std::uint8_t * src = (const std::uint8_t *)buff;
		dst[0] = src[3];
		dst[1] = src[2];
		dst[2] = src[1];
		dst[3] = src[0];
	}
	return f;
}

//------------------------------------------------------------------------------
double IRFloatingPoint::toDouble(bool bigEndian, const void * buff) {
	double d = 0;

	if (IRFloatingPoint::BigEndian() == bigEndian) {
		d = *((const double *)buff);
	} else {
		std::uint8_t * dst = (std::uint8_t *)&d;
		const std::uint8_t * src = (const std::uint8_t *)buff;
		dst[0] = src[7];
		dst[1] = src[6];
		dst[2] = src[5];
		dst[3] = src[4];
		dst[4] = src[3];
		dst[5] = src[2];
		dst[6] = src[1];
		dst[7] = src[0];
	}
	return d;
}

//------------------------------------------------------------------------------
void IRFloatingPoint::toBytes(bool bigEndian, float v, void * buff) {

	if (IRFloatingPoint::BigEndian() == bigEndian) {
		*((float *)buff) = v;
	} else {
		std::uint8_t * dst = (std::uint8_t *)buff;
		std::uint8_t * src = (std::uint8_t *)&v;
		dst[0] = src[3];
		dst[1] = src[2];
		dst[2] = src[1];
		dst[3] = src[0];
	}
}

//------------------------------------------------------------------------------
void IRFloatingPoint::toBytes(bool bigEndian, double v, void * buff) {

	if (IRFloatingPoint::BigEndian() == bigEndian) {
		*((double *)buff) = v;
	} else {
		std::uint8_t * dst = (std::uint8_t *)buff;
		std::uint8_t * src = (std::uint8_t *)&v;
		dst[0] = src[7];
		dst[1] = src[6];
		dst[2] = src[5];
		dst[3] = src[4];
		dst[4] = src[3];
		dst[5] = src[2];
		dst[6] = src[1];
		dst[7] = src[0];
	}
}

//------------------------------------------------------------------------------
