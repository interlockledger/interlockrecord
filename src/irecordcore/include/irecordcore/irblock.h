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
#ifndef _IRECORDCORE_IRBLOCK_H_
#define _IRECORDCORE_IRBLOCK_H_

#include <irecordcore/irtypes.h>

namespace irecordcore {
namespace block {

typedef enum IRRecordType {
	IR_ROOT_RECORD_TYPE = 0,
	IR_DATA_RECORD_TYPE = 1,
	IR_CLOSING_RECORD_TYPE = 2,
	IR_EMERGENCY_CLOSING_RECORD_TYPE = 3
} IRRecordType;

/**
 * This class implements the header of a block.
 *
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
 * @since 2018.02.17
 */
class IRBlockHeader {
private:
	std::uint16_t _version;
	IRRecordType _recordType;
	irecordcore::IRTypedRaw _instanceID;
	std::uint64_t _blockSerial;
	std::uint64_t _blockOffset;
	std::uint64_t _parentBlockOffset;
	std::uint64_t _applicationID;
	std::uint64_t _timestamp;
public:
	IRBlockHeader();

	virtual ~IRBlockHeader() = default;

	std::uint16_t version() const {
		return this->_version;
	}

	IRRecordType recordType() const {
		return this->_recordType;
	}

	IRTypedRaw & instanceID(){
		return this->_instanceID;
	}

	std::uint64_t blockSerial() const {
		return this->_blockSerial;
	}

	void setBlockSerial(std::uint64_t v){
		this->_blockSerial = v;
	}

	std::uint64_t blockOffset() const {
		return this->_blockOffset;
	}

	void setBlockOffset(std::uint64_t v)  {
		this->_blockOffset = v;
	}

	std::uint64_t parentBlockOffset() const {
		return this->_parentBlockOffset;
	}

	void setParentBlockOffset(std::uint64_t v) {
		this->_parentBlockOffset = v;
	}

	std::uint64_t applicationID() const {
		return this->_applicationID;
	}

	void setApplicationID(std::uint64_t v){
		this->_applicationID = v;
	}

	std::uint64_t timestamp() const {
		return this->_timestamp;
	}

	void setTimestamp(std::uint64_t v) {
		this->_timestamp = v;
	}
};

class IRPayload {

};

class IRRootBlockPayload{
private:
	std::uint16_t _version;
	std::uint64_t _networkID;
	IRTypedRaw _emergencyKey;
	std::uint64_t _creationTimestamp;
	std::string _friendlyName;
	std::string _ownerName;
	std::string _comments;
	IRTypedRaw _parentId;
public:

};

class IRClosingPayload {
private:
	bool _emergency;
	std::uint16_t _version;
	std::uint16_t _reason;
	std::string _comments;
	IRTypedRaw _successorId;
public:

};


} // namespace block
} //namespace irecordcore

#endif /* _IRECORDCORE_IRBLOCK_H_ */
