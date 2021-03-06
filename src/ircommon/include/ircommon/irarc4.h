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
#ifndef _IRCOMMON_IRARC4_H_
#define _IRCOMMON_IRARC4_H_

#include <cstdint>
#include <ircommon/irrandom.h>

namespace ircommon {
namespace crypto {

/**
 * This class implements the ARC4 algorithm with a few special features.
 *
 * <p>Although not safe to long term encryption it can be efficiently used to
 * obfuscate information inside the memory of the process.</p>
 *
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
 * @since 2018.01.30
 * @warning Do not use this implementation to store long term information
 * because RC4 is no longer safe for those kind of usage.
 */
class IRARC4 {
private:
	enum {
		CURR = 0,
		SAVED = 1
	};
	typedef struct {
		std::uint8_t s[256];
		int i;
		int j;
	} State;
	State _state[2];
public:
	/**
	 * Creates a new instance of this class. This instance will not be
	 * initialized.
	 */
	IRARC4();

	/**
	 * Creates a new instance of this class.
	 *
	 * @param[in] key The key.
	 * @param[in] keySize The size of the key.
	 */
	IRARC4(const void * key, int keySize);

	/**
	 * Disposes this instance and releases all associated resources.
	 */
	virtual ~IRARC4();

	/**
	 * Sets a new key.
	 *
	 * @param[in] key The key.
	 * @param[in] keySize The size of the key.
	 */
	void setKey(const void * key, int keySize);

	/**
	 * Remixes a new key into the current state. It will apply the original key
	 * mix algorithm but using the current state instead of the standard initial
	 * state.
	 *
	 * @param[in] key The key.
	 * @param[in] keySize The size of the key.
	 */
	void remixKey(const void * key, int keySize);

	/**
	 * Saves the current state.
	 *
	 * @return true on success or false otherwise.
	 * @note Only one state can be saved. This means that each call to this
	 * method will overwrite the previous saved state.
	 */
	void save();

	/**
	 * Loads the saved state.
	 *
	 * @return true on success or false otherwise.
	 * @note Loading a state without a previous call to save will lead to an
	 * undefined behavior.
	 */
	void load();

	/**
	 * Returns the next value of the key stream.
	 *
	 * @return The next key stream byte.
	 */
	std::uint8_t next();

	/**
	 * Skips a given number of entries of the key stream.
	 *
	 * @param[in] n The number of entries to be skipped.
	 */
	void skip(int n);

	/**
	 * Applies the key stream to the specified buffer.
	 *
	 * @param[in,out] buff The buffer.
	 * @param[in] size The size of buff in bytes.
	 * @since 2018.01.31
	 */
	void apply(void * buff, std::uint64_t size);
};

/**
 * This class implements a random generator based on the ARC4 stream cipher.
 *
 * @since 2018.03.15
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
 */
class IRARC4Random: public ircommon::IRRandom {
private:
	IRARC4 _arc4;
public:
	IRARC4Random();

	virtual ~IRARC4Random() = default;

	virtual void setSeed(std::uint64_t seed);

	virtual void setSeed(const void * seed, std::uint64_t seedSize);

	virtual void nextBytes(void * out, std::uint64_t outSize);
};

} // namespace crypto
} // namespace ircommon

#endif /* _IRCOMMON_IRARC4_H_ */
