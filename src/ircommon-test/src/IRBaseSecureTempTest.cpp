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
