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
#ifndef _IRECORDCORE_IRMAC_H_
#define _IRECORDCORE_IRMAC_H_

#include <memory>
#include <irecordcore/irhash.h>
#include <irecordcore/irkey.h>

namespace irecordcore {
namespace crypto {

/**
 * This is the base class for all Message Authentication Code algorithms.
 *
 * @since 2018.03.09
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
 */
class IRMAC: public IRHashAlgorithm {
public:
	/**
	 * Creates a new instance of this class.
	 *
	 * @param[in] type The algorithm type.
	 */
	IRMAC();

	/**
	 * Disposes this instance and releases all associated resources.
	 */
	virtual ~IRMAC();

	/**
	 * Sets the key of this MAC algorithm. It is important to notice that
	 * any call to this method will reset this instance.
	 *
	 * @param[in] key The key.
	 * @param[in] keySize The size of the key in bytes.
	 */
	virtual bool setRawKey(const void * key, std::uint64_t keySize) = 0;

	/**
	 * Sets the key of this MAC algorithm. It is important to notice that
	 * any call to this method will reset this instance.
	 *
	 * @param[in] key The key.
	 */
	virtual bool setKey(IRSecretKey & key) = 0;
};

/**
 * This class implements the HMAC algorithm as defined by RFC2104.
 *
 * @since 2018.03.11
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
 */
class IRHMAC: public IRMAC {
private:
	std::unique_ptr<IRHashAlgorithm> _hash;
	std::uint64_t _blockSize;
	std::unique_ptr<std::uint8_t[]> _ipad;
	std::unique_ptr<std::uint8_t[]> _opad;

	/**
	 * Masks the specified block using the specified mask.
	 *
	 * @param[in,out] block The block to be masked. Must have at least
	 * IRHMAC::blockSize() bytes.
	 * @param[in] The mask to be used.
	 */
	void mask(std::uint8_t * block, std::uint8_t mask);
public:
	/**
	 * Creates a new instance of this class.
	 *
	 * @param[in] hash The hash algorithm. This class will claim full ownership
	 * of this instance.
	 * @param[in] blockSize The block size. It must be always equal to or larger
	 * than the output of the hash algorithm used. Use 0 to let the implementation
	 * decide what block size should be used.
	 * @exception std::invalid_argument If the block size is smaller than the
	 * size of the output of the inner hash.
	 */
	IRHMAC(IRHashAlgorithm * hash, std::uint64_t blockSize = 0);

	/**
	 * Disposes this instance and releases all associated resources.
	 */
	virtual ~IRHMAC();

	/**
	 * Returns the size of the block in bytes.
	 *
	 * @return The size of the block in bytes.
	 */
	std::uint64_t blockSize() const {
		return this->_blockSize;
	}

	virtual bool setRawKey(const void * key, std::uint64_t keySize);

	virtual bool setKey(IRSecretKey & key);

	virtual void reset();

	virtual std::uint64_t size() const;

	virtual std::uint64_t sizeInBytes() const;

	virtual void update(const void * buff, std::uint64_t size);

	virtual bool finalize(void * out, std::uint64_t size);
};

} //namespace crypto
} //namespace irecordcore

#endif /* _IRECORDCORE_IRMAC_H_ */
