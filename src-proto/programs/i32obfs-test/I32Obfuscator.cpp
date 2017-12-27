
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

