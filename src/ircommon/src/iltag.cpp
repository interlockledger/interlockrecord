/*
 * Copyright (c) 2017, Open Communications Security
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
#include <ircommon/iltag.h>
#include <ircommon/ilint.h>

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
ILTagListTag::ILTagListTag(std::uint64_t id): ILTag(id) {
}

//------------------------------------------------------------------------------
bool ILTagListTag::serializeValue(ircommon::IRBuffer & out) const {

	out.writeILInt(this->count());
	for (int i = 0; i < this->count(); i++) {
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
std::uint64_t ILTagListTag::size() const {
	std::uint64_t total;

	total = ILInt::size(this->count());
	for (int i = 0; i < this->count(); i++) {
		if (this->_list[i] == nullptr) {
			total += 1;
		} else {
			total += this->_list[i]->size();
		}
	}
	return total;
}

//------------------------------------------------------------------------------
bool ILTagListTag::deserializeValue(const ILTagFactory & factory,
			const void * buff, std::uint64_t size) {
	IRBuffer inp(buff, size);
	std::uint64_t count;

	if (!inp.readILInt(count)) {
		return false;
	}

	this->clear();
	while(count > 0) {
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

//------------------------------------------------------------------------------
bool ILTagListTag::add(SharedPointer obj) {
	this->_list.push_back(obj);
	return true;
}

//------------------------------------------------------------------------------
bool ILTagListTag::insert(int idx, SharedPointer obj) {

	this->_list.insert(this->_list.begin() + idx, obj);
	return true;
}

//------------------------------------------------------------------------------
bool ILTagListTag::remove(int idx) {

	this->_list.erase(this->_list.begin() + idx);
	return true;
}

//------------------------------------------------------------------------------
ILTagListTag::SharedPointer & ILTagListTag::operator [](int idx) {
	return this->_list[idx];
}

//------------------------------------------------------------------------------
const ILTagListTag::SharedPointer & ILTagListTag::operator [](int idx) const {
	return this->_list[idx];
}

//==============================================================================
// Class ILTagFactory
//------------------------------------------------------------------------------
ILTag * ILTagFactory::create(std::uint64_t tagId) const {

	return nullptr;
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

