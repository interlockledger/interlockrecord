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
#include "ircommon/irutils.h"

#include <cstring>
#ifdef _WIN32
#include <windows.h>
#endif // _WIN32

namespace ircommon {
namespace IRUtils {

//==============================================================================
// IRUtils
//------------------------------------------------------------------------------
void clearMemory(std::uint64_t buffSize, void * buff) {
	if (buff) {
#ifdef _WIN32
		SecureZeroMemory(buff, buffSize);
#else
		// This code was tested with GCC (-O4) and CLANG (-O3) and is guaranteed
		// to remain untouched.
		volatile std::uint8_t * p = (volatile std::uint8_t *)buff;
		volatile std::uint8_t * pEnd = p + buffSize;
		for (;p < pEnd; p++) {
			(*p) = 0;
		}
#endif //__WIN32
	}
}

//------------------------------------------------------------------------------

} //namespace IRUtils
} //namespace ircommon
