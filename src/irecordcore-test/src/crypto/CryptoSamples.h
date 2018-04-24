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
#ifndef _CRYPTO_CRYPTOSAMPLES_H_
#define _CRYPTO_CRYPTOSAMPLES_H_

#include <cstdint>

/**
 * "Human sacrifice, dogs and cats living together, mass hysteria!"
 * Peter Venkman
 */
extern const std::uint8_t CRYPTOSAMPLES_SAMPLE[62];

/**
 * "If aliens visit us, the outcome would be much as when Columbus landed in
 * America, which didn't turn out well for the Native Americans."
 * Stephen Hawking (1942–2018)
 */
extern const std::uint8_t CRYPTOSAMPLES_SAMPLE2[134];

/**
 * "What is your major malfunction ?"
 * Gunnery Sgt. Hartman
 */
extern const std::uint8_t CRYPTOSAMPLES_SAMPLE3[32];

/**
 * "Do or do not. There is no try."
 * Yoda
 */
extern const std::uint8_t CRYPTOSAMPLES_SAMPLE4[30];

/**
 * "I am serious. And don't call me Shirley."
 * Dr. Rumack
 */
extern const std::uint8_t CRYPTOSAMPLES_SAMPLE5[40];

/**
 * "Simple... logic."
 * Spock
 */
extern const std::uint8_t CRYPTOSAMPLES_KEY128[16];

/**
 * "Kosh: You have always been here."
 */
extern const std::uint8_t CRYPTOSAMPLES_KEY256[32];

/**
 * SHA1 of empty.
 */
extern const std::uint8_t CRYPTOSAMPLES_SHA1_EMPTY[20];

/**
 * SHA1 of CRYPTOSAMPLES_SAMPLE.
 */
extern const std::uint8_t CRYPTOSAMPLES_SHA1_SAMPLE[20];

/**
 * SHA256 of empty.
 */
extern const std::uint8_t CRYPTOSAMPLES_SHA256_EMPTY[32];

/**
 * SHA256 of CRYPTOSAMPLES_SAMPLE.
 */
extern const std::uint8_t CRYPTOSAMPLES_SHA256_SAMPLE[32];

/**
 * SHA512 of empty.
 */
extern const std::uint8_t CRYPTOSAMPLES_SHA512_EMPTY[64];

/**
 * SHA512 of CRYPTOSAMPLES_SAMPLE.
 */
extern const std::uint8_t CRYPTOSAMPLES_SHA512_SAMPLE[64];

/**
 * SHA3-256 of empty.
 */
extern const std::uint8_t CRYPTOSAMPLES_SHA3_256_EMPTY[32];

/**
 * SHA3-256 of CRYPTOSAMPLES_SAMPLE.
 */
extern const std::uint8_t CRYPTOSAMPLES_SHA3_256_SAMPLE[32];

/**
 * SHA3-512 of empty.
 */
extern const std::uint8_t CRYPTOSAMPLES_SHA3_512_EMPTY[64];

/**
 * SHA3-512 of CRYPTOSAMPLES_SAMPLE.
 */
extern const std::uint8_t CRYPTOSAMPLES_SHA3_512_SAMPLE[64];

/**
 * HMAC-SHA1("", "")
 */
extern const std::uint8_t CRYPTOSAMPLES_HMAC_SHA1_EMPTY_EMPTY[20];

/**
 * HMAC-SHA256("", "")
 */
extern const std::uint8_t CRYPTOSAMPLES_HMAC_SHA256_EMPTY_EMPTY[32];

/**
 * HMAC-SHA256(CRYPTOSAMPLES_KEY128, "")
 */
extern const std::uint8_t CRYPTOSAMPLES_HMAC_SHA256_KEY128_EMPTY[32];

/**
 * HMAC-SHA256(CRYPTOSAMPLES_SAMPLE, "")
 */
extern const std::uint8_t CRYPTOSAMPLES_HMAC_SHA256_SAMPLE_EMPTY[32];

/**
 * HMAC-SHA256(CRYPTOSAMPLES_KEY128, CRYPTOSAMPLES_SAMPLE2)
 */
extern const std::uint8_t CRYPTOSAMPLES_HMAC_SHA256_KEY128_SAMPLE2[32];

/**
 * HMAC-SHA256(CRYPTOSAMPLES_SAMPLE, CRYPTOSAMPLES_SAMPLE2)
 */
extern const std::uint8_t CRYPTOSAMPLES_HMAC_SHA256_SAMPLE_SAMPLE2[32];

/**
 * HMAC-SHA512(CRYPTOSAMPLES_SAMPLE, CRYPTOSAMPLES_SAMPLE2)
 */
extern const std::uint8_t CRYPTOSAMPLES_HMAC_SHA512_SAMPLE_SAMPLE2[64];

/**
 * AES128(CRYPTOSAMPLES_KEY128, CRYPTOSAMPLES_KEY256)
 */
extern const std::uint8_t CRYPTOSAMPLES_AES128_ECB[32];

/**
 * AES128(CRYPTOSAMPLES_KEY256, CRYPTOSAMPLES_KEY256)
 */
extern const std::uint8_t CRYPTOSAMPLES_AES256_ECB[32];

/**
 * CRYPTOSAMPLES_SAMPLE4 padded with PKCS7 scheme and block size as 8 bytes.
 */
extern const std::uint8_t CRYPTOSAMPLES_SAMPLE4_PADDED_PKCS7[32];

/**
 * 8-byte IV sample (0123456789ABCDEF).
 */
extern const std::uint8_t CRYPTOSAMPLES_IV_8[8];

/**
 * CRYPTOSAMPLES_SAMPLE4 padded with PKCS7 scheme with block size as 8 bytes
 * encoded with a null cipher using CBC mode and CRYPTOSAMPLES_IV_8 as IV.
 */
extern const std::uint8_t CRYPTOSAMPLES_SAMPLE4_PADDED_PKCS7_CBC[32];

#endif /* _CRYPTO_CRYPTOSAMPLES_H_ */
