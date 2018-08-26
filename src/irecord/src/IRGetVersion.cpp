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
#include <irecord/irecord.h>
#include <irecord/irerr.h>
#include "version.h"
#include <cstring>

//------------------------------------------------------------------------------
IR_EXPORT_ATTR int IR_EXPORT_CALL  IRGetVersion(int * versionSize, char * version) {

	// Check parameters
	if (versionSize == nullptr) {
		return IRE_INVALID_PARAM_01;
	}
	if (!version) {
		*versionSize = -1;
	}

	int len = std::strlen(IRECORD_VERSION_STR) + 1;
	if (len <= *versionSize) {
		std::memcpy(version, IRECORD_VERSION_STR, len);
		*versionSize = len;
		return IRE_SUCCESS;
	} else {
		*versionSize = len;
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

