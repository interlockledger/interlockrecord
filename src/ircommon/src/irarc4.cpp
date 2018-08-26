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
#include <ircommon/irarc4.h>
#include <ircommon/irutils.h>
#include <cstring>
#include <ctime>
using namespace ircommon;
using namespace ircommon::crypto;

//==============================================================================
// class IRARC4
//------------------------------------------------------------------------------
IRARC4::IRARC4() {

	std::memset(&(this->_state), 0, sizeof(this->_state));
}

//------------------------------------------------------------------------------
IRARC4::IRARC4(const void * key, int keySize): IRARC4() {

	this->setKey(key, keySize);
}

//------------------------------------------------------------------------------
IRARC4::~IRARC4() {

	IRUtils::clearMemory(&(this->_state), sizeof(this->_state));
}

//------------------------------------------------------------------------------
void IRARC4::setKey(const void * key, int keySize) {
	std::uint8_t * s = this->_state[CURR].s;
	for (int i = 0; i < 256; i++) {
		s[i] = i;
	}
	this->remixKey(key, keySize);
}

//------------------------------------------------------------------------------
void IRARC4::remixKey(const void * key, int keySize) {
	int i;
	int j;
	const std::uint8_t * k = (const std::uint8_t *)key;
	std::uint8_t * s = this->_state[CURR].s;
	std::uint8_t tmp;

	j = 0;
	for (i = 0; i < 256; i++) {
		j = (j + s[i] + k[i % keySize]) & 0xFF;
		tmp = s[i];
		s[i] = s[j];
		s[j] = tmp;
	}
	this->_state[CURR].i = 0;
	this->_state[CURR].j = 0;
}

//------------------------------------------------------------------------------
void IRARC4::save() {

	std::memcpy(&(this->_state[SAVED]), &(this->_state[CURR]), sizeof(State));
}

//------------------------------------------------------------------------------
void IRARC4::load() {

	std::memcpy(&(this->_state[CURR]), &(this->_state[SAVED]), sizeof(State));
}

//------------------------------------------------------------------------------
std::uint8_t IRARC4::next() {
	int & i = this->_state[CURR].i;
	int & j = this->_state[CURR].j;
	std::uint8_t * s = this->_state[CURR].s;
	std::uint8_t tmp;

	i = (i + 1) & 0xFF;
	j = (j + s[i]) & 0xFF;
	tmp = s[i];
	s[i] = this->_state[CURR].s[j];
	s[j] = tmp;
	return s[(s[i] + s[j]) & 0xFF];
}

//------------------------------------------------------------------------------
void IRARC4::skip(int n) {

	for (; n > 0; n--) {
		this->next();
	}
}

//------------------------------------------------------------------------------
void IRARC4::apply(void * buff, std::uint64_t size) {
	std::uint8_t * p;
	std::uint8_t * pEnd;

	p = (std::uint8_t *)buff;
	pEnd = p + size;
	for( ; p != pEnd; p++) {
		*p = (*p ^ this->next());
	}
}

//==============================================================================
// class IRARC4Random
//------------------------------------------------------------------------------
IRARC4Random::IRARC4Random(): _arc4() {
	this->setSeed(std::time(nullptr));
}

//------------------------------------------------------------------------------
void IRARC4Random::setSeed(std::uint64_t seed) {
	std::uint8_t tmp[8];
	IRUtils::int2BE(seed, tmp);
	this->setSeed(tmp, sizeof(tmp));
}

//------------------------------------------------------------------------------
void IRARC4Random::setSeed(const void * seed, std::uint64_t seedSize) {
	this->_arc4.setKey(seed, seedSize);
}

//------------------------------------------------------------------------------
void IRARC4Random::nextBytes(void * out, std::uint64_t outSize) {
	std::uint8_t * p = (std::uint8_t *)out;
	std::uint8_t * pEnd = p + outSize;

	for ( ; p != pEnd; p++) {
		*p = this->_arc4.next();
	}
}

//------------------------------------------------------------------------------
