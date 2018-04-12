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
#ifndef INCLUDE_IRUTILS_IRBUFFER_H_
#define INCLUDE_IRUTILS_IRBUFFER_H_

#include <cstdint>
#include <stdexcept>

namespace ircommon {

namespace IRUtils {

/**
 * Returns the number of bytes to add to a buffer in order to make it
 * a multiple of a given block size.
 *
 * @param[in] buffSize The data size.
 * @param[in] blockSize The block size. Must be a value larger than 0.
 * @return The size of the padding. This value will always be a value between 1 and blockSize.
 * @tparam UINT_TYPE  An unsigned integer type.
 * @since 2017.11.18
 */
template < class UINT_TYPE >
UINT_TYPE getPaddingSize(UINT_TYPE buffSize, UINT_TYPE blockSize) {
	return blockSize - (buffSize % blockSize);
}

/**
 * Returns the new buffer size that makes it a multiple of a given block size. The returned value
 * is guaranteed to be larger than buffSize.
 *
 * @param[in] buffSize The data size.
 * @param[in] blockSize The block size. Must be a value larger than 0.
 * @return The new size of the buffer. It will always be larger than buffSize.
 * @tparam UINT_TYPE  An unsigned integer type.
 * @since 2017.11.18
 */
template < class UINT_TYPE >
UINT_TYPE  getPaddedSize(UINT_TYPE  buffSize, UINT_TYPE  blockSize) {
	return buffSize + getPaddingSize(buffSize, blockSize);
}

/**
 * Returns the new buffer size that makes it a multiple of a given block size. The returned value
 * is guaranteed to be equal or larger than buffSize.
 *
 * @param[in] buffSize The data size.
 * @param[in] blockSize The block size. Must be a value larger than 0.
 * @return The new size of the buffer. It will always be equal or larger than buffSize.
 * @tparam UINT_TYPE  An unsigned integer type.
 * @since 2017.11.18
 */
template < class UINT_TYPE >
UINT_TYPE  getPaddedSizeBestFit(UINT_TYPE  buffSize, UINT_TYPE  blockSize) {
	UINT_TYPE paddingSize;

	paddingSize = getPaddingSize(buffSize, blockSize);
	if (paddingSize == blockSize) {
		paddingSize = 0;
	}
	return buffSize + paddingSize;
}

/**
 * Converts a big endian value into a integer.
 *
 * @param[in] buff The buffer. It must have at least sizeof(v) bytes.
 * @param[out] v The value read.
 * @tparam INT_TYPE An integer type.
 * @since 2017.11.18
 */
template < class INT_TYPE >
void BE2Int(const void * buff, INT_TYPE & v) {
	const std::uint8_t * p;
	const std::uint8_t * pEnd;

	p = (const std::uint8_t *)buff;
	pEnd = p + sizeof(v);
	v = 0;
	for (; p < pEnd; p++) {
		v = (v << 8) | INT_TYPE(*p & 0xFF);
	}
}

/**
 * Converts an integer into a big endian value.
 *
 * @param[in] v The value to be converted.
 * @param[out] buff The buffer that will receive the value. It must have at least sizeof(v) bytes.
 * @tparam INT_TYPE An integer type.
 * @since 2017.11.18
 */
template < class INT_TYPE >
void int2BE(INT_TYPE v, void * buff) {
	std::uint8_t * pBegin;
	std::uint8_t * p;

	pBegin = ((std::uint8_t *)buff) - 1;
	for (p = pBegin + sizeof(INT_TYPE); p > pBegin; p--) {
		*p = (std::uint8_t)(v & 0xFF);
		v = v >> 8;
	}
}

/**
 * Securely fills a memory buffer with zeroes. It is guaranteed to be
 * executed regardless of the optimizations.
 *
 * @param[in] buff The buffer to be zeroed. If set to NULL, this method
 * does nothing.
 * @param[in] buffSize The size of the buffer to be zeroed.
 * @since 2017.11.20
 */
void clearMemory(void * buff, std::uint64_t buffSize);

/**
 * Locks memory segments into RAM. It should prevent the memory page from being
 * removed from the memory and be transfered to disk.
 *
 * <p>On Posix systems, it calls mlock() to achieve this feature. On Windows,
 * it uses VirtualLock() to achieve the same effect.</p>
 *
 * @param[in] addr The address.
 * @param[in] size The size.
 * @return true for success or false otherwise.
 * @since 2018.01.30
 * @see unlockMemory()
 * @note This method may generate great overhead in the system. Do not forget to
 * release all locked memory when it is no longer required.
 */
bool lockMemory(void * addr, std::uint64_t size);

/**
 * Unlocks memory segments locked by lockMemory().
 *
 * @param[in] addr The address.
 * @param[in] size The size.
 * @return true for success or false otherwise.
 * @since 2018.01.30
 * @see lockMemory()
 */
bool unlockMemory(void * addr, std::uint64_t size);

/**
 * This helper class implements a memory cleaner. It can be used to register a
 * buffer that will be cleaned when this class is disposed. It is important to
 * notice that the registered buffer will bel zeroed but not disposed by this
 * class.
 *
 * @since 2018.03.25
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
 * @see IRSecureTemp
 */
class IRAutoMemoryCleaner {
private:
	std::uint64_t _buffSize;
	void * _buff;
public:
	/**
	 * Creates a new instance of this class.
	 *
	 * @param[in] buff The buffer that should be cleaned on the disposal of this
	 * instance. This buffer will not be disposed alongsize with this class.
	 * @param[in] size The size of the buffer.
	 */
	IRAutoMemoryCleaner(void * buff, std::uint64_t size): _buffSize(size),
			_buff(buff) {
	}

