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
#include "CryptoSamples.h"

const std::uint8_t CRYPTOSAMPLES_SAMPLE[62] = {
		0x48, 0x75, 0x6d, 0x61, 0x6e, 0x20, 0x73, 0x61,
		0x63, 0x72, 0x69, 0x66, 0x69, 0x63, 0x65, 0x2c,
		0x20, 0x64, 0x6f, 0x67, 0x73, 0x20, 0x61, 0x6e,
		0x64, 0x20, 0x63, 0x61, 0x74, 0x73, 0x20, 0x6c,
		0x69, 0x76, 0x69, 0x6e, 0x67, 0x20, 0x74, 0x6f,
		0x67, 0x65, 0x74, 0x68, 0x65, 0x72, 0x2c, 0x20,
		0x6d, 0x61, 0x73, 0x73, 0x20, 0x68, 0x79, 0x73,
		0x74, 0x65, 0x72, 0x69, 0x61, 0x21};


const std::uint8_t CRYPTOSAMPLES_SHA1_EMPTY[20] = {
		0xda, 0x39, 0xa3, 0xee, 0x5e, 0x6b, 0x4b, 0x0d, 0x32, 0x55,
		0xbf, 0xef, 0x95, 0x60, 0x18, 0x90, 0xaf, 0xd8, 0x07, 0x09};

// SHA1 of CRYPTOSAMPLES_SAMPLE
// Samples generated with:
//		printf "Human sacrifice, dogs and cats living together, mass hysteria!" | openssl sha1 -binary| xxd -g1
const std::uint8_t CRYPTOSAMPLES_SHA1_SAMPLE[20] = {
		0x30, 0xb7, 0xb3, 0x2d, 0x08, 0xf2, 0x70, 0xcf, 0xe3, 0x30,
		0x0e, 0xff, 0x12, 0x61, 0xdf, 0x53,	0x45, 0x72, 0x60, 0x34};


