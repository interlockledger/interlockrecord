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
	 * @param[in] blockSize The size of the block.
	 * @param[in] srcSize The size of the data.
	 * @return The size of the padding.
	 */
	virtual std::uint64_t getPaddingSize(unsigned int blockSize,
			std::uint64_t srcSize) const = 0;

	/**
	 * Returns the size of the padded data based on the block size and the
	 * data size. This method always returns the sum of srcSize and the
	 * result of getPaddingSize(unsigned int,std::uint64_t).
	 *
	 * @param[in] blockSize The size of the block.
	 * @param[in] srcSize The size of the data to be padded.
	 * @return The size of the padded data.
	 * @see IRPadding::getPaddingSize(unsigned int,std::uint64_t) const
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
 * This abstract class implements some of the basic rules for most of the block
 * padding schemes.
 *
 * @since 2018.04.02
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
 */
class IRBasicPadding : public IRPadding {
protected:
	/**
	 * This method is called by addPadding() to create the actual padding value.
	 *
	 * @param[in] blockSize The size of the block.
	 * @param[out] padding The padding data.
	 * @param[in] paddingSize The size of the padding.
	 */
	virtual void createPadding(unsigned int blockSize, std::uint8_t * padding,
			unsigned int paddingSize) const = 0;

	/**
	 * This method is called by removePadding() to extracts the size of the
	 * padding from the message.
	 *
	 * <p>It is important to notice that, before this method is called, the
	 * following preverifications where already performed:</p>
	 *
	 *   - The srcSize is a multiple of blockSize and is larger than 0;
	 *
	 * <p>The default implementation extracts the size of the padding from the
	 * last byte of the message. It fails if the last byte is either 0 or assumes
	 * a value larger than blockSize.</p>
	 *
	 * @param[in] blockSize The size of the block.
	 * @param[in] src The source.
	 * @param[in] srcSize The size of the source.
	 * @returns The padding size or 0 if the padding size could not be
	 * determined.
	 */
	virtual unsigned int extractPaddingSize(unsigned int blockSize,
			const std::uint8_t * src,
			std::uint64_t srcSize) const;

	/**
	 * This method is called by removePadding() to verify the integrty of the
	 * padding data. The default implementation always return true and must be
	 * overridden whenever necessary.
	 *
	 * @param[in] padding The padding value.
	 * @param[in] paddingSize The size of the padding.
	 * @return true if the padding data is correct or false otherwise.
	 */
	virtual bool checkPadding(const std::uint8_t * padding,
			unsigned int paddingSize) const;
public:
	IRBasicPadding() = default;

	virtual ~IRBasicPadding() = default;

	/**
	 * Returns the size of the padding based on the block size and the data
	 * size.
	 *
	 * <p>This implementation will always return a value between 1 and
	 * blockSize.</p>
	 *
	 * @param[in] blockSize The size of the block.
	 * @param[in] srcSize The size of the data.
	 * @return The size of the padding.
	 */
	virtual std::uint64_t getPaddingSize(unsigned int blockSize,
			std::uint64_t srcSize) const;

	virtual bool addPadding(unsigned int blockSize, const void * src,
			std::uint64_t srcSize, void * dst, std::uint64_t & dstSize) const;

	virtual bool removePadding(unsigned int blockSize,
			const void * src, std::uint64_t & srcSize) const;
};

/**
 * This class implements the zero padding scheme. In this padding scheme, 1 to
 * blockSize bytes with value zero are added to the end of the data in order to
 * make the data a multiple of blockSize.
 *
 * @since 2018.03.28
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
 */
class IRZeroPadding : public IRBasicPadding {
protected:
	virtual void createPadding(unsigned int blockSize, std::uint8_t * padding,
			unsigned int paddingSize) const;

	virtual unsigned int extractPaddingSize(unsigned int blockSize,
			const std::uint8_t * src,
			std::uint64_t srcSize) const;
public:
	IRZeroPadding() = default;

	virtual ~IRZeroPadding() = default;
};


/**
 * This class implements the PKCS #7 (RFC 5652) padding scheme.
 *
 * @since 2018.03.28
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
 */
class IRPKCS7Padding : public IRBasicPadding {
protected:
	virtual void createPadding(unsigned int blockSize, std::uint8_t * padding,
			unsigned int paddingSize) const;

	virtual bool checkPadding(const std::uint8_t * padding,
			unsigned int paddingSize) const;
public:
	IRPKCS7Padding() = default;

	virtual ~IRPKCS7Padding() = default;
};

/**
 * This class implements the ANSI X.923 padding scheme.
 *
 * @since 2018.03.28
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
 */
class IRANSIX923Padding : public IRBasicPadding {
protected:
	virtual void createPadding(unsigned int blockSize, std::uint8_t * padding,
			unsigned int paddingSize) const;

	virtual bool checkPadding(const std::uint8_t * padding,
			unsigned int paddingSize) const;
public:
	IRANSIX923Padding() = default;

	virtual ~IRANSIX923Padding() = default;
};

/**
 * This class implements the ISO 10126 padding.
 *
 * @since 2018.03.28
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
 */
class IRISO10126Padding : public IRBasicPadding {
protected:
	std::unique_ptr<ircommon::IRRandom> _random;

	virtual void createPadding(unsigned int blockSize, std::uint8_t * padding,
			unsigned int paddingSize) const;
public:
	IRISO10126Padding(ircommon::IRRandom * random);

	virtual ~IRISO10126Padding() = default;
};

/**
 * This class implements the OpenCS random padding
 * (https://github.com/interlockledger/specification/blob/master/crypto/ocs-random-padding.md).
 *
 * @since 2018.03.28
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
 */
class IROCSRandomPadding : public IRISO10126Padding {
protected:
	virtual void createPadding(unsigned int blockSize, std::uint8_t * padding,
			unsigned int paddingSize) const;

	virtual unsigned int extractPaddingSize(unsigned int blockSize,
			const std::uint8_t * src,
			std::uint64_t srcSize) const;
public:
	IROCSRandomPadding(ircommon::IRRandom * random);

	virtual ~IROCSRandomPadding() = default;
};

} // namespace crypto
} // namespace irecordcore

#endif /* _IRECORDCORE_IRCIPHPD_H_ */
