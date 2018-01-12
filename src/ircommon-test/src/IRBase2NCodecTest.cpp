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
#include "IRBase2NCodecTest.h"
#include <ircommon/ircodec.h>
#include <algorithm>
#include <cstring>
#include <locale>
#include <stdlib.h>

using namespace ircommon;
using namespace ircommon::codec;

// Samples from https://tools.ietf.org/html/rfc4648
#define IRBase2NCodecTest_RFC4648_BASE64_NP_SIZE (7 * 2)
static const char * IRBase2NCodecTest_RFC4648_BASE64_NP[IRBase2NCodecTest_RFC4648_BASE64_NP_SIZE] = {
		"", 		"",
		"f", 		"Zg",
		"fo", 		"Zm8",
		"foo", 		"Zm9v",
		"foob", 	"Zm9vYg",
		"fooba", 	"Zm9vYmE",
		"foobar",	"Zm9vYmFy"};

#define IRBase2NCodecTest_RFC4648_BASE64_SIZE (7 * 2)
static const char * IRBase2NCodecTest_RFC4648_BASE64[IRBase2NCodecTest_RFC4648_BASE64_SIZE] = {
		"", 		"",
		"f", 		"Zg==",
		"fo", 		"Zm8=",
		"foo", 		"Zm9v",
		"foob", 	"Zm9vYg==",
		"fooba", 	"Zm9vYmE=",
		"foobar",	"Zm9vYmFy"};

//==============================================================================
// class IRDummyBase2NCodec
//------------------------------------------------------------------------------
class IRDummyBase2NCodec: public IRBase2NCodec {
public:
	IRDummyBase2NCodec(std::shared_ptr<IRAlphabet> alphabet, int blockSize = 0,
			int paddingChar = '=', bool ignoreSpaces = false);

	virtual ~IRDummyBase2NCodec() = default;

	void encodeCoreEx(const std::uint8_t * src, int srcSize,
			std::string & dst) const {
		return this->encodeCore(src, srcSize, dst);
	}

	bool decodeCoreEx(const char * src, int srcSize,
			std::uint8_t * dst, int & dstSize) const {
		return this->decodeCore(src, srcSize, dst, dstSize);
	}

	int removePaddingEx(const char * src, int srcSize) const {
		return this->removePadding(src, srcSize);
	}

	void addPaddingEx(std::string & dst, int encodedSize) const {
		this->addPadding(dst, encodedSize);
	}

	bool isIgnoredEx(int c) const {
		return this->isIgnored(c);
	}
};

//------------------------------------------------------------------------------
IRDummyBase2NCodec::IRDummyBase2NCodec(
		std::shared_ptr<IRAlphabet> alphabet, int blockSize,
		int paddingChar, bool ignoreSpaces): IRBase2NCodec(alphabet, blockSize,
				paddingChar, ignoreSpaces) {
}

//==============================================================================
// class IRBase2NCodecTest
//------------------------------------------------------------------------------
IRBase2NCodecTest::IRBase2NCodecTest() {
}

//------------------------------------------------------------------------------
IRBase2NCodecTest::~IRBase2NCodecTest() {
}

//------------------------------------------------------------------------------
void IRBase2NCodecTest::SetUp() {
}

//------------------------------------------------------------------------------
void IRBase2NCodecTest::TearDown() {
}

//------------------------------------------------------------------------------
TEST_F(IRBase2NCodecTest, Constructor) {
	std::shared_ptr<IRAlphabet> a(new IRBinaryAlphabet());
	IRBase2NCodec * c;

	c = new IRBase2NCodec(a);
	ASSERT_EQ(a, c->sharedAlphabet());
	ASSERT_EQ(0, c->blockSize());
	ASSERT_EQ('=', c->paddingCharacter());
	ASSERT_FALSE(c->ignoreSpaces());
	delete c;

	c = new IRBase2NCodec(a, 1);
	ASSERT_EQ(a, c->sharedAlphabet());
	ASSERT_EQ(1, c->blockSize());
	ASSERT_EQ('=', c->paddingCharacter());
	ASSERT_FALSE(c->ignoreSpaces());
	delete c;

	c = new IRBase2NCodec(a, 1, '@');
	ASSERT_EQ(a, c->sharedAlphabet());
	ASSERT_EQ(1, c->blockSize());
	ASSERT_EQ('@', c->paddingCharacter());
	ASSERT_FALSE(c->ignoreSpaces());
	delete c;

	c = new IRBase2NCodec(a, 1, '@', false);
	ASSERT_EQ(a, c->sharedAlphabet());
	ASSERT_EQ(1, c->blockSize());
	ASSERT_EQ('@', c->paddingCharacter());
	ASSERT_FALSE(c->ignoreSpaces());
	delete c;

	c = new IRBase2NCodec(a, 1, '@', true);
	ASSERT_EQ(a, c->sharedAlphabet());
	ASSERT_EQ(1, c->blockSize());
	ASSERT_EQ('@', c->paddingCharacter());
	ASSERT_TRUE(c->ignoreSpaces());
	delete c;
}

