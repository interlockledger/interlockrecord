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
			const void * buff, std::uint64_t size) {
		return (size == size());
	}

	ValueType get() const {
		return this->_value;
	}

	void set(ValueType v) {
		this->_value = v;
	}
};

template <class ValueType, std::uint64_t TagID>
bool ILBasicTag<ValueType, TagID>::serializeValue(ircommon::IRBuffer & out) const {
	return false;
}

template <class ValueType, std::uint64_t TagID>
bool ILBasicTag<ValueType, TagID>::deserializeValue(const ILTagFactory & factory,
		const void * buff, std::uint64_t size) {
	return false;
}

template <class ValueType, std::uint64_t TagID>
std::uint64_t ILBasicTag<ValueType, TagID>::size() const {
	return sizeof(ValueType);
}

//==============================================================================
// Class ILBoolTag
//------------------------------------------------------------------------------
typedef ILBasicTag<bool, ILTag::TAG_BOOL> ILBoolTag;

template <>
bool ILBasicTag<bool, ILTag::TAG_BOOL>::serializeValue(ircommon::IRBuffer & out) const {
	return out.write(this->get()?1:0);
}

template <>
bool ILBasicTag<bool, ILTag::TAG_BOOL>::deserializeValue(const ILTagFactory & factory,
		const void * buff, std::uint64_t size) {
	return false;
}

template <>
std::uint64_t ILBasicTag<bool, ILTag::TAG_BOOL>::size() const {
	return 1;
}


} // namespace iltags
} // namespace ircommon

#endif /* _IRCOMMON_ILTAGSTD_H_ */
