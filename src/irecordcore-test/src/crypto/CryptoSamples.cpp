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
#include "CryptoSamples.h"

// Samples generated with:
//	printf "" | openssl sha1 -binary| xxd -g1 -c8
//	printf "Human sacrifice, dogs and cats living together, mass hysteria!" |
//			openssl sha1 -binary| xxd -g1 -c8

const std::uint8_t CRYPTOSAMPLES_SAMPLE[62] = {
		0x48, 0x75, 0x6d, 0x61, 0x6e, 0x20, 0x73, 0x61,
		0x63, 0x72, 0x69, 0x66, 0x69, 0x63, 0x65, 0x2c,
		0x20, 0x64, 0x6f, 0x67, 0x73, 0x20, 0x61, 0x6e,
		0x64, 0x20, 0x63, 0x61, 0x74, 0x73, 0x20, 0x6c,
		0x69, 0x76, 0x69, 0x6e, 0x67, 0x20, 0x74, 0x6f,
		0x67, 0x65, 0x74, 0x68, 0x65, 0x72, 0x2c, 0x20,
		0x6d, 0x61, 0x73, 0x73, 0x20, 0x68, 0x79, 0x73,
		0x74, 0x65, 0x72, 0x69, 0x61, 0x21};

const std::uint8_t CRYPTOSAMPLES_SAMPLE2[134] = {
		0x49, 0x66, 0x20, 0x61, 0x6c, 0x69, 0x65, 0x6e,
		0x73, 0x20, 0x76, 0x69, 0x73, 0x69, 0x74, 0x20,
		0x75, 0x73, 0x2c, 0x20, 0x74, 0x68, 0x65, 0x20,
		0x6f, 0x75, 0x74, 0x63, 0x6f, 0x6d, 0x65, 0x20,
		0x77, 0x6f, 0x75, 0x6c, 0x64, 0x20, 0x62, 0x65,
		0x20, 0x6d, 0x75, 0x63, 0x68, 0x20, 0x61, 0x73,
		0x20, 0x77, 0x68, 0x65, 0x6e, 0x20, 0x43, 0x6f,
		0x6c, 0x75, 0x6d, 0x62, 0x75, 0x73, 0x20, 0x6c,
		0x61, 0x6e, 0x64, 0x65, 0x64, 0x20, 0x69, 0x6e,
		0x20, 0x41, 0x6d, 0x65, 0x72, 0x69, 0x63, 0x61,
		0x2c, 0x20, 0x77, 0x68, 0x69, 0x63, 0x68, 0x20,
		0x64, 0x69, 0x64, 0x6e, 0x27, 0x74, 0x20, 0x74,
		0x75, 0x72, 0x6e, 0x20, 0x6f, 0x75, 0x74, 0x20,
		0x77, 0x65, 0x6c, 0x6c, 0x20, 0x66, 0x6f, 0x72,
		0x20, 0x74, 0x68, 0x65, 0x20, 0x4e, 0x61, 0x74,
		0x69, 0x76, 0x65, 0x20, 0x41, 0x6d, 0x65, 0x72,
		0x69, 0x63, 0x61, 0x6e, 0x73, 0x2e};

const std::uint8_t CRYPTOSAMPLES_SAMPLE3[32] = {
		0x57, 0x68, 0x61, 0x74, 0x20, 0x69, 0x73, 0x20,
		0x79, 0x6f, 0x75, 0x72, 0x20, 0x6d, 0x61, 0x6a,
		0x6f, 0x72, 0x20, 0x6d, 0x61, 0x6c, 0x66, 0x75,
		0x6e, 0x63, 0x74, 0x69, 0x6f, 0x6e, 0x20, 0x3f
};

extern const std::uint8_t CRYPTOSAMPLES_SAMPLE4[30] = {
		0x44, 0x6F, 0x20, 0x6F, 0x72, 0x20, 0x64, 0x6F,
		0x20, 0x6E, 0x6F, 0x74, 0x2E, 0x20, 0x54, 0x68,
		0x65, 0x72, 0x65, 0x20, 0x69, 0x73, 0x20, 0x6E,
		0x6F, 0x20, 0x74, 0x72, 0x79, 0x2E
};

