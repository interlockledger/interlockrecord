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
private:
	bool _exportable;
public:
	/**
	 * Creates a new instance of this class.
	 */
	IRKey(bool exportable);

	/**
	 * Disposes this instance and releases all associated resources.
	 */
	virtual ~IRKey() = default;

	/**
	 * Verifies if this key is software based or hardware based.
	 *
	 * @return true if the key is backed by software or false otherwise.
	 */
	bool exportable() const {
		return this->_exportable;
	}

	/**
	 * Serializes the key using the Interlock Record format.
	 *
	 * @param[out] out The output stream.
	 * @return true on success or false otherwise.
	 * @note The default implementation always returns false.
	 */
	virtual bool serialize(ircommon::IRBuffer & out);

	/**
	 * Exports the raw key using the format specified each key type.
	 *
	 * <p>On success, this method returns true, the raw key is copied to key
	 * and the actual size o the key is returned in keySize. If this key is not
	 * exportable, it returns false, the buffer key will remain unchanged and
	 * keySize will return as 0.</p>
	 *
	 * <p>If the key is insufficient to hold the key or is set to NULL, this
	 * method will return false and the number of bytes required to hold the
	 * key will be returned in keySize.</p>
	 *
	 * @param[out] key The buffer that will receive the key.
	 * @param[in,out] keySize On input, it is the size of key in bytes. On
	 * output, it is the actual size of the key in bytes.
	 * @return true for success or false otherwise.
	 * @see IRKey::exportable()
	 */
	virtual bool exportKey(void * key, std::uint64_t & keySize);
};

/**
 * Base class for all secret keys.
 *
 * <p>It is important to notice that all keys exported by instances of this
 * class, if supported, will be the raw value of the key.</p>
 *
 * @since 2018.03.12
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
 */
class IRSecretKey: public IRKey {
public:
	/**
	 * Creates a new instance of this class.
	 */
	IRSecretKey(bool exportable): IRKey(exportable) {}

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
 * This class implements the software a based secret key. It is important to
 * notice that the raw key stored by this class will be encrypted in memory
 * in order to minimize the success of potential memory scan attacks.
 *
 * @since 2018.03.12
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
 * @note This class is thread safe.
 */
class IRSecretKeyImpl: public IRSecretKey {
private:
	/**
	 * The protected key in memory.
	 */
	ircommon::crypto::IRProtectedMemory _key;

	/**
	 * Locks this instance for reading.
	 */
	void lock();

	/**
	 * Unlocks this instance.
	 */
	void unlock();

	/**
	 * Returns a pointer to the raw key.
	 *
	 * @return The pointer to the raw key.
	 */
	const void * key() const {
		return this->_key.value();
	}
public:
	/**
	 * Creates a new instance of this class.
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

	virtual bool exportKey(void * key, std::uint64_t & keySize);

	/**
	 * Serializes the key using the Interlock Record format.
	 *
	 * <p>The serialization of this implementation is the raw value of the key
	 * itself.</p>
	 *
	 * @param[out] out The output stream.
	 * @return true on success or false otherwise.
	 */
	virtual bool serialize(ircommon::IRBuffer & out);
};

} //namespace crypto
} //namespace irecordcore

#endif /* _IRECORDCORE_IRKEY_H_ */