//------------------------------------------------------------------------------
TEST_F(IRBase2NCodecTest, ConstructorFail) {
	std::shared_ptr<IRAlphabet> a;
	char map[256];
	IRBase2NCodec * c;

	for (int i = 0; i < sizeof(map); i++) {
		map[i] = i;
	}
	for (int i = 3; i <= sizeof(map); i++) {
		if ((i != 2) && (i != 4) && (i != 8) && (i != 16) && (i != 32) &&
				(i != 64) && (i != 128)) {
			try {
				c = new IRBase2NCodec(std::make_shared<IRGenericAlphabet>(map, i));
				FAIL();
			} catch (std::invalid_argument & e) {}
		}
	}
}

//------------------------------------------------------------------------------
TEST_F(IRBase2NCodecTest, ConstructorSizes) {
	std::shared_ptr<IRAlphabet> a;
	char map[256];
	IRBase2NCodec * c;

	for (int i = 0; i < sizeof(map); i++) {
		map[i] = i;
	}

	for (int charSize = 2; charSize < 8; charSize++) {
		c = new IRBase2NCodec(std::make_shared<IRGenericAlphabet>(
				map, 0x1 << charSize));
		ASSERT_EQ((0x1 << charSize) - 1, c->clearMask());
		ASSERT_EQ(charSize, c->characterSize());
		delete c;
	}
}

//------------------------------------------------------------------------------
TEST_F(IRBase2NCodecTest, alphabet) {
	std::shared_ptr<IRAlphabet> a(new IRBinaryAlphabet());
	IRBase2NCodec * c;

	c = new IRBase2NCodec(a);
	ASSERT_EQ(a->size(), c->alphabet().size());
	ASSERT_EQ(a.get(), c->sharedAlphabet().get());
	delete c;
}

//------------------------------------------------------------------------------
TEST_F(IRBase2NCodecTest, getDecodedSize) {
	IRBase2NCodec * c;

	c = new IRBase2NCodec(std::make_shared<IRBinaryAlphabet>());
	ASSERT_EQ(0, c->getDecodedSize(7));
	ASSERT_EQ(1, c->getDecodedSize(8));
	ASSERT_EQ(1, c->getDecodedSize(9));
	ASSERT_EQ(1, c->getDecodedSize(15));
	ASSERT_EQ(2, c->getDecodedSize(16));
	delete c;

	c = new IRBase2NCodec(std::make_shared<IRBase64Alphabet>());
	ASSERT_EQ(0, c->getDecodedSize(1));
	ASSERT_EQ(1, c->getDecodedSize(2));
	ASSERT_EQ(2, c->getDecodedSize(3));
	ASSERT_EQ(3, c->getDecodedSize(4));
	ASSERT_EQ(3, c->getDecodedSize(5));
	ASSERT_EQ(4, c->getDecodedSize(6));
	delete c;

	// Padding should make not difference
	c = new IRBase2NCodec(std::make_shared<IRBase64Alphabet>(),
			IRBase64Alphabet::DEFAULT_PADDING, IRBase64Alphabet::DEFAULT_PADDING_CHAR);
	ASSERT_EQ(0, c->getDecodedSize(1));
	ASSERT_EQ(1, c->getDecodedSize(2));
	ASSERT_EQ(2, c->getDecodedSize(3));
	ASSERT_EQ(3, c->getDecodedSize(4));
	ASSERT_EQ(3, c->getDecodedSize(5));
	ASSERT_EQ(4, c->getDecodedSize(6));
	delete c;
}

