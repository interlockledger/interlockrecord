

#ifndef __I32Obfuscator_H__
#define __I32Obfuscator_H__

#include <cstdint>

class I32Obfuscator {
public:
	I32Obfuscator();

	virtual ~I32Obfuscator();

	virtual std::uint32_t obfuscate(std::uint32_t v) const;

	virtual std::uint32_t deobfuscate(std::uint32_t v) const;
};

class I32FeistelObfuscator: public I32Obfuscator {
private:
	enum {
		ROUNDS = 16
	};

	std::uint32_t subKeys[ROUNDS];

	void genSubKeys(std::uint32_t key);

	std::uint32_t f(std::uint32_t subKey, std::uint32_t r) const;
public:
	I32FeistelObfuscator(std::uint32_t key = 0);

	virtual ~I32FeistelObfuscator();

	virtual std::uint32_t obfuscate(std::uint32_t v) const;

	virtual std::uint32_t deobfuscate(std::uint32_t v) const;
};

#endif //__I32Obfuscator_H__

