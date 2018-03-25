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
#include "IRSecretKeyGeneratorTest.h"
#include <irecordcore/irkeygen.h>

using namespace irecordcore::crypto;

//==============================================================================
// class IRSecretKeyGeneratorTest
//------------------------------------------------------------------------------
class IRDummySecretKeyGenerator: public IRSecretKeyGenerator{
public:
	IRDummySecretKeyGenerator() = default;

	virtual ~IRDummySecretKeyGenerator() = default;

	virtual bool generateRaw(void * key, unsigned int keySize);

	virtual IRSecretKey * generate();
};

//------------------------------------------------------------------------------
bool IRDummySecretKeyGenerator::generateRaw(void * key, unsigned int keySize) {
	return false;
}

//------------------------------------------------------------------------------
IRSecretKey * IRDummySecretKeyGenerator::generate() {
	return nullptr;
}

//==============================================================================
// class IRSecretKeyGeneratorTest
//------------------------------------------------------------------------------
IRSecretKeyGeneratorTest::IRSecretKeyGeneratorTest() {
}

//------------------------------------------------------------------------------
IRSecretKeyGeneratorTest::~IRSecretKeyGeneratorTest() {
}

//------------------------------------------------------------------------------
void IRSecretKeyGeneratorTest::SetUp() {
}

//------------------------------------------------------------------------------
void IRSecretKeyGeneratorTest::TearDown() {
}

//------------------------------------------------------------------------------
TEST_F(IRSecretKeyGeneratorTest, Constructor) {
	IRSecretKeyGenerator * kg;

	kg = new IRDummySecretKeyGenerator();
	ASSERT_EQ(0, kg->keySize());
	delete kg;
}

//------------------------------------------------------------------------------
TEST_F(IRSecretKeyGeneratorTest, setKeySize) {
	IRDummySecretKeyGenerator kg;

	for (int size = 0; size <= 512; size += 8) {
		ASSERT_TRUE(kg.setKeySize(size));
		ASSERT_EQ(size, kg.keySize());
	}

	ASSERT_TRUE(kg.setKeySize(8));
	for (int size = 1; size < 8; size++) {
		ASSERT_FALSE(kg.setKeySize(size));
		ASSERT_EQ(8, kg.keySize());
	}
}

//------------------------------------------------------------------------------
TEST_F(IRSecretKeyGeneratorTest, keySize) {
	IRDummySecretKeyGenerator kg;

	ASSERT_EQ(0, kg.keySize());
	for (int size = 0; size <= 512; size += 8) {
		ASSERT_TRUE(kg.setKeySize(size));
		ASSERT_EQ(size, kg.keySize());
	}
}

//------------------------------------------------------------------------------
TEST_F(IRSecretKeyGeneratorTest, keySizeInBytes) {
	IRDummySecretKeyGenerator kg;

	ASSERT_EQ(0, kg.keySizeInBytes());
	for (int size = 0; size <= 512; size += 8) {
		ASSERT_TRUE(kg.setKeySize(size));
		ASSERT_EQ(size / 8, kg.keySizeInBytes());
	}
}

//------------------------------------------------------------------------------

