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
#include <ircommon/iltag.h>
#include <ircommon/ilint.h>
#include <cstring>

using namespace ircommon;
using namespace ircommon::iltags;

//==============================================================================
// Class ILTag
//------------------------------------------------------------------------------
static const std::uint64_t ILTag_STANDARD_SIZES[16] = {
		0,  // TAG_NULL
		1,  // TAG_BOOL
		1,  // TAG_INT8
		1,  // TAG_UINT8
		2,  // TAG_INT16
		2,  // TAG_UINT16
		4,  // TAG_INT32
		4,  // TAG_UINT32
		8,  // TAG_INT64
		8,  // TAG_UINT64
		0,  // TAG_ILINT64 - Not defined in this table
		4,  // TAG_BINARY32
		8,  // TAG_BINARY64
		16, // TAG_BINARY128
		0,  // Reserved
		0   // Reserved
};

//------------------------------------------------------------------------------
ILTag::ILTag(std::uint64_t id): _tagID(id) {
}

//------------------------------------------------------------------------------
std::uint64_t ILTag::tagSize() const {
	std::uint64_t ret;

	ret = ILInt::size(this->id()) + this->size();
	if (!this->isImplicit()) {
		ret += ILInt::size(this->size());
	}
	return ret;
}

//------------------------------------------------------------------------------
std::uint64_t ILTag::getImplicitValueSize(std::uint64_t tagId) {

	if (tagId < 16) {
		return ILTag_STANDARD_SIZES[tagId];
	} else {
		return 0;
	}
}

//------------------------------------------------------------------------------
bool ILTag::serialize(ircommon::IRBuffer & out) const {

	// Add the ID.
	if (!out.writeILInt(this->id())) {
		return false;
	}
	// Add the size if required
	if ((!this->isImplicit()) && (!out.writeILInt(this->size()))) {
		return false;
	}
	// Add the body
	return this->serializeValue(out);
}

//==============================================================================
// Class ILRawTag
//------------------------------------------------------------------------------
bool ILRawTag::serializeValue(ircommon::IRBuffer & out) const {
	return out.write(this->value().roBuffer(), this->value().size());
}

//------------------------------------------------------------------------------
bool ILRawTag::deserializeValue(const ILTagFactory & factory,
		const void * buff, std::uint64_t size) {
	return this->_value.set(buff, size);
}

//==============================================================================
// Class ILTagListTag
//------------------------------------------------------------------------------
bool ILBaseTagListTag::serializeValue(ircommon::IRBuffer & out) const {

	for (std::uint64_t i = 0; i < this->count(); i++) {
		if (this->_list[i] == nullptr) {
			// Shortcut to write a TAG_NULL that is a single 0.
			if (!out.write(0)) {
				return false;
			}
		} else {
			if (!this->_list[i]->serialize(out)) {
				return false;
			}
		}
	}
	return true;
}

//------------------------------------------------------------------------------
std::uint64_t ILBaseTagListTag::size() const {
	std::uint64_t total;

	total = 0;
	for (unsigned int i = 0; i < this->count(); i++) {
		if (this->_list[i] == nullptr) {
			total += 1;
		} else {
			total += this->_list[i]->tagSize();
		}
	}
	return total;
}

//------------------------------------------------------------------------------
bool ILBaseTagListTag::deserializeValue(const ILTagFactory & factory,
			const void * buff, std::uint64_t size) {
	IRBuffer inp(buff, size);

	this->clear();
	while (inp.available() != 0) {
		ILTag * tag = factory.deserialize(inp);
		if (!tag) {
			return false;
		}
		if (!this->add(tag)) {
			return false;
		}
	}
	return true;
}

//------------------------------------------------------------------------------
bool ILBaseTagListTag::add(SharedPointer obj) {

	if (this->isFull()) {
		return false;
	} else {
		this->_list.push_back(obj);
		return true;
	}
}

//------------------------------------------------------------------------------
bool ILBaseTagListTag::add(ILTag * obj) {

	if (this->isFull()) {
		return false;
	} else {
		this->_list.push_back(SharedPointer(obj));
		return true;
	}
}

//------------------------------------------------------------------------------
bool ILBaseTagListTag::insert(std::uint64_t idx, SharedPointer obj) {

	if (this->isFull() || (idx >= this->maxEntries())) {
		return false;
	} else {
		this->_list.insert(this->_list.begin() + idx, obj);
		return true;
	}
}

//------------------------------------------------------------------------------
bool ILBaseTagListTag::insert(std::uint64_t idx, ILTag * obj) {

	if (this->isFull() || (idx >= this->maxEntries())) {
		return false;
	} else {
		this->_list.insert(this->_list.begin() + idx, SharedPointer(obj));
		return true;
	}
}

//------------------------------------------------------------------------------
bool ILBaseTagListTag::remove(std::uint64_t idx) {

	this->_list.erase(this->_list.begin() + idx);
	return true;
}

//------------------------------------------------------------------------------
ILBaseTagListTag::SharedPointer & ILBaseTagListTag::operator [](std::uint64_t idx) {
	return this->_list[idx];
}

