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
#ifndef _IRECORDCORE_IRCIPHPD_H_
#define _IRECORDCORE_IRCIPHPD_H_

#include <ircommon/irrandom.h>
#include <memory>
#include <cstdint>

namespace irecordcore {
namespace crypto {

/**
 * This is the base class for all padding schemes.
 *
 * @since 2018.03.28
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
 */
class IRPadding {
public:
	/**
	 * Creates a new instance of this class.
	 */
	IRPadding() = default;

	/**
	 * Disposes this instance and releases all associated resources.
	 */
	virtual ~IRPadding() = default;

	/**
	 * Returns the size of the padding based on the block size and the data
	 * size.
	 *
	 * <p>The default implementation will always return a value between 1 and
	 * blockSize.</p>
	 *
	 * @param[in] blockSize The size of the block.
	 * @param[in] srcSize The size of the data.
	 * @return The size of the padding.
	 */
	virtual std::uint64_t getPaddingSize(unsigned int blockSize,
			std::uint64_t srcSize) const;

	/**
	 * Returns the size of the padded data based on the block size and the
	 * data size.
	 *
	 * <p>The default implementation returns the largest multiple of the block
	 * size that can hold the data size plus at least 1 byte of padding.</p>
	 *
	 * @param[in] blockSize The size of the block.
	 * @param[in] srcSize The size of the data to be padded.
	 * @return The size of the padded data.
	 */
	std::uint64_t getPaddedSize(unsigned int blockSize,
			std::uint64_t srcSize) const {
		return srcSize + this->getPaddingSize(blockSize, srcSize);
	}

	/**
	 * Adds the padding.
	 *
	 * @param[in] blockSize The size of the block.
	 * @param[in] src The source buffer.
	 * @param[in] srcSize The size of src in bytes.
	 * @param[out] dst The destination buffer. This buffer must have at least
	 * getPaddedSize(unsigned int,std::uint64_t) bytes.
	 * @param[in,out] dstSize On input, it is the size of dst. On output, it is
	 * the size of the padded data.
	 * @return true for success or false otherwise.
	 * @note This method can work in locus if src and dst points to exact the
	 * same buffer. If src and dst does not point to the same buffer but they
	 * overlap, the behavior of this method is undefined.
	 */
	virtual bool addPadding(unsigned int blockSize, const void * src,
			std::uint64_t srcSize, void * dst, std::uint64_t & dstSize) const = 0;

	/**
	 * Removes the padding. It is important to notice that this method may fail
	 * if the padding is not valid.
	 *
	 * @param[in] blockSize The size of the block.
	 * @param[in] src The source buffer.
	 * @param[in,out] srcSize On input, it is the size of src. On output, it is
	 * the size of src without the padding.
	 * @return true for success or false otherwise.
	 */
	virtual bool removePadding(unsigned int blockSize,
			const void * src, std::uint64_t & srcSize) const = 0;
};

/**
 * This class implements the zero padding scheme. In this padding scheme, 1 to
 * blockSize bytes with value zero are added to the end of the data in order to
 * make the data a multiple of blockSize.
 *
 * @since 2018.03.28
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
 */
class IRZeroPadding : public IRPadding {
public:
	IRZeroPadding() = default;

	virtual ~IRZeroPadding() = default;

	virtual bool addPadding(unsigned int blockSize, const void * src,
			std::uint64_t srcSize, void * dst, std::uint64_t & dstSize) const;

	virtual bool removePadding(unsigned int blockSize,
			const void * src, std::uint64_t & srcSize) const;
};


/**
 * This class implements the PKCS #7 (RFC 5652) padding scheme.
 *
 * @since 2018.03.28
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
 */
class IRPKCS7Padding : public IRPadding {
public:
	IRPKCS7Padding() = default;

	virtual ~IRPKCS7Padding() = default;

	virtual bool addPadding(unsigned int blockSize, const void * src,
			std::uint64_t srcSize, void * dst, std::uint64_t & dstSize) const;

	virtual bool removePadding(unsigned int blockSize,
			const void * src, std::uint64_t & srcSize) const;
};

/**
 * This class implements the ANSI X.923 padding scheme.
 *
 * @since 2018.03.28
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
 */
class IRANSIX923Padding : public IRPadding {
public:
	IRANSIX923Padding() = default;

	virtual ~IRANSIX923Padding() = default;

	virtual bool addPadding(unsigned int blockSize, const void * src,
			std::uint64_t srcSize, void * dst, std::uint64_t & dstSize) const;

	virtual bool removePadding(unsigned int blockSize,
			const void * src, std::uint64_t & srcSize) const;
};


/**
 * This class implements the OpenCS random padding
 * (https://github.com/interlockledger/specification/blob/master/crypto/ocs-random-padding.md)
 * and the ISO 10126 padding as well.
 *
 * @since 2018.03.28
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
 */
class IROCSRandomPadding : public IRPadding {
private:
	std::unique_ptr<ircommon::IRRandom> _random;

	bool _iso10126;
public:
	IROCSRandomPadding(ircommon::IRRandom * random, bool iso10126 = false);

	virtual ~IROCSRandomPadding() = default;

	bool iso10126() const {
		return this->_iso10126;
	}

	virtual bool addPadding(unsigned int blockSize, const void * src,
			std::uint64_t srcSize, void * dst, std::uint64_t & dstSize) const;

	virtual bool removePadding(unsigned int blockSize,
			const void * src, std::uint64_t & srcSize) const;
};

} // namespace crypto
} // namespace irecordcore

#endif /* _IRECORDCORE_IRCIPHPD_H_ */
