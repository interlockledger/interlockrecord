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
#include "IRCodecTest.h"

#include <ircommon/ircodec.h>
#include <cstring>
using namespace ircommon;
using namespace ircommon::codec;

//==============================================================================
// class IRDummyCodec - This class implements a NULL codec that will be used for
// testing.
//------------------------------------------------------------------------------
class IRDummyCodec: public IRCodec{
protected:
	virtual void encodeCore(const std::uint8_t * src, int srcSize,
			std::string & dst) const;

	virtual bool decodeCore(const char * src, int srcSize,
			std::uint8_t * dst, int & dstSize) const;
public:
	IRDummyCodec() = default;

	virtual ~IRDummyCodec() = default;

	void encodeCoreExt(const std::uint8_t * src, int srcSize,
			std::string & dst) const {
		this->encodeCore(src, srcSize, dst);
	}

	bool decodeCoreExt(const char * src, int srcSize,
			std::uint8_t * dst, int & dstSize) const {
		return this->decodeCore(src, srcSize, dst, dstSize);
	}

	int removePaddingExt(const char * src, int srcSize) const {
		return this->removePadding(src, srcSize);
	}

	void addPaddingEx(std::string & dst, int encodedSize) const {
		return this->addPadding(dst, encodedSize);
	}

	virtual int getEncodedSize(int srcSize) const;

	virtual int getDecodedSize(int srcSize) const;
};

//------------------------------------------------------------------------------
void IRDummyCodec::encodeCore(const std::uint8_t * src, int srcSize,
		std::string & dst) const {
	const std::uint8_t * srcEnd;

	srcEnd = src + srcSize;
	for (; src < srcEnd; src++) {
		dst.append(1, (char)*src);
	}
}

//------------------------------------------------------------------------------
bool IRDummyCodec::decodeCore(const char * src, int srcSize,
		std::uint8_t * dst, int & dstSize) const {
	const char * srcEnd;

	srcEnd = src + srcSize;
	for (; src < srcEnd; src++, dst++) {
		if ((*src) != 0) {
			*dst = std::uint8_t(*src);
		} else {
			return false;
		}
	}
	dstSize = srcSize;
	return true;
}

//------------------------------------------------------------------------------
int IRDummyCodec::getEncodedSize(int srcSize) const {

	return srcSize + 4;
}

//------------------------------------------------------------------------------
int IRDummyCodec::getDecodedSize(int srcSize) const {
	return srcSize + 4;
}

//==============================================================================
// class IRCodecTest
//------------------------------------------------------------------------------
IRCodecTest::IRCodecTest() {
}

//------------------------------------------------------------------------------
IRCodecTest::~IRCodecTest() {
}

//------------------------------------------------------------------------------
void IRCodecTest::SetUp() {
}

//------------------------------------------------------------------------------
void IRCodecTest::TearDown() {
}

//------------------------------------------------------------------------------
TEST_F(IRCodecTest, Constructor) {
	IRCodec * c;

	c = new IRDummyCodec();
	delete c;
}

//------------------------------------------------------------------------------
TEST_F(IRCodecTest, addPadding) {
	IRDummyCodec c;
	std::string dst;

	for (int i = 0; i < 100; i++) {
		dst = "";
		c.addPaddingEx(dst, i);
		ASSERT_STREQ("", dst.c_str());
	}
}

//------------------------------------------------------------------------------
TEST_F(IRCodecTest, removePadding) {
	IRDummyCodec c;
	std::string src;

	src = "0123456789";
	for (unsigned int i = 0; i <= src.size(); i++) {
		ASSERT_EQ(i, c.removePaddingExt(src.c_str(), i));
	}
}

//------------------------------------------------------------------------------
TEST_F(IRCodecTest, getEncodedSize) {
	IRDummyCodec c;

	for (int i = 0; i < 100; i++) {
		ASSERT_EQ(i + 4, c.getEncodedSize(i));
	}
}

//------------------------------------------------------------------------------
TEST_F(IRCodecTest, getDecodedSize) {
	IRDummyCodec c;

	for (int i = 0; i < 100; i++) {
		ASSERT_EQ(i + 4, c.getDecodedSize(i));
	}
}

//------------------------------------------------------------------------------
TEST_F(IRCodecTest, encodeCore) {
	IRDummyCodec c;
	std::string src;
	std::string dst;

	src = "0123456789";
	dst = "";
	c.encodeCoreExt((const std::uint8_t*)src.c_str(), src.size(), dst);
	ASSERT_EQ(src, dst);

	src = "0123456789";
	dst = "1";
	c.encodeCoreExt((const std::uint8_t*)src.c_str(), src.size(), dst);
	ASSERT_STREQ("10123456789", dst.c_str());
}

//------------------------------------------------------------------------------
TEST_F(IRCodecTest, decodeCore) {
	IRDummyCodec c;
	std::string src;
	std::uint8_t dst[32];
	int dstSize;

	src = "0123456789";
	dstSize = src.size();
	ASSERT_TRUE(c.decodeCoreExt(src.c_str(), src.size(), dst, dstSize));
	ASSERT_EQ(src.size(), dstSize);
	ASSERT_EQ(0, std::memcmp(src.c_str(), dst, dstSize));

	src = "0123456789";
	dstSize = src.size();
	std::memset(dst, 0, sizeof(dst));
	ASSERT_TRUE(c.decodeCoreExt(src.c_str(), src.size(), dst + 1, dstSize));
	ASSERT_EQ(src.size(), dstSize);
	ASSERT_EQ(0, dst[0]);
	ASSERT_EQ(0, dst[dstSize + 1]);
	ASSERT_EQ(0, std::memcmp(src.c_str(), dst + 1, dstSize));

	// This decodeCore implementation fails if it finds the character '\0'
	src = "0123456789";
	dstSize = src.size() + 1;
	ASSERT_FALSE(c.decodeCoreExt(src.c_str(), src.size() + 1, dst, dstSize));
}

