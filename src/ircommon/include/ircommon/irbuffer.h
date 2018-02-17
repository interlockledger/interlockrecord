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
 * @note This class is not thread safe.
 */
class IRBuffer {
protected:
	/**
	 * The read/write buffer.
	 */
	std::uint8_t * _buff;

	/**
	 * Pointer to the read only buffer.
	 */
	const std::uint8_t * _robuff;

	/**
	 * Size of the data. It is always smaller than the actual size of the
	 * buffer.
	 */
	std::uint64_t _size;

	/**
	 * Actual size of the buffer.
	 */
	std::uint64_t _buffSize;

	/**
	 * Current read/write position.
	 */
	std::uint64_t _position;

	/**
	 * Size of the increment.
	 */
	std::uint64_t _inc;

	/**
	 * Flag that indicates if this buffer must be considered critical or not.
	 */
	bool _secure;

	/**
	 * Disposes the buffer.
	 *
	 * @param[in] buff The buffer to be disposed.
	 * @param[in] buffSize The size of the buffer.
	 */
	void dispose(std::uint8_t * buff, std::uint64_t buffSize);
public:
	enum {
		/**
		 * Default increment of this buffer.
		 * @since 2018.01.23
		 */
		DEFAULT_INCREMENT = 16
	};

	/**
	 * Creates a new instance of this class. It wraps the constant byte array
	 * pointed by buff. The resulting instance will be read-only.
	 *
	 * @param[in] buff The buffer to be wrapped.
	 * @param[in] buffSize The size of the buffer.
	 * @note The buffer pointed by buff will be used directly so it must exist
	 * during the lifetime of this instance. Furthermore, this buffer will not
	 * be disposed by this instance.
	 */
	IRBuffer(const void * buff, std::uint64_t buffSize);

	/**
	 * Creates a new instance of this class.
	 *
	 * @param[in] reserved The initial reserved size.
	 * @param[in] secure If true, all memory allocations will be treated as secure.
	 * @param[in] inc The size of the increment. Must be a value larger than 0.
	 * @exception std::invalid_argument If inc is 0.
	 */
	IRBuffer(std::uint64_t reserved = 0, bool secure = false,
			std::uint64_t inc = DEFAULT_INCREMENT);

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
	 * @return The pointer to the buffer or NULL if this instance
	 * is read-only.
	 * @warning Never cache this value outside this class because
	 * resize operations may lead to changes in this value.
	 */
	std::uint8_t * buffer() {
		return this->_buff;
	}

	/**
	 * Returns a read-only pointer to the buffer. On writable instances
	 * this value is always equals to IRBuffer::buffer().
	 *
	 * @return The read-only pointer to the buffer.
	 * @warning Never cache this value outside this class because
	 * resize operations may lead to changes in this value.
	 * @note On read-only instances, it will always point to the same
	 * buffer used in the constructor.
	 */
	const std::uint8_t * roBuffer() const {
		if (this->readOnly()) {
			return this->_robuff;
		} else {
			return this->_buff;
		}
	}

	/**
	 * Returns the total size of the buffer.
	 *
	 * @return The total size of the buffer.
	 */
	std::uint64_t bufferSize() const {
		return this->_buffSize;
	}

