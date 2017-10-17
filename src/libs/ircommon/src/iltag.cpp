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

//==============================================================================
// Class ILTag
//------------------------------------------------------------------------------
ILTag::ILTag(std::uint64_t id): _tagID(id) {
}

//------------------------------------------------------------------------------
ILTag::~ILTag() {
}

//------------------------------------------------------------------------------
std::uint64_t ILTag::getSerializedSize() const {

	// ILInt + ILInt + Payload
	return ILInt::size(this->getID()) +
			ILInt::size(this->getSize()) +
			this->getSize();
}

//==============================================================================
// Class ILRawTag
//------------------------------------------------------------------------------
ILRawTag::ILRawTag(std::uint64_t id, std::uint64_t size, bool secure): ILTag(id) {
	this->_data = new std::uint8_t[size];
	this->_size = size;
	this->_secure = secure;
}

//------------------------------------------------------------------------------
ILRawTag::~ILRawTag() {

}

//------------------------------------------------------------------------------
uint64_t ILRawTag::getSize() const {
	return this->_size;
}

//------------------------------------------------------------------------------
std::uint64_t ILRawTag::serialize(std::vector<std::uint8_t> & out) const {
	uint8_t tmp[9];


	return 0;
}

//------------------------------------------------------------------------------
bool ILRawTag::resize(std::uint64_t newSize) {
	return false;
}

