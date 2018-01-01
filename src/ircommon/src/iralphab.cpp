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
#include <ircommon/iralphab.h>
#include <cstring>
#include <cctype>

// This implementation is loosely based on the original code from
// https://github.com/opencs/ocsbincodec-c

using namespace ircommon;

//==============================================================================
// Class IRAlphabet
//------------------------------------------------------------------------------
IRAlphabet::IRAlphabet(int size):_size(size){
}

//==============================================================================
// Class IRGenericAlphabet
//------------------------------------------------------------------------------
IRGenericAlphabet::IRGenericAlphabet(const char * map, int mapSize):
		IRAlphabet(mapSize){
	this->_map = new char[mapSize];
	std::memcpy(this->_map, map, mapSize);
}

//------------------------------------------------------------------------------
IRGenericAlphabet::~IRGenericAlphabet() {
	if (this->_map) {
		delete [] this->_map;
	}
}

//------------------------------------------------------------------------------
int IRGenericAlphabet::getValue(int c) const {

	for (int i = 0; i < this->size(); i++) {
		if (this->_map[i] == c) {
			return i;
		}
	}
	return -1;
}

//------------------------------------------------------------------------------
int IRGenericAlphabet::getChar(int v) const {
	return this->_map[v % this->size()];
}

//==============================================================================
// Class IRBinaryAlphabet
//------------------------------------------------------------------------------
IRBinaryAlphabet::IRBinaryAlphabet(char f, char t): IRAlphabet(2) {
	this->_map[0] = f;
	this->_map[1] = t;
}

//------------------------------------------------------------------------------
IRBinaryAlphabet::~IRBinaryAlphabet() {
}

//------------------------------------------------------------------------------
int IRBinaryAlphabet::getValue(int c) const {

	if (this->_map[0] == c) {
		return 0;
	} else if (this->_map[1] == c) {
		return 1;
	} else {
		return -1;
	}
}

//------------------------------------------------------------------------------
int IRBinaryAlphabet::getChar(int v) const {

	return this->_map[v & 0x1];
}

//==============================================================================
// Class IRHexAlphabet
//------------------------------------------------------------------------------
static const char * IRHexAlphabet_ALPHABET_U = "0123456789ABCDEF";
static const char * IRHexAlphabet_ALPHABET_L = "0123456789abcdef";

IRHexAlphabet::IRHexAlphabet(bool lower): IRAlphabet(16) {
	if (lower) {
		this->_map = IRHexAlphabet_ALPHABET_L;
	} else {
		this->_map = IRHexAlphabet_ALPHABET_U;
	}
}

//------------------------------------------------------------------------------
IRHexAlphabet::~IRHexAlphabet(){
}

//------------------------------------------------------------------------------
int IRHexAlphabet::getValue(int c) const {

	if ((c >= '0') && (c <= '9')) {
		return c - '0';
	} else if ((c >= 'A') && (c <= 'F')) {
		return c - 'A' + 10;
	} else if ((c >= 'a') && (c <= 'f')) {
		return c - 'a' + 10;
	} else {
		return -1;
	}
}

//------------------------------------------------------------------------------
int IRHexAlphabet::getChar(int v) const {

	return this->_map[v & 0xF];
}

//==============================================================================
// Class IRBase32Alphabet
//------------------------------------------------------------------------------
static const char * IRBase32Alphabet_ALPHABET =
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ234567"
		"abcdefghijklmnopqrstuvwxyz234567";

static const char * IRBase32Alphabet_ALPHABET_HEX =
		"0123456789ABCDEFGHIJKLMNOPQRSTUV"
		"0123456789abcdefghijklmnopqrstuv";

//------------------------------------------------------------------------------
IRBase32Alphabet::IRBase32Alphabet(bool lower, bool extendedHex): IRAlphabet(32),
		_extendedHex(extendedHex) {
	int base;

	if (lower) {
		base = 32;
	} else {
		base = 0;
	}
	if (extendedHex) {
		this->_map = IRBase32Alphabet_ALPHABET_HEX + base;
	} else {
		this->_map = IRBase32Alphabet_ALPHABET + base;
	}
}

//------------------------------------------------------------------------------
IRBase32Alphabet::~IRBase32Alphabet() {
}

//------------------------------------------------------------------------------
int IRBase32Alphabet::getValue(int c) const {

	// TODO This code is not ready to be compiled on EBCDIC encoding.
	if (this->_extendedHex) {
		if ((c >= '0') && (c <= '9')) {
			return c - '0';
		} else if ((c >= 'A') && (c <= 'V')) {
			return c - 'A' + 10;
		} else if ((c >= 'a') && (c <= 'v')) {
			return c - 'a' + 10;
		} else {
			return -1;
		}
	} else {
		if ((c >= 'A') && (c <= 'Z')) {
			return c - 'A';
		} else if ((c >= 'a') && (c <= 'z')) {
			return c - 'a';
		} else if ((c >= '2') && (c <= '7')) {
			return c - '2' + 26;
		}else {
			return -1;
		}
	}
}

//------------------------------------------------------------------------------
int IRBase32Alphabet::getChar(int v) const {
	return _map[v & 0x1F];
}

//==============================================================================
// Class IRBase64Alphabet
//------------------------------------------------------------------------------
static const char * IRBase64Alphabet_ALPHABET =
		"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

//------------------------------------------------------------------------------
IRBase64Alphabet::IRBase64Alphabet(bool url):
		IRBase64Alphabet(url?'-':'+', url?'_':'/') {
}

//------------------------------------------------------------------------------
IRBase64Alphabet::IRBase64Alphabet(int s62, int s63) : IRAlphabet(64) {
	std::memcpy(this->_map, IRBase64Alphabet_ALPHABET, 62);
	this->_map[62] = s62;
	this->_map[63] = s63;
}

//------------------------------------------------------------------------------
IRBase64Alphabet::~IRBase64Alphabet(){
}

//------------------------------------------------------------------------------
int IRBase64Alphabet::getValue(int c) const {

	if ((c >= 'A') && (c <= 'Z')) {
		return c - 'A';
	} else if ((c >= 'a') && (c <= 'z')) {
		return c - 'a' + 26;
	} else if ((c >= '0') && (c <= '9')) {
		return c - '0' + 26 + 26;
	} else if (c == this->_map[62]) {
		return 62;
	} else if (c == this->_map[63]) {
		return 63;
	} else {
		return -1;
	}
}

//------------------------------------------------------------------------------
int IRBase64Alphabet::getChar(int v) const {
	return this->_map[v & 0x3F];
}
//------------------------------------------------------------------------------