//------------------------------------------------------------------------------
TEST_F(IRBase2NCodecTest, getEncodedSize) {
	IRBase2NCodec * c;

	c = new IRBase2NCodec(std::make_shared<IRBinaryAlphabet>());
	ASSERT_EQ(0, c->getEncodedSize(0));
	ASSERT_EQ(8, c->getEncodedSize(1));
	delete c;

	c = new IRBase2NCodec(std::make_shared<IRBase64Alphabet>());
	ASSERT_EQ(0, c->getEncodedSize(0));
	ASSERT_EQ(2, c->getEncodedSize(1));
	ASSERT_EQ(3, c->getEncodedSize(2));
	ASSERT_EQ(4, c->getEncodedSize(3));
	ASSERT_EQ(6, c->getEncodedSize(4));
	delete c;

	// Padding should make not difference
	c = new IRBase2NCodec(std::make_shared<IRBase64Alphabet>(),
			IRBase64Alphabet::DEFAULT_PADDING, IRBase64Alphabet::DEFAULT_PADDING_CHAR);
	ASSERT_EQ(0, c->getEncodedSize(0));
	ASSERT_EQ(4, c->getEncodedSize(1));
	ASSERT_EQ(4, c->getEncodedSize(2));
	ASSERT_EQ(4, c->getEncodedSize(3));
	ASSERT_EQ(8, c->getEncodedSize(4));
	ASSERT_EQ(8, c->getEncodedSize(5));
	ASSERT_EQ(8, c->getEncodedSize(6));
	ASSERT_EQ(12, c->getEncodedSize(7));
	delete c;
}

//------------------------------------------------------------------------------
TEST_F(IRBase2NCodecTest, isIgnored) {
	IRDummyBase2NCodec * c;

	c = new IRDummyBase2NCodec(std::make_shared<IRBinaryAlphabet>());
	for (int i = 0; i < 256; i++) {
		ASSERT_FALSE(c->isIgnoredEx(i));
	}
	delete c;

	c = new IRDummyBase2NCodec(std::make_shared<IRBinaryAlphabet>(), 0, '0', false);
	for (int i = 0; i < 256; i++) {
		ASSERT_FALSE(c->isIgnoredEx(i));
	}
	delete c;

	c = new IRDummyBase2NCodec(std::make_shared<IRBinaryAlphabet>(), 0, '0', true);
	for (int i = 0; i < 256; i++) {
		if (std::isspace(char(i), std::locale::classic())) {
			ASSERT_TRUE(c->isIgnoredEx(i));
		} else {
			ASSERT_FALSE(c->isIgnoredEx(i));
		}
	}
	delete c;
}

//------------------------------------------------------------------------------
TEST_F(IRBase2NCodecTest, addPadding) {
	IRDummyBase2NCodec * c;
	std::string dst;

	c = new IRDummyBase2NCodec(std::make_shared<IRBase64Alphabet>(),
			0, IRBase64Alphabet::DEFAULT_PADDING_CHAR);
	dst = "";
	for (int i = 0; i < 10; i++) {
		c->addPaddingEx(dst, i);
		ASSERT_STREQ("", dst.c_str());
	}
	delete c;

	c = new IRDummyBase2NCodec(std::make_shared<IRBase64Alphabet>(),
			IRBase64Alphabet::DEFAULT_PADDING, IRBase64Alphabet::DEFAULT_PADDING_CHAR);
	dst = "";
	c->addPaddingEx(dst, 0);
	ASSERT_STREQ("", dst.c_str());
	dst = "";
	c->addPaddingEx(dst, 1);
	ASSERT_STREQ("===", dst.c_str());
	dst = "";
	c->addPaddingEx(dst, 2);
	ASSERT_STREQ("==", dst.c_str());
	dst = "";
	c->addPaddingEx(dst, 3);
	ASSERT_STREQ("=", dst.c_str());
	dst = "";
	c->addPaddingEx(dst, 4);
	ASSERT_STREQ("", dst.c_str());
	delete c;
}

