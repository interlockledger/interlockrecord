/*
 * Copyright (c) 2017-2018 InterlockLedger Network
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
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


//==============================================================================
// Class IRBlockTag
//------------------------------------------------------------------------------
IRBlockTag::IRBlockTag(): ILTag(TAG_BLOCK) {

}

//------------------------------------------------------------------------------
bool IRBlockTag::serializeValue(ircommon::IRBuffer & out) const {

	if (!this->_signed.serialize(out)) {
		return false;
	}
	return this->_signature.serialize(out);
}
//------------------------------------------------------------------------------

std::uint64_t IRBlockTag::size() const {

	return this->_signature.tagSize() + this->_signed.tagSize();
}

//------------------------------------------------------------------------------
bool IRBlockTag::deserializeValue(
	const ircommon::iltags::ILTagFactory & factory,
	const void * buff, std::uint64_t size) {
	IRBuffer inp(buff, size);

	if (!factory.deserialize(inp, this->_signed)) {
		return false;
	}
	if (!factory.deserialize(inp, this->_signature)) {
		return false;
	}
	return (inp.available() == 0);
}

//==============================================================================
// Class IRSignedTag
//------------------------------------------------------------------------------
IRSignedTag::IRSignedTag() : ILTag(TAG_SIGNED) {
	// TODO Implementation missing.
}

//------------------------------------------------------------------------------
bool IRSignedTag::serializeValue(ircommon::IRBuffer & out) const {

	if (!this->_header.serialize(out)) {
		return false;
	}
	if (!this->_payload.serialize(out)) {
		return false;
	}
	return this->_nextPub.serialize(out);
}

//------------------------------------------------------------------------------
std::uint64_t IRSignedTag::size() const {

	return this->_header.tagSize() + this->_payload.tagSize() + this->_nextPub.tagSize();
}

//------------------------------------------------------------------------------
bool IRSignedTag::deserializeValue(
	const ircommon::iltags::ILTagFactory & factory,
	const void * buff, std::uint64_t size) {
	IRBuffer inp(buff, size);

	if (!factory.deserialize(inp, this->_header)) {
		return false;
	}
	if (!factory.deserialize(inp, this->_payload)) {
		return false;
	}
	if (!factory.deserialize(inp, this->_nextPub)) {
		return false;
	}
	return (inp.available() == 0);
}

//==============================================================================
// Class IRHeaderTag
//------------------------------------------------------------------------------
IRHeaderTag::IRHeaderTag(): ILBaseTagListTag(TAG_HEADER) {
	// TODO Verify the implementation
}

//------------------------------------------------------------------------------
bool IRHeaderTag::checkIntegrity()
{
	//TODO Implementation required!
	return false;
};

//------------------------------------------------------------------------------
bool IRHeaderTag::setHeader(const irecordcore::block::IRBlockHeader & header) 
{
	//TODO Implementation required!
	return false;
};

//------------------------------------------------------------------------------
bool IRHeaderTag::extractHeader(irecordcore::block::IRBlockHeader & header)
{
	//TODO Implementation required!
	return false;
};

//==============================================================================
// Class IRTagFactory
//------------------------------------------------------------------------------
ircommon::iltags::ILTag * IRTagFactory::create(std::uint64_t tagId) const {
	//TODO Implementation required!
	return nullptr;
}
//------------------------------------------------------------------------------
