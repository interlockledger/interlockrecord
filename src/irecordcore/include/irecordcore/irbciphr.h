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
#ifndef _IRECORDCORE_IRBCIPHR_H_
#define _IRECORDCORE_IRBCIPHR_H_

#include <irecordcore/ircipher.h>
#include <botan/block_cipher.h>
#include <botan/aes.h>

namespace irecordcore {
namespace crypto {

/**
 * This class template implements a IRBlockCipherAlgorithm using the Botan2 as
 * its backend.
 *
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
 * @since 2018.04.09
 */
template <class BotanBlockCipherType>
class IRBotanBlockCipherAlgorithm: public IRBlockCipherAlgorithm {
private:
	BotanBlockCipherType _cipher;
public:
	IRBotanBlockCipherAlgorithm(bool cipherMode) :
			IRBlockCipherAlgorithm(cipherMode), _cipher() {
	}

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
		return this->_cipher.maximum_keylength();
	}

	virtual unsigned int maxKeySize() const override {
		return this->_cipher.maximum_keylength();
	}

	virtual bool isValidKeySize(unsigned int keySize) const override {
		return this->_cipher.valid_keylength (keySize);
	}

	virtual bool setRawKey(const void * key, std::uint64_t keySize) override {
		return this->_cipher.set_key((const std::uint8_t *)key, keySize);
	}

	virtual unsigned int blockSize() const override {
		return this->_cipher.block_size();
	}
};

typedef IRBotanBlockCipherAlgorithm<Botan::AES_128> IRAES128BlockCipherAlgorithm;

typedef IRBotanBlockCipherAlgorithm<Botan::AES_256> IRAES256BlockCipherAlgorithm;

} // namespace crypto
} // namespace irecordcore

#endif /* _IRECORDCORE_IRBCIPHR_H_ */
