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
#ifndef _IRCOMMON_ILTAGSTD_H_
#define _IRCOMMON_ILTAGSTD_H_

#include <ircommon/iltag.h>
#include <cstring>

namespace ircommon {
namespace iltags {

class ILNullTag : public ILTag {
protected:
	virtual bool serializeValue(ircommon::IRBuffer & out) const {
		return true;
	}
public:
	ILNullTag() : ILTag(ILTag::TAG_NULL){}

	virtual ~ILNullTag() = default;

	virtual std::uint64_t size() const {
		return 0;
	}

	virtual bool deserializeValue(const ILTagFactory & factory,
			const void * buff, std::uint64_t size) {
		return (size == 0);
	}
};

template <class ValueType, std::uint64_t TagID>
class ILBasicTag : public ILTag {
protected:
	ValueType _value;

	virtual bool serializeValue(ircommon::IRBuffer & out) const;
public:
	ILBasicTag() : ILTag(TagID){}
	virtual ~ILBasicTag() = default;

	virtual std::uint64_t size() const {
		return sizeof(ValueType);
	}

	virtual bool deserializeValue(const ILTagFactory & factory,
			const void * buff, std::uint64_t size);

	ValueType get() const {
		return this->_value;
	}

	void set(ValueType v) {
		this->_value = v;
	}
};

typedef ILBasicTag<bool, ILTag::TAG_BOOL> ILBoolTag;

typedef ILBasicTag<std::int8_t, ILTag::TAG_INT8> ILInt8Tag;

typedef ILBasicTag<std::uint8_t, ILTag::TAG_UINT8> ILUInt8Tag;

typedef ILBasicTag<std::int16_t, ILTag::TAG_INT16> ILInt16Tag;

typedef ILBasicTag<std::uint16_t, ILTag::TAG_UINT16> ILUInt16Tag;

typedef ILBasicTag<std::int32_t, ILTag::TAG_INT32> ILInt32Tag;

typedef ILBasicTag<std::uint32_t, ILTag::TAG_UINT32> ILUInt32Tag;

typedef ILBasicTag<std::int64_t, ILTag::TAG_INT64> ILInt64Tag;

typedef ILBasicTag<std::uint64_t, ILTag::TAG_UINT64> ILUInt64Tag;

typedef ILBasicTag<std::uint64_t, ILTag::TAG_ILINT64> ILILIntTag;

typedef ILBasicTag<float, ILTag::TAG_BINARY32> ILBinary32Tag;

typedef ILBasicTag<double, ILTag::TAG_BINARY64> ILBinary64Tag;

typedef ILBasicTag<std::string, ILTag::TAG_STRING> ILStringTag;

template <std::uint64_t TagID, std::uint64_t ValueSize>
class ILBasicFixedOpaqueTag : public ILTag {
protected:
	std::uint8_t _value[ValueSize];

	virtual bool serializeValue(ircommon::IRBuffer & out) const;
public:
	ILBasicFixedOpaqueTag() : ILTag(TagID){}
	virtual ~ILBasicFixedOpaqueTag() = default;

	virtual std::uint64_t size() const {
		return ValueSize;
	}

	virtual bool deserializeValue(const ILTagFactory & factory,
			const void * buff, std::uint64_t size) {
		if (size != ValueSize) {
			return false;
		}
		std::memcpy(this->_value, buff, ValueSize);
		return true;
	}

	const void * get() const {
		return this->_value;
	}
};

typedef ILBasicFixedOpaqueTag<ILTag::TAG_BINARY128, 16> ILBinary128Tag;

class IRByteArrayTag: public ILRawTag {
public:
	IRByteArrayTag(bool secure = false) : ILRawTag(ILTag::TAG_BYTE_ARRAY, secure){}
	virtual ~IRByteArrayTag() = default;
};

class IRBigIntTag: public ILRawTag {
public:
	IRBigIntTag() : ILRawTag(ILTag::TAG_BINT, true){}
	virtual ~IRBigIntTag() = default;
};

//IRBigDecimalTag
//IRILIntArrayTag
//IRILTagArrayTag

/**
 * This class implements a factory that handle all standard tag types.
 *
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
 * @since 2018.01.22
 */
class ILStandardTagFactory: public ILTagFactory {
public:
	/**
	 * Creates a new instance of this class.
	 */
	ILStandardTagFactory(bool secure): ILTagFactory(secure) {};

	/**
	 * Disposes this instance and releases all associated resources.
	 */
	virtual ~ILStandardTagFactory() = default;

	virtual ILTag * create(std::uint64_t tagId) const;
};

} // namespace iltags
} // namespace ircommon

#endif /* _IRCOMMON_ILTAGSTD_H_ */
