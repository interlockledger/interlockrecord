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
