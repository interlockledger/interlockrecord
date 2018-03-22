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
#include "IRDummyRandom.h"
#include <ircommon/irutils.h>
#include <cstring>
#include <thread>

//==============================================================================
// class IRDummyRandom
//------------------------------------------------------------------------------
void IRDummyRandom::setSeed(std::uint64_t seed) {
	this->_seed = seed;
}

//------------------------------------------------------------------------------
void  IRDummyRandom::setSeed(const void * seed, std::uint64_t seedSize) {
	std::uint8_t tmp[8];

	std::memset(tmp, 0, sizeof(tmp));
	std::memcpy(tmp, seed, (seedSize < 8)? seedSize : 8);
	IRUtils::BE2Int(tmp, this->_seed);
}

//------------------------------------------------------------------------------
void IRDummyRandom::nextBytes(void * out, std::uint64_t outSize) {
	std::uint8_t * p = (std::uint8_t *)out;

	for (unsigned int i = 0; i < outSize; i++, p++) {
		*p = (std::uint8_t)(this->_seed & 0xFF);
		this->_seed++;
	}
}

//==============================================================================
// class IRDelayedRandom
//------------------------------------------------------------------------------
IRDelayedRandom::IRDelayedRandom(IRRandom * random, std::uint64_t delay):
		IRRandom(), _random(random), _delay(delay) {
}

//------------------------------------------------------------------------------
IRDelayedRandom::~IRDelayedRandom() {
	if (this->_random) {
		delete this->_random;
	}
}

//------------------------------------------------------------------------------
void IRDelayedRandom::delay(){
	std::this_thread::sleep_for(std::chrono::milliseconds(this->_delay));
}

//------------------------------------------------------------------------------
void IRDelayedRandom::setSeed(std::uint64_t seed){
	this->delay();
	this->_random->setSeed(seed);
}

//------------------------------------------------------------------------------
void IRDelayedRandom::setSeed(const void * seed, std::uint64_t seedSize){
	this->delay();
	this->_random->setSeed(seed, seedSize);
}

//------------------------------------------------------------------------------
bool IRDelayedRandom::nextBoolean() {
	this->delay();
	return this->_random->nextBoolean();
}

//------------------------------------------------------------------------------
std::uint8_t IRDelayedRandom::next() {
	this->delay();
	return this->_random->next();
}

//------------------------------------------------------------------------------
std::uint16_t IRDelayedRandom::next16() {
	this->delay();
	return this->_random->next16();
}

//------------------------------------------------------------------------------
std::uint32_t IRDelayedRandom::next32() {
	this->delay();
	return this->_random->next32();
}

//------------------------------------------------------------------------------
std::uint64_t IRDelayedRandom::next64() {
	this->delay();
	return this->_random->next64();
}

//------------------------------------------------------------------------------
float IRDelayedRandom::nextFloat() {
	this->delay();
	return this->_random->nextFloat();
}


//------------------------------------------------------------------------------
double IRDelayedRandom::nextDouble() {
	this->delay();
	return this->_random->nextDouble();
}

//------------------------------------------------------------------------------
void IRDelayedRandom::nextBytes(void * out, std::uint64_t outSize) {
	this->delay();
	this->_random->nextBytes(out, outSize);
}

//------------------------------------------------------------------------------