//------------------------------------------------------------------------------
const ILBaseTagListTag::SharedPointer & ILBaseTagListTag::operator [](std::uint64_t idx) const {
	return this->_list[idx];
}

//------------------------------------------------------------------------------
ILBaseTagListTag::SharedPointer & ILBaseTagListTag::get(std::uint64_t idx) {

	if (idx < this->count()) {
		return (*this)[idx];
	} else {
		throw std::out_of_range("Out of range!");
	}
}

//------------------------------------------------------------------------------
const ILBaseTagListTag::SharedPointer & ILBaseTagListTag::get(std::uint64_t idx) const {

	if (idx < this->count()) {
		return (*this)[idx];
	} else {
		throw std::out_of_range("Out of range!");
	}
}

//==============================================================================
// Class ILBaseTagArrayTag
//------------------------------------------------------------------------------
bool ILBaseTagArrayTag::serializeValue(ircommon::IRBuffer & out) const {

    if (!out.writeILInt(this->count())) {
    	return false;
    }
    return ILBaseTagListTag::serializeValue(out);
}

//------------------------------------------------------------------------------
std::uint64_t ILBaseTagArrayTag::size() const {
	return ILInt::size(this->count()) + ILBaseTagListTag::size();
}

//------------------------------------------------------------------------------
bool ILBaseTagArrayTag::deserializeValue(const ILTagFactory & factory,
		const void * buff, std::uint64_t size) {
	IRBuffer inp(buff, size);
	std::uint64_t count;

	this->clear();
	if (!inp.readILInt(count)) {
		return false;
	}
	if (count > this->maxEntries()) {
		return false;
	}
	for(; count > 0; count--) {
		ILTag * tag = factory.deserialize(inp);
		if (!tag) {
			return false;
		}
		if (!this->add(tag)) {
			return false;
		}
	}
	return (inp.available() == 0);
}

//==============================================================================
// Class ILTagFactory
//------------------------------------------------------------------------------
ILTag * ILTagFactory::create(std::uint64_t tagId) const {

	if (this->strictMode()) {
		return nullptr;
	} else {
		return new ILRawTag(tagId, this->secure());
	}
}

//------------------------------------------------------------------------------
ILTag * ILTagFactory::deserialize(IRBuffer & inp) const {
	ILTag * tag;
	std::uint64_t tagId;
	std::uint64_t tagSize;

	if (!extractTagHeader(inp, tagId, tagSize)){
		return nullptr;
	}
	if (inp.available() < tagSize) {
		return nullptr;
	}
	tag = this->create(tagId);
	if (tag == nullptr) {
		return nullptr;
	}
	if (tag->deserializeValue(*this, inp.roPosBuffer(), tagSize)) {
		inp.skip(tagSize);
		return tag;
	} else {
		delete tag;
		return nullptr;
	}
}

//------------------------------------------------------------------------------
bool ILTagFactory::extractTagHeader(IRBuffer & inp,
		std::uint64_t & tagId, std::uint64_t & tagSize) {

	// ID
	if (!inp.readILInt(tagId)) {
		return false;
	}
	// Size
	if (tagId == ILTag::TAG_ILINT64) {
		if (inp.available() > 0) {
			tagSize = ILInt::encodedSize(*inp.roPosBuffer());
			return true;
		} else {
			return false;
		}
	} else if (ILTag::isImplicit(tagId)) {
			tagSize = ILTag::getImplicitValueSize(tagId);
			return true;
	} else {
		return inp.readILInt(tagSize);
	}
}

//------------------------------------------------------------------------------
bool ILTagFactory::deserialize(IRBuffer & inp, ILTag & tag) const {
	std::uint64_t tagId;
	std::uint64_t tagSize;

	if (!extractTagHeader(inp, tagId, tagSize)){
		return false;
	}
	if (inp.available() < tagSize) {
		return false;
	}
	if (tagId != tag.id()) {
		return false;
	}
	if (tag.deserializeValue(*this, inp.roPosBuffer(), tagSize)) {
		inp.skip(tagSize);
		return true;
	} else {
		return false;
	}
}

//==============================================================================
// Class ILTagUtil
//------------------------------------------------------------------------------
bool ILTagUtil::sameID(const ILTag & a, const ILTag & b) {
	return (a.id() == b.id());
}

//------------------------------------------------------------------------------
bool ILTagUtil::sameClass(const ILTag & a, const ILTag & b) {
	return (typeid(a) == typeid(b));
}

//------------------------------------------------------------------------------
bool ILTagUtil::equals(const ILTag & a, const ILTag & b) {
	IRBuffer ba(0, true);
	IRBuffer bb(0, true);

	if (a.id() != b.id()) {
		return false;
	}
	if (!a.serialize(ba)) {
		return false;
	}
	if (!b.serialize(bb)) {
		return false;
	}
	if (ba.size() != bb.size()) {
		return false;
	}
	return (std::memcmp(ba.roBuffer(), bb.roBuffer(), ba.size()) == 0);
}

//------------------------------------------------------------------------------

