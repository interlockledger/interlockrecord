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
#ifndef INCLUDE_IRCOMMON_IRBUFFER_H_
#define INCLUDE_IRCOMMON_IRBUFFER_H_

#include <cstdint>

namespace ircommon {

// TODO This class requires tests

/**
 * This class implements a simple memory buffer. It can be used as either a
 * shell around an existing buffer (read-olnly) or as a dynamic memory buffer.
 *
 * @since 2017.10.09
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
 */
class IRBuffer {
protected:
	std::uint8_t * _buff;

	const std::uint8_t * _robuff;

	std::uint64_t _size;

	std::uint64_t _buffSize;

	std::uint64_t _position;

	std::uint64_t _inc;

	bool _secure;

	void dispose(std::uint64_t buffSize, std::uint8_t * buff);
public:
	IRBuffer(std::uint64_t buffSize, const void * buff);

	IRBuffer(std::uint64_t initialSize, bool secure = false, std::uint64_t inc = 512);

	virtual ~IRBuffer();

	std::uint64_t size() const {
		return _size;
	}

	std::uint64_t position() const {
		return _position;
	}

	std::uint64_t available() const {
		return size() - position();
	}

	std::uint8_t * buffer() {
		return this->_buff;
	}

	const std::uint8_t * buffer() const {
		return this->_robuff;
	}

	bool isReadOnly() const {
		return (this->_buff == nullptr) && (this->_robuff);
	}

	bool setSize(std::uint64_t size);

	void setPosition(std::uint64_t position);

	std::uint64_t skip(std::int64_t delta);

	std::uint64_t rewind(std::int64_t delta);

	bool reserve(std::uint64_t newSize);

	bool write(std::uint64_t buffSize, const void * buff);

	std::uint64_t read(std::uint64_t buffSize, void * buff);
};

} //namespace ircommon

#endif /* INCLUDE_IRCOMMON_IRBUFFER_H_ */
