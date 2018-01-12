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
#include "IRIDGeneratorTest.h"
#include <stdlib.h>
#include <set>
#include <ircommon/iridgen.h>
using namespace ircommon;
using namespace ircommon::crypto;

//==============================================================================
// class IRIDGeneratorTest
//------------------------------------------------------------------------------
IRIDGeneratorTest::IRIDGeneratorTest() {
}

//------------------------------------------------------------------------------
IRIDGeneratorTest::~IRIDGeneratorTest() {
}

//------------------------------------------------------------------------------
void IRIDGeneratorTest::SetUp() {
}

//------------------------------------------------------------------------------
void IRIDGeneratorTest::TearDown() {
}

//------------------------------------------------------------------------------
TEST_F(IRIDGeneratorTest,Constructor) {
	IRIDGenerator * g;

	g = new IRIDGenerator(0);
	ASSERT_EQ(0, g->getCounter());
	delete g;
}

//------------------------------------------------------------------------------
TEST_F(IRIDGeneratorTest, setGetCounter) {
	IRIDGenerator g;

	for (int i = 0; i < 16; i++) {
		int v = rand();
		g.setCounter(v);
		ASSERT_EQ(v, g.getCounter());
	}
}

//------------------------------------------------------------------------------
TEST_F(IRIDGeneratorTest, next) {
	IRIDGenerator g;
	I32FeistelObfuscator o;
	std::set<std::uint32_t> dups;

	for (int i = 0; i < 64; i++) {
		int v = g.next();
		ASSERT_NE(0, v);
		ASSERT_EQ(dups.end(), dups.find(v));
		dups.insert(v);
	}

	g.setCounter(o.deobfuscate(0));
	ASSERT_NE(0, g.next());
}

//------------------------------------------------------------------------------

