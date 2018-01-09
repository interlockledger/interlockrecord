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
#include "IRJsonIntegerTest.h"
#include <ircommon/irjson.h>
using namespace ircommon::json;

//==============================================================================
// class IRJsonIntegerTest
//------------------------------------------------------------------------------
IRJsonIntegerTest::IRJsonIntegerTest() {
}

//------------------------------------------------------------------------------
IRJsonIntegerTest::~IRJsonIntegerTest() {
}

//------------------------------------------------------------------------------
void IRJsonIntegerTest::SetUp() {
}

//------------------------------------------------------------------------------
void IRJsonIntegerTest::TearDown() {
}

//------------------------------------------------------------------------------
TEST_F(IRJsonIntegerTest,Constructor) {
	IRJsonInteger * i;

	i = new IRJsonInteger();
	ASSERT_EQ(IRJsonValue::INTEGER, i->type());
	ASSERT_EQ(0, i->get());
	delete i;

	i = new IRJsonInteger(123456789012ll);
	ASSERT_EQ(IRJsonValue::INTEGER, i->type());
	ASSERT_EQ(123456789012ll, i->get());
	delete i;
}

//------------------------------------------------------------------------------
TEST_F(IRJsonIntegerTest,getSet) {
	IRJsonInteger i;

	ASSERT_EQ(0, i.get());
	i.set(123456789012ll);
	ASSERT_EQ(123456789012ll, i.get());
}

//------------------------------------------------------------------------------
TEST_F(IRJsonIntegerTest, as) {
	IRJsonInteger i;

	try{
		i.asBoolean();
		FAIL();
	} catch(std::domain_error & e){}
	try{
		i.asDecimal();
		FAIL();
	} catch(std::domain_error & e){}
	try{
		i.asString();
		FAIL();
	} catch(std::domain_error & e){}
	ASSERT_EQ(0, i.asInteger());
}

//------------------------------------------------------------------------------
TEST_F(IRJsonIntegerTest, equals) {
	IRJsonInteger a(1);
	IRJsonInteger b(1);
	IRJsonInteger c(2);

	ASSERT_TRUE(a.equals(a));
	ASSERT_TRUE(a.equals(b));
	ASSERT_FALSE(a.equals(c));

	ASSERT_FALSE(a.equals(IRJsonArray()));
	ASSERT_FALSE(a.equals(IRJsonBoolean()));
	ASSERT_FALSE(a.equals(IRJsonDecimal()));
	ASSERT_FALSE(a.equals(IRJsonInteger()));
	ASSERT_FALSE(a.equals(IRJsonNull()));
	ASSERT_FALSE(a.equals(IRJsonObject()));
	ASSERT_FALSE(a.equals(IRJsonString()));
}
//------------------------------------------------------------------------------

