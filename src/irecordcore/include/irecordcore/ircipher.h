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
#ifndef _IRECORDCORE_IRCIPHER_H_
#define _IRECORDCORE_IRCIPHER_H_

#include <irecordcore/irkey.h>

namespace irecordcore {
namespace crypto {

/**
 * This is the base class for all cipher algorithms.
 *
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
 * @since 2018.04.04
 */
class IRCipherAlgorithm {
private:
	bool _cipherMode;
public:
	IRCipherAlgorithm(bool cipherMode):_cipherMode(cipherMode){}

	virtual ~IRCipherAlgorithm() = default;

	/**
	 * Returns the cipher mode.
	 *
	 * @return true if it is a cipher algorithm or false if it is a decipher
	 * algorithm.
	 */
	bool cipherMode() const {
		return this->_cipherMode;
	}

	/**
	 * Process the data.
	 *
	 * @param[in] src The data to be processed.
	 * @param[in] srcSize The size of the data to be processed.
	 * @param[out] dst The output.
	 * @param[in,out] dstSize On input, the size of the dst. On output, it is
	 * the actual size of the data.
	 * @return true on success or false otherwise.
	 */
	virtual bool process(const void * src, std::uint64_t srcSize,
			void * dst, std::uint64_t & dstSize);

	virtual unsigned int minKeySize() const = 0;

	virtual unsigned int maxKeySize() const = 0;

	/**
	 * Verifies if a given key size is valid for this cipher.
	 *
	 * @param[in] keySize The size of the key in bits.
	 * @return true if the key size is valid or false otherwise.
	 */
	virtual bool isValidKeySize(unsigned int keySize) const;
};

/**
 * This is the base class for all block ciphers.
 *
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
 * @since 2018.04.04
 */
class IRBlockCipherAlgorithm : public IRCipherAlgorithm {
public:
	IRBlockCipherAlgorithm(bool cipherMode);

	virtual ~IRBlockCipherAlgorithm() = default;

	/**
	 * Sets the key.
	 *
	 * @param[in] key The key.
	 * @param[in] keySize The key size in bytes.
	 */
	virtual bool setKey(const void * key, std::uint64_t keySize) = 0;

	/**
	 * Sets the key. By default,
	 *
	 * @param[in] key The key.
	 */
	virtual bool setKey(IRSecretKey * key);

	/**
	 * Returns the block size.
	 *
	 * @return The block size in bits.
	 */
	virtual unsigned int blockSize() const = 0;

	/**
	 * Returns the block size in bytes.
	 *
	 * @return The block size in bytes.
	 */
	virtual unsigned int blockSizeInBytes() const;

	/**
	 * Process the data.
	 *
	 * @param[in] src The data to be processed.
	 * @param[in] srcSize The size of the data to be processed. It must be a
	 * multiple of blockSize.
	 * @param[out] dst The output.
	 * @param[in,out] dstSize On input, the size of the dst. On output, it is
	 * the actual size of the data.
	 * @return true on success or false otherwise.
	 */
	virtual bool process(const void * src, std::uint64_t srcSize,
			void * dst, std::uint64_t & dstSize);

	/**
	 * Process the data in blocks.
	 *
	 * @param[in] src The data to be processed.
	 * @param[out] dst The output. It must have the same size of src.
	 * @param[in] blockCount The number of blocks to be processed.
	 * @return true on success or false otherwise.
	 */
	virtual bool processBlocks(const void * src, void * dst,
			unsigned int blockCount) = 0;
};


class IRNullBlockCipherAlgorithm : public IRBlockCipherAlgorithm {
private:
	unsigned int _blockSize;
public:
	IRNullBlockCipherAlgorithm(bool cipherMode, unsigned int blockSize);

	virtual ~IRNullBlockCipherAlgorithm() = default;

	virtual unsigned int minKeySize() const;

	virtual unsigned int maxKeySize() const;

	virtual bool isValidKeySize(unsigned int keySize) const;

	virtual bool setKey(const void * key, std::uint64_t keySize);

	virtual bool setKey(IRSecretKey * key);

	virtual unsigned int blockSize() const;

	virtual bool processBlocks(const void * src, void * dst,
			unsigned int blockCount);
};

} //namespace crypto
} //namespace irecordcore

#endif /* _IRECORDCORE_IRCIPHER_H_ */
