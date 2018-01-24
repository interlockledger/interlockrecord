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
#include <ircommon/iltagstd.h>
#include <ircommon/irutils.h>
#include <ircommon/ilint.h>
#include <ircommon/irfp.h>
using namespace ircommon;
using namespace ircommon::iltags;

//==============================================================================
// Class ILNullTag
//------------------------------------------------------------------------------
bool ILNullTag::serializeValue(ircommon::IRBuffer & out) const {
	return true;
}

//------------------------------------------------------------------------------
bool ILNullTag::deserializeValue(const ILTagFactory & factory,
		const void * buff, std::uint64_t size) {
	return (size == 0);
}

//==============================================================================
// Class ILBoolTag
//------------------------------------------------------------------------------
template <>
bool ILBasicTag<bool, ILTag::TAG_BOOL>::serializeValue(
		ircommon::IRBuffer & out) const {
	return out.write(this->get()?1:0);
}

//------------------------------------------------------------------------------
template <>
bool ILBasicTag<bool, ILTag::TAG_BOOL>::deserializeValue(
		const ILTagFactory & factory, const void * buff, std::uint64_t size) {
 	if (size != 1) {
		return false;
	}
	const std::uint8_t * p = (const std::uint8_t *)buff;
	if (*p == 0) {
		this->_value = false;
		return true;
	} else if (*p == 1) {
		this->_value = true;
		return true;
	} else {
		return false;
	}
}

//------------------------------------------------------------------------------
template <>
std::uint64_t ILBasicTag<bool, ILTag::TAG_BOOL>::size() const {
	return 1;
}

//==============================================================================
// Class ILInt8Tag
//------------------------------------------------------------------------------
template <>
bool ILBasicTag<std::int8_t, ILTag::TAG_INT8>::serializeValue(
		ircommon::IRBuffer & out) const {
	return out.write(this->get());
}

//------------------------------------------------------------------------------
template <>
bool ILBasicTag<std::int8_t, ILTag::TAG_INT8>::deserializeValue(
		const ILTagFactory & factory, const void * buff, std::uint64_t size) {
 	if (size != 1) {
		return false;
	} else {
		this->_value = *((const std::int8_t *)buff);
		return true;
	}
}

//==============================================================================
// Class ILUInt8Tag
//------------------------------------------------------------------------------
template <>
bool ILBasicTag<std::uint8_t, ILTag::TAG_UINT8>::serializeValue(
		ircommon::IRBuffer & out) const {
	return out.write(this->get());
}

//------------------------------------------------------------------------------
template <>
bool ILBasicTag<std::uint8_t, ILTag::TAG_UINT8>::deserializeValue(
		const ILTagFactory & factory, const void * buff, std::uint64_t size) {
 	if (size != 1) {
		return false;
	} else {
		this->_value = *((const std::uint8_t *)buff);
		return true;
	}
}

//==============================================================================
// Class ILInt16Tag
//------------------------------------------------------------------------------
template <>
bool ILBasicTag<std::int16_t, ILTag::TAG_INT16>::serializeValue(
		ircommon::IRBuffer & out) const {

	if (!out.reserve(out.position() + sizeof(this->_value))) {
		return false;
	}
	IRUtils::int2BE(this->_value, out.posBuffer());
	return (out.skip(sizeof(this->_value)) == sizeof(this->_value));
}

//------------------------------------------------------------------------------
template <>
bool ILBasicTag<std::int16_t, ILTag::TAG_INT16>::deserializeValue(
		const ILTagFactory & factory, const void * buff, std::uint64_t size) {
 	if (size != this->size()) {
		return false;
	} else {
		IRUtils::BE2Int(buff, this->_value);
		return true;
	}
}

//==============================================================================
// Class ILUInt16Tag
//------------------------------------------------------------------------------
template <>
bool ILBasicTag<std::uint16_t, ILTag::TAG_UINT16>::serializeValue(
		ircommon::IRBuffer & out) const {

	if (!out.reserve(out.position() + sizeof(this->_value))) {
		return false;
	}
	IRUtils::int2BE(this->_value, out.posBuffer());
	return (out.skip(sizeof(this->_value)) == sizeof(this->_value));
}

