/*
 * Copyright (c) 2017, Open Communications Security
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
#include "IRBufferTest.h"
#include <ircommon/irbuffer.h>
#include <ircommon/ilint.h>
#include <ircommon/irfp.h>
#include <cstring>
using namespace ircommon;

#define IRBufferTest_SAMPLE_SIZE 232
static const char * IRBufferTest_SAMPLE =
		"I've seen things you people wouldn't believe. Attack ships on fire off"
		" the shoulder of Orion. I watched C-beams glitter in the dark near the"
		" Tannhauser Gate. All those moments will be lost in time, like tears in"
		" rain. Time to die.";

//==============================================================================
// class IRBufferTest
//------------------------------------------------------------------------------
IRBufferTest::IRBufferTest() {
}

//------------------------------------------------------------------------------
IRBufferTest::~IRBufferTest() {
}

//------------------------------------------------------------------------------
void IRBufferTest::SetUp() {
}

//------------------------------------------------------------------------------
void IRBufferTest::TearDown() {
}

//------------------------------------------------------------------------------
TEST_F(IRBufferTest, ConstructorRO) {
	IRBuffer * b;

	b =new IRBuffer(IRBufferTest_SAMPLE, IRBufferTest_SAMPLE_SIZE);
	ASSERT_TRUE(b->readOnly());
	ASSERT_EQ(0, b->position());
	ASSERT_EQ(IRBufferTest_SAMPLE_SIZE, b->bufferSize());
	ASSERT_EQ(IRBufferTest_SAMPLE_SIZE, b->available());
	ASSERT_EQ(IRBufferTest_SAMPLE_SIZE, b->size());
	ASSERT_FALSE(b->secure());
	ASSERT_TRUE(b->buffer() == nullptr);
	ASSERT_TRUE(b->roBuffer() == (const std::uint8_t *)IRBufferTest_SAMPLE);
	delete b;
}

//------------------------------------------------------------------------------
TEST_F(IRBufferTest, ConstructorRW) {
	IRBuffer * b;

	b = new IRBuffer();
	ASSERT_FALSE(b->readOnly());
	ASSERT_FALSE(b->secure());
	ASSERT_EQ(0, b->position());
	ASSERT_EQ(IRBuffer::DEFAULT_INCREMENT, b->increment());
	ASSERT_EQ(0, b->available());
	ASSERT_EQ(IRBuffer::DEFAULT_INCREMENT, b->bufferSize());
	ASSERT_EQ(0, b->size());
	ASSERT_TRUE(b->buffer() != nullptr);
	ASSERT_TRUE(b->roBuffer() == b->buffer());
	delete b;

	b = new IRBuffer(IRBuffer::DEFAULT_INCREMENT);
	ASSERT_FALSE(b->readOnly());
	ASSERT_FALSE(b->secure());
	ASSERT_EQ(0, b->position());
	ASSERT_EQ(IRBuffer::DEFAULT_INCREMENT, b->increment());
	ASSERT_EQ(0, b->available());
	ASSERT_EQ(IRBuffer::DEFAULT_INCREMENT * 2, b->bufferSize());
	ASSERT_EQ(0, b->size());
	ASSERT_TRUE(b->buffer() != nullptr);
	ASSERT_TRUE(b->roBuffer() == b->buffer());
	delete b;

	b = new IRBuffer(IRBuffer::DEFAULT_INCREMENT, false);
	ASSERT_FALSE(b->readOnly());
	ASSERT_FALSE(b->secure());
	ASSERT_EQ(0, b->position());
	ASSERT_EQ(IRBuffer::DEFAULT_INCREMENT, b->increment());
	ASSERT_EQ(0, b->available());
	ASSERT_EQ(IRBuffer::DEFAULT_INCREMENT * 2, b->bufferSize());
	ASSERT_EQ(0, b->size());
	ASSERT_TRUE(b->buffer() != nullptr);
	ASSERT_TRUE(b->roBuffer() == b->buffer());
	delete b;

	b = new IRBuffer(IRBuffer::DEFAULT_INCREMENT, true);
	ASSERT_FALSE(b->readOnly());
	ASSERT_TRUE(b->secure());
	ASSERT_EQ(0, b->position());
	ASSERT_EQ(IRBuffer::DEFAULT_INCREMENT, b->increment());
	ASSERT_EQ(0, b->available());
	ASSERT_EQ(IRBuffer::DEFAULT_INCREMENT * 2, b->bufferSize());
	ASSERT_EQ(0, b->size());
	ASSERT_TRUE(b->buffer() != nullptr);
	ASSERT_TRUE(b->roBuffer() == b->buffer());
	delete b;

	b = new IRBuffer(16, false, 32);
	ASSERT_FALSE(b->readOnly());
	ASSERT_FALSE(b->secure());
	ASSERT_EQ(0, b->position());
	ASSERT_EQ(32, b->increment());
	ASSERT_EQ(0, b->available());
	ASSERT_EQ(32, b->bufferSize());
	ASSERT_EQ(0, b->size());
	ASSERT_TRUE(b->buffer() != nullptr);
	ASSERT_TRUE(b->roBuffer() == b->buffer());
	delete b;

	b = new IRBuffer(16, true, 32);
	ASSERT_FALSE(b->readOnly());
	ASSERT_TRUE(b->secure());
	ASSERT_EQ(0, b->position());
	ASSERT_EQ(32, b->increment());
	ASSERT_EQ(0, b->available());
	ASSERT_EQ(32, b->bufferSize());
	ASSERT_EQ(0, b->size());
	ASSERT_TRUE(b->buffer() != nullptr);
	ASSERT_TRUE(b->roBuffer() == b->buffer());
	delete b;


	try {
		b = new IRBuffer(16, true, 0);
		FAIL();
	} catch(std::invalid_argument & e) {}
}

//------------------------------------------------------------------------------
TEST_F(IRBufferTest, secure) {
	IRBuffer * b;

	b =new IRBuffer(IRBufferTest_SAMPLE, IRBufferTest_SAMPLE_SIZE);
	ASSERT_FALSE(b->secure());
	delete b;

	b = new IRBuffer();
	ASSERT_FALSE(b->secure());
	delete b;

	b = new IRBuffer(16);
	ASSERT_FALSE(b->secure());
	delete b;

	b = new IRBuffer(16, false);
	ASSERT_FALSE(b->secure());
	delete b;

	b = new IRBuffer(16, true);
	ASSERT_TRUE(b->secure());
	delete b;

	b = new IRBuffer(16, false, 32);
	ASSERT_FALSE(b->secure());
	delete b;

	b = new IRBuffer(16, true, 32);
	ASSERT_TRUE(b->secure());
	delete b;
}

//------------------------------------------------------------------------------
TEST_F(IRBufferTest, setSizeRO) {
	IRBuffer b(IRBufferTest_SAMPLE, IRBufferTest_SAMPLE_SIZE);

	ASSERT_FALSE(b.setSize(0));
	ASSERT_EQ(IRBufferTest_SAMPLE_SIZE, b.size());
	ASSERT_FALSE(b.setSize(10));
	ASSERT_EQ(IRBufferTest_SAMPLE_SIZE, b.size());
}

//------------------------------------------------------------------------------
TEST_F(IRBufferTest, setSizeRW) {
	IRBuffer b;

	ASSERT_EQ(0, b.size());
	ASSERT_EQ(16, b.bufferSize());

	ASSERT_TRUE(b.setSize(0));
	ASSERT_EQ(0, b.size());
	ASSERT_EQ(16, b.bufferSize());
	ASSERT_EQ(0, b.position());

	ASSERT_TRUE(b.setSize(16));
	ASSERT_EQ(16, b.size());
	ASSERT_EQ(16, b.bufferSize());
	ASSERT_EQ(0, b.position());

	b.setPosition(15);
	ASSERT_TRUE(b.setSize(17));
	ASSERT_EQ(17, b.size());
	ASSERT_EQ(32, b.bufferSize());
	ASSERT_EQ(15, b.position());

	ASSERT_TRUE(b.setSize(1));
	ASSERT_EQ(1, b.size());
	ASSERT_EQ(32, b.bufferSize());
	ASSERT_EQ(1, b.position());
}

//------------------------------------------------------------------------------
TEST_F(IRBufferTest, readOnly) {
	IRBuffer bro(IRBufferTest_SAMPLE, IRBufferTest_SAMPLE_SIZE);
	IRBuffer brw;

	ASSERT_TRUE(bro.readOnly());
	ASSERT_FALSE(brw.readOnly());
}

//------------------------------------------------------------------------------
TEST_F(IRBufferTest, buffer) {
	IRBuffer bro(IRBufferTest_SAMPLE, IRBufferTest_SAMPLE_SIZE);
	IRBuffer brw;

	ASSERT_TRUE(bro.buffer() == nullptr);

	ASSERT_TRUE(brw.roBuffer() != nullptr);
	ASSERT_TRUE(brw.roBuffer() == brw.buffer());
}

//------------------------------------------------------------------------------
TEST_F(IRBufferTest, roBuffer) {
	IRBuffer bro(IRBufferTest_SAMPLE, IRBufferTest_SAMPLE_SIZE);
	IRBuffer brw;

	ASSERT_TRUE(bro.roBuffer());
	ASSERT_TRUE(bro.roBuffer() == (const std::uint8_t *)IRBufferTest_SAMPLE);

	ASSERT_TRUE(brw.roBuffer() != nullptr);
	ASSERT_TRUE(brw.roBuffer() == brw.buffer());
}

//------------------------------------------------------------------------------
TEST_F(IRBufferTest, beginning) {
	IRBuffer bro(IRBufferTest_SAMPLE, IRBufferTest_SAMPLE_SIZE);
	IRBuffer brw;

	ASSERT_EQ(0, bro.position());
	bro.ending();
	ASSERT_EQ(bro.size(), bro.position());
	bro.beginning();
	ASSERT_EQ(0, bro.position());

	ASSERT_TRUE(brw.setSize(16));
	brw.ending();
	ASSERT_EQ(brw.size(), brw.position());
	brw.beginning();
	ASSERT_EQ(0, brw.position());
}

//------------------------------------------------------------------------------
TEST_F(IRBufferTest, ending) {
	IRBuffer bro(IRBufferTest_SAMPLE, IRBufferTest_SAMPLE_SIZE);
	IRBuffer brw;

	ASSERT_EQ(0, bro.position());
	bro.ending();
	ASSERT_EQ(bro.size(), bro.position());

	ASSERT_TRUE(brw.setSize(16));
	ASSERT_EQ(0, brw.position());
	brw.ending();
	ASSERT_EQ(brw.size(), brw.position());
}

//------------------------------------------------------------------------------
TEST_F(IRBufferTest, setPositionRO) {
	IRBuffer b(IRBufferTest_SAMPLE, IRBufferTest_SAMPLE_SIZE);

	ASSERT_EQ(0, b.position());
	b.setPosition(1);
	ASSERT_EQ(1, b.position());
	b.setPosition(b.size());
	ASSERT_EQ(b.size(), b.position());
	b.setPosition(b.size() + 1);
	ASSERT_EQ(b.size(), b.position());
}

//------------------------------------------------------------------------------
TEST_F(IRBufferTest, setPositionRW) {
	IRBuffer b;

	ASSERT_EQ(0, b.position());
	b.setPosition(0);
	ASSERT_EQ(0, b.position());
	b.setPosition(1);
	ASSERT_EQ(0, b.position());

	ASSERT_TRUE(b.setSize(16));
	ASSERT_EQ(16, b.size());
	ASSERT_EQ(0, b.position());

	b.setPosition(b.size());
	ASSERT_EQ(b.size(), b.position());
	b.setPosition(b.size() + 1);
	ASSERT_EQ(b.size(), b.position());
}

//------------------------------------------------------------------------------
TEST_F(IRBufferTest, skipRO) {
	IRBuffer b(IRBufferTest_SAMPLE, IRBufferTest_SAMPLE_SIZE);

	ASSERT_EQ(0, b.position());
	ASSERT_EQ(1, b.skip(1));
	ASSERT_EQ(1, b.position());

	ASSERT_EQ(32, b.skip(32));
	ASSERT_EQ(33, b.position());

	ASSERT_EQ(IRBufferTest_SAMPLE_SIZE - 33, b.skip(IRBufferTest_SAMPLE_SIZE));
	ASSERT_EQ(IRBufferTest_SAMPLE_SIZE, b.position());
}

//------------------------------------------------------------------------------
TEST_F(IRBufferTest, skipRW) {
	IRBuffer b;

	ASSERT_EQ(0, b.position());
	ASSERT_EQ(0, b.skip(1));
	ASSERT_EQ(0, b.position());

	ASSERT_TRUE(b.setSize(32));
	ASSERT_EQ(0, b.skip(0));
	ASSERT_EQ(0, b.position());

	ASSERT_EQ(1, b.skip(1));
	ASSERT_EQ(1, b.position());

	ASSERT_EQ(16, b.skip(16));
	ASSERT_EQ(17, b.position());

	ASSERT_EQ(15, b.skip(16));
	ASSERT_EQ(32, b.position());
}

//------------------------------------------------------------------------------
TEST_F(IRBufferTest, rewindRO) {
	IRBuffer b(IRBufferTest_SAMPLE, IRBufferTest_SAMPLE_SIZE);

	ASSERT_EQ(0, b.position());
	ASSERT_EQ(0, b.rewind(0));
	ASSERT_EQ(0, b.position());

	b.setPosition(IRBufferTest_SAMPLE_SIZE);
	ASSERT_EQ(1, b.rewind(1));
	ASSERT_EQ(IRBufferTest_SAMPLE_SIZE - 1, b.position());

	ASSERT_EQ(2, b.rewind(2));
	ASSERT_EQ(IRBufferTest_SAMPLE_SIZE - 3, b.position());

	ASSERT_EQ(IRBufferTest_SAMPLE_SIZE - 3, b.rewind(IRBufferTest_SAMPLE_SIZE));
	ASSERT_EQ(0, b.position());
}

//------------------------------------------------------------------------------
TEST_F(IRBufferTest, rewindRW) {
	IRBuffer b;

	ASSERT_EQ(0, b.position());
	ASSERT_EQ(0, b.rewind(0));
	ASSERT_EQ(0, b.position());

	ASSERT_TRUE(b.setSize(32));
	b.setPosition(32);
	ASSERT_EQ(1, b.rewind(1));
	ASSERT_EQ(31, b.position());

	ASSERT_EQ(2, b.rewind(2));
	ASSERT_EQ(29, b.position());

	ASSERT_EQ(29, b.rewind(IRBufferTest_SAMPLE_SIZE));
	ASSERT_EQ(0, b.position());
}

//------------------------------------------------------------------------------
TEST_F(IRBufferTest, reserveRO) {
	IRBuffer b(IRBufferTest_SAMPLE, IRBufferTest_SAMPLE_SIZE);

	ASSERT_FALSE(b.reserve(0));
	ASSERT_EQ(IRBufferTest_SAMPLE_SIZE, b.size());
	ASSERT_EQ(IRBufferTest_SAMPLE_SIZE, b.bufferSize());

	ASSERT_FALSE(b.reserve(10));
	ASSERT_EQ(IRBufferTest_SAMPLE_SIZE, b.size());
	ASSERT_EQ(IRBufferTest_SAMPLE_SIZE, b.bufferSize());

	ASSERT_FALSE(b.reserve(IRBufferTest_SAMPLE_SIZE + 1));
	ASSERT_EQ(IRBufferTest_SAMPLE_SIZE, b.size());
	ASSERT_EQ(IRBufferTest_SAMPLE_SIZE, b.bufferSize());
}

//------------------------------------------------------------------------------
TEST_F(IRBufferTest, reserveRW) {
	IRBuffer b;

	ASSERT_TRUE(b.reserve(0));
	ASSERT_EQ(0, b.size());
	ASSERT_EQ(16, b.bufferSize());

	ASSERT_TRUE(b.reserve(16));
	ASSERT_EQ(0, b.size());
	ASSERT_EQ(16, b.bufferSize());

	ASSERT_TRUE(b.reserve(17));
	ASSERT_EQ(0, b.size());
	ASSERT_EQ(32, b.bufferSize());
}

//------------------------------------------------------------------------------
TEST_F(IRBufferTest, readRO) {
	IRBuffer b(IRBufferTest_SAMPLE, IRBufferTest_SAMPLE_SIZE);
	std::string s;
	char buff[512];
	std::uint64_t read;

	read = b.read(buff, 0);
	ASSERT_EQ(0, b.position());
	ASSERT_EQ(0, read);

	read = b.read(buff, 16);
	ASSERT_EQ(16, b.position());
	ASSERT_EQ(16, read);
	s.append(buff, read);

	read = b.read(buff, 16);
	ASSERT_EQ(32, b.position());
	ASSERT_EQ(16, read);
	s.append(buff, read);

	read = b.read(buff, sizeof(buff));
	ASSERT_EQ(IRBufferTest_SAMPLE_SIZE, b.position());
	ASSERT_EQ(IRBufferTest_SAMPLE_SIZE - 32, read);
	s.append(buff, read);

	ASSERT_STREQ(IRBufferTest_SAMPLE, s.c_str());
}

//------------------------------------------------------------------------------
TEST_F(IRBufferTest, readRW) {
	IRBuffer b;
	std::string s;
	char buff[512];
	std::uint64_t read;

	// Empty
	read = b.read(buff, 0);
	ASSERT_EQ(0, b.position());
	ASSERT_EQ(0, read);

	read = b.read(buff, 16);
	ASSERT_EQ(0, b.position());
	ASSERT_EQ(0, read);

	// Write something
	ASSERT_TRUE(b.set(IRBufferTest_SAMPLE, IRBufferTest_SAMPLE_SIZE));

	read = b.read(buff, 0);
	ASSERT_EQ(0, b.position());
	ASSERT_EQ(0, read);

	read = b.read(buff, 16);
	ASSERT_EQ(16, b.position());
	ASSERT_EQ(16, read);
	s.append(buff, read);

	read = b.read(buff, 16);
	ASSERT_EQ(32, b.position());
	ASSERT_EQ(16, read);
	s.append(buff, read);

	read = b.read(buff, sizeof(buff));
	ASSERT_EQ(IRBufferTest_SAMPLE_SIZE, b.position());
	ASSERT_EQ(IRBufferTest_SAMPLE_SIZE - 32, read);
	s.append(buff, read);

	ASSERT_STREQ(IRBufferTest_SAMPLE, s.c_str());
}

//------------------------------------------------------------------------------
TEST_F(IRBufferTest, writeRO) {
	IRBuffer b(IRBufferTest_SAMPLE, IRBufferTest_SAMPLE_SIZE);

	b.setPosition(1);
	ASSERT_EQ(1, b.position());

	ASSERT_FALSE(b.write(IRBufferTest_SAMPLE, 0));
	ASSERT_EQ(1, b.position());

	ASSERT_FALSE(b.write(IRBufferTest_SAMPLE, IRBufferTest_SAMPLE_SIZE));
	ASSERT_EQ(1, b.position());
}

//------------------------------------------------------------------------------
TEST_F(IRBufferTest, writeRW) {
	const char * p;
	IRBuffer b;

	p = IRBufferTest_SAMPLE;

	ASSERT_TRUE(b.write(p, 0));
	ASSERT_EQ(0, b.size());
	ASSERT_EQ(0, b.position());

	ASSERT_TRUE(b.write(p, 10));
	ASSERT_EQ(10, b.size());
	ASSERT_EQ(10, b.position());
	p += 10;

	ASSERT_TRUE(b.write(p, 10));
	ASSERT_EQ(20, b.size());
	ASSERT_EQ(20, b.position());
	p += 10;

	ASSERT_TRUE(b.write(p, IRBufferTest_SAMPLE_SIZE - 20));
	ASSERT_EQ(IRBufferTest_SAMPLE_SIZE, b.size());
	ASSERT_EQ(IRBufferTest_SAMPLE_SIZE, b.position());

	ASSERT_STREQ(IRBufferTest_SAMPLE, (const char *)b.roBuffer());
}

//------------------------------------------------------------------------------
TEST_F(IRBufferTest, shrink) {
	IRBuffer bro(IRBufferTest_SAMPLE, IRBufferTest_SAMPLE_SIZE);
	IRBuffer brw;

	ASSERT_FALSE(bro.shrink());

	ASSERT_TRUE(brw.setSize(64));
	ASSERT_EQ(64, brw.size());
	ASSERT_EQ(80, brw.bufferSize());
	brw.setPosition(15);

	ASSERT_TRUE(brw.setSize(17));
	ASSERT_EQ(15, brw.position());

	ASSERT_TRUE(brw.shrink());
	ASSERT_EQ(17, brw.bufferSize());
	ASSERT_EQ(15, brw.position());

	ASSERT_TRUE(brw.setSize(16));
	ASSERT_EQ(15, brw.position());
	ASSERT_TRUE(brw.shrink());
	ASSERT_EQ(16, brw.bufferSize());
	ASSERT_EQ(15, brw.position());

	ASSERT_TRUE(brw.setSize(10));
	ASSERT_EQ(10, brw.position());
	ASSERT_TRUE(brw.shrink());
	ASSERT_EQ(16, brw.bufferSize());
	ASSERT_EQ(10, brw.position());
}

//------------------------------------------------------------------------------
TEST_F(IRBufferTest, writeILIntRO) {
	IRBuffer b(IRBufferTest_SAMPLE, IRBufferTest_SAMPLE_SIZE);

	ASSERT_FALSE(b.writeILInt(0));
}

//------------------------------------------------------------------------------
#define IRBufferTest_ILINT_VALUES_COUNT 10
const static std::uint8_t IRBufferTest_ILINT_VALUES_BIN[46] = {
		0x00,
		0xF7,
		0xF8, 0x01,
		0xF9, 0x01, 0x23,
		0xFA, 0x01, 0x23, 0x45,
		0xFB, 0x01, 0x23, 0x45, 0x67,
		0xFC, 0x01, 0x23, 0x45, 0x67, 0x89,
		0xFD, 0x01, 0x23, 0x45, 0x67, 0x89, 0xAB,
		0xFE, 0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD,
		0xFF, 0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF};

const static std::uint64_t IRBufferTest_ILINT_VALUES[IRBufferTest_ILINT_VALUES_COUNT] = {
		0x00ll,
		0xF7ll,
		0xF8ll + 0x01,
		0xF8ll + 0x0123ll,
		0xF8ll + 0x012345ll,
		0xF8ll + 0x01234567ll,
		0xF8ll + 0x0123456789ll,
		0xF8ll + 0x0123456789ABll,
		0xF8ll + 0x0123456789ABCDll,
		0xF8ll + 0x0123456789ABCDEFll};

TEST_F(IRBufferTest, writeILIntRW) {
	IRBuffer b;
	std::uint64_t v;
	std::uint8_t buff[16];
	int buffSize;

	v = 0;
	buffSize = ILInt::encode(v, buff, sizeof(buff));
	b.setSize(0);
	ASSERT_TRUE(b.writeILInt(v));
	ASSERT_EQ(buffSize, b.size());
	ASSERT_EQ(buffSize, b.position());
	ASSERT_EQ(0, memcmp(b.roBuffer(), buff, buffSize));

	b.setSize(16);
	b.setPosition(0);
	ASSERT_TRUE(b.writeILInt(v));
	ASSERT_EQ(16, b.size());
	ASSERT_EQ(buffSize, b.position());
	ASSERT_EQ(0, memcmp(b.roBuffer(), buff, buffSize));

	b.setSize(1);
	b.setPosition(1);
	ASSERT_TRUE(b.writeILInt(v));
	ASSERT_EQ(1 + buffSize, b.size());
	ASSERT_EQ(1 + buffSize, b.position());
	ASSERT_EQ(0, memcmp(b.roBuffer() + 1, buff, buffSize));

	b.setSize(16);
	b.setPosition(1);
	ASSERT_TRUE(b.writeILInt(v));
	ASSERT_EQ(16, b.size());
	ASSERT_EQ(1 + buffSize, b.position());
	ASSERT_EQ(0, memcmp(b.roBuffer() + 1, buff, buffSize));

	// Full ILInt
	v = 0xFFFFFFFFFFFFFFFFl;
	buffSize = ILInt::encode(v, buff, sizeof(buff));
	b.setSize(0);
	ASSERT_TRUE(b.writeILInt(v));
	ASSERT_EQ(buffSize, b.size());
	ASSERT_EQ(buffSize, b.position());
	ASSERT_EQ(0, memcmp(b.roBuffer(), buff, buffSize));

	b.setSize(16);
	b.setPosition(0);
	ASSERT_TRUE(b.writeILInt(v));
	ASSERT_EQ(16, b.size());
	ASSERT_EQ(buffSize, b.position());
	ASSERT_EQ(0, memcmp(b.roBuffer(), buff, buffSize));

	b.setSize(1);
	b.setPosition(1);
	ASSERT_TRUE(b.writeILInt(v));
	ASSERT_EQ(1 + buffSize, b.size());
	ASSERT_EQ(1 + buffSize, b.position());
	ASSERT_EQ(0, memcmp(b.roBuffer() + 1, buff, buffSize));

	b.setSize(16);
	b.setPosition(1);
	ASSERT_TRUE(b.writeILInt(v));
	ASSERT_EQ(16, b.size());
	ASSERT_EQ(1 + buffSize, b.position());
	ASSERT_EQ(0, memcmp(b.roBuffer() + 1, buff, buffSize));

	// Sequence of writes
	b.setSize(0);
	for (int i = 0; i < IRBufferTest_ILINT_VALUES_COUNT; i++) {
		ASSERT_TRUE(b.writeILInt(IRBufferTest_ILINT_VALUES[i]));
	}
	ASSERT_EQ(sizeof(IRBufferTest_ILINT_VALUES_BIN), b.size());
	ASSERT_EQ(0, std::memcmp(
			IRBufferTest_ILINT_VALUES_BIN,
			b.roBuffer(),
			sizeof(IRBufferTest_ILINT_VALUES_BIN)));
}

//------------------------------------------------------------------------------
TEST_F(IRBufferTest, readILIntRO) {
	IRBuffer b(IRBufferTest_ILINT_VALUES_BIN, sizeof(IRBufferTest_ILINT_VALUES_BIN));
	std::uint64_t v;

	for (int i = 0; i < IRBufferTest_ILINT_VALUES_COUNT; i++) {
		ASSERT_TRUE(b.readILInt(v));
		ASSERT_EQ(IRBufferTest_ILINT_VALUES[i], v);
	}

	// No fail with one
	for (int prefix = 0; prefix < 0xF8; prefix++) {
		std::uint8_t buff[16];
		std::uint64_t v;
		std::memset(buff, 0x01, sizeof(buff));
		buff[0] = prefix;
		IRBuffer c(buff, 1);
		ASSERT_TRUE(c.readILInt(v));
		ASSERT_EQ(prefix, v);

		// With offset
		std::memset(buff, 0x01, sizeof(buff));
		buff[1] = prefix;
		IRBuffer d(buff, 2);
		d.skip(1);
		ASSERT_TRUE(d.readILInt(v));
		ASSERT_EQ(prefix, v);
	}

	// Multi-byte
	std::uint64_t s = 0x01;
	for (int prefix = 0xF8; prefix <= 0xFF; prefix++) {
		std::uint8_t buff[16];
		std::uint64_t v;

		std::memset(buff, 0x01, sizeof(buff));
		buff[0] = prefix;
		IRBuffer c(buff, prefix - 0xF8 + 1 + 1);
		ASSERT_TRUE(c.readILInt(v));
		ASSERT_EQ(s + 0xF8, v);

		std::memset(buff, 0x01, sizeof(buff));
		buff[1] = prefix;
		IRBuffer d(buff, prefix - 0xF8 + 1 + 1 + 1);
		d.skip(1);
		ASSERT_TRUE(d.readILInt(v));
		ASSERT_EQ(s + 0xF8, v);
		s = (s << 8) + 1;
	}

	for (int i = 0; i < 8; i++) {
		std::uint8_t buff[16];
		int prefix = 0xF8 + i;
		std::memset(buff, 0x01, sizeof(buff));
		buff[0] = prefix;
		for (int size = 0; size <= i; size++) {
			IRBuffer b(buff, size);
			std::uint64_t v;
			ASSERT_FALSE(b.readILInt(v));
		}

		std::memset(buff, 0x01, sizeof(buff));
		buff[1] = prefix;
		for (int size = 0; size <= i; size++) {
			IRBuffer b(buff, size + 1);
			b.skip(1);
			std::uint64_t v;
			ASSERT_FALSE(b.readILInt(v));
		}
	}
}

//------------------------------------------------------------------------------
TEST_F(IRBufferTest, readILIntRW) {
	IRBuffer b;
	std::uint64_t v;

	b.set(IRBufferTest_ILINT_VALUES_BIN, sizeof(IRBufferTest_ILINT_VALUES_BIN));
	for (int i = 0; i < IRBufferTest_ILINT_VALUES_COUNT; i++) {
		ASSERT_TRUE(b.readILInt(v));
		ASSERT_EQ(IRBufferTest_ILINT_VALUES[i], v);
	}

	// No fail with one
	for (int prefix = 0; prefix < 0xF8; prefix++) {
		std::uint8_t buff[16];
		std::uint64_t v;
		std::memset(buff, 0x01, sizeof(buff));
		buff[0] = prefix;
		IRBuffer c;
		c.set(buff, 1);
		ASSERT_TRUE(c.readILInt(v));
		ASSERT_EQ(prefix, v);

		// With offset
		std::memset(buff, 0x01, sizeof(buff));
		buff[1] = prefix;
		IRBuffer d;
		d.set(buff, 2);
		d.skip(1);
		ASSERT_TRUE(d.readILInt(v));
		ASSERT_EQ(prefix, v);
	}

	// Multi-byte
	std::uint64_t s = 0x01;
	for (int prefix = 0xF8; prefix <= 0xFF; prefix++) {
		std::uint8_t buff[16];
		std::uint64_t v;

		std::memset(buff, 0x01, sizeof(buff));
		buff[0] = prefix;
		IRBuffer c;
		c.set(buff, prefix - 0xF8 + 1 + 1);
		ASSERT_TRUE(c.readILInt(v));
		ASSERT_EQ(s + 0xF8, v);

		std::memset(buff, 0x01, sizeof(buff));
		buff[1] = prefix;
		IRBuffer d;
		d.set(buff, prefix - 0xF8 + 1 + 1 + 1);
		d.skip(1);
		ASSERT_TRUE(d.readILInt(v));
		ASSERT_EQ(s + 0xF8, v);
		s = (s << 8) + 1;
	}

	for (int i = 0; i < 8; i++) {
		std::uint8_t buff[16];
		int prefix = 0xF8 + i;
		std::memset(buff, 0x01, sizeof(buff));
		buff[0] = prefix;
		for (int size = 0; size <= i; size++) {
			IRBuffer b;
			b.set(buff, size);
			std::uint64_t v;
			ASSERT_FALSE(b.readILInt(v));
		}

		std::memset(buff, 0x01, sizeof(buff));
		buff[1] = prefix;
		for (int size = 0; size <= i; size++) {
			IRBuffer b;
			b.set(buff, size + 1);
			b.skip(1);
			std::uint64_t v;
			ASSERT_FALSE(b.readILInt(v));
		}
	}
}

//------------------------------------------------------------------------------
TEST_F(IRBufferTest, roPosBuffer) {
	IRBuffer b(IRBufferTest_ILINT_VALUES_BIN, sizeof(IRBufferTest_ILINT_VALUES_BIN));

	while (b.available() > 0) {
		ASSERT_EQ(b.roBuffer() + b.position(), b.roPosBuffer());
		b.skip(1);
	}

	IRBuffer brw;
	brw.set(IRBufferTest_ILINT_VALUES_BIN, sizeof(IRBufferTest_ILINT_VALUES_BIN));
	while (brw.available() > 0) {
		ASSERT_EQ(brw.roBuffer() + brw.position(), brw.roPosBuffer());
		brw.skip(1);
	}
}

//------------------------------------------------------------------------------
TEST_F(IRBufferTest, posBuffer) {
	IRBuffer b(IRBufferTest_ILINT_VALUES_BIN, sizeof(IRBufferTest_ILINT_VALUES_BIN));

	while (b.available() > 0) {
		ASSERT_EQ(nullptr, b.posBuffer());
		b.skip(1);
	}

	IRBuffer brw;
	brw.set(IRBufferTest_ILINT_VALUES_BIN, sizeof(IRBufferTest_ILINT_VALUES_BIN));
	while (brw.available() > 0) {
		ASSERT_EQ(brw.buffer() + brw.position(), brw.posBuffer());
		brw.skip(1);
	}
}

//------------------------------------------------------------------------------
TEST_F(IRBufferTest, increment) {

	for (std::uint64_t inc = 1; inc < 32; inc++) {
		IRBuffer b(0, false, inc);
		ASSERT_EQ(inc, b.increment());
	}

	for (std::uint64_t inc = 1; inc < 32; inc++) {
		IRBuffer b(0, true, inc);
		ASSERT_EQ(inc, b.increment());
	}
}

//------------------------------------------------------------------------------
TEST_F(IRBufferTest, CONSTANTS) {

	ASSERT_EQ(16, IRBuffer::DEFAULT_INCREMENT);
}

//------------------------------------------------------------------------------
const static std::uint8_t IRBufferTest_INT_SAMPLE[32] = {
		0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF,
		0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF};

//------------------------------------------------------------------------------
TEST_F(IRBufferTest, writeInt8) {
	IRBuffer b;
	IRBuffer rob(IRBufferTest_INT_SAMPLE, sizeof(IRBufferTest_INT_SAMPLE));
	std::int8_t v;

	v = 0x45;
	ASSERT_FALSE(rob.writeInt(v));

	ASSERT_EQ(0, b.size());
	ASSERT_EQ(0, b.position());

	v = 0x01;
	ASSERT_TRUE(b.writeInt(v));
	ASSERT_EQ(sizeof(v), b.size());
	ASSERT_EQ(sizeof(v), b.position());

	v = 0x23;
	ASSERT_TRUE(b.writeInt(v));
	ASSERT_EQ(sizeof(v) * 2, b.size());
	ASSERT_EQ(sizeof(v) * 2, b.position());

	ASSERT_EQ(0, std::memcmp(IRBufferTest_INT_SAMPLE, b.roBuffer(), b.size()));

	b.beginning();
	v = 0x23;
	ASSERT_TRUE(b.writeInt(v));
	ASSERT_EQ(sizeof(v) * 2, b.size());
	ASSERT_EQ(sizeof(v), b.position());
}

//------------------------------------------------------------------------------
TEST_F(IRBufferTest, writeIntU8) {
	IRBuffer b;
	IRBuffer rob(IRBufferTest_INT_SAMPLE, sizeof(IRBufferTest_INT_SAMPLE));
	std::uint8_t v;

	v = 0x45;
	ASSERT_FALSE(rob.writeInt(v));

	ASSERT_EQ(0, b.size());
	ASSERT_EQ(0, b.position());

	v = 0x01;
	ASSERT_TRUE(b.writeInt(v));
	ASSERT_EQ(sizeof(v), b.size());
	ASSERT_EQ(sizeof(v), b.position());

	v = 0x23;
	ASSERT_TRUE(b.writeInt(v));
	ASSERT_EQ(sizeof(v) * 2, b.size());
	ASSERT_EQ(sizeof(v) * 2, b.position());

	ASSERT_EQ(0, std::memcmp(IRBufferTest_INT_SAMPLE, b.roBuffer(), b.size()));

	b.beginning();
	v = 0x23;
	ASSERT_TRUE(b.writeInt(v));
	ASSERT_EQ(sizeof(v) * 2, b.size());
	ASSERT_EQ(sizeof(v), b.position());
}

//------------------------------------------------------------------------------
TEST_F(IRBufferTest, writeInt16) {
	IRBuffer b;
	IRBuffer rob(IRBufferTest_INT_SAMPLE, sizeof(IRBufferTest_INT_SAMPLE));
	std::int16_t v;

	v = 0x4567;
	ASSERT_FALSE(rob.writeInt(v));

	ASSERT_EQ(0, b.size());
	ASSERT_EQ(0, b.position());

	v = 0x0123;
	ASSERT_TRUE(b.writeInt(v));
	ASSERT_EQ(sizeof(v), b.size());
	ASSERT_EQ(sizeof(v), b.position());

	v = 0x4567;
	ASSERT_TRUE(b.writeInt(v));
	ASSERT_EQ(sizeof(v) * 2, b.size());
	ASSERT_EQ(sizeof(v) * 2, b.position());

	ASSERT_EQ(0, std::memcmp(IRBufferTest_INT_SAMPLE, b.roBuffer(), b.size()));

	b.beginning();
	v = 0x2345;
	ASSERT_TRUE(b.writeInt(v));
	ASSERT_EQ(sizeof(v) * 2, b.size());
	ASSERT_EQ(sizeof(v), b.position());
}

//------------------------------------------------------------------------------
TEST_F(IRBufferTest, writeIntU16) {
	IRBuffer b;
	IRBuffer rob(IRBufferTest_INT_SAMPLE, sizeof(IRBufferTest_INT_SAMPLE));
	std::uint16_t v;

	v = 0x4567;
	ASSERT_FALSE(rob.writeInt(v));

	ASSERT_EQ(0, b.size());
	ASSERT_EQ(0, b.position());

	v = 0x0123;
	ASSERT_TRUE(b.writeInt(v));
	ASSERT_EQ(sizeof(v), b.size());
	ASSERT_EQ(sizeof(v), b.position());

	v = 0x4567;
	ASSERT_TRUE(b.writeInt(v));
	ASSERT_EQ(sizeof(v) * 2, b.size());
	ASSERT_EQ(sizeof(v) * 2, b.position());

	ASSERT_EQ(0, std::memcmp(IRBufferTest_INT_SAMPLE, b.roBuffer(), b.size()));

	b.beginning();
	v = 0x2345;
	ASSERT_TRUE(b.writeInt(v));
	ASSERT_EQ(sizeof(v) * 2, b.size());
	ASSERT_EQ(sizeof(v), b.position());
}

//------------------------------------------------------------------------------
TEST_F(IRBufferTest, writeInt32) {
	IRBuffer b;
	IRBuffer rob(IRBufferTest_INT_SAMPLE, sizeof(IRBufferTest_INT_SAMPLE));
	std::int32_t v;

	v = 0x456789AB;
	ASSERT_FALSE(rob.writeInt(v));

	ASSERT_EQ(0, b.size());
	ASSERT_EQ(0, b.position());

	v = 0x01234567;
	ASSERT_TRUE(b.writeInt(v));
	ASSERT_EQ(sizeof(v), b.size());
	ASSERT_EQ(sizeof(v), b.position());

	v = 0x89ABCDEF;
	ASSERT_TRUE(b.writeInt(v));
	ASSERT_EQ(sizeof(v) * 2, b.size());
	ASSERT_EQ(sizeof(v) * 2, b.position());

	ASSERT_EQ(0, std::memcmp(IRBufferTest_INT_SAMPLE, b.roBuffer(), b.size()));

	b.beginning();
	v = 0x23456789;
	ASSERT_TRUE(b.writeInt(v));
	ASSERT_EQ(sizeof(v) * 2, b.size());
	ASSERT_EQ(sizeof(v), b.position());
}


//------------------------------------------------------------------------------
TEST_F(IRBufferTest, writeIntU32) {
	IRBuffer b;
	IRBuffer rob(IRBufferTest_INT_SAMPLE, sizeof(IRBufferTest_INT_SAMPLE));
	std::uint32_t v;

	v = 0x456789AB;
	ASSERT_FALSE(rob.writeInt(v));

	ASSERT_EQ(0, b.size());
	ASSERT_EQ(0, b.position());

	v = 0x01234567;
	ASSERT_TRUE(b.writeInt(v));
	ASSERT_EQ(sizeof(v), b.size());
	ASSERT_EQ(sizeof(v), b.position());

	v = 0x89ABCDEF;
	ASSERT_TRUE(b.writeInt(v));
	ASSERT_EQ(sizeof(v) * 2, b.size());
	ASSERT_EQ(sizeof(v) * 2, b.position());

	ASSERT_EQ(0, std::memcmp(IRBufferTest_INT_SAMPLE, b.roBuffer(), b.size()));

	b.beginning();
	v = 0x23456789;
	ASSERT_TRUE(b.writeInt(v));
	ASSERT_EQ(sizeof(v) * 2, b.size());
	ASSERT_EQ(sizeof(v), b.position());
}

//------------------------------------------------------------------------------
TEST_F(IRBufferTest, writeInt64) {
	IRBuffer b;
	IRBuffer rob(IRBufferTest_INT_SAMPLE, sizeof(IRBufferTest_INT_SAMPLE));
	std::int64_t v;

	v = 0x456789AB;
	ASSERT_FALSE(rob.writeInt(v));

	ASSERT_EQ(0, b.size());
	ASSERT_EQ(0, b.position());

	v = 0x0123456789ABCDEFll;
	ASSERT_TRUE(b.writeInt(v));
	ASSERT_EQ(sizeof(v), b.size());
	ASSERT_EQ(sizeof(v), b.position());

	v = 0x0123456789ABCDEFll;
	ASSERT_TRUE(b.writeInt(v));
	ASSERT_EQ(sizeof(v) * 2, b.size());
	ASSERT_EQ(sizeof(v) * 2, b.position());

	ASSERT_EQ(0, std::memcmp(IRBufferTest_INT_SAMPLE, b.roBuffer(), b.size()));

	b.beginning();
	v = 0x23456789;
	ASSERT_TRUE(b.writeInt(v));
	ASSERT_EQ(sizeof(v) * 2, b.size());
	ASSERT_EQ(sizeof(v), b.position());
}
//------------------------------------------------------------------------------
TEST_F(IRBufferTest, writeUInt64) {
	IRBuffer b;
	IRBuffer rob(IRBufferTest_INT_SAMPLE, sizeof(IRBufferTest_INT_SAMPLE));
	std::uint64_t v;

	v = 0x456789AB;
	ASSERT_FALSE(rob.writeInt(v));

	ASSERT_EQ(0, b.size());
	ASSERT_EQ(0, b.position());

	v = 0x0123456789ABCDEFll;
	ASSERT_TRUE(b.writeInt(v));
	ASSERT_EQ(sizeof(v), b.size());
	ASSERT_EQ(sizeof(v), b.position());

	v = 0x0123456789ABCDEFll;
	ASSERT_TRUE(b.writeInt(v));
	ASSERT_EQ(sizeof(v) * 2, b.size());
	ASSERT_EQ(sizeof(v) * 2, b.position());

	ASSERT_EQ(0, std::memcmp(IRBufferTest_INT_SAMPLE, b.roBuffer(), b.size()));

	b.beginning();
	v = 0x23456789;
	ASSERT_TRUE(b.writeInt(v));
	ASSERT_EQ(sizeof(v) * 2, b.size());
	ASSERT_EQ(sizeof(v), b.position());
}

//------------------------------------------------------------------------------
TEST_F(IRBufferTest, readInt8) {
	std::int8_t v;
	IRBuffer b;
	IRBuffer rob(IRBufferTest_INT_SAMPLE, sizeof(v) * 2);

	b.set(rob.roBuffer(), rob.size());
	b.beginning();
	ASSERT_TRUE(b.readInt(v));
	ASSERT_EQ(0x01, v);
	ASSERT_TRUE(b.readInt(v));
	ASSERT_EQ(0x23, v);
	ASSERT_FALSE(b.readInt(v));

	rob.beginning();
	ASSERT_TRUE(rob.readInt(v));
	ASSERT_EQ(0x01, v);
	ASSERT_TRUE(rob.readInt(v));
	ASSERT_EQ(0x23, v);
	ASSERT_FALSE(rob.readInt(v));
}

//------------------------------------------------------------------------------
TEST_F(IRBufferTest, readIntU8) {
	std::uint8_t v;
	IRBuffer b;
	IRBuffer rob(IRBufferTest_INT_SAMPLE, sizeof(v) * 2);

	b.set(rob.roBuffer(), rob.size());
	b.beginning();
	ASSERT_TRUE(b.readInt(v));
	ASSERT_EQ(0x01, v);
	ASSERT_TRUE(b.readInt(v));
	ASSERT_EQ(0x23, v);
	ASSERT_FALSE(b.readInt(v));

	rob.beginning();
	ASSERT_TRUE(rob.readInt(v));
	ASSERT_EQ(0x01, v);
	ASSERT_TRUE(rob.readInt(v));
	ASSERT_EQ(0x23, v);
	ASSERT_FALSE(rob.readInt(v));
}

//------------------------------------------------------------------------------
TEST_F(IRBufferTest, readInt16) {
	std::int16_t v;
	IRBuffer b;
	IRBuffer rob(IRBufferTest_INT_SAMPLE, sizeof(v) * 2);

	b.set(rob.roBuffer(), rob.size());
	b.beginning();
	ASSERT_TRUE(b.readInt(v));
	ASSERT_EQ(0x0123, v);
	ASSERT_TRUE(b.readInt(v));
	ASSERT_EQ(0x4567, v);
	ASSERT_FALSE(b.readInt(v));

	rob.beginning();
	ASSERT_TRUE(rob.readInt(v));
	ASSERT_EQ(0x0123, v);
	ASSERT_TRUE(rob.readInt(v));
	ASSERT_EQ(0x4567, v);
	ASSERT_FALSE(rob.readInt(v));
}

//------------------------------------------------------------------------------
TEST_F(IRBufferTest, readIntU16) {
	std::uint16_t v;
	IRBuffer b;
	IRBuffer rob(IRBufferTest_INT_SAMPLE, sizeof(v) * 2);

	b.set(rob.roBuffer(), rob.size());
	b.beginning();
	ASSERT_TRUE(b.readInt(v));
	ASSERT_EQ(0x0123, v);
	ASSERT_TRUE(b.readInt(v));
	ASSERT_EQ(0x4567, v);
	ASSERT_FALSE(b.readInt(v));

	rob.beginning();
	ASSERT_TRUE(rob.readInt(v));
	ASSERT_EQ(0x0123, v);
	ASSERT_TRUE(rob.readInt(v));
	ASSERT_EQ(0x4567, v);
	ASSERT_FALSE(rob.readInt(v));
}

//------------------------------------------------------------------------------
TEST_F(IRBufferTest, readInt32) {
	std::int32_t v;
	IRBuffer b;
	IRBuffer rob(IRBufferTest_INT_SAMPLE, sizeof(v) * 2);

	b.set(rob.roBuffer(), rob.size());
	b.beginning();
	ASSERT_TRUE(b.readInt(v));
	ASSERT_EQ(0x01234567, v);
	ASSERT_TRUE(b.readInt(v));
	ASSERT_EQ(0x89ABCDEF, v);
	ASSERT_FALSE(b.readInt(v));

	rob.beginning();
	ASSERT_TRUE(rob.readInt(v));
	ASSERT_EQ(0x01234567, v);
	ASSERT_TRUE(rob.readInt(v));
	ASSERT_EQ(0x89ABCDEF, v);
	ASSERT_FALSE(rob.readInt(v));
}

//------------------------------------------------------------------------------
TEST_F(IRBufferTest, readIntU32) {
	std::uint32_t v;
	IRBuffer b;
	IRBuffer rob(IRBufferTest_INT_SAMPLE, sizeof(v) * 2);

	b.set(rob.roBuffer(), rob.size());
	b.beginning();
	ASSERT_TRUE(b.readInt(v));
	ASSERT_EQ(0x01234567, v);
	ASSERT_TRUE(b.readInt(v));
	ASSERT_EQ(0x89ABCDEF, v);
	ASSERT_FALSE(b.readInt(v));

	rob.beginning();
	ASSERT_TRUE(rob.readInt(v));
	ASSERT_EQ(0x01234567, v);
	ASSERT_TRUE(rob.readInt(v));
	ASSERT_EQ(0x89ABCDEF, v);
	ASSERT_FALSE(rob.readInt(v));
}

//------------------------------------------------------------------------------
TEST_F(IRBufferTest, readInt64) {
	std::int64_t v;
	IRBuffer b;
	IRBuffer rob(IRBufferTest_INT_SAMPLE, sizeof(v) * 2);

	b.set(rob.roBuffer(), rob.size());
	b.beginning();
	ASSERT_TRUE(b.readInt(v));
	ASSERT_EQ(0x0123456789ABCDEFll, v);
	ASSERT_TRUE(b.readInt(v));
	ASSERT_EQ(0x0123456789ABCDEFll, v);
	ASSERT_FALSE(b.readInt(v));

	rob.beginning();
	ASSERT_TRUE(rob.readInt(v));
	ASSERT_EQ(0x0123456789ABCDEFll, v);
	ASSERT_TRUE(rob.readInt(v));
	ASSERT_EQ(0x0123456789ABCDEFll, v);
	ASSERT_FALSE(rob.readInt(v));
}

//------------------------------------------------------------------------------
TEST_F(IRBufferTest, readIntU64) {
	std::uint64_t v;
	IRBuffer b;
	IRBuffer rob(IRBufferTest_INT_SAMPLE, sizeof(v) * 2);

	b.set(rob.roBuffer(), rob.size());
	b.beginning();
	ASSERT_TRUE(b.readInt(v));
	ASSERT_EQ(0x0123456789ABCDEFll, v);
	ASSERT_TRUE(b.readInt(v));
	ASSERT_EQ(0x0123456789ABCDEFll, v);
	ASSERT_FALSE(b.readInt(v));

	rob.beginning();
	ASSERT_TRUE(rob.readInt(v));
	ASSERT_EQ(0x0123456789ABCDEFll, v);
	ASSERT_TRUE(rob.readInt(v));
	ASSERT_EQ(0x0123456789ABCDEFll, v);
	ASSERT_FALSE(rob.readInt(v));
}

//------------------------------------------------------------------------------
TEST_F(IRBufferTest, writeFloatSingle) {
	float v;
	IRBuffer b;
	IRBuffer rob(IRBufferTest_INT_SAMPLE, sizeof(v) * 2);
	std::uint8_t exp[sizeof(v) * 2];

	v = 0;
	ASSERT_FALSE(rob.writeFloat(v));

	ASSERT_EQ(0, b.size());
	ASSERT_EQ(0, b.position());

	v = 1.23456;
	ASSERT_TRUE(b.writeFloat(v));
	ASSERT_EQ(sizeof(v), b.size());
	ASSERT_EQ(sizeof(v), b.position());

	v = -1.23456;
	ASSERT_TRUE(b.writeFloat(v));
	ASSERT_EQ(sizeof(v) * 2, b.size());
	ASSERT_EQ(sizeof(v) * 2, b.position());

	// Check value
	v = 1.23456;
	IRFloatingPoint::toBytes(true, v, exp);
	v = -1.23456;
	IRFloatingPoint::toBytes(true, v, exp + sizeof(v));
	ASSERT_EQ(0, std::memcmp(exp, b.roBuffer(), sizeof(exp)));

	//
	v = -1.23456;
	b.beginning();
	ASSERT_TRUE(b.writeFloat(v));
	ASSERT_EQ(sizeof(v) * 2, b.size());
	ASSERT_EQ(sizeof(v), b.position());
}

//------------------------------------------------------------------------------
TEST_F(IRBufferTest, writeFloatDouble) {
	double v;
	IRBuffer b;
	IRBuffer rob(IRBufferTest_INT_SAMPLE, sizeof(v) * 2);
	std::uint8_t exp[sizeof(v) * 2];

	v = 0;
	ASSERT_FALSE(rob.writeFloat(v));

	ASSERT_EQ(0, b.size());
	ASSERT_EQ(0, b.position());

	v = 1.23456;
	ASSERT_TRUE(b.writeFloat(v));
	ASSERT_EQ(sizeof(v), b.size());
	ASSERT_EQ(sizeof(v), b.position());

	v = -1.23456;
	ASSERT_TRUE(b.writeFloat(v));
	ASSERT_EQ(sizeof(v) * 2, b.size());
	ASSERT_EQ(sizeof(v) * 2, b.position());

	// Check value
	v = 1.23456;
	IRFloatingPoint::toBytes(true, v, exp);
	v = -1.23456;
	IRFloatingPoint::toBytes(true, v, exp + sizeof(v));
	ASSERT_EQ(0, std::memcmp(exp, b.roBuffer(), sizeof(exp)));

	v = -1.23456;
	b.beginning();
	ASSERT_TRUE(b.writeFloat(v));
	ASSERT_EQ(sizeof(v) * 2, b.size());
	ASSERT_EQ(sizeof(v), b.position());
}

//------------------------------------------------------------------------------
TEST_F(IRBufferTest, readFloatSingle) {
	float v;
	float e;
	std::uint8_t exp[sizeof(v) * 2];

	// Prepare the values to be checked
	v = 1.23456;
	IRFloatingPoint::toBytes(true, v, exp);
	v = -1.23456;
	IRFloatingPoint::toBytes(true, v, exp + sizeof(v));

	IRBuffer b;
	ASSERT_TRUE(b.set(exp, sizeof(exp)));
	IRBuffer rob(exp, sizeof(exp));

	ASSERT_TRUE(b.readFloat(v));
	e = 1.23456;
	ASSERT_EQ(e, v);
	ASSERT_TRUE(b.readFloat(v));
	e = -1.23456;
	ASSERT_EQ(e, v);
	ASSERT_FALSE(b.readFloat(v));

	ASSERT_TRUE(rob.readFloat(v));
	e = 1.23456;
	ASSERT_EQ(e, v);
	ASSERT_TRUE(rob.readFloat(v));
	e = -1.23456;
	ASSERT_EQ(e, v);
	ASSERT_FALSE(rob.readFloat(v));
}

//------------------------------------------------------------------------------
TEST_F(IRBufferTest, readFloatDouble) {
	double v;
	double e;
	std::uint8_t exp[sizeof(v) * 2];

	// Prepare the values to be checked
	v = 1.23456;
	IRFloatingPoint::toBytes(true, v, exp);
	v = -1.23456;
	IRFloatingPoint::toBytes(true, v, exp + sizeof(v));

	IRBuffer b;
	ASSERT_TRUE(b.set(exp, sizeof(exp)));
	IRBuffer rob(exp, sizeof(exp));

	ASSERT_TRUE(b.readFloat(v));
	e = 1.23456;
	ASSERT_EQ(e, v);
	ASSERT_TRUE(b.readFloat(v));
	e = -1.23456;
	ASSERT_EQ(e, v);
	ASSERT_FALSE(b.readFloat(v));

	ASSERT_TRUE(rob.readFloat(v));
	e = 1.23456;
	ASSERT_EQ(e, v);
	ASSERT_TRUE(rob.readFloat(v));
	e = -1.23456;
	ASSERT_EQ(e, v);
	ASSERT_FALSE(rob.readFloat(v));
}

//------------------------------------------------------------------------------
TEST_F(IRBufferTest, set) {
	IRBuffer buff;
	IRBuffer roBuff(IRBufferTest_SAMPLE, IRBufferTest_SAMPLE_SIZE);

	ASSERT_FALSE(roBuff.set(IRBufferTest_SAMPLE, IRBufferTest_SAMPLE_SIZE));

	// Set on empty
	ASSERT_TRUE(buff.set(IRBufferTest_SAMPLE, IRBufferTest_SAMPLE_SIZE));
	ASSERT_EQ(IRBufferTest_SAMPLE_SIZE, buff.size());
	ASSERT_EQ(0, buff.position());
	ASSERT_EQ(0, std::memcmp(IRBufferTest_SAMPLE, buff.roBuffer(), IRBufferTest_SAMPLE_SIZE));

	// Replace a larger value
	buff.ending();
	ASSERT_TRUE(buff.set(IRBufferTest_SAMPLE, IRBufferTest_SAMPLE_SIZE));
	ASSERT_EQ(IRBufferTest_SAMPLE_SIZE, buff.size());
	ASSERT_EQ(0, buff.position());
	ASSERT_EQ(0, std::memcmp(IRBufferTest_SAMPLE, buff.roBuffer(), IRBufferTest_SAMPLE_SIZE));

	// Replace a larger value
	ASSERT_TRUE(buff.write(IRBufferTest_SAMPLE, IRBufferTest_SAMPLE_SIZE));
	buff.ending();
	ASSERT_TRUE(buff.set(IRBufferTest_SAMPLE, IRBufferTest_SAMPLE_SIZE));
	ASSERT_EQ(IRBufferTest_SAMPLE_SIZE, buff.size());
	ASSERT_EQ(0, buff.position());
	ASSERT_EQ(0, std::memcmp(IRBufferTest_SAMPLE, buff.roBuffer(), IRBufferTest_SAMPLE_SIZE));
}

//------------------------------------------------------------------------------
TEST_F(IRBufferTest, copy) {
	IRBuffer buff;
	IRBuffer buff2;
	IRBuffer roBuff(IRBufferTest_SAMPLE, IRBufferTest_SAMPLE_SIZE);

	// Test on read-only instance
	ASSERT_FALSE(roBuff.copy(buff));
	ASSERT_FALSE(roBuff.copy(roBuff));

	// Copy one instance to itself
	ASSERT_TRUE(buff.write(1));
	ASSERT_TRUE(buff.copy(buff));
	ASSERT_EQ(1, buff.position());

	// Copy empty to non-empty
	ASSERT_TRUE(buff.copy(buff2));
	ASSERT_EQ(0, buff.size());
	ASSERT_EQ(0, buff.position());

	// Copy read-only
	roBuff.setPosition(3);
	ASSERT_TRUE(buff.copy(roBuff));
	ASSERT_EQ(roBuff.position(), buff.position());
	ASSERT_EQ(roBuff.size(), buff.size());
	ASSERT_EQ(0, std::memcmp(roBuff.roBuffer(), buff.roBuffer(), buff.size()));
}

//------------------------------------------------------------------------------





