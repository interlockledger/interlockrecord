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

class IRCipherAlgorithm {
private:
	bool _cipherMode;
public:

	void setCipherMode(bool )

	bool isCipher() const {
		return this->_cipherMode;
	}
};

class IRBlockCipherAlgorithm : public IRCipherAlgorithm {
public:
	IRBlockCipherAlgorithm() = default;

	virtual ~IRBlockCipherAlgorithm() = default;

	/**
	 * Sets the key.
	 *
	 * @param[in] key The key.
	 * @param[in] keySize The key size in bytes.
	 */
	virtual void setKey(const void * key, std::uint64_t keySize) = 0;

	/**
	 * Sets the key.
	 *
	 * @param[in] key The key.
	 */
	virtual void setKey(IRSecretKey * key) = 0;

	/**
	 * Returns the block size.
	 *
	 * @return The block size in bits.
	 */
	virtual unsigned int blockSize() = 0;

	/**
	 * Returns the block size in bytes.
	 *
	 * @return The block size in bytes.
	 */
	virtual unsigned int blockSizeInBytes() = 0;

	/**
	 * Process a single block. Both src and dst must have
	 * IRBlockCipherAlgorithm::blockSizeInBytes() bytes.
	 *
	 * @param[in] src The source block.
	 * @param[out] dst The destination block.
	 */
	virtual void process(const void * src, void * dst) = 0;
};

} //namespace crypto
} //namespace irecordcore

#endif /* _IRECORDCORE_IRCIPHER_H_ */
