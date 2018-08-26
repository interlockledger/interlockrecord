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
#include <ircommon/irshrand.h>

using namespace ircommon;
using namespace ircommon::threading;

//==============================================================================
// Class IRRandom
//------------------------------------------------------------------------------
IRSharedRandom::IRSharedRandom(IRRandom * random): IRRandom(), _random(random),
		_mutex() {
}

//------------------------------------------------------------------------------
void IRSharedRandom::setSeed(std::uint64_t seed) {
	std::lock_guard<std::mutex> lock(this->_mutex);
	this->_random->setSeed(seed);
}

//------------------------------------------------------------------------------
void IRSharedRandom::setSeed(const void * seed, std::uint64_t seedSize) {
	std::lock_guard<std::mutex> lock(this->_mutex);
	this->_random->setSeed(seed, seedSize);
}

//------------------------------------------------------------------------------
bool IRSharedRandom::nextBoolean() {
	std::lock_guard<std::mutex> lock(this->_mutex);
	return this->_random->nextBoolean();
}

//------------------------------------------------------------------------------
std::uint8_t IRSharedRandom::next() {
	std::lock_guard<std::mutex> lock(this->_mutex);
	return this->_random->next();
}

//------------------------------------------------------------------------------
std::uint16_t IRSharedRandom::next16() {
	std::lock_guard<std::mutex> lock(this->_mutex);
	return this->_random->next16();
}

//------------------------------------------------------------------------------
std::uint32_t IRSharedRandom::next32() {
	std::lock_guard<std::mutex> lock(this->_mutex);
	return this->_random->next32();
}

//------------------------------------------------------------------------------
std::uint64_t IRSharedRandom::next64() {
	std::lock_guard<std::mutex> lock(this->_mutex);
	return this->_random->next64();
}

//------------------------------------------------------------------------------
float IRSharedRandom::nextFloat() {
	std::lock_guard<std::mutex> lock(this->_mutex);
	return this->_random->nextFloat();
}

//------------------------------------------------------------------------------
double IRSharedRandom::nextDouble() {
	std::lock_guard<std::mutex> lock(this->_mutex);
	return this->_random->nextDouble();
}

//------------------------------------------------------------------------------
void IRSharedRandom::nextBytes(void * out, std::uint64_t outSize) {
	std::lock_guard<std::mutex> lock(this->_mutex);
	this->_random->nextBytes(out, outSize);
}
//------------------------------------------------------------------------------

