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