//------------------------------------------------------------------------------
TEST_F(IRBase2NCodecTest, removePadding) {
	IRDummyBase2NCodec * c;
	std::string src;

	c = new IRDummyBase2NCodec(std::make_shared<IRBase64Alphabet>(),
			0, IRBase64Alphabet::DEFAULT_PADDING_CHAR);

	for (int i = 0; i < 10; i++) {
		src = "";
		src.append(i, '=');
		ASSERT_EQ(src.size(), c->removePaddingEx(src.c_str(), src.size()));
	}
	delete c;

	c = new IRDummyBase2NCodec(std::make_shared<IRBase64Alphabet>(),
			IRBase64Alphabet::DEFAULT_PADDING, IRBase64Alphabet::DEFAULT_PADDING_CHAR);
	src = "";
	ASSERT_EQ(0, c->removePaddingEx(src.c_str(), src.size()));
	src = "abcd";
	ASSERT_EQ(4, c->removePaddingEx(src.c_str(), src.size()));
	src = "abc=";
	ASSERT_EQ(3, c->removePaddingEx(src.c_str(), src.size()));
	src = "ab==";
	ASSERT_EQ(2, c->removePaddingEx(src.c_str(), src.size()));
	src = "a===";
	ASSERT_EQ(-1, c->removePaddingEx(src.c_str(), src.size()));
	src = "a====";
	ASSERT_EQ(-1, c->removePaddingEx(src.c_str(), src.size()));
	src = "a=====";
	ASSERT_EQ(-1, c->removePaddingEx(src.c_str(), src.size()));
	delete c;
}

//------------------------------------------------------------------------------
TEST_F(IRBase2NCodecTest, decodeCore) {
	IRDummyBase2NCodec * c;
	std::uint8_t dst[32];
	int dstSize;
	std::string src;
	std::string exp;

	c = new IRDummyBase2NCodec(std::make_shared<IRBase64Alphabet>());
	for (int i = 0; i < IRBase2NCodecTest_RFC4648_BASE64_NP_SIZE; i += 2) {
		exp = IRBase2NCodecTest_RFC4648_BASE64_NP[i];
		src = IRBase2NCodecTest_RFC4648_BASE64_NP[i + 1];
		std::memset(dst, 0xFF, sizeof(dst));
		dstSize = sizeof(dst);
		ASSERT_TRUE(c->decodeCoreEx(src.c_str(), src.size(), dst, dstSize));
		ASSERT_EQ(exp.size(), dstSize);
		dst[dstSize] = 0;
		ASSERT_STREQ(exp.c_str(), (const char *)dst);
	}
	// Add invalid
	for (int i = 2; i < IRBase2NCodecTest_RFC4648_BASE64_NP_SIZE; i += 2) {
		exp = IRBase2NCodecTest_RFC4648_BASE64_NP[i];
		src = IRBase2NCodecTest_RFC4648_BASE64_NP[i + 1];
		src[0] = '!';
		std::memset(dst, 0xFF, sizeof(dst));
		dstSize = sizeof(dst);
		ASSERT_FALSE(c->decodeCoreEx(src.c_str(), src.size(), dst, dstSize));
	}
	for (int i = 0; i < IRBase2NCodecTest_RFC4648_BASE64_NP_SIZE; i += 2) {
		exp = IRBase2NCodecTest_RFC4648_BASE64_NP[i];
		src = IRBase2NCodecTest_RFC4648_BASE64_NP[i + 1];
		src.insert(src.begin(), ' '); // Add an space
		std::memset(dst, 0xFF, sizeof(dst));
		dstSize = sizeof(dst);
		ASSERT_FALSE(c->decodeCoreEx(src.c_str(), src.size(), dst, dstSize));
	}
	delete c;

	c = new IRDummyBase2NCodec(std::make_shared<IRBase64Alphabet>(), 0,
			IRBase64Alphabet::DEFAULT_PADDING_CHAR, true);
	for (int i = 0; i < IRBase2NCodecTest_RFC4648_BASE64_NP_SIZE; i += 2) {
		exp = IRBase2NCodecTest_RFC4648_BASE64_NP[i];
		src = IRBase2NCodecTest_RFC4648_BASE64_NP[i + 1];
		std::memset(dst, 0xFF, sizeof(dst));
		dstSize = sizeof(dst);
		ASSERT_TRUE(c->decodeCoreEx(src.c_str(), src.size(), dst, dstSize));
		ASSERT_EQ(exp.size(), dstSize);
		dst[dstSize] = 0;
		ASSERT_STREQ(exp.c_str(), (const char *)dst);
	}
	for (int i = 0; i < IRBase2NCodecTest_RFC4648_BASE64_NP_SIZE; i += 2) {
		exp = IRBase2NCodecTest_RFC4648_BASE64_NP[i];
		src = IRBase2NCodecTest_RFC4648_BASE64_NP[i + 1];
		src.insert(src.begin(), ' '); // Add an space
		std::memset(dst, 0xFF, sizeof(dst));
		dstSize = sizeof(dst);
		ASSERT_TRUE(c->decodeCoreEx(src.c_str(), src.size(), dst, dstSize));
		ASSERT_EQ(exp.size(), dstSize);
		dst[dstSize] = 0;
		ASSERT_STREQ(exp.c_str(), (const char *)dst);
	}
	delete c;
}

