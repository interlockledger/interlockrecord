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
#ifndef _IRECORDCORE_IRTYPES_H_
#define _IRECORDCORE_IRTYPES_H_

#include <ircommon/irbuffer.h>

namespace irecordcore {

/**
 * This class implements a IRBuffer that is associated with a given type
 * (an unsigned 16-bit integer).
 *
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
 * @since 2018.02.17
 */
class IRTypedRaw: public ircommon::IRBuffer {
private:
	/**
	 * The type.
	 */
	std::uint16_t _type;
public:
	/**
	 * Creates a new instance of this class.
	 *
	 * @param[in] reserved The initial reserved size.
	 * @param[in] secure If true, all memory allocations will be treated as secure.
	 * @param[in] inc The size of the increment. Must be a value larger than 0.
	 * @exception std::invalid_argument If inc is 0.
	 */
	IRTypedRaw(std::uint64_t reserve, bool secure = false,
				std::uint64_t inc = DEFAULT_INCREMENT):
			IRBuffer(reserve, secure, inc), _type(0){
	}

	/**
	 * Disposes this instance and releases all associated resources.
	 */
	virtual ~IRTypedRaw() = default;

	/**
	 * Sets the type.
	 *
	 * @param[in] v The type.
	 */
	void setType(std::uint16_t v) {
		this->_type = v;
	}

	/**
	 * Returns the associated type.
	 *
	 * @return The type.
	 */
	std::uint16_t type() const {
		return this->_type;
	}

	/**
	 * Copies another instance into this instance.
	 *
	 * @param[in] other The other instance.
	 * @return true for success or false otherwise.
	 */
	bool copy(const IRTypedRaw & other);

	/**
	 * Copies another instance into this instance.
	 *
	 * @param[in] other The other instance.
	 * @return true for success or false otherwise.
	 */
	bool copy(const IRTypedRaw * other) {
		return this->copy(*other);
	}

	/**
	 * Verifies if this instance contains the same value of another instance.
	 *
	 * @param[in] other The other instance.
	 * @return true it their contents are the same or false otherwise.
	 * @note The current read/write position ignored.
	 */
	bool equals(const IRTypedRaw & other) const;

	/**
	 * Verifies if this instance contains the same value of another instance.
	 *
	 * @param[in] other The other instance.
	 * @return true it their contents are the same or false otherwise.
	 * @note The current read/write position ignored.
	 */
	bool equals(const IRTypedRaw * other) const {
		return this->equals(*other);
	}
};

} // namespace irecordcore

#endif /* _IRECORDCORE_IRTYPES_H_ */

