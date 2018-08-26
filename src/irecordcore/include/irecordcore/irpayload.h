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
#ifndef _IRECORDCORE_IRPAYLOAD_H_
#define _IRECORDCORE_IRPAYLOAD_H_

#include <irecordcore/irtypes.h>

namespace irecordcore {
namespace block {

class IRRootBlockPayload {
private:
	std::uint16_t _version;
	std::uint64_t _networkID;
	irecordcore::IRTypedRaw _emergencyKey;
	std::uint64_t _creationTimestamp;
	std::string _friendlyName;
	std::string _ownerName;
	std::string _comments;
	irecordcore::IRTypedRaw _parentId;
public:
	IRRootBlockPayload();

	virtual ~IRRootBlockPayload() = default;

	// Add getters and setters
};

class IRClosingPayload {
private:
	bool _emergency;
	std::uint16_t _version;
	std::uint16_t _reason;
	std::string _comments;
	irecordcore::IRTypedRaw _successorID;
public:

	bool emergency() const {
		return this->_emergency;
	}

	void setEmergency(bool v) {
		this->_emergency = v;
	}

	irecordcore::IRTypedRaw & successorID() {
		return this->_successorID;
	}
};

} // namespace block
} //namespace irecordcore

#endif /* _IRECORDCORE_IRPAYLOAD_H_ */
