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
#ifndef _IRECORDCORE_IRBCIPHR_H_
#define _IRECORDCORE_IRBCIPHR_H_

#include <irecordcore/ircipher.h>
#include <botan/block_cipher.h>
#include <botan/aes.h>

namespace irecordcore {
namespace crypto {

/**
 * This class template implements a IRBlockCipherAlgorithm using the
 * Botan::BlockCipher instances as its backend.
 *
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
 * @since 2018.04.09
 */
template <class BotanBlockCipherType>
class IRBotanBlockCipherAlgorithm: public IRBlockCipherAlgorithm {
private:
	/**
	 * The inner Botan::BlockCipher instance.
	 */
	BotanBlockCipherType _cipher;
public:
	/**
	 * Creates a new instance of this class.
	 *
	 * @param[in] cipherMode set to true to create a cipher or false to create a
	 * decipher.
	 */
	IRBotanBlockCipherAlgorithm(bool cipherMode) :
			IRBlockCipherAlgorithm(cipherMode), _cipher() {
	}

	/**
	 * Disposes this instance and releases all associated resources.
	 */
	virtual ~IRBotanBlockCipherAlgorithm() {
	}

	virtual bool processBlocks(const void * src, void * dst,
			unsigned int blockCount) override {

		if (blockCount) {
			if (this->cipherMode()) {
				this->_cipher.encrypt_n((const std::uint8_t *)src,
						(std::uint8_t *)dst, blockCount);
			} else {
				this->_cipher.decrypt_n((const std::uint8_t *)src,
						(std::uint8_t *)dst, blockCount);
			}
		}
		return true;
	}

	virtual unsigned int minKeySize() const override {
		return this->_cipher.maximum_keylength() * 8;
	}

	virtual unsigned int maxKeySize() const override {
		return this->_cipher.maximum_keylength() * 8;
	}

	virtual bool isValidKeySize(unsigned int keySize) const override {
		if (keySize % 8) {
			return false;
		} else {
			return this->_cipher.valid_keylength (keySize / 8);
		}
	}

	virtual bool setRawKey(const void * key, std::uint64_t keySize) override {
		if (this->isValidKeySize(keySize * 8)) {
			this->_cipher.set_key((const std::uint8_t *)key, keySize);
			return true;
		} else {
			return false;
		}
	}

	virtual unsigned int blockSizeInBytes() const override {
		return this->_cipher.block_size();
	}

	virtual unsigned int blockSize() const override {
		return this->blockSizeInBytes() * 8;
	}
};

/**
 * This class implements the software based AES128 (FIPS 197) algorithm.
 *
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
 * @since 2018.04.09
 */
typedef IRBotanBlockCipherAlgorithm<Botan::AES_128>
		IRAES128BlockCipherAlgorithm;

/**
 * This class implements the software based AES256 (FIPS 197) algorithm.
 *
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
 * @since 2018.04.09
 */
typedef IRBotanBlockCipherAlgorithm<Botan::AES_256>
		IRAES256BlockCipherAlgorithm;

} // namespace crypto
} // namespace irecordcore

#endif /* _IRECORDCORE_IRBCIPHR_H_ */
