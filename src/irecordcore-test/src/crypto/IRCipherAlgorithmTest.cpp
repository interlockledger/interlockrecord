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
#include "IRCipherAlgorithmTest.h"
#include <irecordcore/ircipher.h>

using namespace irecordcore::crypto;

//==============================================================================
// class IRDummyCipherAlgorithm
//------------------------------------------------------------------------------
class IRDummyCipherAlgorithm: public IRCipherAlgorithm {
public:
	IRDummyCipherAlgorithm(bool cipherMode):IRCipherAlgorithm(cipherMode){}

	virtual ~IRDummyCipherAlgorithm() = default;

	virtual bool process(const void * src, std::uint64_t srcSize,
			void * dst, std::uint64_t & dstSize);

	virtual unsigned int minKeySize() const;

	virtual unsigned int maxKeySize() const;

	virtual bool isValidKeySize(unsigned int keySize) const;
};

//------------------------------------------------------------------------------
bool IRDummyCipherAlgorithm::process(const void * src, std::uint64_t srcSize,
		void * dst, std::uint64_t & dstSize) {
	return false;
}

//------------------------------------------------------------------------------
unsigned int IRDummyCipherAlgorithm::minKeySize() const {
	return 0;
}

//------------------------------------------------------------------------------
unsigned int IRDummyCipherAlgorithm::maxKeySize() const {
	return 0;
}

//------------------------------------------------------------------------------
bool IRDummyCipherAlgorithm::isValidKeySize(unsigned int keySize) const {
	return false;
}


//==============================================================================
// class IRCipherAlgorithmTest
//------------------------------------------------------------------------------
IRCipherAlgorithmTest::IRCipherAlgorithmTest() {
}

//------------------------------------------------------------------------------
IRCipherAlgorithmTest::~IRCipherAlgorithmTest() {
}

//------------------------------------------------------------------------------
void IRCipherAlgorithmTest::SetUp() {
}

//------------------------------------------------------------------------------
void IRCipherAlgorithmTest::TearDown() {
}

//------------------------------------------------------------------------------
TEST_F(IRCipherAlgorithmTest,Constructor) {
	IRDummyCipherAlgorithm * c;

	c = new IRDummyCipherAlgorithm(true);
	ASSERT_TRUE(c->cipherMode());
	delete c;

	c = new IRDummyCipherAlgorithm(false);
	ASSERT_FALSE(c->cipherMode());
	delete c;
}

//------------------------------------------------------------------------------

