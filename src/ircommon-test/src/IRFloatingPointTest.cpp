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
#include "IRFloatingPointTest.h"
#include <ircommon/irfp.h>
using namespace ircommon;

//==============================================================================
// class IRFloatingPointTest
//------------------------------------------------------------------------------
IRFloatingPointTest::IRFloatingPointTest() {
}

//------------------------------------------------------------------------------
IRFloatingPointTest::~IRFloatingPointTest() {
}

//------------------------------------------------------------------------------
void IRFloatingPointTest::SetUp() {
}

//------------------------------------------------------------------------------
void IRFloatingPointTest::TearDown() {
}

//------------------------------------------------------------------------------
float IRFloatingPointTest::GetFloatSample(std::uint32_t v) {
	float f = 0;
	std::uint8_t * p =(std::uint8_t *)&f;

	if (IRFloatingPoint::BigEndian()) {
		p = p + 3;
		for (int i = 0; i < 4; i++) {
			*p = v & 0xFF;
			v = v >> 8;
			p--;
		}
	} else {
		for (int i = 0; i < 4; i++) {
			*p = v & 0xFF;
			v = v >> 8;
			p++;
		}
	}
	return f;
}

//------------------------------------------------------------------------------
double IRFloatingPointTest::GetDoubleSample(std::uint64_t v) {
	double d = 0;
	std::uint8_t * p =(std::uint8_t *)&d;

	if (IRFloatingPoint::BigEndian()) {
		p = p + 7;
		for (int i = 0; i < 8; i++) {
			*p = (v & 0xFF);
			v = v >> 8;
			p--;
		}
	} else {
		for (int i = 0; i < 8; i++) {
			*p = (v & 0xFF);
			v = v >> 8;
			p++;
		}
	}
	return d;
}

//------------------------------------------------------------------------------
TEST_F(IRFloatingPointTest, BigEndian) {
	float f = -0.0f;
	std::uint8_t * p;

	p = (std::uint8_t *)&f;
	ASSERT_EQ(p[0] == 0x80, IRFloatingPoint::BigEndian());
}

//------------------------------------------------------------------------------
TEST_F(IRFloatingPointTest, LittleEndian) {
	float f = -0.0f;
	std::uint8_t * p;

	p = (std::uint8_t *)&f;
	ASSERT_EQ(p[3] == 0x80, IRFloatingPoint::LittleEndian());
}

//------------------------------------------------------------------------------
TEST_F(IRFloatingPointTest, IEEE754) {
	ASSERT_TRUE(IRFloatingPoint::IEEE754());
}

//------------------------------------------------------------------------------
TEST_F(IRFloatingPointTest, toSingle) {
	const std::uint8_t srcBE[sizeof(float)] = {0x01, 0x23, 0x45, 0x67};
	const std::uint8_t srcLE[sizeof(float)] = {0x67, 0x45, 0x23, 0x01};
	float f;

	f = IRFloatingPointTest::GetFloatSample(0x01234567);
	ASSERT_EQ(f, IRFloatingPoint::toSingle(true, srcBE));
	ASSERT_EQ(f, IRFloatingPoint::toSingle(false, srcLE));
}

//------------------------------------------------------------------------------
TEST_F(IRFloatingPointTest, toDouble) {
	const std::uint8_t srcBE[sizeof(double)] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF};
	const std::uint8_t srcLE[sizeof(double)] = {0xEF, 0xCD, 0xAB, 0x89, 0x67, 0x45, 0x23, 0x01};
	double d;

	d = IRFloatingPointTest::GetDoubleSample(0x0123456789ABCDEFl);
	ASSERT_EQ(d, IRFloatingPoint::toDouble(true, srcBE));
	ASSERT_EQ(d, IRFloatingPoint::toDouble(false, srcLE));
}

//------------------------------------------------------------------------------
TEST_F(IRFloatingPointTest, toBytesFloat) {
	const std::uint8_t srcBE[sizeof(float)] = {0x01, 0x23, 0x45, 0x67};
	const std::uint8_t srcLE[sizeof(float)] = {0x67, 0x45, 0x23, 0x01};
	std::uint8_t dst[sizeof(float)];
	float f;

	f = IRFloatingPointTest::GetFloatSample(0x01234567);
	IRFloatingPoint::toBytes(true, f, dst);
	ASSERT_EQ(0, memcmp(dst, srcBE, sizeof(dst)));
	IRFloatingPoint::toBytes(false, f, dst);
	ASSERT_EQ(0, memcmp(dst, srcLE, sizeof(dst)));
}

//------------------------------------------------------------------------------
TEST_F(IRFloatingPointTest, toBytesDouble) {
	const std::uint8_t srcBE[sizeof(double)] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF};
	const std::uint8_t srcLE[sizeof(double)] = {0xEF, 0xCD, 0xAB, 0x89, 0x67, 0x45, 0x23, 0x01};
	std::uint8_t dst[sizeof(double)];
	double d;

	d = IRFloatingPointTest::GetDoubleSample(0x0123456789ABCDEFl);
	IRFloatingPoint::toBytes(true, d, dst);
	ASSERT_EQ(0, memcmp(dst, srcBE, sizeof(dst)));
	IRFloatingPoint::toBytes(false, d, dst);
	ASSERT_EQ(0, memcmp(dst, srcLE, sizeof(dst)));
}

//------------------------------------------------------------------------------
TEST_F(IRFloatingPointTest, toFloatSingle) {
	const std::uint8_t srcBE[sizeof(float)] = {0x01, 0x23, 0x45, 0x67};
	const std::uint8_t srcLE[sizeof(float)] = {0x67, 0x45, 0x23, 0x01};
	float f;
	float v;

	f = IRFloatingPointTest::GetFloatSample(0x01234567);
	IRFloatingPoint::toFloat(true, srcBE, v);
	ASSERT_EQ(f, v);
	IRFloatingPoint::toFloat(false, srcLE, v);
	ASSERT_EQ(f, v);
}

//------------------------------------------------------------------------------
TEST_F(IRFloatingPointTest, toFloatDouble) {
	const std::uint8_t srcBE[sizeof(double)] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF};
	const std::uint8_t srcLE[sizeof(double)] = {0xEF, 0xCD, 0xAB, 0x89, 0x67, 0x45, 0x23, 0x01};
	double d;
	double v;

	d = IRFloatingPointTest::GetDoubleSample(0x0123456789ABCDEFl);
	IRFloatingPoint::toFloat(true, srcBE, v);
	ASSERT_EQ(d, v);
	IRFloatingPoint::toFloat(false, srcLE, v);
	ASSERT_EQ(d, v);
}

//------------------------------------------------------------------------------
