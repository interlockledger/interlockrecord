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
#ifndef _IRCOMMON_IRARC4_H_
#define _IRCOMMON_IRARC4_H_

#include <cstdint>

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
};

} // namespace crypto
} // namespace ircommon

#endif /* _IRCOMMON_IRARC4_H_ */