const std::uint8_t CRYPTOSAMPLES_SAMPLE5[40] = {
		0x49, 0x20, 0x61, 0x6D, 0x20, 0x73, 0x65, 0x72,
		0x69, 0x6F, 0x75, 0x73, 0x2E, 0x20, 0x41, 0x6E,
		0x64, 0x20, 0x64, 0x6F, 0x6E, 0x27, 0x74, 0x20,
		0x63, 0x61, 0x6C, 0x6C, 0x20, 0x6D, 0x65, 0x20,
		0x53, 0x68, 0x69, 0x72, 0x6C, 0x65, 0x79, 0x2E
};

const std::uint8_t CRYPTOSAMPLES_KEY128[16] = {
		0x53, 0x69, 0x6d, 0x70, 0x6c, 0x65, 0x2e, 0x2e,
		0x2e, 0x20, 0x6c, 0x6f, 0x67, 0x69, 0x63, 0x2e};

const std::uint8_t CRYPTOSAMPLES_KEY256[32] = {
		0x4b, 0x6f, 0x73, 0x68, 0x3a, 0x20, 0x59, 0x6f,
		0x75, 0x20, 0x68, 0x61, 0x76, 0x65, 0x20, 0x61,
		0x6c, 0x77, 0x61, 0x79, 0x73, 0x20, 0x62, 0x65,
		0x65, 0x6e, 0x20, 0x68, 0x65, 0x72, 0x65, 0x2e};

const std::uint8_t CRYPTOSAMPLES_SHA1_EMPTY[20] = {
		0xda, 0x39, 0xa3, 0xee, 0x5e, 0x6b, 0x4b, 0x0d, 0x32, 0x55,
		0xbf, 0xef, 0x95, 0x60, 0x18, 0x90, 0xaf, 0xd8, 0x07, 0x09};

const std::uint8_t CRYPTOSAMPLES_SHA1_SAMPLE[20] = {
		0x30, 0xb7, 0xb3, 0x2d, 0x08, 0xf2, 0x70, 0xcf, 0xe3, 0x30,
		0x0e, 0xff, 0x12, 0x61, 0xdf, 0x53,	0x45, 0x72, 0x60, 0x34};

const std::uint8_t CRYPTOSAMPLES_SHA256_EMPTY[32] = {
		0xe3, 0xb0, 0xc4, 0x42, 0x98, 0xfc, 0x1c, 0x14,
		0x9a, 0xfb, 0xf4, 0xc8, 0x99, 0x6f, 0xb9, 0x24,
		0x27, 0xae, 0x41, 0xe4, 0x64, 0x9b, 0x93, 0x4c,
		0xa4, 0x95, 0x99, 0x1b, 0x78, 0x52, 0xb8, 0x55};

const std::uint8_t CRYPTOSAMPLES_SHA256_SAMPLE[32] = {
		0x29, 0x62, 0xfe, 0x17, 0x08, 0xf1, 0xd9, 0x21,
		0xa7, 0x55, 0x95, 0xb2, 0xa5, 0x7b, 0x53, 0xb1,
		0x71, 0x30, 0x93, 0x84, 0x16, 0x28, 0xf9, 0xf4,
		0xc8, 0x8b, 0x45, 0x5a, 0xe2, 0x26, 0xe9, 0x8e};

const std::uint8_t CRYPTOSAMPLES_SHA512_EMPTY[64] = {
		0xcf, 0x83, 0xe1, 0x35, 0x7e, 0xef, 0xb8, 0xbd,
		0xf1, 0x54, 0x28, 0x50, 0xd6, 0x6d, 0x80, 0x07,
		0xd6, 0x20, 0xe4, 0x05, 0x0b, 0x57, 0x15, 0xdc,
		0x83, 0xf4, 0xa9, 0x21, 0xd3, 0x6c, 0xe9, 0xce,
		0x47, 0xd0, 0xd1, 0x3c, 0x5d, 0x85, 0xf2, 0xb0,
		0xff, 0x83, 0x18, 0xd2, 0x87, 0x7e, 0xec, 0x2f,
		0x63, 0xb9, 0x31, 0xbd, 0x47, 0x41, 0x7a, 0x81,
		0xa5, 0x38, 0x32, 0x7a, 0xf9, 0x27, 0xda, 0x3e};

