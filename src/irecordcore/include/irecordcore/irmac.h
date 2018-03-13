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
#ifndef _IRECORDCORE_IRMAC_H_
#define _IRECORDCORE_IRMAC_H_

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
	virtual bool setKey(const void * key, std::uint64_t keySize) = 0;

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
class IRHMAC: IRMAC {
private:
	IRHashAlgorithm * _hash;
	std::uint64_t _blockSize;
	std::uint8_t * _ipad;
	std::uint8_t * _opad;

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
	 * than the output of the hash algorithm used (defaults to 64 as defined by
	 * the RFC).
	 */
	IRHMAC(IRHashAlgorithm * hash, std::uint64_t blockSize = 64);

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

	virtual bool setKey(const void * key, std::uint64_t keySize);

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
