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
#include "IRPaddingTest.h"
#include <irecordcore/irciphpd.h>

using namespace irecordcore::crypto;

//==============================================================================
// class IRPaddingTest
//------------------------------------------------------------------------------
class IRDummyPadding : public IRPadding {
private:
	unsigned int _paddingSize;
public:
	IRDummyPadding(): _paddingSize(0) {	}

	virtual ~IRDummyPadding() = default;

	unsigned int paddingSize() const {
		return this->_paddingSize;
	}

	void setPaddingSize(unsigned int paddingSize) {
		this->_paddingSize = paddingSize;
	}

	virtual std::uint64_t getPaddingSize(unsigned int blockSize,
			std::uint64_t srcSize) const;

	virtual bool addPadding(unsigned int blockSize, const void * src,
			std::uint64_t srcSize, void * dst, std::uint64_t & dstSize) const;

	virtual bool removePadding(unsigned int blockSize,
			const void * src, std::uint64_t & srcSize) const;
};

//------------------------------------------------------------------------------
std::uint64_t IRDummyPadding::getPaddingSize(unsigned int blockSize,
		std::uint64_t srcSize) const {
	return this->paddingSize();
}

//------------------------------------------------------------------------------
bool IRDummyPadding::addPadding(unsigned int blockSize, const void * src,
		std::uint64_t srcSize, void * dst, std::uint64_t & dstSize) const{
	return false;
}


//------------------------------------------------------------------------------
bool IRDummyPadding::removePadding(unsigned int blockSize,
		const void * src, std::uint64_t & srcSize) const {
	return false;
}

//==============================================================================
// class IRPaddingTest
//------------------------------------------------------------------------------
IRPaddingTest::IRPaddingTest() {
}

//------------------------------------------------------------------------------
IRPaddingTest::~IRPaddingTest() {
}

//------------------------------------------------------------------------------
void IRPaddingTest::SetUp() {
}

//------------------------------------------------------------------------------
void IRPaddingTest::TearDown() {
}

//------------------------------------------------------------------------------
TEST_F(IRPaddingTest, Constructor) {
	IRDummyPadding * p;

	p = new IRDummyPadding();
	delete p;
}

//------------------------------------------------------------------------------
TEST_F(IRPaddingTest, getPaddingSize) {
	IRDummyPadding p;

	for (unsigned int blockSize = 1; blockSize <= 8; blockSize++) {
		for (std::uint64_t srcSize = 0; srcSize <= 16; srcSize++) {
			ASSERT_EQ(blockSize - (srcSize % blockSize),
					p.getPaddingSize(blockSize, srcSize));
		}
	}
}

//------------------------------------------------------------------------------
TEST_F(IRPaddingTest, getPaddedSize) {
	IRDummyPadding p;

	for (unsigned int blockSize = 1; blockSize <= 8; blockSize++) {
		for (std::uint64_t srcSize = 0; srcSize <= 16; srcSize++) {
			ASSERT_EQ(blockSize - (srcSize % blockSize) + srcSize,
					p.getPaddedSize(blockSize, srcSize));
		}
	}
}

//------------------------------------------------------------------------------