const std::uint8_t CRYPTOSAMPLES_SHA512_SAMPLE[64] = {
		0xfe, 0xff, 0x6f, 0xdb, 0x55, 0xed, 0xe1, 0x01,
		0xea, 0x39, 0xc9, 0xa9, 0x49, 0x11, 0xfe, 0x94,
		0xe0, 0xb7, 0x56, 0xa1, 0xf5, 0x58, 0x86, 0x2d,
		0x83, 0x5a, 0x7d, 0xe5, 0x8f, 0x01, 0x67, 0x81,
		0x15, 0xd7, 0x78, 0xb3, 0x1c, 0xaa, 0x1c, 0xd7,
		0xb6, 0x73, 0xba, 0xec, 0x95, 0x7b, 0xcd, 0x5a,
		0x14, 0x64, 0x83, 0xb5, 0xa4, 0x24, 0x66, 0x76,
		0xc8, 0xd8, 0x76, 0x06, 0x84, 0xfa, 0x54, 0xfc};

const std::uint8_t CRYPTOSAMPLES_SHA3_256_EMPTY[32] = {
		0xa7, 0xff, 0xc6, 0xf8, 0xbf, 0x1e, 0xd7, 0x66,
		0x51, 0xc1, 0x47, 0x56, 0xa0, 0x61, 0xd6, 0x62,
		0xf5, 0x80, 0xff, 0x4d, 0xe4, 0x3b, 0x49, 0xfa,
		0x82, 0xd8, 0x0a, 0x4b, 0x80, 0xf8, 0x43, 0x4a};

// TODO Verify it later because it was generated using this code and Botan2.
const std::uint8_t CRYPTOSAMPLES_SHA3_256_SAMPLE[32] = {
		0x1B, 0x41, 0xC1, 0xE6, 0x75, 0x09, 0x79, 0x26,
		0xB5, 0xE4, 0xFC, 0xA1, 0x67, 0xA6, 0x9D, 0x68,
		0x59, 0xEC, 0xC1, 0x71, 0x6E, 0xD5, 0x98, 0x5D,
		0xA8, 0x76, 0x4D, 0x73, 0x6C, 0xAA, 0x77, 0x8E};

const std::uint8_t CRYPTOSAMPLES_SHA3_512_EMPTY[64] = {
		0xa6, 0x9f, 0x73, 0xcc, 0xa2, 0x3a, 0x9a, 0xc5,
		0xc8, 0xb5, 0x67, 0xdc, 0x18, 0x5a, 0x75, 0x6e,
		0x97, 0xc9, 0x82, 0x16, 0x4f, 0xe2, 0x58, 0x59,
		0xe0, 0xd1, 0xdc, 0xc1, 0x47, 0x5c, 0x80, 0xa6,
		0x15, 0xb2, 0x12, 0x3a, 0xf1, 0xf5, 0xf9, 0x4c,
		0x11, 0xe3, 0xe9, 0x40, 0x2c, 0x3a, 0xc5, 0x58,
		0xf5, 0x00, 0x19, 0x9d, 0x95, 0xb6, 0xd3, 0xe3,
		0x01, 0x75, 0x85, 0x86, 0x28, 0x1d, 0xcd, 0x26};

