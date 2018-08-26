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
#include "ircommon/ilint.h"

using namespace ircommon;

//==============================================================================
// Class ILInt
//------------------------------------------------------------------------------
int ILInt::size(uint64_t v) {

	if (v < ILINT_BASE) {
		return 1;
	} else if (v <= (0xFF + ILINT_BASE)) {
		return 2;
	} else if ( v <= (0xFFFF + ILINT_BASE)){
		return 3;
	} else if ( v <= (0xFFFFFFl + ILINT_BASE)){
		return 4;
	} else if ( v <= (0xFFFFFFFFll + ILINT_BASE)){
		return 5;
	} else if ( v <= (0xFFFFFFFFFFll + ILINT_BASE)){
		return 6;
	} else if ( v <= (0xFFFFFFFFFFFFll + ILINT_BASE)){
		return 7;
	} else if ( v <= (0xFFFFFFFFFFFFFFll + ILINT_BASE)){
		return 8;
	} else {
		return 9;
	}
}

//------------------------------------------------------------------------------
int ILInt::encode(uint64_t v, void * out, int outSize) {
	int size;
	uint8_t * p;
	int i;

	size = ILInt::size(v);
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

//------------------------------------------------------------------------------
int ILInt::decode(const void * inp, int inpSize, uint64_t * v) {
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
		if (*v > (0xFFFFFFFFFFFFFFFFll - ILINT_BASE)) {
			return 0;
		}
		*v += ILINT_BASE;
		size++;
		return size;
	}
}
//------------------------------------------------------------------------------
