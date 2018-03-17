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
#include <ircommon/irrandom.h>
#include <ircommon/irutils.h>
#include <algorithm>
#include <ctime>
#include <cstring>

using namespace ircommon;

//==============================================================================
// Class IRRandom
//------------------------------------------------------------------------------
bool IRRandom::nextBoolean() {
	std::uint32_t v;

	v = this->next32();
	v = v ^ (v >> 16);
	v = v ^ (v >> 8);
	v = v ^ (v >> 4);
	v = v ^ (v >> 2);
	v = v ^ (v >> 1);
	return (v & 0x1) == 1;
}

//------------------------------------------------------------------------------
std::uint8_t IRRandom::next() {
	return (std::uint8_t)(this->next32() & 0xFF);
}

//------------------------------------------------------------------------------
std::uint16_t IRRandom::next16() {
	return (std::uint16_t)(this->next32() & 0xFFFF);
}

//------------------------------------------------------------------------------
std::uint32_t IRRandom::next32() {
	std::uint8_t tmp[4];
	std::uint32_t v;

	this->nextBytes(&tmp, sizeof(tmp));
	IRUtils::BE2Int(tmp, v);
	return v;
}

//------------------------------------------------------------------------------
std::uint64_t IRRandom::next64() {
	return (((std::uint64_t)this->next32()) << 32) +
			((std::uint64_t)this->next32());
}

//------------------------------------------------------------------------------
float IRRandom::nextFloat() {
	return (this->next32() & 0x7FFFFF) / ((float)0x800000);
}

//------------------------------------------------------------------------------
double IRRandom::nextDouble() {
	return (this->next64() & 0xFFFFFFFFFFFFFll) / ((double)0x10000000000000ll);
}

//==============================================================================
// Class IRRandom
//------------------------------------------------------------------------------
IRXORShifRandom::IRXORShifRandom() {
	this->setSeed(std::time(nullptr));
}

//------------------------------------------------------------------------------
void IRXORShifRandom::setSeed(std::uint64_t seed) {

	this->_state[0] = seed;
	this->_state[1] = 0;
}

//------------------------------------------------------------------------------
std::uint64_t IRXORShifRandom::nextValue() {
	std::uint64_t x = this->_state[0];
	const std::uint64_t y = this->_state[1];

	this->_state[0] = y;
	x ^= x << 23;
	this->_state[1] = x ^ y ^ (x >> 17) ^ (y >> 26);
	return this->_state[1] + y;
}

//------------------------------------------------------------------------------
std::uint32_t IRXORShifRandom::next32() {
	return (std::uint32_t)((this->nextValue() >> 8) & 0xFFFFFFFF);
}

//------------------------------------------------------------------------------
void IRXORShifRandom::nextBytes(void * out, std::uint64_t outSize) {
	std::uint32_t v;
	std::uint8_t * p = (std::uint8_t *)out;

	while (outSize > 0) {
		v = this->next32();
		std::uint64_t n = (outSize < 4)? outSize : 4;
		for ( ; n > 0; n--) {
			*p = ((v >> 24) & 0xFF);
			v = v << 8;
			p++;
		}
		outSize = outSize - n;
	}
}

//------------------------------------------------------------------------------
