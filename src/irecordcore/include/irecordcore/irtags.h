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
#ifndef _IRECORDCORE_IRTAGS_H_
#define _IRECORDCORE_IRTAGS_H_

#include <ircommon/iltag.h>
#include <ircommon/iltagstd.h>

namespace irecordcore {
namespace tags {

/**
 * Tag IDs defined by the InterlockRecord.
 *
 * @since 2018.02.01
 */
typedef enum IRTagType {
	TAG_BLOCK = 32,
	TAG_SIGNED = 33,
	TAG_BLOCK_SIG = 34,
	TAG_HEADER = 35,
	TAG_PAYLOAD = 36,
	TAG_PUB = 37,
	TAG_SIG = 38,
	TAG_HASH = 39
} IRTagType;

/**
 * This is the base class for all tags that have a 16-bit unsigned integer
 * as a type followed by a raw value.
 *
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
 * @since 2018.02.01
 */
class IRBaseType16RawTag : public ircommon::iltags::ILTag {
protected:
	std::uint16_t _type;
	ircommon::IRBuffer _value;
	virtual bool serializeValue(ircommon::IRBuffer & out) const;
public:
	IRBaseType16RawTag(std::uint64_t id, bool secure);

	virtual ~IRBaseType16RawTag() = default;

	virtual std::uint64_t size() const;

	virtual bool deserializeValue(
			const ircommon::iltags::ILTagFactory & factory,
			const void * buff, std::uint64_t size);

	std::uint16_t type() const {
		return this->_type;
	}

	void setType(std::uint16_t type) {
		this->_type = type;
	}

	ircommon::IRBuffer & value() {
		return this->_value;
	}

	const ircommon::IRBuffer & value() const {
		return this->_value;
	}
};

class IRPubTag: public IRBaseType16RawTag {
public:
	IRPubTag() : IRBaseType16RawTag(TAG_PUB, false) {
	}

	virtual ~IRPubTag() = default;
};

class IRSigTag: public IRBaseType16RawTag {
public:
	IRSigTag() : IRBaseType16RawTag(TAG_SIG, false) {
	}

	virtual ~IRSigTag() = default;
};

class IRHashTag: public IRBaseType16RawTag {
public:
	IRHashTag() : IRBaseType16RawTag(TAG_HASH, false) {
	}

	virtual ~IRHashTag() = default;
};


class IRPayloadTag: public ircommon::iltags::ILRawTag {
public:
	IRPayloadTag(): ircommon::iltags::ILRawTag(TAG_PAYLOAD){
	}

	virtual ~IRPayloadTag() = default;
};

class IRBlockSigTag: ircommon::iltags::ILTag {
protected:
	ircommon::iltags::ILUInt16Tag _parentHashType;
	IRSigTag _signature;
	virtual bool serializeValue(ircommon::IRBuffer & out) const;
public:
	IRBlockSigTag() : ILTag(TAG_BLOCK_SIG) {}

	virtual ~IRBlockSigTag() = default;

	virtual std::uint64_t size() const;

	virtual bool deserializeValue(
			const ircommon::iltags::ILTagFactory & factory,
			const void * buff, std::uint64_t size);

	ircommon::iltags::ILUInt16Tag & parentHashType() {
		return this->_parentHashType;
	}

	const ircommon::iltags::ILUInt16Tag & parentHashType() const{
		return this->_parentHashType;
	}

	IRSigTag & signature() {
		return this->_signature;
	}

	const IRSigTag & signature() const {
		return this->_signature;
	}
};

class IRHeaderTag: ircommon::iltags::ILTag {
protected:
	ircommon::iltags::ILUInt16Tag _version;
	ircommon::iltags::ILUInt8Tag _recordType;
	IRHashTag _instanceId;
	ircommon::iltags::ILILIntTag _blockSerial;
	ircommon::iltags::ILILIntTag _blockOffset;
	ircommon::iltags::ILILIntTag _parentBlockOffset;
	ircommon::iltags::ILILIntTag _applicationId;
	ircommon::iltags::ILILIntTag _timestamp;
	virtual bool serializeValue(ircommon::IRBuffer & out) const;
public:
	IRHeaderTag();

	virtual ~IRHeaderTag() = default;

	virtual std::uint64_t size() const;

	virtual bool deserializeValue(
			const ircommon::iltags::ILTagFactory & factory,
			const void * buff, std::uint64_t size);

	// TODO add the getters
};

class IRSignedTag: ircommon::iltags::ILTag {
protected:
	IRHeaderTag _header;
	IRPayloadTag _payload;
	IRPubTag _nextPub;

	virtual bool serializeValue(ircommon::IRBuffer & out) const;
public:
	IRSignedTag();
	virtual ~IRSignedTag() = default;

	virtual std::uint64_t size() const;

	virtual bool deserializeValue(
			const ircommon::iltags::ILTagFactory & factory,
			const void * buff, std::uint64_t size);
};

class IRBlockTag: ircommon::iltags::ILTag {
protected:
	IRSignedTag _signed;

	IRBlockSigTag _signature;

	virtual bool serializeValue(ircommon::IRBuffer & out) const;
public:
	IRBlockTag();
	virtual ~IRBlockTag() = default;

	virtual std::uint64_t size() const;

	virtual bool deserializeValue(
			const ircommon::iltags::ILTagFactory & factory,
			const void * buff, std::uint64_t size);
};

class IRTagFactory: public  ircommon::iltags::ILStandardTagFactory {
public:
	/**
	 * Creates a new instance of this class.
	 *
	 * @param[in] secureMode The secure mode state.
	 * @param[in] strictMode The strict mode state.
	 */
	IRTagFactory(bool secureMode = false, bool strictMode = false):
		 ircommon::iltags::ILStandardTagFactory(secureMode, strictMode) {};

	/**
	 * Disposes this instance and releases all associated resources.
	 */
	virtual ~IRTagFactory() = default;

	virtual  ircommon::iltags::ILTag * create(std::uint64_t tagId) const;
};

} // namespace irecordcore
} // namespace irecord

#endif /* _IRECORDCORE_IRTAGS_H_ */
