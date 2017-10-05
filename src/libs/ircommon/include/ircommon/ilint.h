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
#ifndef __ILCOMMON_ILINT_H__
#define __ILCOMMON_ILINT_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif //__cplusplus

/**
 * Returns the number of bytes required to encode the given value.
 *
 * @param[in] v The value to be encoded.
 * @return The number of bytes required to store the value.
 */
int ILIntSize(uint64_t v);

/**
 * Encodes the value v into the ILInt value.
 *
 * @param[in] v The value.
 * @param[out] out The output buffer.
 * @param[in] outSize The number of bytes in out.
 * @return The number of bytes used or 0 in case of failure.
 */
int ILIntEncode(uint64_t v, void * out, int outSize);

/**
 * Decodes the ILInt values.
 *
 * @param[in] inp The value to be decoded.
 * @param[in] inpSize The size of inp.
 * @param[out] v The output value.
 * @return The number of bytes read from inp or 0 in case of failure.
 */
int ILIntDecode(const void * inp, int inpSize, uint64_t * v);

#ifdef __cplusplus
} // extern "C"
#endif //__cplusplus

#endif //__ILCOMMON_ILINT_H__