//------------------------------------------------------------------------------
template <>
bool ILBasicTag<std::uint16_t, ILTag::TAG_UINT16>::deserializeValue(
		const ILTagFactory & factory, const void * buff, std::uint64_t size) {
 	if (size != this->size()) {
		return false;
	} else {
		IRUtils::BE2Int(buff, this->_value);
		return true;
	}
}

//==============================================================================
// Class ILInt32Tag
//------------------------------------------------------------------------------
template <>
bool ILBasicTag<std::int32_t, ILTag::TAG_INT32>::serializeValue(
		ircommon::IRBuffer & out) const {

	if (!out.reserve(out.position() + sizeof(this->_value))) {
		return false;
	}
	IRUtils::int2BE(this->_value, out.posBuffer());
	return (out.skip(sizeof(this->_value)) == sizeof(this->_value));
}

//------------------------------------------------------------------------------
template <>
bool ILBasicTag<std::int32_t, ILTag::TAG_INT32>::deserializeValue(
		const ILTagFactory & factory, const void * buff, std::uint64_t size) {
 	if (size != this->size()) {
		return false;
	} else {
		IRUtils::BE2Int(buff, this->_value);
		return true;
	}
}

//==============================================================================
// Class ILUInt32Tag
//------------------------------------------------------------------------------
template <>
bool ILBasicTag<std::uint32_t, ILTag::TAG_UINT32>::serializeValue(
		ircommon::IRBuffer & out) const {

	if (!out.reserve(out.position() + sizeof(this->_value))) {
		return false;
	}
	IRUtils::int2BE(this->_value, out.posBuffer());
	return (out.skip(sizeof(this->_value)) == sizeof(this->_value));
}

//------------------------------------------------------------------------------
template <>
bool ILBasicTag<std::uint32_t, ILTag::TAG_UINT32>::deserializeValue(
		const ILTagFactory & factory, const void * buff, std::uint64_t size) {
 	if (size != this->size()) {
		return false;
	} else {
		IRUtils::BE2Int(buff, this->_value);
		return true;
	}
}

//==============================================================================
// Class ILInt64Tag
//------------------------------------------------------------------------------
template <>
bool ILBasicTag<std::int64_t, ILTag::TAG_INT64>::serializeValue(
		ircommon::IRBuffer & out) const {

	if (!out.reserve(out.position() + sizeof(this->_value))) {
		return false;
	}
	IRUtils::int2BE(this->_value, out.posBuffer());
	return (out.skip(sizeof(this->_value)) == sizeof(this->_value));
}

//------------------------------------------------------------------------------
template <>
bool ILBasicTag<std::int64_t, ILTag::TAG_INT64>::deserializeValue(
		const ILTagFactory & factory, const void * buff, std::uint64_t size) {
 	if (size != this->size()) {
		return false;
	} else {
		IRUtils::BE2Int(buff, this->_value);
		return true;
	}
}

//==============================================================================
// Class ILUInt64Tag
//------------------------------------------------------------------------------
template <>
bool ILBasicTag<std::uint64_t, ILTag::TAG_UINT64>::serializeValue(
		ircommon::IRBuffer & out) const {

	if (!out.reserve(out.position() + sizeof(this->_value))) {
		return false;
	}
	IRUtils::int2BE(this->_value, out.posBuffer());
	return (out.skip(sizeof(this->_value)) == sizeof(this->_value));
}

//------------------------------------------------------------------------------
template <>
bool ILBasicTag<std::uint64_t, ILTag::TAG_UINT64>::deserializeValue(
		const ILTagFactory & factory, const void * buff, std::uint64_t size) {
 	if (size != this->size()) {
		return false;
	} else {
		IRUtils::BE2Int(buff, this->_value);
		return true;
	}
}

