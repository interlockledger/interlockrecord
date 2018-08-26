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
	/**
	 * Cipher mode. If true it is a cipher otherwise it is a decipher.
	 */
	bool _cipherMode;
public:
	/**
	 * Creates a new instance of this class.
	 *
	 * @param[in] cipherMode set to true to create a cipher or false to create a
	 * decipher.
	 */
	IRCipherAlgorithm(bool cipherMode):_cipherMode(cipherMode){}

	/**
	 * Diposes this instance and releases all associated resources.
	 */
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
			void * dst, std::uint64_t & dstSize) = 0;

	/**
	 * Returns the minimum key size in bits.
	 *
	 * @return The minimum key size.
	 */
	virtual unsigned int minKeySize() const = 0;

	/**
	 * Returns the maximum key size in bits.
	 *
	 * @return The maximum key size.
	 */
	virtual unsigned int maxKeySize() const = 0;

	/**
	 * Verifies if a given key size is valid for this cipher.
	 *
	 * @param[in] keySize The size of the key in bits.
	 * @return true if the key size is valid or false otherwise.
	 */
	virtual bool isValidKeySize(unsigned int keySize) const = 0;
};

/**
 * This is the base class for all block ciphers.
 *
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
 * @since 2018.04.04
 */
class IRBlockCipherAlgorithm : public IRCipherAlgorithm {
public:
	/**
	 * Creates a new instance of this class.
	 *
	 * @param[in] cipherMode set to true to create a cipher or false to create a
	 * decipher.
	 */
	IRBlockCipherAlgorithm(bool cipherMode);

	/**
	 * Diposes this instance and releases all associated resources.
	 */
	virtual ~IRBlockCipherAlgorithm() = default;

	/**
	 * Sets the key.
	 *
	 * @param[in] key The key.
	 * @param[in] keySize The key size in bytes.
	 */
	virtual bool setRawKey(const void * key, std::uint64_t keySize) = 0;

	/**
	 * Sets the key. By default, it tries to export the key and execute
	 * setKey(const void *,std::uint64_t).
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
			void * dst, std::uint64_t & dstSize) override;

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

/**
 * This class implements a null block cipher. It just copies the data from the
 * input into the output using an abritrary block size.
 *
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
 * @since 2018.04.09
 */
class IRNullBlockCipherAlgorithm : public IRBlockCipherAlgorithm {
private:
	/**
	 * Size of the block in bits.
	 */
	unsigned int _blockSize;
public:
	/**
	 * Creates a new instance of this class.
	 *
	 * @param[in] cipherMode set to true to create a cipher or false to create a
	 * decipher.
	 * @param[in] blockSize in bits. It must be a value multiple of 8 and larger
	 * than 1.
	 */
	IRNullBlockCipherAlgorithm(bool cipherMode, unsigned int blockSize);

	/**
	 * Diposes this instance and releases all associated resources.
	 */
	virtual ~IRNullBlockCipherAlgorithm() = default;

	virtual unsigned int minKeySize() const override;

	virtual unsigned int maxKeySize() const override;

	virtual bool isValidKeySize(unsigned int keySize) const override;

	virtual bool setRawKey(const void * key, std::uint64_t keySize) override;

	virtual bool setKey(IRSecretKey * key) override;

	virtual unsigned int blockSize() const override;

	virtual bool processBlocks(const void * src, void * dst,
			unsigned int blockCount) override;
};

} //namespace crypto
} //namespace irecordcore

#endif /* _IRECORDCORE_IRCIPHER_H_ */
