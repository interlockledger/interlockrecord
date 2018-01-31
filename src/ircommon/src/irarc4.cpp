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
#include <ircommon/irarc4.h>
#include <ircommon/irutils.h>
#include <cstring>
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

//------------------------------------------------------------------------------
