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
 * @author Cesar Luiz Ferracin (cferraz at opencs.com.br)
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

	/**
	* Returns the version number.
	*
	* @return the version number.
	*/
	std::uint16_t version() const {
		return this->_version;
	}

	/**
	* Set the version number.
	*/
	void setVersion(std::uint16_t v) {
		this->_version = v;
	}

	/**
	* Returns the record type.
	*
	* @return the record type.
	*/
	IRRecordType recordType() const {
		return this->_recordType;
	}

	/**
	* Returns the instance ID for read/write.
	*
	* @return the instance ID for read/write.
	*/
	IRTypedRaw & instanceID(){
		return this->_instanceID;
	}

	/**
	* Returns the instance ID for read.
	*
	* @return the instance ID for read.
	*/
	const IRTypedRaw & instanceID() const {
		return this->_instanceID;
	}

	/**
	* Returns the block serial.
	*
	* @return the block serial.
	*/
	std::uint64_t blockSerial() const {
		return this->_blockSerial;
	}

	/**
	* Set the block serial.
	*/
	void setBlockSerial(std::uint64_t v){
		this->_blockSerial = v;
	}

	/**
	* Returns the block offset.
	*
	* @return the block offset.
	*/
	std::uint64_t blockOffset() const {
		return this->_blockOffset;
	}

	/**
	* Set the block offset.
	*/
	void setBlockOffset(std::uint64_t v)  {
		this->_blockOffset = v;
	}

	/**
	* Returns the parent block offset.
	*
	* @return the parent block offset.
	*/
	std::uint64_t parentBlockOffset() const {
		return this->_parentBlockOffset;
	}

	/**
	* Set the parent block offset.
	*/
	void setParentBlockOffset(std::uint64_t v) {
		this->_parentBlockOffset = v;
	}

	/**
	* Returns the application ID.
	*
	* @return the application ID.
	*/
	std::uint64_t applicationID() const {
		return this->_applicationID;
	}

	/**
	* Set the application ID.
	*/
	void setApplicationID(std::uint64_t v){
		this->_applicationID = v;
	}

	/**
	* Returns the timestamp.
	*
	* @return the timestamp.
	*/
	std::uint64_t timestamp() const {
		return this->_timestamp;
	}

	/**
	* Set the timestamp.
	*/
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

	/**
	* Returns the version number.
	*
	* @return the version number.
	*/
	std::uint16_t version() const {
		return this->_version;
	}

	/**
	* Set the version number.
	*/
	void setVersion(std::uint16_t v) {
		this->_version = v;
	}

	/**
	* Returns the network ID.
	*
	* @return the network ID.
	*/
	std::uint64_t networkID() const {
		return this->_networkID;
	}

	/**
	* Set the network ID.
	*/
	void setNetworkID(std::uint64_t n) {
		this->_networkID = n;
	}

	/**
	* Returns the emergency Key for read/write.
	*
	* @return the emergency Key for read/write.
	*/
	IRTypedRaw & emergencyKey() {
		return this->_emergencyKey;
	}

	/**
	* Returns the emergency Key for read.
	*
	* @return the emergency Key for read.
	*/
	const IRTypedRaw & emergencyKey() const {
		return this->_emergencyKey;
	}

	/**
	* Returns the creation timestamp.
	*
	* @return the creation timestamp.
	*/
	std::uint64_t creationTimestamp() const {
		return this->_creationTimestamp;
	}

	/**
	* Set the creation timestamp.
	*/
	void setCreationTimestamp(std::uint64_t t) {
		this->_creationTimestamp = t;
	}

	/**
	* Returns the friendly name.
	*
	* @return the friendly name.
	*/
	std::string friendlyName() const {
		return this->_friendlyName;
	}

	/**
	* Set the network friendly name.
	*/
	void setFriendlyName(std::string f) {
		this->_friendlyName = f;
	}

	/**
	* Returns the owner name.
	*
	* @return the owner name.
	*/
	std::string ownerName() const {
		return this->_ownerName;
	}

	/**
	* Set the owner name.
	*/
	void setOwnerName(std::string o) {
		this->_ownerName = o;
	}

	/**
	* Returns the comments.
	*
	* @return the comments.
	*/
	std::string comments() const {
		return this->_comments;
	}

	/**
	* Set the comments.
	*/
	void setComments(std::string c) {
		this->_comments = c;
	}

	/**
	* Returns the parent id for read/write.
	*
	* @return the parent id for read/write.
	*/
	IRTypedRaw & parentId() {
		return this->_parentId;
	}

	/**
	* Returns the parent id for read.
	*
	* @return the parent id for read.
	*/
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

	/**
	* Returns the emergency.
	*
	* @return the emergency.
	*/
	bool emergency() const {
		return this->_emergency;
	}

	/**
	* Set the emergency.
	*/
	void setEmergency(bool e) {
		this->_emergency = e;
	}

	/**
	* Returns the version.
	*
	* @return the version.
	*/
	std::uint16_t version() const {
		return this->_version;
	}

	/**
	* Set the version.
	*/
	void setVersion(std::uint16_t v) {
		this->_version = v;
	}

	/**
	* Returns the reason.
	*
	* @return the reason.
	*/
	std::uint16_t reason() const {
		return this->_reason;
	}

	/**
	* Set the reason.
	*/
	void setReason(std::uint16_t r) {
		this->_reason = r;
	}

	/**
	* Returns the comments.
	*
	* @return the comments.
	*/
	std::string comments() const {
		return this->_comments;
	}

	/**
	* Set the comments.
	*/
	void setComments(std::string c) {
		this->_comments = c;
	}

	/**
	* Returns the successor id for read/write.
	*
	* @return the successor id for read/write.
	*/
	IRTypedRaw & successorId() {
		return this->_successorId;
	}

	/**
	* Returns the successor id for read.
	*
	* @return the successor id for read.
	*/
	const IRTypedRaw & successorId() const {
		return this->_successorId;
	}
};

} // namespace block
} //namespace irecordcore

#endif /* _IRECORDCORE_IRBLOCK_H_ */
