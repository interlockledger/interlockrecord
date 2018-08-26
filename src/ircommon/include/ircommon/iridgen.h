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
