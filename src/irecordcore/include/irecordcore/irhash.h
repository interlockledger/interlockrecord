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
#ifndef IRECORDCORE_INCLUDE_IRECORDCORE_IRHASH_H_
#define IRECORDCORE_INCLUDE_IRECORDCORE_IRHASH_H_

#include <ircommon/irbuffer.h>
#include <irecordcore/ircrypto.h>
#include <cstdint>
#include <botan/sha160.h>
#include <botan/sha2_32.h>
#include <botan/sha2_64.h>
#include <botan/sha3.h>

namespace irecordcore {
namespace crypto {

/**
 * This abstract class defines the interface for all hash like algorithms that
 * compress an arbitrary byte sequence into a fixed size byte array.
 *
 * @since 2018.03.09
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
 */
class IRHashAlgorithm {
public:
	IRHashAlgorithm() = default;

	virtual ~IRHashAlgorithm() = default;

	/**
	 * Resets this instance.
	 */
	virtual void reset() = 0;

	/**
	 * Returns the size of this hash in bits.
	 *
	 * @return The size of the hash in bits.
	 */
	virtual std::uint64_t size() const = 0;

	/**
	 * Returns the size of this hash in bytes.
	 *
	 * @return The size of the hash in bytes.
	 * @note The default implementation just returns IRHashAlgorithm::size()
	 * divided 8.
	 */
	virtual std::uint64_t sizeInBytes() const;

	/**
	 * Updates this hash.
	 *
	 * @param[in] buff The data.
	 * @param[in] size The size of buff in bytes.
	 */
	virtual void update(const void * buff, std::uint64_t size) = 0;

	/**
	 * Finalizes the computation of the hash.
	 *
	 * @param[out] out The buffer that will receive the data.
	 * @param[in] size Size of the buffer out. It mus be always equal or larger
	 * than sizeInBytes().
	 * @return true for success or false otherwise.
	 */
	virtual bool finalize(void * out, std::uint64_t size) = 0;
};

/**
 * This is the base class for all hash algorithms.
 *
 * @since 2018.02.01
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
 */
class IRHash : public IRHashAlgorithm {
private:
	/**
	 * Type of the hash.
	 */
	IRHashAlg _type;
public:
	/**
	 * Creates a new instance of this class.
	 *
	 * @param[in] type The algorithm type.
	 */
	IRHash(IRHashAlg type);

	/**
	 * Disposes this instance and releases all associated resources.
	 */
	virtual ~IRHash();

	/**
	 * Returns the hash type.
	 *
	 * @return The hash type.
	 */
	IRHashAlg type() const {
		return this->_type;
	}
};

/**
 * This class implements the COPY hash algorithm.
 *
 * @since 2018.02.01
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
 * @note This class holds all the information inside an internal secure buffer.
 * Given that, do not forget to dispose this instance in order to release memory.
 */
class IRCopyHash  : public IRHash {
protected:
	/**
	 * The inner state.
	 */
	ircommon::IRBuffer _state;
public:
	/**
	 * Creates a new instance of this class.
	 *
	 * @param[in] reserved Reserved bytes in the internal buffer.
	 */
	IRCopyHash(std::uint64_t reserved = 0):IRHash(IR_HASH_COPY),
			_state(reserved, true) {}

	/**
	 * Disposes this instance and releases all associated resources.
	 */
	virtual ~IRCopyHash() = default;

	virtual void reset();

	virtual std::uint64_t size() const;

	virtual void update(const void * buff, std::uint64_t size);

	virtual bool finalize(void * out, std::uint64_t size);
};

/**
 * This class template implements the hash algorithm implemented by Botan 2.
 *
 * @since 2018.02.01
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
 * @tparam BotanHashImpl Botan 2 class that implements the hash.
 * @tparam Type The hash type.
 */
template <class BotanHashImpl, IRHashAlg Type>
class IRBotanHash : public IRHash {
protected:
	BotanHashImpl _hash;
public:
	IRBotanHash(): IRHash(Type) {}

	virtual ~IRBotanHash(){}

	virtual void reset() {
		this->_hash.clear();
	}

	virtual std::uint64_t size() const {
		return this->sizeInBytes() * 8;
	}

	virtual std::uint64_t sizeInBytes() const {
		return this->_hash.output_length();
	}

	virtual void update(const void * buff, std::uint64_t size) {
		this->_hash.update((const std::uint8_t *)buff, size);
	}

	virtual bool finalize(void * out, std::uint64_t size) {
		if (size < this->sizeInBytes()) {
			return false;
		}
		this->_hash.final((std::uint8_t *)out);
		return true;
	}
};

/**
 * This class implements the SHA1 algorithm.
 *
 * @since 2018.02.01
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
 */
typedef IRBotanHash<Botan::SHA_160, IR_HASH_SHA1> IRSHA1Hash;

/**
 * This class implements the SHA256 algorithm.
 *
 * @since 2018.02.01
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
 */
typedef IRBotanHash<Botan::SHA_256, IR_HASH_SHA256> IRSHA256Hash;

/**
 * This class implements the SHA512 algorithm.
 *
 * @since 2018.02.01
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
 */
typedef IRBotanHash<Botan::SHA_512, IR_HASH_SHA512> IRSHA512Hash;

/**
 * This class template encapsulates the SHA3 hash algorithm implemented by
 * Botan 2.
 *
 * @since 2018.02.06
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
 * @tparam BotanHashImpl This parameter can be Botan::Keccak_1600 or
 * Botan::SHA_3.
 * @tparam OutputSize The output size. Must be 224, 256, 384, or 512.
 * @tparam Type The hash type.
 */
template <class BotanHashImpl, size_t OutputSize, IRHashAlg Type>
class IRBotanKeccakHash : public IRHash {
protected:
	BotanHashImpl _hash;
public:
	IRBotanKeccakHash(): IRHash(Type),_hash(OutputSize) {}

	virtual ~IRBotanKeccakHash() = default;

	virtual void reset() {
		this->_hash.clear();
	}

	virtual std::uint64_t size() const {
		return this->sizeInBytes() * 8;
	}

	virtual std::uint64_t sizeInBytes() const {
		return this->_hash.output_length();
	}

	virtual void update(const void * buff, std::uint64_t size) {
		this->_hash.update((const std::uint8_t *)buff, size);
	}

	virtual bool finalize(void * out, std::uint64_t size) {
		if (size < this->sizeInBytes()) {
			return false;
		}
		this->_hash.final((std::uint8_t *)out);
		return true;
	}
};

typedef IRBotanKeccakHash<Botan::SHA_3,256, IR_HASH_SHA3_256> IRSHA3_256Hash;

typedef IRBotanKeccakHash<Botan::SHA_3, 512, IR_HASH_SHA3_512> IRSHA3_512Hash;

class IRHashFactory {
public:
	IRHash * create(std::uint16_t type);
};

} //namespace crypto
} //namespace irecordcore

#endif /* IRECORDCORE_INCLUDE_IRECORDCORE_IRHASH_H_ */
