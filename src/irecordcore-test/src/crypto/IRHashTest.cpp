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
