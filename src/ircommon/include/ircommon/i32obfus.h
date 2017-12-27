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
#ifndef __ILCOMMON_I32OBFUS__
#define __ILCOMMON_I32OBFUS__

#include <cstdint>

namespace ircommon {

/**
 * This class is the base class for all I32 obfuscators. The obfuscation
 * algorithm must map one value into another using a bijective function.
 *
 *
 * <p>The default implementation does nothing. In other words, it maps
 * the value to itself.</p>
 *
 * @since 2017.12.27
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
 */
class I32Obfuscator {
public:
	/**
	 * Creates a new instance of this class.
	 */
	I32Obfuscator();

	/**
	 * Disposes this instance and releases all associated resources.
	 */
	virtual ~I32Obfuscator();

	/**
	 * Obfuscates a 32-bit unsigned integer.
	 *
	 * @param[in] v The value to be obfuscated.
	 * @return The obfuscated value.
	 * @note This method must be thread safe.
	 */
	virtual std::uint32_t obfuscate(std::uint32_t v) const;

	/**
	 * Deobfuscates a 32-bit unsigned integer.
	 *
	 * @param[in] v The value to be deobfuscated.
	 * @return The deobfuscated value.
	 * @note This method must be thread safe.
	 */
	virtual std::uint32_t deobfuscate(std::uint32_t v) const;
};

/**
 * This class implements a I32Obfuscator that uses a very simple
 * Feistel network to obfuscate the value.
 *
 * <p>It is important to notice that this algorithm is not
 * supposed to be used to protect/unprotect data for long term
 * storage. The mapping may change from instance to instance and
 * from version to version of this class.</p>
 *
 * @since 2017.12.27
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
 */
class I32FeistelObfuscator: public I32Obfuscator {
private:
	enum {
		/**
		 * Number of Feistel Network rounds.
		 */
		ROUNDS = 16
	};

	/**
	 * Subkeys.
	 */
	std::uint32_t subKeys[ROUNDS];

	/**
	 * Generates the subkeys.
	 *
	 * @param[in] key The obfuscation key.
	 */
	void genSubKeys(std::uint32_t key);

	/**
	 * The inner Feistel function.
	 *
	 * @param[in] subKey The subkey.
	 * @param[in] r The r value.
	 * @return a 16-bit value.
	 */
	std::uint32_t f(std::uint32_t subKey, std::uint32_t r) const;
public:
	/**
	 * Creates a new instance of this class.
	 *
	 * @param[in] key The obfuscation key.
	 */
	I32FeistelObfuscator(std::uint32_t key = 0);

	/**
	 * Disposes this instance and releases all assoicated resources.
	 */
	virtual ~I32FeistelObfuscator();

	/**
	 * @copydoc
	 */
	virtual std::uint32_t obfuscate(std::uint32_t v) const;

	/**
	 * @copydoc
	 */
	virtual std::uint32_t deobfuscate(std::uint32_t v) const;
};

} // namespace ircommon

#endif //__ILCOMMON_I32OBFUS__