//------------------------------------------------------------------------------
TEST_F(IRCodecTest, encode) {
	IRDummyCodec c;
	std::string src;
	std::string dst;
	int encSize;

	src = "0123456789";
	dst = "";
	encSize = c.encode(src.c_str(), src.size(), dst);
	ASSERT_EQ(src.size(), encSize);
	ASSERT_STREQ(src.c_str(), dst.c_str());

	src = "0123456789";
	dst = "1";
	encSize = c.encode(src.c_str(), src.size(), dst);
	ASSERT_EQ(src.size(), encSize);
	ASSERT_STREQ("10123456789", dst.c_str());

	ASSERT_EQ(-1, c.encode(NULL, src.size(), dst));
	ASSERT_EQ(-1, c.encode(src.c_str(), -1, dst));
}

//------------------------------------------------------------------------------
TEST_F(IRCodecTest, decode) {
	IRDummyCodec c;
	std::string src;
	char dst[32];
	int dstSize;

	src = "0123456789";
	std::memset(dst, 0, sizeof(dst));
	dstSize = c.getDecodedSize(src.size());
	ASSERT_TRUE(c.decode(src, dst, dstSize));
	ASSERT_EQ(src.size(), dstSize);
	ASSERT_EQ(0, std::memcmp(src.c_str(), dst, dstSize));

	src = "0123456789";
	std::memset(dst, 0, sizeof(dst));
	dstSize = c.getDecodedSize(src.size());
	ASSERT_TRUE(c.decode(src, dst + 1, dstSize));
	ASSERT_EQ(src.size(), dstSize);
	ASSERT_EQ(0, dst[0]);
	ASSERT_EQ(0, dst[src.size() + 1]);
	ASSERT_EQ(0, std::memcmp(src.c_str(), dst + 1, dstSize));

	src = "0123456789";
	std::memset(dst, 0, sizeof(dst));
	dstSize = c.getDecodedSize(src.size()) - 1;
	ASSERT_FALSE(c.decode(src, dst, dstSize));

	src = "0123456789";
	std::memset(dst, 0, sizeof(dst));
	dstSize = c.getDecodedSize(src.size());
	ASSERT_FALSE(c.decode(src, NULL, dstSize));

	src = "0123456789";
	src.append(1, 0);
	std::memset(dst, 0, sizeof(dst));
	dstSize = c.getDecodedSize(src.size());
	ASSERT_FALSE(c.decode(src, dst, dstSize));
}

//------------------------------------------------------------------------------
TEST_F(IRCodecTest, decodeRanged) {
	IRDummyCodec c;
	std::string src;
	char dst[32];
	int dstSize;

	src = "0123456789";
	std::memset(dst, 0, sizeof(dst));
	dstSize = c.getDecodedSize(src.size());
	ASSERT_TRUE(c.decode(src, 0, src.size(), dst, dstSize));
	ASSERT_EQ(src.size(), dstSize);
	ASSERT_EQ(0, std::memcmp(src.c_str(), dst, dstSize));

	src = "0123456789";
	std::memset(dst, 0, sizeof(dst));
	dstSize = c.getDecodedSize(src.size() - 2);
	ASSERT_TRUE(c.decode(src, 1, src.size() - 2, dst, dstSize));
	ASSERT_EQ(src.size()- 2, dstSize);
	ASSERT_EQ(0, std::memcmp(src.c_str() + 1, dst, dstSize));

	src = "0123456789";
	std::memset(dst, 0, sizeof(dst));
	dstSize = c.getDecodedSize(src.size());
	ASSERT_FALSE(c.decode(src, 1, src.size(), dst, dstSize));

	src = "0123456789";
	std::memset(dst, 0, sizeof(dst));
	dstSize = c.getDecodedSize(src.size());
	ASSERT_FALSE(c.decode(src, src.size(), 1, dst, dstSize));

	src = "0123456789";
	std::memset(dst, 0, sizeof(dst));
	dstSize = c.getDecodedSize(src.size());
	ASSERT_FALSE(c.decode(src, -1, src.size(), dst, dstSize));

	src = "0123456789";
	std::memset(dst, 0, sizeof(dst));
	dstSize = c.getDecodedSize(src.size());
	ASSERT_FALSE(c.decode(src, 0, -1, dst, dstSize));

	src = "0123456789";
	std::memset(dst, 0, sizeof(dst));
	dstSize = c.getDecodedSize(src.size());
	ASSERT_FALSE(c.decode(src, 0, src.size(), NULL, dstSize));

	src = "0123456789";
	std::memset(dst, 0, sizeof(dst));
	dstSize = -1;
	ASSERT_FALSE(c.decode(src, 0, src.size(), dst, dstSize));
}
//------------------------------------------------------------------------------


