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
#ifndef _IRECORDCORE_IRKEY_H_
#define _IRECORDCORE_IRKEY_H_

#include <cstdint>
#include <ircommon/irpmem.h>
#include <ircommon/irbuffer.h>

namespace irecordcore {
namespace crypto {

/**
 * Base class for all cryptographic keys.
 *
 * @since 2018.03.12
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
 */
class IRKey {
public:
	/**
	 * Creates a new instance of this class.
	 */
	IRKey() = default;

	/**
	 * Disposes this instance and releases all associated resources.
	 */
	virtual ~IRKey() = default;

	/**
	 * Serializes the key using the Interlock Record format.
	 *
	 * @param[out] out The output stream.
	 * @return true on success or false otherwise.
	 * @note The default implementation always returns false.
	 */
	virtual bool serialize(ircommon::IRBuffer & out);
};

/**
 * Base class for all secret keys.
 *
 * @since 2018.03.12
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
 */
class IRSecretKey: public IRKey {
public:
	/**
	 * Creates a new instance of this class.
	 */
	IRSecretKey() = default;

	/**
	 * Disposes this instance and releases all associated resources.
	 */
	virtual ~IRSecretKey() = default;

	/**
	 * Retuns the size of the key in bits.
	 *
	 * @return The size of the key in bits.
	 */
	virtual std::uint64_t size() = 0;

	/**
	 * Retuns the size of the key in bytes.
	 *
	 * @return The size of the key in bytes.
	 */
	virtual std::uint64_t sizeInBytes() = 0;
};

/**
 * This class implements the software a based secret key.
 *
 * @since 2018.03.12
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
 * @note This class is thread safe.
 */
class IRSecretKeyImpl: public IRSecretKey {
private:
	ircommon::crypto::IRProtectedMemory _key;
public:
	/**
	 * Creates a new instance of this class. Once created, the instance will be
	 * unlocked for reading.
	 *
	 * @param[in] key The raw key.
	 * @param[in] keySize The size of the key in bytes.
	 * @except std::runtime_error In case of runtime error.
	 */
	IRSecretKeyImpl(const void * key, std::uint64_t keySize);

	/**
	 * Disposes this instance and releases all associated resources.
	 */
	virtual ~IRSecretKeyImpl();

	virtual std::uint64_t size();

	virtual std::uint64_t sizeInBytes();

	/**
	 * Locks this instance for reading. It also grants exclusive access to the
	 * key's actual value. Once called, this instance must be released by a call
	 * to unlock().
	 *
	 * <p>It is important to notice that this method should not be called more
	 * than once in a row by the same thread because it will lead to deadlocks.
	 * </p>
	 *
	 * @except std::runtime_error In case of runtime error.
	 */
	void lock();

	/**
	 * Unlocks this instance. It releases the exclusive lock to the actual value
	 * of the key.
	 *
	 * @except std::runtime_error In case of error.
	 */
	void unlock();

	/**
	 * Returns the raw key value. The actual key value will be available if the
	 * key is locked for reading.
	 *
	 * @return The raw key value or nullptr if it is not available.
	 * @see lock()
	 * @see unlock()
	 */
	const void * key() const {
		return this->_key.value();
	}

	/**
	 * Copies the value of the key into a buffer.
	 *
	 * @param[out] key The output key.
	 * @param[in] keysize The size of the key in bytes.
	 * @return The actual number of bytes written or 0 for failure.
	 * @note Do not call this method if this instance is already locked for
	 * reading by the same thread. Doing so will lead to deadlocks.
	 */
	std::uint64_t copy(void * key, std::uint64_t keySize);

	/**
	 * Serializes the key using the Interlock Record format.
	 *
	 * <p>The serialization of this implementation is the raw value of the key
	 * itself.</p>
	 *
	 * @param[out] out The output stream.
	 * @return true on success or false otherwise.
	 * @note Do not call this method if this instance is already locked for
	 * reading by the same thread. Doing so will lead to deadlocks.
	 */
	virtual bool serialize(ircommon::IRBuffer & out);
};

} //namespace crypto
} //namespace irecordcore

#endif /* _IRECORDCORE_IRKEY_H_ */
