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
