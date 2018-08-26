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
#include <irecordcore/irsrand.h>
#include <botan/auto_rng.h>

using namespace irecordcore;
using namespace irecordcore::crypto;

//==============================================================================
// Class IRSecureRandom
//------------------------------------------------------------------------------
IRSecureRandom::IRSecureRandom(): IRSecureRandom(new Botan::AutoSeeded_RNG()) {
}

//------------------------------------------------------------------------------
IRSecureRandom::IRSecureRandom(Botan::RandomNumberGenerator * rng):
		_random(rng) {
}

//------------------------------------------------------------------------------
void IRSecureRandom::setSeed(std::uint64_t seed) {
	this->setSeed(&seed, sizeof(seed));
}

//------------------------------------------------------------------------------
void IRSecureRandom::setSeed(const void * seed, std::uint64_t seedSize) {
	this->_random->add_entropy((const std::uint8_t *)seed, seedSize);
}

//------------------------------------------------------------------------------
void IRSecureRandom::nextBytes(void * out, std::uint64_t outSize) {
	this->_random->randomize((std::uint8_t *) out, outSize);
}

//------------------------------------------------------------------------------
