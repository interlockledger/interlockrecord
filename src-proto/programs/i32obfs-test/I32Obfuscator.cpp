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
#include "I32Obfuscator.h"

//------------------------------------------------------------------------------
// class I32Obfuscator
//------------------------------------------------------------------------------
I32Obfuscator::I32Obfuscator() {
}

//------------------------------------------------------------------------------
I32Obfuscator::~I32Obfuscator() {
}

//------------------------------------------------------------------------------
std::uint32_t I32Obfuscator::obfuscate(std::uint32_t v) const {
	return v;
}

//------------------------------------------------------------------------------
std::uint32_t I32Obfuscator::deobfuscate(std::uint32_t v) const {
	return v;
}

//------------------------------------------------------------------------------
// Class I32FeistelObfuscator
//------------------------------------------------------------------------------
I32FeistelObfuscator::I32FeistelObfuscator(std::uint32_t key) {
	this->genSubKeys(key);
}

//------------------------------------------------------------------------------
I32FeistelObfuscator::~I32FeistelObfuscator() {
}

//------------------------------------------------------------------------------
void I32FeistelObfuscator::genSubKeys(std::uint32_t key) {
	
	// This is a subkey expansion based on the Linear Congruential Generator
	// suggested by Numerical Recipes by Press, W. H. et al.
	this->subKeys[0] = key;
	for (int i = 1; i < I32FeistelObfuscator::ROUNDS; i++) {
		this->subKeys[i] = (this->subKeys[i - 1] * 1664525) + 1013904223;
	}		
}

//------------------------------------------------------------------------------
std::uint32_t I32FeistelObfuscator::f(std::uint32_t subKey, std::uint32_t r) const {

	return (((subKey + r) * 1664525) + 1013904223) & 0xFFFF;
}

//------------------------------------------------------------------------------
std::uint32_t I32FeistelObfuscator::obfuscate(std::uint32_t v) const {
	std::uint32_t l;
	std::uint32_t r;
	std::uint32_t t;
	
	l = (v >> 16) & 0xFFFF;
	r = v & 0xFFFF;
	for (int i = 0; i < I32FeistelObfuscator::ROUNDS; i++) {
		t = r;
		r = l ^ this->f(this->subKeys[i], r);
		l = t;
	}
	return (r << 16) | l;
}

//------------------------------------------------------------------------------
std::uint32_t I32FeistelObfuscator::deobfuscate(std::uint32_t v) const {
	std::uint32_t l;
	std::uint32_t r;
	std::uint32_t t;
	
	l = (v >> 16) & 0xFFFF;
	r = v & 0xFFFF;
	for (int i = I32FeistelObfuscator::ROUNDS - 1; i >= 0; i--) {
		t = r;
		r = l ^ this->f(this->subKeys[i], r);
		l = t;
	}
	return (r << 16) | l;
}

//------------------------------------------------------------------------------

