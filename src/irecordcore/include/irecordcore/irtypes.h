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

