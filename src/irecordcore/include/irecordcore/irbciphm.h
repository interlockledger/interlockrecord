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
#ifndef _IRECORDCORE_IRBCIPHM_H_
#define _IRECORDCORE_IRBCIPHM_H_

#include <memory>
#include <ircommon/irutils.h>
#include <irecordcore/ircipher.h>
#include <irecordcore/irciphpd.h>

namespace irecordcore {
namespace crypto {

class IRBlockCipherMode {
protected:
	std::unique_ptr<IRPadding> _padding;

	std::unique_ptr<IRBlockCipherAlgorithm> _cipher;

	unsigned int _blockSize;

	ircommon::IRUtils::IRSecureTemp _block;

	bool processBlock(const void * src, void * dst) = 0;
public:
	IRBlockCipherMode(IRPadding * padding, IRBlockCipherAlgorithm * cipher);

	virtual ~IRBlockCipherMode() = default;

	std::uint64_t getOutputSize(std::uint64_t srcSize) const;

	/**
	 * Process a chunk of data.
	 *
	 * @param[in] src The data to be processed.
	 * @param[in] srcSize The size of src in bytes.
	 * @param[out] dst The output.
	 * @param[in,out] dstSrc On input, it is the size of dst. On output, it is
	 * the actual size of the output.
	 * @return true on success or false otherwise.
	 */
	bool process(const void * src, std::uint64_t srcSize, void * dst,
			std::uint64_t & dstSize);

	bool finalize(const void * src, std::uint64_t srcSize, void * dst,
			std::uint64_t & dstSize);
};

} // namespace crypto
} // namespace irecordcore

#endif /* _IRECORDCORE_IRBCIPHM_H_ */