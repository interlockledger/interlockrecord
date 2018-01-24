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

//------------------------------------------------------------------------------


