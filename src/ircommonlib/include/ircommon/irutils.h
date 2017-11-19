/*
 * Copyright (c) 2017, Open Communications Security
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
#ifndef INCLUDE_IRUTILS_IRBUFFER_H_
#define INCLUDE_IRUTILS_IRBUFFER_H_

namespace ircommon {

/**
 * @namespace ircommon::IRUtils
 * Utility functions used by this library.
 */
namespace IRUtils {

/**
 * Returns the number of bytes to add to a buffer in order to make it
 * a multiple of a given block size.
 *
 * @param[in] buffSize The data size.
 * @param[in] blockSize The block size. Must be a value larger than 0.
 * @return The size of the padding. This value will always be a value between 1 and blockSize.
 * @tparam UINT_TYPE  An unsigned integer type.
 * @since 2017.11.18
 */
template < class UINT_TYPE >
UINT_TYPE getPaddingSize(UINT_TYPE buffSize, UINT_TYPE blockSize) {
	return blockSize - (buffSize % blockSize);
}

/**
 * Returns the new buffer size that makes it a multiple of a given block size. The returned value
 * is guaranteed to be larger than buffSize.
 *
 * @param[in] buffSize The data size.
 * @param[in] blockSize The block size. Must be a value larger than 0.
 * @return The new size of the buffer. It will always be larger than buffSize.
 * @tparam UINT_TYPE  An unsigned integer type.
 * @since 2017.11.18
 */
template < class UINT_TYPE >
UINT_TYPE  getPaddedSize(UINT_TYPE  buffSize, UINT_TYPE  blockSize) {
	return buffSize + getPaddingSize(buffSize, blockSize);
}

/**
 * Returns the new buffer size that makes it a multiple of a given block size. The returned value
 * is guaranteed to be equal or larger than buffSize.
 *
 * @param[in] buffSize The data size.
 * @param[in] blockSize The block size. Must be a value larger than 0.
 * @return The new size of the buffer. It will always be equal or larger than buffSize.
 * @tparam UINT_TYPE  An unsigned integer type.
 * @since 2017.11.18
 */
template < class UINT_TYPE >
UINT_TYPE  getPaddedSizeBestFit(UINT_TYPE  buffSize, UINT_TYPE  blockSize) {
	UINT_TYPE paddingSize;

	paddingSize = getPaddingSize(buffSize, blockSize);
	if (paddingSize == blockSize) {
		paddingSize = 0;
	}
	return buffSize + paddingSize;
}

} // namespace IRUtils

} //namespace ircommon

#endif /* INCLUDE_IRUTILS_IRBUFFER_H_ */
