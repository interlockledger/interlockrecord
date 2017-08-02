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
#include <ilint.h>

#define ILINT_BASE 0xF8

int ILIntSize(uint64_t v) {
	
	if (v < ILINT_BASE) {
		return 1;
	} else if (v < (0xFF + ILINT_BASE)) {
		return 2;
	} else if ( v < (0xFFFF + ILINT_BASE)){
		return 3;
	} else if ( v < (0xFFFFFFl + ILINT_BASE)){
		return 4;
	} else if ( v < (0xFFFFFFFFl + ILINT_BASE)){
		return 5;
	} else if ( v < (0xFFFFFFFFFFl + ILINT_BASE)){
		return 6;
	} else if ( v < (0xFFFFFFFFFFFFl + ILINT_BASE)){
		return 7;
	} else if ( v < (0xFFFFFFFFFFFFFFl + ILINT_BASE)){
		return 8;
	} else {
		return 9;
	}
}

int ILIntEncode(uint64_t v, void * out, int outSize) {
	int size;
	uint8_t * p;
	int i;

	size = ILIntSize(v);
	if (outSize < size) {
		return 0;
	}
	p = (uint8_t *)out;
	if (size == 1) {
		*p = (uint8_t)(v & 0xFF);
	} else {
		*p = ILINT_BASE + (size - 2);
		p++;
		v = v - ILINT_BASE;
		for (i = ((size - 2) * 8); i >= 0; i -=8, p++) {
			*p = (uint8_t)((v >> i) & 0xFF);
		}
	}
	return size;
}

int ILIntDecode(const void * inp, int inpSize, uint64_t * v) {
	const uint8_t * p;
	const uint8_t * pEnd;
	int size;

	if (inpSize <= 0) {
		return 0;
	}
	p = (const uint8_t *) inp;
	size = *p;
	if (size < ILINT_BASE) {
		*v = size;
		return 1;
	} else {
		p++;
		size = size - ILINT_BASE + 1;
		if (inpSize <= size) {
			return 0;
		}
		pEnd = p + size;
		*v = 0;
		for (; p < pEnd; p++) {
			*v = ((*v) << 8) | ((*p) & 0xFF);
		}
		if (*v >= (0xFFFFFFFFFFFFFFFFl - ILINT_BASE)) {
			return 0;
		}
		*v += ILINT_BASE;
		size++;
		if (size != ILIntSize(*v))

		return size;
	}
}

