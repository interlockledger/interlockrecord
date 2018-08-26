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
