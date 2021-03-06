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
#ifndef _IRECORDCORE_IRBCIPHM_H_
#define _IRECORDCORE_IRBCIPHM_H_

#include <memory>
#include <ircommon/irutils.h>
#include <irecordcore/ircipher.h>
#include <irecordcore/irciphpd.h>

namespace irecordcore {
namespace crypto {

/**
 * This class is the base class for all block cipher modes.
 *
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
 * @since 2018.04.18
 */
class IRBlockCipherMode {
protected:
	/**
	 * The inner padding.
	 */
	std::unique_ptr<IRPadding> _padding;
	/**
	 * The inner cipher.
	 */
	std::unique_ptr<IRBlockCipherAlgorithm> _cipher;
	/**
	 * The value for the temporary block.
	 */
	ircommon::IRUtils::IRSecureTemp _tmpBlock;

	/**
	 * Process a single block. The default implementation does the following:
	 *
	 * 	* Call prepareBlock(src);
	 * 	* Calls cipherDecipherBlock(src, dst);
	 * 	* Call postBlock(dst);
	 *
	 * @param[in,out] src The plaintext. It may be modified on the output.
	 * @param[out] dst The output.
	 * @return true for success or false otherwise.
	 */
	virtual bool processBlock(std::uint8_t * src, std::uint8_t * dst);

	/**
	 * Ciphers/decipher the block. It is called by processBlock() in order to
	 * transform the block using the cipher. The default implementation just
	 * call the inner cipher's processBlock() method for a single block.
	 *
	 * @param[in] src It may be modified on the output.
	 * @param[out] dst The output.
	 * @return true for success or false otherwise.
	 */
	virtual bool cipherDecipherBlock(std::uint8_t * src, std::uint8_t * dst);

	/**
	 * Prepare the block. This method is called by  processBlock() in order to
	 * change the src block before encryption/decryption whenever necessary.
	 *
	 * <p>The default implementation does nothing.</p>
	 *
	 * @param[in,out] src The plaintext. It may be modified on the output.
	 * @return true for success or false otherwise.
	 */
	virtual bool prepareBlock(std::uint8_t * src);

	/**
	 * Post process the output. The default implementation does nothing.
	 *
	 * @param[in] src The plaintext. It may be modified on the output.
	 * @param[in,out] dst The output.
	 * @return true for success or false otherwise.
	 */
	virtual bool postBlock(const std::uint8_t * src, std::uint8_t * dst);
public:
	/**
	 * Creates a new instance of this class.
	 *
	 * @param[in] cipher The cipher to be used. It must be ready to be used.
	 * @param[in] padding The padding to be used.
	 * @note This class will take ownership of both cipher and padding instances.
	 */
	IRBlockCipherMode(IRBlockCipherAlgorithm * cipher, IRPadding * padding);

	/**
	 * Disposes this instance and releases all associated resources.
	 */
	virtual ~IRBlockCipherMode() = default;

	/**
	 * Grants a read-only access to the inner padding.
	 *
	 * @return The inner padding.
	 */
	const IRPadding & padding() const {
		return *(this->_padding);
	}

	/**
	 * Grants a read-only access to the inner cipher.
	 *
	 * @return The inner cipher.
	 */
	const IRBlockCipherAlgorithm & cipher() const {
		return *(this->_cipher);
	}

	/**
	 * Returns the current block size in bytes.
	 *
	 * @return The block size.
	 */
	inline std::uint64_t blockSizeInBytes() const {
		return this->_tmpBlock.size();
	}

	/**
	 * Returns the current cipher mode.
	 *
	 * @return true for ciphering or false for deciphering.
	 */
	inline bool cipherMode() const {
		return this->_cipher->cipherMode();
	}

	/**
	 * Resets this instance in order to start over. All previous work in
	 * progress, if any will be disposed.
	 */
	virtual void reset();

	/**
	 * Returns the required output size for a given input size. The returned
	 * value will be the largest multiple of a block larger than srcSize when
	 * ciphering or srcSize on deciphering.
	 *
	 * @param[in] srcSize The size of the sorce.
	 * @return The required size of the output.
	 */
	std::uint64_t getOutputSize(std::uint64_t srcSize) const;

	/**
	 * Returns the number of bytes that remains to be processed alongside with
	 * the next chunck.
	 *
	 * @return The number of bytes inside the internal buffer.
	 */
	std::uint64_t remaining() const {
		return this->_tmpBlock.remaining();
	}

	/**
	 * Process a chunk of data. All bytes from source will be consumed but some
	 * bytes may remain inside this instance to be processed in the next chunck.
	 *
	 * @param[in] src The data to be processed.
	 * @param[in] srcSize The size of src in bytes.
	 * @param[out] dst The output.
	 * @param[in,out] dstSrc On input, it is the size of dst. On output, it is
	 * the actual size of the output.
	 * @param[in] last Flag that indicates if it is the last chunk of data or
	 * not.
	 * @return true on success or false otherwise.
	 * @note It is important to notice that calls to this method with srcSize
	 * as zero while deciphering data may lead to failures when last is true
	 * because the padding may already be processed without being removed by
	 * previous calls.
	 */
	bool process(const void * src, std::uint64_t srcSize, void * dst,
			std::uint64_t & dstSize, bool last = false);
};

/**
 * This class implements the CBC block cipher mode.
 *
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
 * @since 2018.04.18
 */
class IRCBCBlockCipherMode : public IRBlockCipherMode {
protected:
	/**
	 * The IV.
	 */
	ircommon::IRUtils::IRSecureTemp _iv;
	/**
	 * The last ciphered block.
	 */
	ircommon::IRUtils::IRSecureTemp _lastBlock;
	virtual bool prepareBlock(std::uint8_t * src) override;
	virtual bool postBlock(const std::uint8_t * src, std::uint8_t * dst) override;

	void xorBlock(const std::uint8_t * src, std::uint8_t * dst);
public:
	/**
	 * Creates a new instance of this class.
	 *
	 * @param[in] cipher The cipher to be used. It must be ready to be used.
	 * @param[in] padding The padding to be used.
	 * @note This class will take ownership of both cipher and padding instances.
	 */
	IRCBCBlockCipherMode(IRBlockCipherAlgorithm * cipher, IRPadding * padding);

	/**
	 * Disposes this instance and releases all associated resources.
	 */
	virtual ~IRCBCBlockCipherMode() = default;

	/**
	 * Sets the IV value. The IV must have at least blockSizeInBytes(). If
	 * ivSize is larger than the size of the block only the first
	 * blockSizeInBytes() bytes will be used.
	 *
	 * <p>The default IV will set all bytes to zero.</p>
	 *
	 * @param[in] iv The IV value.
	 * @param[in] ivSize The size of the IV.
	 * @return true for success or false otherwise.
	 */
	bool setIV(const void * iv, std::uint64_t ivSize);

	/**
	 * Returns the current IV. It has always blockSizeInBytes() bytes.
	 *
	 * @return A pointer to the current IV.
	 */
	const void * iv() const {
		return _iv.buff();
	}

	virtual void reset() override;
};

} // namespace crypto
} // namespace irecordcore

#endif /* _IRECORDCORE_IRBCIPHM_H_ */
