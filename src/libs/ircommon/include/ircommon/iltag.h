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
#ifndef _IRCOMMON_ILTAG_H_
#define _IRCOMMON_ILTAG_H_

#include <cstdint>
#include <vector>

namespace ircommon {

class ILTag {
private:
	std::uint64_t _tagID;
public:
	ILTag(std::uint64_t id);

	virtual ~ILTag();

	uint64_t getID() const {
		return this->_tagID;
	}

	virtual std::uint64_t getSize() const = 0;

	virtual std::uint64_t getSerializedSize() const;

	std::uint64_t serialize(std::vector<std::uint8_t> & out) const;
};

class ILRawTag: public ILTag {
protected:
	std::uint64_t _size;

	std::uint8_t * _data;

	bool _secure;
public:
	ILRawTag(std::uint64_t id, std::uint64_t size, bool secure);

	virtual ~ILRawTag();

	virtual uint64_t getSize() const;

	uint64_t serialize(std::vector<std::uint8_t> & out) const;

	bool resize(std::uint64_t newSize);

	const std::uint8_t * data() const {
		return this->_data;
	}

	std::uint8_t * data() {
		return this->_data;
	}
};

} //namespace ircommon

#endif /* _IRCOMMON_ILTAG_H_ */