const std::uint8_t CRYPTOSAMPLES_SHA3_512_SAMPLE[64] = {
		0x17, 0xF0, 0xFA, 0xDB, 0x87, 0x85, 0x2F, 0x4C,
		0xB9, 0x30, 0xDB, 0x41, 0x4F, 0x75, 0xD2, 0x24,
		0x3D, 0x28, 0xCA, 0xFF, 0x9B, 0x1A, 0x5E, 0xBB,
		0xDB, 0x00, 0xE5, 0x99, 0x66, 0xDE, 0xB6, 0x1F,
		0x7C, 0x28, 0x6F, 0x2C, 0xE5, 0xF1, 0xDC, 0x00,
		0xA2, 0xA4, 0xA4, 0x45, 0xD4, 0xFF, 0x83, 0x21,
		0x6D, 0x3B, 0x00, 0x4B, 0x95, 0xB8, 0xA7, 0x60,
		0x84, 0x1E, 0x81, 0xE2, 0x7E, 0x67, 0x97, 0x04};

// Generated with:
// printf "" | openssl sha256 -hmac ""
const std::uint8_t CRYPTOSAMPLES_HMAC_SHA1_EMPTY_EMPTY[20] = {
		0xfb, 0xdb, 0x1d, 0x1b, 0x18, 0xaa, 0x6c, 0x08,
		0x32, 0x4b, 0x7d, 0x64, 0xb7, 0x1f, 0xb7, 0x63,
		0x70, 0x69, 0x0e, 0x1d
};

// Generated with:
// printf "" | openssl sha256 -hmac ""
const std::uint8_t CRYPTOSAMPLES_HMAC_SHA256_EMPTY_EMPTY[32] = {
		0xb6, 0x13, 0x67, 0x9a, 0x08, 0x14, 0xd9, 0xec,
		0x77, 0x2f, 0x95, 0xd7, 0x78, 0xc3, 0x5f, 0xc5,
		0xff, 0x16, 0x97, 0xc4, 0x93, 0x71, 0x56, 0x53,
		0xc6, 0xc7, 0x12, 0x14, 0x42, 0x92, 0xc5, 0xad};

const std::uint8_t CRYPTOSAMPLES_HMAC_SHA256_KEY128_EMPTY[32] = {
		0x86, 0xe0, 0xf0, 0x4e, 0xfb, 0xe7, 0xaa, 0xaf,
		0x4f, 0x6c, 0xcb, 0x68, 0x22, 0xac, 0x26, 0x59,
		0x85, 0xda, 0x81, 0xb6, 0x2e, 0x2d, 0x07, 0x2a,
		0xdb, 0x28, 0xdc, 0x77, 0xff, 0x53, 0xf6, 0xdf};

const std::uint8_t CRYPTOSAMPLES_HMAC_SHA256_SAMPLE_EMPTY[32] = {
		0x13, 0xfc, 0x55, 0xc9, 0xe4, 0x8c, 0xa2, 0x23,
		0x08, 0xf1, 0xe5, 0x32, 0xaa, 0x47, 0x0f, 0xa6,
		0x34, 0x9e, 0x88, 0x19, 0x64, 0x89, 0xba, 0x7a,
		0x35, 0x41, 0xe7, 0x82, 0xc8, 0x59, 0x04, 0x97};

// Generated with:
// printf "If aliens visit us, the outcome would be much as when Columbus landed in America, which didn't turn out well for the Native Americans." | openssl sha256 -hmac "Simple... logic."
const std::uint8_t CRYPTOSAMPLES_HMAC_SHA256_KEY128_SAMPLE2[32] = {
		0xd6, 0xd4, 0x58, 0x6f, 0x60, 0x8f, 0xba, 0xaf,
		0x65, 0xf0, 0x56, 0x18, 0xd0, 0xbe, 0x8c, 0xe8,
		0xed, 0xb5, 0xdf, 0x04, 0x1b, 0x39, 0x82, 0xd3,
		0xe4, 0x72, 0x18, 0x81, 0x1f, 0xf2, 0xd0, 0x98};

// Generated with:
// printf "If aliens visit us, the outcome would be much as when Columbus landed in America, which didn't turn out well for the Native Americans." | openssl sha256 -hmac "Human sacrifice, dogs and cats living together, mass hysteria!"
const std::uint8_t CRYPTOSAMPLES_HMAC_SHA256_SAMPLE_SAMPLE2[32] = {
		0x47, 0xed, 0xac, 0xc2, 0x91, 0xcf, 0xcc, 0x25,
		0x67, 0xe6, 0x29, 0xab, 0x21, 0xfb, 0x42, 0xa6,
		0x15, 0x93, 0xdb, 0x13, 0x75, 0x39, 0x48, 0xf1,
		0xb7, 0xf4, 0x88, 0x4c, 0x46, 0xce, 0x7b, 0x55};

