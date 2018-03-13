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
#ifndef _IRCOMMON_IRIDGEN_H_
#define _IRCOMMON_IRIDGEN_H_

#include <ircommon/i32obfus.h>

namespace ircommon {

/**
 * This class implements an ID generator. It generates pseudo random sequence
 * of integers from 1 to (2^32)-1. It also guarantees that a generated ID will
 * not repeat numbers until at least (2^32)-1 executions.
 *
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
 * @since 2017.01.11
 * @note This class is not thread safe.
 */
class IRIDGenerator{
private:
	/**
	 * The current event counter.
	 */
	std::uint32_t _counter;
	/**
	 * The obfuscator of the counter.
	 */
	ircommon::crypto::I32FeistelObfuscator _obfuscator;
public:
	/**
	 * Creates a new instance of this class.
	 *
	 * @param[in] seed The generator seed.
	 */
	IRIDGenerator(std::uint32_t seed = 0): _counter(0), _obfuscator(seed){
	}

	/**
	 * Disposes this instance and releases all associated resources.
	 */
	~IRIDGenerator() = default;

	/**
	 * Returns the current value of the internal counter.
	 *
	 * @return The value of the internal counter.
	 * @since 2017.01.12
	 */
	std::uint32_t getCounter() const {
		return this->_counter;
	}

	/**
	 * Sets the value of the internal counter.
	 *
	 * @param[in] v The new value of the counter.
	 * @since 2017.01.12
	 */
	void setCounter(std::uint32_t v) {
		this->_counter = v;
	}

	/**
	 * Returns the next id.
	 *
	 * @return The next id in the sequence. This ID is guaranteed to be greater
	 * than zero.
	 */
	inline std::uint32_t next() {
		std::uint32_t id;

		do {
			id = this->_obfuscator.obfuscate(this->_counter);
			this->_counter++;
		} while (id == 0);
		return id;
	}
};

} // namespace ircommon

#endif /* _IRCOMMON_IRIDGEN_H_ */