	/**
	 * Checks if this instace is read-only.
	 *
	 * @return true if the instance is read-only or false otherwise.
	 */
	bool readOnly() const {
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
	 * @param[in] buff The buffer.
	 * @param[in] buffSize Size of the buffer.
	 * @return true on success or false otherwise.
	 */
	bool write(const void * buff, std::uint64_t buffSize);

	/**
	 * Reads bytes.
	 *
	 * @param[out] buff The buffer that will hold the bytes read.
	 * @param[in] buffSize The number of bytes to read.
	 * @return The actual number of bytes read.
	 */
	std::uint64_t read(void * buff, std::uint64_t buffSize);

	/**
	 * Checks if this instance is secure or not.
	 *
	 * @return true if the instance is secure or false otherwise.
	 */
	bool secure() const {
		return this->_secure;
	}

	/**
	 * Sets the contents of this buffer. On success, the contents of
	 * buff will be copied into the internal buffer and the position will
	 * be moved to the begining of the data.
	 *
	 * @param[in] buff The data to be copied.
	 * @param[in] buffSize The number of bytes in buff.
	 * @return true on success or false otherwise.
	 * @note This method does not work in read-only buffers.
	 * @since 2018.01.16
	 */
	bool set(const void * buff, std::uint64_t buffSize);

	/**
	 * Moves the read/write position to the begining of the data.
	 * It has the same effect of setPosition(0).
	 * @since 2018.01.16
	 */
	void beginning(){
		this->_position = 0;
	}

	/**
	 * Moves the read/write position to the end of the data.
	 * It has the same effect of setPosition(size()).
	 * @since 2018.01.16
	 */
	void ending(){
		this->_position = this->_size;
	}

	/**
	 * This method reduces the buffer to the minimum size required
	 * to hold the actual data.
	 *
	 * <p>On success, the buffer size will be reduced to the same
	 * size of the data. It is important to notice that the minimum
	 * buffer size will always be the size of the increment.</p>
	 *
	 * @return true on success or false otherwise.
	 * @note On failure, the instance will remain unchanged.
	 * @note This method does not work in read-only buffers.
	 * @since 2018.01.16
	 */
	bool shrink();

	/**
	 * Writes an ILInt64 value into the buffer.
	 *
	 * @param[in] v The value to be written.
	 * @return true for success or false otherwise.
	 * @since 2018.01.20
	 */
	bool writeILInt(std::uint64_t v);

	/**
	 * Reads an ILInt64 value from the buffer.
	 *
	 * @param[in] v The value read.
	 * @return true for success or false otherwise.
	 * @since 2018.01.20
	 */
	bool readILInt(std::uint64_t & v);

	/**
	 * Returns a read-only pointer to the buffer at the current position.
	 *
	 * @return The pointer in the buffer at the current position.
	 * @since 2018.01.22
	 */
	const std::uint8_t * roPosBuffer() const {
		return this->roBuffer() + this->position();
	}

	/**
	 * Returns a read/write pointer to the buffer at the current position.
	 *
	 * @return The pointer in the buffer at the current position.
	 * @since 2018.01.22
	 */
	std::uint8_t * posBuffer() {
		if (this->readOnly()) {
			return nullptr;
		} else {
			return this->buffer() + this->position();
		}
	}

	/**
	 * Writes a single byte to the buffer.
	 *
	 * @param[in] v The byte value.
	 * @return true for success or false otherwise.
	 * @since 2018.01.22
	 */
	bool write(int v);

	/**
	 * Reads a single byte from the buffer.
	 *
	 * @return The byte read or -1 if no more bytes is available.
	 * @since 2018.01.22
	 */
	int read();

	/**
	 * The increment step of this instance.
	 *
	 * @return The size of the increment.
	 * @since 2018.01.23
	 */
	std::uint64_t increment() const {
		return this->_inc;
	}

	/**
	 * Writes an unsigned 8-bit integer using the big endian encoding.
	 *
	 * @param[in] v The value.
	 * @return true for success or false otherwise.
	 * @since 2018.01.26
	 */
	bool writeInt(std::uint8_t v);

	/**
	 * Writes a signed 8-bit integer using the big endian encoding.
	 *
	 * @param[in] v The value.
	 * @return true for success or false otherwise.
	 * @since 2018.01.26
	 */
	bool writeInt(std::int8_t v) {
		return this->writeInt(std::uint8_t(v));
	}

	/**
	 * Writes an unsigned 16-bit integer using the big endian encoding.
	 *
	 * @param[in] v The value.
	 * @return true for success or false otherwise.
	 * @since 2018.01.26
	 */
	bool writeInt(std::uint16_t v);

	/**
	 * Writes a signed 16-bit integer using the big endian encoding.
	 *
	 * @param[in] v The value.
	 * @return true for success or false otherwise.
	 * @since 2018.01.26
	 */
	bool writeInt(std::int16_t v) {
		return writeInt(std::uint16_t(v));
	}

	/**
	 * Writes an unsigned 32-bit integer using the big endian encoding.
	 *
	 * @param[in] v The value.
	 * @return true for success or false otherwise.
	 * @since 2018.01.26
	 */
	bool writeInt(std::uint32_t v);

	/**
	 * Writes a signed 32-bit integer using the big endian encoding.
	 *
	 * @param[in] v The value.
	 * @return true for success or false otherwise.
	 * @since 2018.01.26
	 */
	bool writeInt(std::int32_t v) {
		return writeInt(std::uint32_t(v));
	}

	/**
	 * Writes an unsigned 8-bit integer using the big endian encoding.
	 *
	 * @param[in] v The value.
	 * @return true for success or false otherwise.
	 * @since 2018.01.26
	 */
	bool writeInt(std::uint64_t v);

	/**
	 * Writes a signed 16-bit integer using the big endian encoding.
	 *
	 * @param[in] v The value.
	 * @return true for success or false otherwise.
	 * @since 2018.01.26
	 */
	bool writeInt(std::int64_t v) {
		return writeInt(std::uint64_t(v));
	}

	/**
	 * Reads a unsigned 8-bit integer using the big endian encoding.
	 *
	 * @param[in] v The value.
	 * @return true for success or false otherwise.
	 * @since 2018.01.26
	 */
	bool readInt(std::uint8_t & v);

	/**
	 * Reads a signed 8-bit integer using the big endian encoding.
	 *
	 * @param[in] v The value.
	 * @return true for success or false otherwise.
	 * @since 2018.01.26
	 */
	bool readInt(std::int8_t & v) {
		return readInt(reinterpret_cast<std::uint8_t&>(v));
	}

	/**
	 * Reads a unsigned 8-bit integer using the big endian encoding.
	 *
	 * @param[in] v The value.
	 * @return true for success or false otherwise.
	 * @since 2018.01.26
	 */
	bool readInt(std::uint16_t & v);

	/**
	 * Reads a signed 16-bit integer using the big endian encoding.
	 *
	 * @param[in] v The value.
	 * @return true for success or false otherwise.
	 * @since 2018.01.26
	 */
	bool readInt(std::int16_t & v) {
		return readInt(reinterpret_cast<std::uint16_t&>(v));
	}

	/**
	 * Reads a unsigned 8-bit integer using the big endian encoding.
	 *
	 * @param[in] v The value.
	 * @return true for success or false otherwise.
	 * @since 2018.01.26
	 */
	bool readInt(std::uint32_t & v);

	/**
	 * Reads a signed 32-bit integer using the big endian encoding.
	 *
	 * @param[in] v The value.
	 * @return true for success or false otherwise.
	 * @since 2018.01.26
	 */
	bool readInt(std::int32_t & v) {
		return readInt(reinterpret_cast<std::uint32_t&>(v));
	}

	/**
	 * Reads a unsigned 8-bit integer using the big endian encoding.
	 *
	 * @param[in] v The value.
	 * @return true for success or false otherwise.
	 * @since 2018.01.26
	 */
	bool readInt(std::uint64_t & v);

	/**
	 * Reads a signed 64-bit integer using the big endian encoding.
	 *
	 * @param[in] v The value.
	 * @return true for success or false otherwise.
	 * @since 2018.01.26
	 */
	bool readInt(std::int64_t & v) {
		return readInt(reinterpret_cast<std::uint64_t&>(v));
	}

	/**
	 * Writes a single precision floating point using IEEE754 in the big endian
	 * encoding.
	 *
	 * @param[in] v The value.
	 * @return true for success or false otherwise.
	 * @since 2018.01.26
	 */
	bool writeFloat(float v);

	/**
	 * Writes a double precision floating point using IEEE754 in the big endian
	 * encoding.
	 *
	 * @param[in] v The value.
	 * @return true for success or false otherwise.
	 * @since 2018.01.26
	 */
	bool writeFloat(double v);

	/**
	 * Reads a single precision floating point  using IEEE754 in the big endian
	 * encoding.
	 *
	 * @param[in] v The value.
	 * @return true for success or false otherwise.
	 * @since 2018.01.26
	 */
	bool readFloat(float & v);

	/**
	 * Reads a double precision floating point  using IEEE754 in the big endian
	 * encoding.
	 *
	 * @param[in] v The value.
	 * @return true for success or false otherwise.
	 * @since 2018.01.26
	 */
	bool readFloat(double & v);

	/**
	 * Copies the contents of another instance into this instance. It will copy
	 * the current data and the current read/write position.
	 *
	 * @param[in] other The other instance.
	 * @return true for success or false otherwise.
	 * @since 2018.02.17
	 */
	bool copy(const IRBuffer * other) {
		return this->copy(*other);
	}

	/**
	 * Copies the contents of another instance into this instance. It will copy
	 * the current data and the current read/write position.
	 *
	 * @param[in] other The other instance.
	 * @return true for success or false otherwise.
	 * @since 2018.02.17
	 */
	bool copy(const IRBuffer & other);
};

} //namespace ircommon

#endif /* INCLUDE_IRCOMMON_IRBUFFER_H_ */