//==============================================================================
// Class ILILInt64Tag
//------------------------------------------------------------------------------
template <>
bool ILBasicTag<std::uint64_t, ILTag::TAG_ILINT64>::serializeValue(
		ircommon::IRBuffer & out) const {

	return out.writeILInt(this->_value);
}

//------------------------------------------------------------------------------
template <>
bool ILBasicTag<std::uint64_t, ILTag::TAG_ILINT64>::deserializeValue(
		const ILTagFactory & factory, const void * buff, std::uint64_t size) {

	if (ILInt::decode(buff, size, &(this->_value)) != size) {
		return false;
	}
}

//------------------------------------------------------------------------------
template <>
std::uint64_t ILBasicTag<std::uint64_t, ILTag::TAG_ILINT64>::size() const {
	return ILInt::size(this->_value);
}

//==============================================================================
// Class ILBinary32Tag
//------------------------------------------------------------------------------
template <>
bool ILBasicTag<float, ILTag::TAG_BINARY32>::serializeValue(
		ircommon::IRBuffer & out) const {

	if (!out.reserve(out.position() + sizeof(this->_value))) {
		return false;
	}
	IRFloatingPoint::toBytes(true, this->_value, out.posBuffer());
	return (out.skip(sizeof(this->_value)) == sizeof(this->_value));
}

//------------------------------------------------------------------------------
template <>
bool ILBasicTag<float, ILTag::TAG_BINARY32>::deserializeValue(
		const ILTagFactory & factory, const void * buff, std::uint64_t size) {
 	if (size != this->size()) {
		return false;
	} else {
		this->_value = IRFloatingPoint::toSingle(true, buff);
		return true;
	}
}

//==============================================================================
// Class ILBinary64Tag
//------------------------------------------------------------------------------
template <>
bool ILBasicTag<double, ILTag::TAG_BINARY64>::serializeValue(
		ircommon::IRBuffer & out) const {

	if (!out.reserve(out.position() + sizeof(this->_value))) {
		return false;
	}
	IRFloatingPoint::toBytes(true, this->_value, out.posBuffer());
	return (out.skip(sizeof(this->_value)) == sizeof(this->_value));
}

//------------------------------------------------------------------------------
template <>
bool ILBasicTag<double, ILTag::TAG_BINARY64>::deserializeValue(
		const ILTagFactory & factory, const void * buff, std::uint64_t size) {
 	if (size != this->size()) {
		return false;
	} else {
		this->_value = IRFloatingPoint::toDouble(true, buff);
		return true;
	}
}

//==============================================================================
// Class ILStringTag
//------------------------------------------------------------------------------
template <>
bool ILBasicTag<std::string, ILTag::TAG_STRING>::serializeValue(
		ircommon::IRBuffer & out) const {
	return out.write(this->_value.c_str(), this->_value.size());
}

//------------------------------------------------------------------------------
template <>
bool ILBasicTag<std::string, ILTag::TAG_STRING>::deserializeValue(
		const ILTagFactory & factory, const void * buff, std::uint64_t size) {

	this->_value.clear();
	this->_value.assign((const char *)buff, size);
	return true;
}

//------------------------------------------------------------------------------
template <>
std::uint64_t ILBasicTag<std::string, ILTag::TAG_STRING>::size() const {
	return this->_value.size();
}

//==============================================================================
// Class ILBigDecimalTag
//------------------------------------------------------------------------------
std::uint64_t ILBigDecimalTag::size() const {
	return sizeof(this->_scale) + this->_integral.size();
}

//------------------------------------------------------------------------------
bool ILBigDecimalTag::deserializeValue(const ILTagFactory & factory,
		const void * buff, std::uint64_t size) {
	std::uint64_t v;

	if (size < sizeof(this->_scale)){
		return false;
	}
	IRUtils::BE2Int(buff, this->_scale);
	return this->_integral.set(
			((const std::uint8_t *)buff) + sizeof(this->_scale),
			size - sizeof(this->_scale));
}

