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
	ASSERT_EQ(0, p->paddingSize());
	delete p;
}

//------------------------------------------------------------------------------
TEST_F(IRPaddingTest, paddingSize) {
	IRDummyPadding p;

	ASSERT_EQ(0, p.paddingSize());
	for (unsigned int paddingSize = 1; paddingSize <= 8; paddingSize++) {
		p.setPaddingSize(paddingSize);
		ASSERT_EQ(paddingSize, p.paddingSize());
	}
}

//------------------------------------------------------------------------------
TEST_F(IRPaddingTest, getPaddedSize) {
	IRDummyPadding p;

	for (unsigned int blockSize = 1; blockSize <= 8; blockSize++) {
		for (unsigned int paddingSize = 0; paddingSize <= 8; paddingSize++) {
			p.setPaddingSize(paddingSize);
			for (std::uint64_t srcSize = 0; srcSize <= 16; srcSize++) {
				ASSERT_EQ(p.getPaddingSize(blockSize, srcSize) + srcSize,
						p.getPaddedSize(blockSize, srcSize));
			}
		}
	}
}

//------------------------------------------------------------------------------

