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

//------------------------------------------------------------------------------
void IRRandom::nextBytesFrom32(IRRandom & random, void * out,
		std::uint64_t outSize) {
	std::uint32_t v;
	std::uint8_t * p = (std::uint8_t *)out;

	while (outSize > 0) {
		v = random.next32();
		std::uint64_t n = (outSize < 4)? outSize : 4;
		outSize = outSize - n;
		for ( ; n > 0; n--) {
			*p = ((v >> 24) & 0xFF);
			v = v << 8;
			p++;
		}
	}
}

//==============================================================================
// Class IRRandom
//------------------------------------------------------------------------------
IRXORShifRandom::IRXORShifRandom() {
	this->setSeed(std::time(nullptr));
}

//------------------------------------------------------------------------------
IRXORShifRandom::IRXORShifRandom(std::uint64_t seed) {
	this->setSeed(seed);
}

//------------------------------------------------------------------------------
void IRXORShifRandom::setSeed(std::uint64_t seed) {

	this->_state[0] = seed;
	this->_state[1] = 0x6a09e667bb67ae85ll ^ seed;
}

//------------------------------------------------------------------------------
void IRXORShifRandom::setSeed(const void * seed, std::uint64_t seedSize) {
	std::uint8_t tmp[16];
	std::uint64_t s0;
	std::uint64_t s1;

	std::memset(tmp, 0, sizeof(tmp));
	std::memcpy(tmp, seed, seedSize > 16 ? 16: seedSize);
	IRUtils::BE2Int(tmp, s0);
	IRUtils::BE2Int(tmp + 8, s1);
	this->setSeed(s0, s1);
}

//------------------------------------------------------------------------------
void IRXORShifRandom::setSeed(std::uint64_t seed0, std::uint64_t seed1) {

	if ((seed0 == 0) && (seed1 == 0)) {
		seed0 = 1;
	}
	this->_state[0] = seed0;
	this->_state[1] = seed1;
}

//------------------------------------------------------------------------------
std::uint64_t IRXORShifRandom::nextValue() {
	std::uint64_t x = this->_state[0];
	const std::uint64_t y = this->_state[1];

	this->_state[0] = y;
	x ^= x << 23;
	this->_state[1] = x ^ y ^ (x >> 17) ^ (y >> 26);
	std::uint64_t v = this->_state[1] + y;
	return v;
}

//------------------------------------------------------------------------------
std::uint32_t IRXORShifRandom::next32() {
	return (std::uint32_t)((this->nextValue() >> 8) & 0xFFFFFFFF);
}

//------------------------------------------------------------------------------
void IRXORShifRandom::nextBytes(void * out, std::uint64_t outSize) {
	IRRandom::nextBytesFrom32(*this, out, outSize);
}

//------------------------------------------------------------------------------
