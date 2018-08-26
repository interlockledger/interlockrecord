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
#include <irecordcore/irblock.h>

using namespace irecordcore;
using namespace irecordcore::block;

//==============================================================================
// Class IRBlockHeader
//------------------------------------------------------------------------------
IRBlockHeader::IRBlockHeader(): _version(0), _recordType(IR_ROOT_RECORD_TYPE), 
	_instanceID(64), _blockSerial(0), _blockOffset(0), _parentBlockOffset(0), 
	_applicationID(0), _timestamp(0) {
}

//==============================================================================
// Class IRRootBlockPayload
//------------------------------------------------------------------------------
IRRootBlockPayload::IRRootBlockPayload(): _version(0), _networkID(0),
	_emergencyKey(64), _creationTimestamp(0), _friendlyName(""),
	_ownerName(""), _comments(""), _parentId(64) {
}

//==============================================================================
// Class IRClosingPayload
//------------------------------------------------------------------------------
IRClosingPayload::IRClosingPayload() : _version(0), _emergency(false),
		_reason(0), _comments(""), _successorId(64) {
}
//------------------------------------------------------------------------------
