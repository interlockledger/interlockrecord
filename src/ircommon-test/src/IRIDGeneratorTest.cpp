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

