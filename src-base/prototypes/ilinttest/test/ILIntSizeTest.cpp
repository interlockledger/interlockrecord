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
#include "ILIntSizeTest.h"
#include "ilint.h"

//==============================================================================
// class ILIntSizeTest
//------------------------------------------------------------------------------
ILIntSizeTest::ILIntSizeTest() {
}

//------------------------------------------------------------------------------
ILIntSizeTest::~ILIntSizeTest() {
}

//------------------------------------------------------------------------------
void ILIntSizeTest::SetUp() {
}

//------------------------------------------------------------------------------
void ILIntSizeTest::TearDown() {
}

//------------------------------------------------------------------------------
TEST_F(ILIntSizeTest, Size) {

	ASSERT_EQ(1, ILIntSize(0));
	ASSERT_EQ(1, ILIntSize(247));

	ASSERT_EQ(2, ILIntSize(248));
	ASSERT_EQ(2, ILIntSize(0xFF + 248));

	ASSERT_EQ(3, ILIntSize(0xFF + 248 + 1));
	ASSERT_EQ(3, ILIntSize(0xFFFF + 248));

	ASSERT_EQ(4, ILIntSize(0xFFFF + 248 + 1));
	ASSERT_EQ(4, ILIntSize(0xFFFFFF + 248));

	ASSERT_EQ(5, ILIntSize(0xFFFFFF + 248 + 1));
	ASSERT_EQ(5, ILIntSize(0xFFFFFFFFl + 248));

	ASSERT_EQ(6, ILIntSize(0xFFFFFFFFl + 248 + 1));
	ASSERT_EQ(6, ILIntSize(0xFFFFFFFFFFl + 248));

	ASSERT_EQ(7, ILIntSize(0xFFFFFFFFFFl + 248 + 1));
	ASSERT_EQ(7, ILIntSize(0xFFFFFFFFFFFFl + 248));

	ASSERT_EQ(8, ILIntSize(0xFFFFFFFFFFFFl + 248 + 1));
	ASSERT_EQ(8, ILIntSize(0xFFFFFFFFFFFFFFl + 248));

	ASSERT_EQ(9, ILIntSize(0xFFFFFFFFFFFFFFl + 248 + 1));
	ASSERT_EQ(9, ILIntSize(0xFFFFFFFFFFFFFFFFl));
}
//------------------------------------------------------------------------------

