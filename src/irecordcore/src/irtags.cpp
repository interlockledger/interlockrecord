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
#include <irecordcore/irtags.h>

using namespace irecordcore;
using namespace irecordcore::tags;
using namespace ircommon;
using namespace ircommon::iltags;

//==============================================================================
// Class IRBaseType16RawTag
//------------------------------------------------------------------------------
IRBaseType16RawTag::IRBaseType16RawTag(std::uint64_t id, bool secure):
		ircommon::iltags::ILTag(id), _value(0, secure) {
}

//------------------------------------------------------------------------------
bool IRBaseType16RawTag::serializeValue(ircommon::IRBuffer & out) const {

	if (!out.writeInt(this->value().type())){
		return false;
	}
	return out.write(this->_value.roBuffer(), this->_value.size());
}

//------------------------------------------------------------------------------
std::uint64_t IRBaseType16RawTag::size() const {

	return sizeof(this->value().type()) + this->_value.size();
}

//------------------------------------------------------------------------------
bool IRBaseType16RawTag::deserializeValue(
		const ircommon::iltags::ILTagFactory & factory,
		const void * buff, std::uint64_t size) {
	IRBuffer inp(buff, size);
	std::uint16_t type;

	if (!inp.readInt(type)) {
		return false;
	}
	this->_value.setType(type);
	return this->_value.set(inp.roPosBuffer(), inp.available());
}

//==============================================================================
// Class IRBlockSigTag
//------------------------------------------------------------------------------
bool IRBlockSigTag::serializeValue(ircommon::IRBuffer & out) const {

	if (!this->_parentHashType.serialize(out)) {
		return false;
	}
	return this->_signature.serialize(out);
}

//------------------------------------------------------------------------------
std::uint64_t IRBlockSigTag::size() const {

	return this->_parentHashType.tagSize() + this->_signature.tagSize();
}

//------------------------------------------------------------------------------
bool IRBlockSigTag::deserializeValue(
		const ircommon::iltags::ILTagFactory & factory,
		const void * buff, std::uint64_t size) {
	IRBuffer inp(buff, size);

	if (!factory.deserialize(inp, this->_parentHashType)) {
		return false;
	}
	if (!factory.deserialize(inp, this->_signature)) {
		return false;
	}
	return (inp.available() == 0);
}

//------------------------------------------------------------------------------

