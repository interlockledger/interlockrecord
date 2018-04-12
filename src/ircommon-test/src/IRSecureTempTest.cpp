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
#include "IRSecureTempTest.h"
#include <ircommon/irutils.h>

#include <cstdint>
#include <cstring>

using namespace std;
using namespace ircommon;

//==============================================================================
// class IRSecureTempTest
//------------------------------------------------------------------------------
IRSecureTempTest::IRSecureTempTest() {
}

//------------------------------------------------------------------------------
IRSecureTempTest::~IRSecureTempTest() {
}

//------------------------------------------------------------------------------
void IRSecureTempTest::SetUp() {
}

//------------------------------------------------------------------------------
void IRSecureTempTest::TearDown() {
}

//------------------------------------------------------------------------------
TEST_F(IRSecureTempTest,Constructor) {

	for (unsigned int size = 1; size <= 64; size++) {
		IRUtils::IRSecureTemp tmp(size);
		IRUtils::IRSecureTemp & rTmp = tmp;

		ASSERT_EQ(size, tmp.size());
		ASSERT_TRUE(tmp.buff() != nullptr);
		ASSERT_TRUE(tmp.buff() == rTmp.buff());

		std::uint8_t exp[size];
		std::memset(exp, 0, sizeof(exp));
		std::memset(tmp.buff(), 0xFA, tmp.size());
		tmp.clear();
		ASSERT_EQ(0, std::memcmp(exp, tmp.buff(), size));
	}
}
//------------------------------------------------------------------------------

