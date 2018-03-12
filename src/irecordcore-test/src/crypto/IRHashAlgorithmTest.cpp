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

	for(std::uint64_t i; i < 128; i++) {
		DummyIRHashAlgorithm h(i);
		ASSERT_EQ(i / 8, h.sizeInBytes());
	}
}

//------------------------------------------------------------------------------

