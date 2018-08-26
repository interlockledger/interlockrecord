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
	// From https://github.com/interlockledger/specification/blob/master/crypto/hash.md
	IR_HASH_SHA1 = 0,
	IR_HASH_SHA256 = 1,
	IR_HASH_SHA512 = 2,
	IR_HASH_SHA3_256 = 3,
	IR_HASH_SHA3_512 = 4,
	IR_HASH_SHA224 = 5,
	IR_HASH_SHA384 = 6,
	IR_HASH_SHA3_224 = 7,
	IR_HASH_SHA3_384 = 8,
	IR_WHIRLPOOL = 9,
	IR_RIPEMD_160 = 10,
	IR_HASH_COPY = 0xFFFF
} IRHashAlg;

/**
 * Constants for signature algorithms.
 *
 * @since 2018.02.01
 */
typedef enum IRSignAlg {
	// From https://github.com/interlockledger/specification/blob/master/crypto/dsign.md
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
