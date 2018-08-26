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
#ifndef __ILCOMMON_I32OBFUS__
#define __ILCOMMON_I32OBFUS__

#include <cstdint>

namespace ircommon {
namespace crypto {

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

} //namespace crypto
} // namespace ircommon

#endif //__ILCOMMON_I32OBFUS__