//------------------------------------------------------------------------------
TEST_F(IRBase2NCodecTest, encodeCore) {
	IRDummyBase2NCodec * c;
	std::string dst;
	std::string src;
	std::string exp;

	c = new IRDummyBase2NCodec(std::make_shared<IRBase64Alphabet>());
	for (int i = 0; i < IRBase2NCodecTest_RFC4648_BASE64_NP_SIZE; i += 2) {
		dst = "";
		src = IRBase2NCodecTest_RFC4648_BASE64_NP[i];
		exp = IRBase2NCodecTest_RFC4648_BASE64_NP[i + 1];
		c->encodeCoreEx((const std::uint8_t *)(src.c_str()), src.size(), dst);
		ASSERT_EQ(exp.size(), dst.size());
		ASSERT_STREQ(exp.c_str(), dst.c_str());
	}
	for (int i = 0; i < IRBase2NCodecTest_RFC4648_BASE64_NP_SIZE; i += 2) {
		dst = "-";
		src = IRBase2NCodecTest_RFC4648_BASE64_NP[i];
		exp = IRBase2NCodecTest_RFC4648_BASE64_NP[i + 1];
		exp.insert(exp.begin(), '-');
		c->encodeCoreEx((const std::uint8_t *)(src.c_str()), src.size(), dst);
		ASSERT_EQ(exp.size(), dst.size());
		ASSERT_STREQ(exp.c_str(), dst.c_str());
	}
	delete c;
}

//------------------------------------------------------------------------------
TEST_F(IRBase2NCodecTest, encode64NoPadding) {
	IRBase2NCodec c(std::make_shared<IRBase64Alphabet>());
	std::string dst;
	std::string src;
	std::string exp;
	int dstSize;

	// Basic tests
	for (int i = 0; i < IRBase2NCodecTest_RFC4648_BASE64_NP_SIZE; i += 2) {
		exp = IRBase2NCodecTest_RFC4648_BASE64_NP[i + 1];
		src = IRBase2NCodecTest_RFC4648_BASE64_NP[i];
		dst.clear();
		dstSize = sizeof(dst);
		dstSize = c.encode(src.c_str(), src.size(), dst);
		ASSERT_EQ(exp.size(), dstSize);
		ASSERT_STREQ(exp.c_str(), dst.c_str());
	}
}

//------------------------------------------------------------------------------
TEST_F(IRBase2NCodecTest, encode64Padding) {
	IRBase2NCodec c(std::make_shared<IRBase64Alphabet>(), IRBase64Alphabet::DEFAULT_PADDING);
	std::string dst;
	std::string src;
	std::string exp;
	int dstSize;

	// Basic tests
	for (int i = 0; i < IRBase2NCodecTest_RFC4648_BASE64_SIZE; i += 2) {
		exp = IRBase2NCodecTest_RFC4648_BASE64[i + 1];
		src = IRBase2NCodecTest_RFC4648_BASE64[i];
		dst.clear();
		dstSize = sizeof(dst);
		dstSize = c.encode(src.c_str(), src.size(), dst);
		ASSERT_EQ(exp.size(), dstSize);
		ASSERT_STREQ(exp.c_str(), dst.c_str());
	}
}

