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
	ASSERT_EQ(0, b->available());
	ASSERT_EQ(16, b->bufferSize());
	ASSERT_EQ(0, b->size());
	ASSERT_TRUE(b->buffer() != nullptr);
	ASSERT_TRUE(b->roBuffer() == b->buffer());
	delete b;

	b = new IRBuffer(16);
	ASSERT_FALSE(b->readOnly());
	ASSERT_FALSE(b->secure());
	ASSERT_EQ(0, b->position());
	ASSERT_EQ(0, b->available());
	ASSERT_EQ(32, b->bufferSize());
	ASSERT_EQ(0, b->size());
	ASSERT_TRUE(b->buffer() != nullptr);
	ASSERT_TRUE(b->roBuffer() == b->buffer());
	delete b;

	b = new IRBuffer(16, false);
	ASSERT_FALSE(b->readOnly());
	ASSERT_FALSE(b->secure());
	ASSERT_EQ(0, b->position());
	ASSERT_EQ(0, b->available());
	ASSERT_EQ(32, b->bufferSize());
	ASSERT_EQ(0, b->size());
	ASSERT_TRUE(b->buffer() != nullptr);
	ASSERT_TRUE(b->roBuffer() == b->buffer());
	delete b;

	b = new IRBuffer(16, true);
	ASSERT_FALSE(b->readOnly());
	ASSERT_TRUE(b->secure());
	ASSERT_EQ(0, b->position());
	ASSERT_EQ(0, b->available());
	ASSERT_EQ(32, b->bufferSize());
	ASSERT_EQ(0, b->size());
	ASSERT_TRUE(b->buffer() != nullptr);
	ASSERT_TRUE(b->roBuffer() == b->buffer());
	delete b;

	b = new IRBuffer(16, false, 32);
	ASSERT_FALSE(b->readOnly());
	ASSERT_FALSE(b->secure());
	ASSERT_EQ(0, b->position());
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
	ASSERT_EQ(0, b->available());
	ASSERT_EQ(32, b->bufferSize());
	ASSERT_EQ(0, b->size());
	ASSERT_TRUE(b->buffer() != nullptr);
	ASSERT_TRUE(b->roBuffer() == b->buffer());
	delete b;
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
	char buff[512];
	std::uint64_t read;

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
	const char * pEnd;
	IRBuffer b;

	p = IRBufferTest_SAMPLE;
	pEnd = p + IRBufferTest_SAMPLE_SIZE;

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

