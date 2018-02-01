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
#ifndef _IRECORDCORE_IRCRYPTO_H_
#define _IRECORDCORE_IRCRYPTO_H_

namespace irecordcore {
namespace crypto {

/**
 * Constants for Hash algorithms.
 *
 * @since 2018.02.01
 */
typedef enum IRHashAlg {
	// From https://devel.opencs.com.br/redmine/projects/interlockledger-docs/wiki/Hash_algorithms
	IR_HASH_SHA1 = 0,
	IR_HASH_SHA256 = 1,
	IR_HASH_SHA512 = 2,
	IR_HASH_SHA3_256 = 3,
	IR_HASH_SHA3_512 = 4,
	IR_HASH_COPY = 0xFFFF
} IRHashAlg;

/**
 * Constants for signature algorithms.
 *
 * @since 2018.02.01
 */
typedef enum IRSignAlg {
	// From https://devel.opencs.com.br/redmine/projects/interlockledger-docs/wiki/Signature_algorithms
	IR_SIG_RSA = 0,
	IR_SIG_RSA_1_5 = 1,
	IR_SIG_DSA = 2,
	IR_SIG_ELGAMAL = 3,
	IR_SIG_ECDSA = 4,
	IR_SIG_EDDSA = 5,
} IRSignAlg;

} //namespace crypto
} //namespace irecordcore

#endif /* _IRECORDCORE_IRCRYPTO_H_ */
