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
ILTag::ILTag(std::uint64_t id): _tagID(id) {
}

//------------------------------------------------------------------------------
std::uint64_t ILTag::tagSize() const {
	std::uint64_t ret;

	ret = ILInt::size(this->getID()) + this->size();
	if (!this->isImplicit()) {
		ret += ILInt::size(this->size());
	}
	return ret;
}

//------------------------------------------------------------------------------
bool ILTag::serialize(ircommon::IRBuffer & out) const {

	// Add the ID.
	if (!out.writeILInt(this->getID())) {
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
ILRawTag::ILRawTag(std::uint64_t id, bool secure): ILTag(id),
		_value(0, 16, secure) {
}

//------------------------------------------------------------------------------
std::uint64_t ILRawTag::size() const {
	return this->value().size();
}

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

	for (int i = 0; i < this->count(); i++) {
		if (!this->_list[i]->serialize(out)) {
			return false;
		}
	}
	return true;
}

//------------------------------------------------------------------------------
std::uint64_t ILTagListTag::size() const {
	std::uint64_t total;

	total = 0;
	for (int i = 0; i < this->count(); i++) {
		total += this->_list[i]->size();
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
bool ILTagFactory::getTagSize(std::uint64_t tagId, IRBuffer & inp,
		 std::uint64_t & size) {
	const std::uint64_t SIZES[16] = {0, 1, 1, 1,
									2, 2, 4, 4,
									8, 8, 0, 4,
									8, 16, 0, 0};
	if (ILTag::isImplicit(tagId)) {
		if (tagId == ILTag::TAG_ILINT64) {
			if (inp.available() == 0) {
				return false;
			}
			size = ILInt::encodedSize(*inp.roPosBuffer());
			return true;
		} else {
			size = SIZES[tagId];
			return true;
		}
	} else {
		return inp.readILInt(size);
	}
}

//------------------------------------------------------------------------------
ILTag * ILTagFactory::create(std::uint64_t tagId) const {
	return nullptr;
}

//------------------------------------------------------------------------------
ILTag * ILTagFactory::deserialize(IRBuffer & inp) const {
	ILTag * tag;
	std::uint64_t tagId;
	std::uint64_t tagSize;

	if (!inp.readILInt(tagId)) {
		return nullptr;
	}
	if (!ILTagFactory::getTagSize(tagId, inp, tagSize)) {
		return nullptr;
	}
	//TODO
	return nullptr;
}

//------------------------------------------------------------------------------
