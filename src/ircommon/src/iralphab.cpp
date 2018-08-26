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
#include <ircommon/iralphab.h>
#include <cstring>
#include <cctype>

// This implementation is loosely based on the original code from
// https://github.com/opencs/ocsbincodec-c

using namespace ircommon;
using namespace ircommon::codec;

//==============================================================================
// Class IRAlphabet
//------------------------------------------------------------------------------
IRAlphabet::IRAlphabet(int size):_size(size){

	if (size < 2) {
		throw std::invalid_argument("Invalid size.");
	}
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

	if (t == f) {
		throw std::invalid_argument("f cannot be equal to t.");
	}
	this->_map[0] = f;
	this->_map[1] = t;
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
