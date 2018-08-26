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
#include "IRHashAlgorithmTest.h"
#include <irecordcore/irhash.h>

using namespace irecordcore;
using namespace irecordcore::crypto;

//==============================================================================
// class DummyIRHash
//------------------------------------------------------------------------------
class DummyIRHashAlgorithm: public IRHashAlgorithm {
private:
	 std::uint64_t _size;
public:
	 DummyIRHashAlgorithm(std::uint64_t size):IRHashAlgorithm(), _size(size){}

	virtual ~DummyIRHashAlgorithm() = default;

	virtual void reset();

	virtual std::uint64_t size() const;

	virtual void update(const void * buff, std::uint64_t size);

	virtual bool finalize(void * out, std::uint64_t size);
};

//------------------------------------------------------------------------------
void DummyIRHashAlgorithm::reset() {
}

//------------------------------------------------------------------------------
std::uint64_t DummyIRHashAlgorithm::size() const {
	return this->_size;
}

//------------------------------------------------------------------------------
void DummyIRHashAlgorithm::update(const void * buff, std::uint64_t size) {
}

//------------------------------------------------------------------------------
bool DummyIRHashAlgorithm::finalize(void * out, std::uint64_t size) {
	return false;
}

//==============================================================================
// class IRHashAlgorithmTest
//------------------------------------------------------------------------------
IRHashAlgorithmTest::IRHashAlgorithmTest() {
}

//------------------------------------------------------------------------------
IRHashAlgorithmTest::~IRHashAlgorithmTest() {
}

//------------------------------------------------------------------------------
void IRHashAlgorithmTest::SetUp() {
}

//------------------------------------------------------------------------------
void IRHashAlgorithmTest::TearDown() {
}

//------------------------------------------------------------------------------
TEST_F(IRHashAlgorithmTest,Constructor) {
	DummyIRHashAlgorithm * h;

	h = new DummyIRHashAlgorithm(1);
	ASSERT_EQ(1, h->size());
	delete h;
}

//------------------------------------------------------------------------------
TEST_F(IRHashAlgorithmTest, sizeInBytes) {

	for(std::uint64_t i = 0; i < 128; i++) {
		DummyIRHashAlgorithm h(i);
		ASSERT_EQ(i / 8, h.sizeInBytes());
	}
}

//------------------------------------------------------------------------------

