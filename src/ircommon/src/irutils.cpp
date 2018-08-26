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
#include "ircommon/irutils.h"

#include <cstring>
#ifdef _WIN32
#include <windows.h>
#else
#include <sys/mman.h>
#endif // _WIN32

namespace ircommon {
namespace IRUtils {

//==============================================================================
// IRUtils
//------------------------------------------------------------------------------
void clearMemory(void * buff, std::uint64_t buffSize) {
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
bool lockMemory(void * addr, std::uint64_t size) {
#ifdef _WIN32
	return (VirtualLock(addr, size) == TRUE);
#else
	return (mlock(addr, size) == 0);
#endif //_WIN32
}

//------------------------------------------------------------------------------
bool unlockMemory(void * addr, std::uint64_t size) {
#ifdef _WIN32
	return (VirtualUnlock(addr, size) == TRUE);
#else
	return (munlock(addr, size) == 0);
#endif //_WIN32
}

//------------------------------------------------------------------------------

} //namespace IRUtils
} //namespace ircommon