//------------------------------------------------------------------------------
TEST_F(IRBase2NCodecTest, decode64NoPadding) {
	IRBase2NCodec c(std::make_shared<IRBase64Alphabet>());
	std::string src;
	std::string exp;
	char dst[64];
	int dstSize;

	for (int i = 0; i < IRBase2NCodecTest_RFC4648_BASE64_NP_SIZE; i += 2) {
		exp = IRBase2NCodecTest_RFC4648_BASE64_NP[i];
		src = IRBase2NCodecTest_RFC4648_BASE64_NP[i+1];
		std::memset(dst, 0xFF, sizeof(dst));
		dstSize = sizeof(dst) - 1;
		ASSERT_TRUE(c.decode(src.c_str(), dst + 1, dstSize));
		ASSERT_EQ(exp.size(), dstSize);
		ASSERT_EQ(char(0xFF), dst[0]);
		ASSERT_EQ(char(0xFF), dst[dstSize + 1]);
		dst[dstSize + 1] = 0;
		ASSERT_STREQ(exp.c_str(), (dst + 1));
	}

	for (int i = 0; i < IRBase2NCodecTest_RFC4648_BASE64_NP_SIZE; i += 2) {
		exp = IRBase2NCodecTest_RFC4648_BASE64_NP[i];
		src = IRBase2NCodecTest_RFC4648_BASE64_NP[i+1];
		std::memset(dst, 0xFF, sizeof(dst));
		dstSize = sizeof(dst) - 1;
		ASSERT_TRUE(c.decode(src, dst + 1, dstSize));
		ASSERT_EQ(exp.size(), dstSize);
		ASSERT_EQ(char(0xFF), dst[0]);
		ASSERT_EQ(char(0xFF), dst[dstSize + 1]);
		dst[dstSize + 1] = 0;
		ASSERT_STREQ(exp.c_str(), (dst + 1));
	}

	for (int i = 0; i < IRBase2NCodecTest_RFC4648_BASE64_NP_SIZE; i += 2) {
		exp = IRBase2NCodecTest_RFC4648_BASE64_NP[i];
		src = IRBase2NCodecTest_RFC4648_BASE64_NP[i+1];
		src.insert(src.begin(), '@');
		src.push_back('@');
		std::memset(dst, 0xFF, sizeof(dst));
		dstSize = sizeof(dst) - 1;
		ASSERT_TRUE(c.decode(src, 1, src.size() - 2, dst + 1, dstSize));
		ASSERT_EQ(exp.size(), dstSize);
		ASSERT_EQ(char(0xFF), dst[0]);
		ASSERT_EQ(char(0xFF), dst[dstSize + 1]);
		dst[dstSize + 1] = 0;
		ASSERT_STREQ(exp.c_str(), (dst + 1));
	}
}

//------------------------------------------------------------------------------
TEST_F(IRBase2NCodecTest, decode64Padding) {
	IRBase2NCodec c(std::make_shared<IRBase64Alphabet>(), IRBase64Alphabet::DEFAULT_PADDING);
	std::string src;
	std::string exp;
	char dst[64];
	int dstSize;

	for (int i = 0; i < IRBase2NCodecTest_RFC4648_BASE64_SIZE; i += 2) {
		exp = IRBase2NCodecTest_RFC4648_BASE64[i];
		src = IRBase2NCodecTest_RFC4648_BASE64[i+1];
		std::memset(dst, 0xFF, sizeof(dst));
		dstSize = sizeof(dst) - 1;
		ASSERT_TRUE(c.decode(src.c_str(), dst + 1, dstSize));
		ASSERT_EQ(exp.size(), dstSize);
		ASSERT_EQ(char(0xFF), dst[0]);
		ASSERT_EQ(char(0xFF), dst[dstSize + 1]);
		dst[dstSize + 1] = 0;
		ASSERT_STREQ(exp.c_str(), (dst + 1));
	}

	for (int i = 0; i < IRBase2NCodecTest_RFC4648_BASE64_SIZE; i += 2) {
		exp = IRBase2NCodecTest_RFC4648_BASE64[i];
		src = IRBase2NCodecTest_RFC4648_BASE64[i+1];
		std::memset(dst, 0xFF, sizeof(dst));
		dstSize = sizeof(dst) - 1;
		ASSERT_TRUE(c.decode(src, dst + 1, dstSize));
		ASSERT_EQ(exp.size(), dstSize);
		ASSERT_EQ(char(0xFF), dst[0]);
		ASSERT_EQ(char(0xFF), dst[dstSize + 1]);
		dst[dstSize + 1] = 0;
		ASSERT_STREQ(exp.c_str(), (dst + 1));
	}

	for (int i = 0; i < IRBase2NCodecTest_RFC4648_BASE64_SIZE; i += 2) {
		exp = IRBase2NCodecTest_RFC4648_BASE64[i];
		src = IRBase2NCodecTest_RFC4648_BASE64[i+1];
		src.insert(src.begin(), '@');
		src.push_back('@');
		std::memset(dst, 0xFF, sizeof(dst));
		dstSize = sizeof(dst) - 1;
		ASSERT_TRUE(c.decode(src, 1, src.size() - 2, dst + 1, dstSize));
		ASSERT_EQ(exp.size(), dstSize);
		ASSERT_EQ(char(0xFF), dst[0]);
		ASSERT_EQ(char(0xFF), dst[dstSize + 1]);
		dst[dstSize + 1] = 0;
		ASSERT_STREQ(exp.c_str(), (dst + 1));
	}
}

