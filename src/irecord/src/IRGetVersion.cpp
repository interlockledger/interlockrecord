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
#include <irecord/irecord.h>
#include <irecord/irerr.h>
#include "version.h"
#include <cstring>

//------------------------------------------------------------------------------
IR_EXPORT_ATTR int IR_EXPORT_CALL  IRGetVersion(char * version, int * versionSize) {

	// Check parameters
	if (version == nullptr) {
		return IRE_GET_INVALID_PARAM(0);
	}
	if (versionSize == nullptr) {
		return IRE_GET_INVALID_PARAM(1);
	}

	int len = std::strlen(IRECORD_VERSION_STR);
	if ((len + 1) < *versionSize) {
		std::memcpy(version, IRECORD_VERSION_STR, len + 1);
		
		return IRE_SUCCESS;
	} else {
		return IRE_BUFFER_TOO_SHORT;
	} 
}

//------------------------------------------------------------------------------
IR_EXPORT_ATTR int IR_EXPORT_CALL IRGetVersionInt(int * major, int * minor) {

	if (major == nullptr) {
		return IRE_GET_INVALID_PARAM(0);
	}
	if (minor == nullptr) {
		return IRE_GET_INVALID_PARAM(1);
	}
	*major = IRECORD_VERSION_MAJOR;
	*minor = IRECORD_VERSION_MINOR;
	return IRE_SUCCESS;
}
//------------------------------------------------------------------------------

