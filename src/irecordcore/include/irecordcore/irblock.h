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
#include <string>

namespace irecordcore {
namespace block {

/**
 * This enumeration defines the record types as defined at
 * https://devel.opencs.com.br/redmine/projects/interlockledger-docs/wiki/ILBlock.
 *
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
 * @since 2018.03.06
 */
typedef enum IRRecordType {
	IR_ROOT_RECORD_TYPE = 0,
	IR_DATA_RECORD_TYPE = 1,
	IR_CLOSING_RECORD_TYPE = 2,
	IR_EMERGENCY_CLOSING_RECORD_TYPE = 3
} IRRecordType;

/**
 * This class implements the DTO that holds the header of a block.
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

	void setVersion(std::uint16_t v) {
		this->_version = v;
	}

	IRRecordType recordType() const {
		return this->_recordType;
	}

	IRTypedRaw & instanceID(){
		return this->_instanceID;
	}

	const IRTypedRaw & instanceID() const {
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

	IRRootBlockPayload();

	virtual ~IRRootBlockPayload() = default;

	std::uint16_t version() const {
		return this->_version;
	}

	void setVersion(std::uint16_t v) {
		this->_version = v;
	}

	std::uint64_t networkID() const {
		return this->_networkID;
	}

	void setNetworkID(std::uint64_t n) {
		this->_networkID = n;
	}

	IRTypedRaw & emergencyKey() {
		return this->_emergencyKey;
	}

	const IRTypedRaw & emergencyKey() const {
		return this->_emergencyKey;
	}

	std::uint64_t creationTimestamp() const {
		return this->_creationTimestamp;
	}

	void setCreationTimestamp(std::uint64_t t) {
		this->_creationTimestamp = t;
	}

	std::string friendlyName() const {
		return this->_friendlyName;
	}

	void setFriendlyName(std::string f) {
		this->_friendlyName = f;
	}

	std::string ownerName() const {
		return this->_ownerName;
	}

	void setOwnerName(std::string o) {
		this->_ownerName = o;
	}

	std::string comments() const {
		return this->_comments;
	}

	void setComments(std::string c) {
		this->_comments = c;
	}

	IRTypedRaw & parentId() {
		return this->_parentId;
	}

	const IRTypedRaw & parentId() const {
		return this->_parentId;
	}

};

class IRClosingPayload {
private:
	std::uint16_t _version;
	bool _emergency;
	std::uint16_t _reason;
	std::string _comments;
	IRTypedRaw _successorId;
public:

	IRClosingPayload();

	virtual ~IRClosingPayload() = default;

	bool emergency() const {
		return this->_emergency;
	}

	void setEmergency(bool e) {
		this->_emergency = e;
	}

	std::uint16_t version() const {
		return this->_version;
	}

	void setVersion(std::uint16_t v) {
		this->_version = v;
	}

	std::uint16_t reason() const {
		return this->_reason;
	}

	void setReason(std::uint16_t r) {
		this->_reason = r;
	}

	std::string comments() const {
		return this->_comments;
	}

	void setComments(std::string c) {
		this->_comments = c;
	}

	IRTypedRaw & successorId() {
		return this->_successorId;
	}

	const IRTypedRaw & successorId() const {
		return this->_successorId;
	}
};

} // namespace block
} //namespace irecordcore

#endif /* _IRECORDCORE_IRBLOCK_H_ */
