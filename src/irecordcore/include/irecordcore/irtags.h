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
#include <irecordcore/irtypes.h>
#include <irecordcore/irblock.h>

namespace irecordcore {
namespace tags {

/**
 * Tag IDs defined by the InterlockRecord.
 *
 * @since 2018.02.01
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
 */
typedef enum IRTagType {
    /**
     * ID of the InterlockRecord's block tag.
     */
	TAG_BLOCK = 32,
    /**
     * ID of the InterlockRecord's signed data tag.
     */
	TAG_SIGNED = 33,
    /**
     * ID of the InterlockRecord's signature tag.
     */
	TAG_BLOCK_SIG = 34,
    /**
     * ID of the InterlockRecord's header tag.
     */
	TAG_HEADER = 35,
    /**
     * ID of the InterlockRecord's payload tag.
     */
	TAG_PAYLOAD = 36,
    /**
     * ID of the InterlockRecord's public key tag.
     */
	TAG_PUB = 37,
    /**
     * ID of the InterlockRecord's signature tag.
     */
	TAG_SIG = 38,
    /**
     * ID of the InterlockRecord's hash tag.
     */
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
    /**
     * The tag value.
     */
	irecordcore::IRTypedRaw _value;

	virtual bool serializeValue(ircommon::IRBuffer & out) const;
public:
    /**
     * Creates a new instance of this class.
     *
     * @param[in] id The tag id.
     * @param[in] secure The secure mode flag.
     */
	IRBaseType16RawTag(std::uint64_t id, bool secure);

	/**
	 * Disposes this instance and releases all associated resources.
	 */
	virtual ~IRBaseType16RawTag() = default;

	virtual std::uint64_t size() const;

	virtual bool deserializeValue(
			const ircommon::iltags::ILTagFactory & factory,
			const void * buff, std::uint64_t size);

	/**
	 * Returns the value of this tag without its type.
	 *
	 * @return The read/write buffer that holds the value.
	 */
	irecordcore::IRTypedRaw & value() {
		return this->_value;
	}

	/**
	 * Returns the value of this tag without its type.
	 *
	 * @return The read only buffer that holds the value.
	 */
	const irecordcore::IRTypedRaw & value() const {
		return this->_value;
	}
};

/**
 * This class implements the InterlockRecord's public key tag.
 *
 * @since 2018.02.01
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
 */
class IRPubTag: public IRBaseType16RawTag {
public:
	IRPubTag() : IRBaseType16RawTag(TAG_PUB, false) {
	}

	virtual ~IRPubTag() = default;
};

/**
 * This class implements the InterlockRecord's signature tag.
 *
 * @since 2018.02.01
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
 */
class IRSigTag: public IRBaseType16RawTag {
public:
	IRSigTag() : IRBaseType16RawTag(TAG_SIG, false) {
	}

	virtual ~IRSigTag() = default;
};

/**
 * This class implements the InterlockRecord's hash tag.
 *
 * @since 2018.02.01
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
 */
class IRHashTag: public IRBaseType16RawTag {
public:
	IRHashTag() : IRBaseType16RawTag(TAG_HASH, false) {
	}

	virtual ~IRHashTag() = default;
};

/**
 * This class implements the InterlockRecord's payload tag.
 *
 * @since 2018.02.01
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
 */
class IRPayloadTag: public ircommon::iltags::ILRawTag {
public:
	IRPayloadTag(): ircommon::iltags::ILRawTag(TAG_PAYLOAD){
	}

	virtual ~IRPayloadTag() = default;
};

/**
 * This class implements the InterlockRecord's block signature tag.
 *
 * @since 2018.02.01
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
 */
class IRBlockSigTag: public ircommon::iltags::ILTag {
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

/**
 * This class implements the InterlockRecord's header tag.
 *
 * @since 2018.02.01
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
 * @author Cesar Luiz Feraccin Jun Takada Chino (fchino at opencs.com.br)
 */
class IRHeaderTag: ircommon::iltags::ILBaseTagListTag {
public:
	IRHeaderTag();

	virtual ~IRHeaderTag() = default;

	/**
	 * Verifies the header's integrity.
	 *
	 * @return true if the header is OK or false otherwise.
	 */
	bool checkIntegrity();

	/**
	 * Sets the fields of the header.
	 *
	 * @param[in] header The header values.
	 * @return true for success or false otherwise.
	 */
	bool setHeader(const irecordcore::block::IRBlockHeader & header);

	/**
	 * Extracts the header values from this tag.
	 *
	 * @param[out] header The header fields.
	 * @return true for success or false otherwise.
	 */
	bool extractHeader(irecordcore::block::IRBlockHeader & header);
};

/**
 * This class implements the InterlockRecord's signed tag.
 *
 * @since 2018.02.01
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
 */
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

	// Add the getters (rw/ro).
};

/**
 * This class implements the InterlockRecord's block tag.
 *
 * @since 2018.02.01
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
 */
class IRBlockTag: public ircommon::iltags::ILTag {
protected:
	IRSignedTag _signed;

	IRBlockSigTag _signature;

	virtual bool serializeValue(ircommon::IRBuffer & out) const;
public:
	IRBlockTag() : ILTag(TAG_BLOCK) {}

	virtual ~IRBlockTag() = default;

	virtual std::uint64_t size() const;

	virtual bool deserializeValue(
			const ircommon::iltags::ILTagFactory & factory,
			const void * buff, std::uint64_t size);

	// Add the getters (rw/ro).
};

/**
 * This class implements the InterlockRecord's ILTagFactory.
 *
 * @since 2018.02.01
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
 */
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


