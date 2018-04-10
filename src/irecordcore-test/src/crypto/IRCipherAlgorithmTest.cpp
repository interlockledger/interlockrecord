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

