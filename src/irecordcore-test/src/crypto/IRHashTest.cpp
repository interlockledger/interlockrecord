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
#include "IRHashTest.h"
#include <irecordcore/irhash.h>

using namespace irecordcore;
using namespace irecordcore::crypto;

//==============================================================================
// class DummyIRHash
//------------------------------------------------------------------------------
class DummyIRHash: public IRHash {
public:
	DummyIRHash(IRHashAlg type):IRHash(type) {}
	virtual ~DummyIRHash() = default;

	virtual void reset();

	virtual std::uint64_t size() const;

	virtual void update(const void * buff, std::uint64_t size);

	virtual bool finalize(void * out, std::uint64_t size);
};

//------------------------------------------------------------------------------
void DummyIRHash::reset() {
}

//------------------------------------------------------------------------------
std::uint64_t DummyIRHash::size() const {
	return 0;
}

//------------------------------------------------------------------------------
void DummyIRHash::update(const void * buff, std::uint64_t size) {
}

//------------------------------------------------------------------------------
bool DummyIRHash::finalize(void * out, std::uint64_t size) {
	return false;
}

//==============================================================================
// class IRHashTest
//------------------------------------------------------------------------------
IRHashTest::IRHashTest() {
}

//------------------------------------------------------------------------------
IRHashTest::~IRHashTest() {
}

//------------------------------------------------------------------------------
void IRHashTest::SetUp() {
}

//------------------------------------------------------------------------------
void IRHashTest::TearDown() {
}

//------------------------------------------------------------------------------
TEST_F(IRHashTest, Constructor) {
	IRHash * h;

	h = new DummyIRHash(IR_HASH_SHA1);
	ASSERT_EQ(IR_HASH_SHA1, h->type());
	ASSERT_EQ(0, h->size());
	delete h;

	h = new DummyIRHash(IR_HASH_SHA256);
	ASSERT_EQ(IR_HASH_SHA256, h->type());
	ASSERT_EQ(0, h->size());
	delete h;
}

//------------------------------------------------------------------------------
TEST_F(IRHashTest, type) {
	IRHashAlg types[6] = {
		IR_HASH_SHA1,
		IR_HASH_SHA256,
		IR_HASH_SHA512,
		IR_HASH_SHA3_256,
		IR_HASH_SHA3_512,
		IR_HASH_COPY};

	for (int i = 0; i < 6; i++) {
		DummyIRHash h(types[i]);
		ASSERT_EQ(types[i], h.type());
	}
}

//------------------------------------------------------------------------------
