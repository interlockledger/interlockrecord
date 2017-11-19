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
	/**
	 * Creates a new instance of this class. It wraps the constant byte array buff. The
	 * resulting instance will be read-only.
	 *
	 * @param[in] buffSize The size of the buffer.
	 * @param[in] buff The buffer to be wrapped.
	 * @note The buffer pointed by buff will be used directly so it must exist
	 * during the lifetime of this instance. Furthermore, this buffer will not
	 * be disposed by this instance.
	 */
	IRBuffer(std::uint64_t buffSize, const void * buff);

	/**
	 * Creates a new instance of this class.
	 *
	 * @param[in] reserved The initial reserved size.
	 * @param[in] secure If true, all memory allocations will be treated as secure.
	 * @param[in] inc The size of the increment.
	 */
	IRBuffer(std::uint64_t reserved, bool secure = false, std::uint64_t inc = 16);

	/**
	 * Disposes this instance and releases all associated resources.
	 */
	virtual ~IRBuffer();

	/**
	 * Returns the size of the data stored in this buffer.
	 *
	 * @return the size in bytes.
	 */
	std::uint64_t size() const {
		return _size;
	}

	/**
	 * Returns the position used by all read/write operations.
	 *
	 * @return the size in bytes.
	 */
	std::uint64_t position() const {
		return _position;
	}

	/**
	 * Return the number of bytes still available to be read from this
	 * buffer.
	 *
	 * @return The number of available bytes.
	 */
	std::uint64_t available() const {
		return size() - position();
	}

	/**
	 * Returns a writeable pointer to the buffer.
	 *
	 * @return The pointer to the buffer.
	 * @note Never cache this value outside this class because
	 * resize operations may lead to changes in this value.
	 */
	std::uint8_t * buffer() {
		return this->_buff;
	}

	/**
	 * Returns a read-only pointer to the buffer.
	 *
	 * @return The pointer to the buffer.
	 * @note Never cache this value outside this class because
	 * resize operations may lead to changes in this value.
	 */
	const std::uint8_t * buffer() const {
		return this->_robuff;
	}

	/**
	 * Returns the total size of the buffer.
	 *
	 * @return The total size of the buffer.
	 */
	std::uint64_t getBufferSize() const {
		return this->_buffSize;
	}

	/**
	 * Checks if this instace is read-only.
	 *
	 * @return true if the instance is read-only or false otherwise.
	 */
	bool isReadOnly() const {
		return (this->_buff == nullptr) && (this->_robuff);
	}

	/**
	 * Sets the size of the data inside this buffer. The internal
	 * buffer will be resized as required in order to accomodate the new
	 * size.
	 *
	 * @param[in] size The new data size.
	 * @return true on success or false otherwise.
	 * @note This method will never shrink the internal buffer.
	 */
	bool setSize(std::uint64_t size);

	/**
	 * Sets the position of read/write operations.
	 *
	 * @param[in] position The new position.
	 * @note This operation will never pass the end of data.
	 */
	void setPosition(std::uint64_t position);

	/**
	 * Moves the read/write position forward a given number of bytes.
	 *
	 * @param[in] delta The number of bytes to skip.
	 * @return The number of skipped bytes.
	 * @note This operation will never pass the end of data.
	 */
	std::uint64_t skip(std::int64_t delta);

	/**
	 * Moves the read/write position backward a given number of bytes.
	 *
	 * @param[in] delta The number of bytes to skip.
	 * @return The number of skipped bytes.
	 */
	std::uint64_t rewind(std::int64_t delta);

	/**
	 * Prepares the internal buffer to grow up to a certain number of bytes.
	 * The data size will not be modfied by this operation.
	 *
	 * @param[in] newSize The new reserved size.
	 * @return true for success or false otherwise.
	 * @note This method will never shrink the internal buffer.
	 */
	bool reserve(std::uint64_t newSize);

	/**
	 * Writes a certain number of bytes into the buffer.
	 *
	 * @param[in] buffSize Size of the buffer.
	 * @param[in] buff The buffer.
	 * @return true on success or false otherwise.
	 */
	bool write(std::uint64_t buffSize, const void * buff);

	/**
	 * Reads bytes.
	 *
	 * @param[in] buffSize The number of bytes to read.
	 * @param[out] buff The buffer that will hold the bytes read.
	 * @return The actual number of bytes read.
	 */
	std::uint64_t read(std::uint64_t buffSize, void * buff);
};

} //namespace ircommon

#endif /* INCLUDE_IRCOMMON_IRBUFFER_H_ */
