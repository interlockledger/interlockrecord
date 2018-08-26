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
#include "IRBaseSecureTempTest.h"
#include <ircommon/irutils.h>
#include <cstring>

using namespace ircommon;
using namespace ircommon::IRUtils;

//==============================================================================
// class IRBaseSecureTempTest
//------------------------------------------------------------------------------
IRBaseSecureTempTest::IRBaseSecureTempTest() {
}

//------------------------------------------------------------------------------
IRBaseSecureTempTest::~IRBaseSecureTempTest() {
}

//------------------------------------------------------------------------------
void IRBaseSecureTempTest::SetUp() {
}

//------------------------------------------------------------------------------
void IRBaseSecureTempTest::TearDown() {
}

//------------------------------------------------------------------------------
TEST_F(IRBaseSecureTempTest, Constructor) {
	IRBaseSecureTemp<std::uint16_t> * tmp;

	for (std::uint64_t size = 1; size <=16; size++) {
		tmp = new IRBaseSecureTemp<std::uint16_t>(size);
		ASSERT_EQ(size, tmp->size());
		ASSERT_EQ(0, tmp->position());
		delete tmp;
	}
}

//------------------------------------------------------------------------------
TEST_F(IRBaseSecureTempTest, size) {

	for (std::uint64_t size = 1; size <=16; size++) {
		IRBaseSecureTemp<std::uint16_t> tmp(size);
		ASSERT_EQ(size, tmp.size());
		for (std::uint64_t position = 0; position < tmp.size(); position++) {
			tmp.setPosition(position);
			ASSERT_EQ(size, tmp.size());
		}
	}
}

//------------------------------------------------------------------------------
TEST_F(IRBaseSecureTempTest, clear) {
	IRBaseSecureTemp<std::uint16_t> tmp(32);
	std::uint16_t expected[32];

	for (unsigned int i = 0; i < tmp.size(); i++) {
		tmp.buff()[i] = i;
	}
	std::memset(expected, 0, sizeof(expected));
	ASSERT_NE(0, std::memcmp(tmp.buff(), expected, sizeof(expected)));

	tmp.clear();
	ASSERT_EQ(0, std::memcmp(tmp.buff(), expected, sizeof(expected)));
}

//------------------------------------------------------------------------------
TEST_F(IRBaseSecureTempTest, buff) {
	IRBaseSecureTemp<std::uint16_t> tmp(32);
	IRBaseSecureTemp<std::uint16_t> & cTmp = tmp;

	for (unsigned int i = 0; i < tmp.size(); i++) {
		tmp.buff()[i] = i;
	}
	for (unsigned int i = 0; i < tmp.size(); i++) {
		ASSERT_EQ(i, tmp.buff()[i]);
		ASSERT_EQ(i, cTmp.buff()[i]);
	}
}

//------------------------------------------------------------------------------
TEST_F(IRBaseSecureTempTest, position) {
	IRBaseSecureTemp<std::uint16_t> tmp(32);
	IRBaseSecureTemp<std::uint16_t> & cTmp = tmp;

	ASSERT_EQ(0, tmp.position());
	for (unsigned int i = 0; i <= tmp.size(); i++) {
		tmp.setPosition(i);
		ASSERT_EQ(i, tmp.position());
		ASSERT_EQ(i, cTmp.position());
	}

	try {
		tmp.setPosition(33);
		FAIL();
	} catch (std::invalid_argument & e){}
}

//------------------------------------------------------------------------------
TEST_F(IRBaseSecureTempTest, reset) {
	IRBaseSecureTemp<std::uint16_t> tmp(32);
	IRBaseSecureTemp<std::uint16_t> & cTmp = tmp;

	ASSERT_EQ(0, tmp.position());
	for (unsigned int i = 0; i <= tmp.size(); i++) {
		tmp.setPosition(i);
		ASSERT_EQ(i, tmp.position());
		tmp.reset();
		ASSERT_EQ(0, cTmp.position());
	}
}

//------------------------------------------------------------------------------
TEST_F(IRBaseSecureTempTest, remaining) {
	IRBaseSecureTemp<std::uint16_t> tmp(32);
	IRBaseSecureTemp<std::uint16_t> & cTmp = tmp;

	tmp.clear();
	ASSERT_EQ(0, tmp.position());
	for (unsigned int i = 0; i <= tmp.size(); i++) {
		tmp.setPosition(i);
		std::uint64_t remaining = tmp.size() - i;
		ASSERT_EQ(remaining, tmp.remaining());
		ASSERT_EQ(remaining, cTmp.remaining());
	}
}

//------------------------------------------------------------------------------
TEST_F(IRBaseSecureTempTest, posBuff) {
	IRBaseSecureTemp<std::uint16_t> tmp(32);
	IRBaseSecureTemp<std::uint16_t> & cTmp = tmp;

	tmp.clear();
	ASSERT_EQ(0, tmp.position());
	for (unsigned int i = 0; i <= tmp.size(); i++) {
		tmp.setPosition(i);
		*tmp.posBuff() = i;
		ASSERT_EQ(i, tmp.buff()[i]);
		ASSERT_EQ(i, *cTmp.posBuff());
	}
}

//------------------------------------------------------------------------------
TEST_F(IRBaseSecureTempTest, indexOperator) {
	IRBaseSecureTemp<std::uint16_t> tmp(32);
	IRBaseSecureTemp<std::uint16_t> & cTmp = tmp;

	for (unsigned int i = 0; i <= tmp.size(); i++) {
		tmp.clear();
		tmp[i] = i;
		ASSERT_EQ(i, tmp.buff()[i]);
		ASSERT_EQ(i, tmp[i]);
		ASSERT_EQ(i, cTmp[i]);
	}
}

//------------------------------------------------------------------------------
