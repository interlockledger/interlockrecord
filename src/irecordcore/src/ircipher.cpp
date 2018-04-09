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
#include <irecordcore/ircipher.h>
#include <ircommon/irutils.h>

using namespace irecordcore;
using namespace irecordcore::crypto;

//==============================================================================
// Class IRCipherAlgorithm
//------------------------------------------------------------------------------
bool IRCipherAlgorithm::process(const void * src, std::uint64_t srcSize,
		void * dst, std::uint64_t & dstSize) {
	return false;
}

//==============================================================================
// Class IRBlockCipherAlgorithm
//------------------------------------------------------------------------------
IRBlockCipherAlgorithm::IRBlockCipherAlgorithm(bool cipherMode):
		IRCipherAlgorithm(cipherMode) {
}

//------------------------------------------------------------------------------
unsigned int IRBlockCipherAlgorithm::blockSizeInBytes() const {
	return this->blockSize() / 8;
}

//------------------------------------------------------------------------------
bool IRBlockCipherAlgorithm::setKey(IRSecretKey * key) {
	std::uint64_t rawKeySize;

	if (!key->exportable()) {
		return false;
	}
	rawKeySize = key->sizeInBytes();
	if (rawKeySize == 0) {
		return false;
	}
	ircommon::IRUtils::IRSecureTemp rawKey(rawKeySize);
	if (key->exportKey(rawKey.buff(), rawKeySize)) {
		return this->setKey((const void *)rawKey.buff(), rawKeySize);
	} else {
		return false;
	}
}

//------------------------------------------------------------------------------
