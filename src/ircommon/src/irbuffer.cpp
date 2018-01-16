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
#include <ircommon/irbuffer.h>
#include <ircommon/irutils.h>
#include <cstring>
#include <algorithm>
#include <stdexcept>
#include <new>

using namespace ircommon;

//==============================================================================
// Class IRBuffer
//------------------------------------------------------------------------------
IRBuffer::IRBuffer(const void * buff, std::uint64_t buffSize):
		_secure(false), _inc(0), _buff(nullptr),
		_robuff((const std::uint8_t *)buff),
		_size(buffSize), _buffSize(buffSize), _position(0) {
}

//------------------------------------------------------------------------------
IRBuffer::IRBuffer(std::uint64_t reserved, bool secure, std::uint64_t inc):
		_secure(secure), _inc(inc), _robuff(nullptr),
		_size(0), _position(0){

	if (inc == 0) {
		throw std::invalid_argument("inc cannot be 0");
	}

	this->_buffSize = IRUtils::getPaddedSize(reserved, this->_inc);
	this->_buff = new(std::nothrow) std::uint8_t[this->_buffSize];
}

//------------------------------------------------------------------------------
IRBuffer::~IRBuffer() {
	if (!this->readOnly()) {
		this->dispose(this->_buff, this->_buffSize);
	}
}

//------------------------------------------------------------------------------
bool IRBuffer::setSize(std::uint64_t size) {
	bool retval;

	if (this->readOnly()) {
		return false;
	}

	if (this->_buffSize < size) {
		if (!this->reserve(size)) {
			return false;
		}
	}
	this->_size = size;
	if (this->_position > this->_size) {
		this->_position = this->_size;
	}
	return true;
}

//------------------------------------------------------------------------------
void IRBuffer::setPosition(std::uint64_t position) {

	if (position > this->size()) {
		this->_position = this->size();
	} else {
		this->_position = position;
	}
}

//------------------------------------------------------------------------------
std::uint64_t IRBuffer::skip(std::int64_t delta) {
	std::uint64_t newPos;
	std::uint64_t retval;

	// TODO Optimize later
	newPos = this->position() + delta;
	if (newPos <= this->size()) {
		retval = delta;
	} else {
		retval = this->size() - this->position();
		newPos = this->size();
	}
	this->_position = newPos;
	return retval;
}

//------------------------------------------------------------------------------
std::uint64_t IRBuffer::rewind(std::int64_t delta) {
	std::uint64_t newPos;
	std::uint64_t retval;

	// TODO Optimize later
	if (delta < this->position()) {
		newPos = this->_position - delta;
		retval = delta;
	} else {
		newPos = 0;
		retval = this->_position;
	}
	this->_position = newPos;
	return retval;
}

//------------------------------------------------------------------------------
bool IRBuffer::reserve(std::uint64_t newSize) {

	if (this->readOnly()) {
		return false;
	}

	if (newSize > this->_buffSize) {
		std::uint64_t newBuffSize = IRUtils::getPaddedSize(newSize, this->_inc);
		std::uint8_t * newBuff = new(std::nothrow) std::uint8_t[newBuffSize];
		if (newBuff) {
			if (this->_buff) {
				std::memcpy(newBuff, this->_buff, this->_buffSize);
				this->dispose(this->_buff, this->_buffSize);
			}
			this->_buff = newBuff;
			this->_buffSize = newBuffSize;
			return true;
		} else {
			return false;
		}
	} else {
		return true;
	}
}

//------------------------------------------------------------------------------
bool IRBuffer::write(const void * buff, std::uint64_t buffSize) {
	std::uint64_t w;

	if (this->readOnly()) {
		return false;
	}

	if (!this->reserve(this->_position + buffSize)) {
		return false;
	}
	std::memcpy(this->_buff + this->_position, buff, buffSize);
	this->_position += buffSize;
	this->_size = std::max(this->_size, this->_position);
	return true;
}

//------------------------------------------------------------------------------
std::uint64_t IRBuffer::read(void * buff, std::uint64_t buffSize) {
	std::uint64_t r;

	r = std::min(this->available(), buffSize);
	std::memcpy(buff,this->roBuffer() + this->_position, r);
	this->_position += r;
	return r;
}

//------------------------------------------------------------------------------
void IRBuffer::dispose(std::uint8_t * buff, std::uint64_t buffSize) {

	if (buff) {
		if (this->_secure) {
			IRUtils::clearMemory(buff, buffSize);
		}
		delete [] buff;
	}
}

//------------------------------------------------------------------------------
bool IRBuffer::set(const void * buff, std::uint64_t buffSize) {

	if (this->readOnly()) {
		return false;
	}

	if (this->reserve(buffSize)) {
		std::memcpy(this->_buff, buff, buffSize);
		this->_size = buffSize;
		this->_position = 0;
		return true;
	} else {
		return false;
	}
}

//------------------------------------------------------------------------------
bool IRBuffer::shrink() {

	if (this->readOnly()) {
		return false;
	}

	if (this->_size == this->_buffSize) {
		return true;
	} else {
		std::uint64_t newBuffSize = std::max(this->_size, this->_inc);
		std::uint8_t * newBuff = new(std::nothrow) std::uint8_t[newBuffSize];
		if (!newBuff) {
			return false;
		} else {
			std::memcpy(newBuff, this->_buff, this->_size);
			this->dispose(this->_buff, this->_buffSize);
			this->_buffSize = newBuffSize;
			this->_buff = newBuff;
			return true;
		}
	}
}

//------------------------------------------------------------------------------