// Generated with:
// printf "If aliens visit us, the outcome would be much as when Columbus landed in America, which didn't turn out well for the Native Americans." | openssl sha512 -hmac "Human sacrifice, dogs and cats living together, mass hysteria!"
const std::uint8_t CRYPTOSAMPLES_HMAC_SHA512_SAMPLE_SAMPLE2[64] = {
		0x04, 0x9f, 0x11, 0x6f, 0xdf, 0x71, 0x66, 0x3c,
		0xb3, 0x93, 0x78, 0xd3, 0xa6, 0x62, 0xf7, 0xcd,
		0xb5, 0x83, 0xae, 0xd0, 0x83, 0x56, 0xff, 0xca,
		0x1c, 0x79, 0xda, 0x59, 0x66, 0xa5, 0x26, 0x3d,
		0xfe, 0xe1, 0x2d, 0xc9, 0xa4, 0x8f, 0x85, 0x44,
		0x15, 0x80, 0xd3, 0xb5, 0xb5, 0x8c, 0x10, 0x39,
		0x7b, 0x0c, 0x77, 0xcb, 0x99, 0x0b, 0x25, 0x38,
		0xb5, 0x76, 0x47, 0x8d, 0x61, 0x42, 0x1f, 0x53};

// Generated with ./tools/samples/generate.sh
const std::uint8_t CRYPTOSAMPLES_AES128_ECB[32] = {
		0x64, 0x99, 0x3f, 0x6a, 0x19, 0xf9, 0x47, 0x39,
		0xff, 0xa5, 0x0b, 0xa8, 0x1f, 0xa6, 0xeb, 0x18,
		0x06, 0x19, 0xe8, 0x97, 0xa2, 0xc7, 0x9c, 0xc2,
		0x7a, 0x5e, 0x8b, 0xe5, 0xa1, 0x50, 0x61, 0x6b};

// Generated with ./tools/samples/generate.sh
const std::uint8_t CRYPTOSAMPLES_AES256_ECB[32] = {
		0xed, 0x5c, 0xe3, 0x84, 0x2a, 0xd7, 0x8d, 0xb3,
		0x3f, 0x0e, 0x08, 0x98, 0xc3, 0xbe, 0x8e, 0x21,
		0xd7, 0xb3, 0x16, 0xbb, 0x9e, 0x8a, 0x90, 0x53,
		0x8a, 0x8f, 0xba, 0xc4, 0x11, 0xa5, 0x08, 0x36};

const std::uint8_t CRYPTOSAMPLES_SAMPLE4_PADDED_PKCS7[32] = {
		0x44, 0x6F, 0x20, 0x6F, 0x72, 0x20, 0x64, 0x6F,
		0x20, 0x6E, 0x6F, 0x74, 0x2E, 0x20, 0x54, 0x68,
		0x65, 0x72, 0x65, 0x20, 0x69, 0x73, 0x20, 0x6E,
		0x6F, 0x20, 0x74, 0x72, 0x79, 0x2E, 0x02, 0x02
};

const std::uint8_t CRYPTOSAMPLES_IV_8[8] = {
		0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF
};

const std::uint8_t CRYPTOSAMPLES_SAMPLE4_PADDED_PKCS7_CBC[32] = {
		0x45, 0x4C, 0x65, 0x08, 0xFB, 0x8B, 0xA9, 0x80,
		0x65, 0x22, 0x0A, 0x7C, 0xD5, 0xAB, 0xFD, 0xE8,
		0x00, 0x50, 0x6F, 0x5C, 0xBC, 0xD8, 0xDD, 0x86,
		0x6F, 0x70, 0x1B, 0x2E, 0xC5, 0xF6, 0xDF, 0x84
};