	// Copy constructor is forbidden
	IRAutoMemoryCleaner(const IRAutoMemoryCleaner &) = delete;

	/**
	 * Disposes ths instance and cleans the buffer registered inside it. The
	 * buffer itself will not be disposed.
	 */
	~IRAutoMemoryCleaner() {
		this->clear();
	}

	/**
	 * Cleans the buffer.
	 */
	void clear() {
		clearMemory(this->_buff, this->_buffSize);
	}
};

/**
 * This helper class implements a temporary basic type buffer that will clean
 * itself when disposed.
 *
 * @since 2018.04.12
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
 * @see IRAutoMemoryCleaner
 */
template <class BaseType>
class IRBaseSecureTemp {
private:
	std::uint64_t _buffSize;
	BaseType * _buff;
	std::uint64_t _position;
public:
	/**
	 * Creates a new instance of this class.
	 *
	 * @param[in] size The size of the temporary buffer in bytes.
	 */
	IRBaseSecureTemp(std::uint64_t size): _buffSize(size),
			_buff(new BaseType[size]), _position(0) {
	}

	// Copy constructor is forbidden
	IRBaseSecureTemp(const IRBaseSecureTemp &) = delete;

	/**
	 * Disposes this instance and releases all associated resources.
	 */
	~IRBaseSecureTemp() {
		if (this->_buff) {
			this->clear();
			delete [] this->_buff;
		}
	}

	/**
	 * Cleans the buffer.
	 */
	inline void clear() {
		clearMemory(this->_buff, this->_buffSize * sizeof(BaseType));
	}

	/**
	 * Returns the temporary buffer size.
	 *
	 * @return The buffer size.
	 */
	inline std::uint64_t size() const {
		return this->_buffSize;
	}

	/**
	 * Returns a read/write pointer to the temporary buffer.
	 *
	 * @return The buffer.
	 */
	inline BaseType * buff() {
		return this->_buff;
	}

	/**
	 * Returns a read-only pointer to the temporary buffer.
	 *
	 * @return The buffer.
	 */
	inline const BaseType * buff() const {
		return this->_buff;
	}

	/**
	 * Returns a read-write pointer to the temporary buffer at the current
	 * position.
	 *
	 * @return The buffer.
	 */
	inline const BaseType * posBuff() {
		return this->_buff + this->_position;
	}

	/**
	 * Returns a read-only pointer to the temporary buffer at the current
	 * position.
	 *
	 * @return The buffer.
	 */
	inline const BaseType * posBuff() const {
		return this->_buff + this->_position;
	}

	/**
	 * Returns the current position.
	 *
	 * @return The current position.
	 */
	inline std::uint64_t position() const {
		return this->_position;
	}

	/**
	 * Sets the current position.
	 *
	 * @param[in] position The new position. It cannot be a value larger than
	 * IRSecureTemp::size().
	 * @note As a safeguard, this method will throw an std::invalid_argument in
	 * case of error.
	 */
	inline void setPosition(std::uint64_t position) {
		if (position > this->size()) {
			throw std::invalid_argument("");
		}
		this->_position = position;
	}

	/**
	 * Returns the remaing bytes based on the current position.
	 *
	 * @return The current position.
	 */
	inline std::uint64_t remaining() const {
		return this->_buffSize - this->_position;
	}
};

/**
 * This helper class implements a temporary byte buffer that will clean itself
 * when disposed.
 *
 * <p>Starting on version 2018.04.12, IRSecureTemp is now a specialization of
 * the class template IRBaseSecureTemp with BaseType as std::uint8_t.</p>
 *
 * @since 2018.03.25
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
 * @see IRAutoMemoryCleaner
 */
typedef IRBaseSecureTemp<std::uint8_t> IRSecureTemp;

} // namespace IRUtils

} //namespace ircommon

#endif /* INCLUDE_IRUTILS_IRBUFFER_H_ */