//------------------------------------------------------------------------------
TEST_F(IRBase2NCodecTest, encodeDecode64NoPadding) {
	IRBase2NCodec c(std::make_shared<IRBase64Alphabet>());
	std::uint8_t src[1024];
	std::uint8_t dec[2048];
	int decSize;
	std::string enc;

	int dstSize;
	for (int srcSize = 0; srcSize <= 1024; srcSize++) {
		std::generate_n(src, srcSize, rand);
		enc.clear();
		c.encode(src, srcSize, enc);
		decSize = sizeof(dec);
		ASSERT_TRUE(c.decode(enc, dec, decSize));
		ASSERT_EQ(srcSize, decSize);
		ASSERT_EQ(0, memcmp(src, dec, srcSize));
	}
}

//------------------------------------------------------------------------------
TEST_F(IRBase2NCodecTest, encodeDecode64Padding) {
	IRBase2NCodec c(std::make_shared<IRBase64Alphabet>(), IRBase64Alphabet::DEFAULT_PADDING);
	std::uint8_t src[1024];
	std::uint8_t dec[2048];
	int decSize;
	std::string enc;

	int dstSize;
	for (int srcSize = 0; srcSize <= 1024; srcSize++) {
		std::generate_n(src, srcSize, rand);
		enc.clear();
		c.encode(src, srcSize, enc);
		decSize = sizeof(dec);
		ASSERT_TRUE(c.decode(enc, dec, decSize));
		ASSERT_EQ(srcSize, decSize);
		ASSERT_EQ(0, memcmp(src, dec, srcSize));
	}
}

//------------------------------------------------------------------------------
TEST_F(IRBase2NCodecTest, encodeDecode32NoPadding) {
	IRBase2NCodec c(std::make_shared<IRBase32Alphabet>());
	std::uint8_t src[1024];
	std::uint8_t dec[2048];
	int decSize;
	std::string enc;

	int dstSize;
	for (int srcSize = 0; srcSize <= 1024; srcSize++) {
		std::generate_n(src, srcSize, rand);
		enc.clear();
		c.encode(src, srcSize, enc);
		decSize = sizeof(dec);
		ASSERT_TRUE(c.decode(enc, dec, decSize));
		ASSERT_EQ(srcSize, decSize);
		ASSERT_EQ(0, memcmp(src, dec, srcSize));
	}
}

//------------------------------------------------------------------------------
TEST_F(IRBase2NCodecTest, encodeDecode32Padding) {
	IRBase2NCodec c(std::make_shared<IRBase32Alphabet>(), IRBase32Alphabet::DEFAULT_PADDING);
	std::uint8_t src[1024];
	std::uint8_t dec[2048];
	int decSize;
	std::string enc;

	int dstSize;
	for (int srcSize = 0; srcSize <= 1024; srcSize++) {
		std::generate_n(src, srcSize, rand);
		enc.clear();
		c.encode(src, srcSize, enc);
		decSize = sizeof(dec);
		ASSERT_TRUE(c.decode(enc, dec, decSize));
		ASSERT_EQ(srcSize, decSize);
		ASSERT_EQ(0, memcmp(src, dec, srcSize));
	}
}
//------------------------------------------------------------------------------