//------------------------------------------------------------------------------
bool ILBigDecimalTag::serializeValue(ircommon::IRBuffer & out) const {

	if (!out.reserve(out.position() + sizeof(this->_scale))) {
		return false;
	}
	IRUtils::int2BE(this->_scale, out.posBuffer());
	out.skip(sizeof(this->_scale));
	return out.write(this->_integral.roBuffer(), this->_integral.size());
}

//==============================================================================
// Class ILILIntArrayTag
//------------------------------------------------------------------------------
bool ILILIntArrayTag::serializeValue(ircommon::IRBuffer & out) const {

	if (!out.writeILInt(this->count())) {
		return false;
	}
	for (std::uint64_t i = 0; i < this->count(); i++) {
		if (!out.writeILInt(this->get(i))) {
			return false;
		}
	}
	return true;
}

//------------------------------------------------------------------------------
std::uint64_t ILILIntArrayTag::size() const {
	std::uint64_t s;

	s = ILInt::size(this->count());
	for (std::uint64_t i = 0; i < this->count(); i++) {
		s += ILInt::size(this->get(i));
	}
	return s;
}

//------------------------------------------------------------------------------
bool ILILIntArrayTag::deserializeValue(const ILTagFactory & factory,
		const void * buff, std::uint64_t size) {
	IRBuffer inp(buff, size);
	std::uint64_t count;
	std::uint64_t v;

	if (!inp.readILInt(count)) {
		return false;
	}
	for(; count > 0; count--) {
		if (!inp.readILInt(v)) {
			return false;
		}
		this->add(v);
	}
	return (inp.available() == 0);
}

//------------------------------------------------------------------------------
bool ILILIntArrayTag::add(std::uint64_t v) {

	this->_values.push_back(v);
	return true;
}

//------------------------------------------------------------------------------
bool ILILIntArrayTag::insert(std::uint64_t idx, std::uint64_t v) {

	this->_values.insert(this->_values.begin() + idx, v);
	return true;
}

//------------------------------------------------------------------------------
bool ILILIntArrayTag::remove(std::uint64_t idx) {

	this->_values.erase(this->_values.begin() + idx);
	return true;
}

//==============================================================================
// Class ILStandardTagFactory
//------------------------------------------------------------------------------
ILTag * ILStandardTagFactory::create(std::uint64_t tagId) const {

	switch (tagId) {
	case ILTag::TAG_NULL:
		return new ILNullTag();
	case ILTag::TAG_BOOL:
		return new ILBoolTag();
	case ILTag::TAG_INT8:
		return new ILInt8Tag();
	case ILTag::TAG_UINT8:
		return new ILUInt8Tag();
	case ILTag::TAG_INT16:
		return new ILInt16Tag();
	case ILTag::TAG_UINT16:
		return new ILUInt16Tag();
	case ILTag::TAG_INT32:
		return new ILInt32Tag();
	case ILTag::TAG_UINT32:
		return new ILUInt32Tag();
	case ILTag::TAG_INT64:
		return new ILInt64Tag();
	case ILTag::TAG_UINT64:
		return new ILUInt64Tag();
	case ILTag::TAG_ILINT64:
		return new ILILIntTag();
	case ILTag::TAG_BINARY32:
		return new ILBinary32Tag();
	case ILTag::TAG_BINARY64:
		return new ILBinary64Tag();
	case ILTag::TAG_BINARY128:
		return new ILBinary128Tag();
	case ILTag::TAG_BYTE_ARRAY:
		return new ILByteArrayTag(this->secure());
	case ILTag::TAG_STRING:
		return new ILStringTag();
	case ILTag::TAG_BINT:
		return new ILBigIntTag();
	case ILTag::TAG_BDEC:
		return new ILBigDecimalTag();
	case ILTag::TAG_ILINT64_ARRAY:
		return new ILILIntArrayTag();
	case ILTag::TAG_ILTAG_ARRAY:
		return new ILILTagArrayTag();
	default:
		return nullptr;
	}
}

//------------------------------------------------------------------------------


