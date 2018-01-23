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
using namespace ircommon;
using namespace ircommon::iltags;

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
bool ILBasicTag<std::int8_t, ILTag::TAG_UINT8>::serializeValue(
		ircommon::IRBuffer & out) const {
	return out.write(this->get());
}

//------------------------------------------------------------------------------
template <>
bool ILBasicTag<std::int8_t, ILTag::TAG_UINT8>::deserializeValue(
		const ILTagFactory & factory, const void * buff, std::uint64_t size) {
 	if (size != 1) {
		return false;
	} else {
		this->_value = *((const std::uint8_t *)buff);
		return true;
	}
}
//------------------------------------------------------------------------------


