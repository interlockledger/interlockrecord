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
#include <ircommon/irbuffer.h>
#include <ircommon/ilint.h>
#include <ircommon/irfp.h>
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
		_buff(nullptr),	_robuff((const std::uint8_t *)buff),
		_size(buffSize), _buffSize(buffSize), _position(0),
		_inc(0), _secure(false) {
}

//------------------------------------------------------------------------------
IRBuffer::IRBuffer(std::uint64_t reserved, bool secure, std::uint64_t inc):
		_robuff(nullptr),_size(0), _position(0), _inc(inc), _secure(secure) {

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
std::uint64_t IRBuffer::skip(std::uint64_t delta) {
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
std::uint64_t IRBuffer::rewind(std::uint64_t delta) {
	std::uint64_t newPos;
	std::uint64_t retval;

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
bool IRBuffer::writeILInt(std::uint64_t v) {
	std::uint64_t newSize;
	int vSize;

	if (this->readOnly()) {
		return false;
	}

	vSize = ILInt::size(v);
	newSize = std::max(this->position() + vSize, this->size());
	if (this->setSize(newSize)) {
		ILInt::encode(v, this->buffer() + this->position(), vSize);
		this->_position += vSize;
		return true;
	} else {
		return false;
	}
}

//------------------------------------------------------------------------------
bool IRBuffer::readILInt(std::uint64_t & v) {
	int read;

	read = ILInt::decode(this->roBuffer() + this->position(),
			this->available(), &v);
	if (read == 0) {
		return false;
	} else {
		this->_position += read;
		return true;
	}
}

//------------------------------------------------------------------------------
bool IRBuffer::write(int v) {

	if (this->readOnly()) {
		return false;
	}
	if (!this->reserve(this->_position + 1)){
		return false;
	}
	*(this->posBuffer()) = (std::uint8_t)v;
	this->_position++;
	this->_size = std::max(this->_size, this->_position);
	return true;
}

//------------------------------------------------------------------------------
int IRBuffer::read() {
	if (this->position() < this->size()) {
		this->_position++;
		return *(this->roPosBuffer() - 1) & 0xFF;
	} else {
		return -1;
	}
}

//------------------------------------------------------------------------------
bool IRBuffer::writeInt(std::uint8_t v) {

	if (this->readOnly()) {
		return false;
	}
	if (this->reserve(this->position() + sizeof(v))) {
		IRUtils::int2BE(v, this->posBuffer());
		this->_position += sizeof(v);
		this->_size = std::max(this->_size, this->_position);
		return true;
	} else {
		return false;
	}
}

//------------------------------------------------------------------------------
bool IRBuffer::writeInt(std::uint16_t v) {

	if (this->readOnly()) {
		return false;
	}
	if (this->reserve(this->position() + sizeof(v))) {
		IRUtils::int2BE(v, this->posBuffer());
		this->_position += sizeof(v);
		this->_size = std::max(this->_size, this->_position);
		return true;
	} else {
		return false;
	}
}

//------------------------------------------------------------------------------
bool IRBuffer::writeInt(std::uint32_t v) {

	if (this->readOnly()) {
		return false;
	}
	if (this->reserve(this->position() + sizeof(v))) {
		IRUtils::int2BE(v, this->posBuffer());
		this->_position += sizeof(v);
		this->_size = std::max(this->_size, this->_position);
		return true;
	} else {
		return false;
	}
}

//------------------------------------------------------------------------------
bool IRBuffer::writeInt(std::uint64_t v) {

	if (this->readOnly()) {
		return false;
	}
	if (this->reserve(this->position() + sizeof(v))) {
		IRUtils::int2BE(v, this->posBuffer());
		this->_position += sizeof(v);
		this->_size = std::max(this->_size, this->_position);
		return true;
	} else {
		return false;
	}
}

//------------------------------------------------------------------------------
bool IRBuffer::readInt(std::uint8_t & v) {

	if (this->available() >= sizeof(v)) {
		IRUtils::BE2Int(this->roPosBuffer(), v);
		this->_position += sizeof(v);
		return true;
	} else {
		return false;
	}
}

//------------------------------------------------------------------------------
bool IRBuffer::readInt(std::uint16_t & v) {

	if (this->available() >= sizeof(v)) {
		IRUtils::BE2Int(this->roPosBuffer(), v);
		this->_position += sizeof(v);
		return true;
	} else {
		return false;
	}
}

//------------------------------------------------------------------------------
bool IRBuffer::readInt(std::uint32_t & v) {

	if (this->available() >= sizeof(v)) {
		IRUtils::BE2Int(this->roPosBuffer(), v);
		this->_position += sizeof(v);
		return true;
	} else {
		return false;
	}
}

//------------------------------------------------------------------------------
bool IRBuffer::readInt(std::uint64_t & v) {

	if (this->available() >= sizeof(v)) {
		IRUtils::BE2Int(this->roPosBuffer(), v);
		this->_position += sizeof(v);
		return true;
	} else {
		return false;
	}
}

//------------------------------------------------------------------------------
bool IRBuffer::writeFloat(float v) {

	if (this->readOnly()) {
		return false;
	}
	if (this->reserve(this->position() + sizeof(v))) {
		IRFloatingPoint::toBytes(true, v, this->posBuffer());
		this->_position += sizeof(v);
		this->_size = std::max(this->_size, this->_position);
		return true;
	} else {
		return false;
	}
}

//------------------------------------------------------------------------------
bool IRBuffer::writeFloat(double v) {

	if (this->readOnly()) {
		return false;
	}
	if (this->reserve(this->position() + sizeof(v))) {
		IRFloatingPoint::toBytes(true, v, this->posBuffer());
		this->_position += sizeof(v);
		this->_size = std::max(this->_size, this->_position);
		return true;
	} else {
		return false;
	}
}

//------------------------------------------------------------------------------
bool IRBuffer::readFloat(float & v) {

	if (this->available() >= sizeof(v)) {
		v = IRFloatingPoint::toSingle(true, this->roPosBuffer());
		this->_position += sizeof(v);
		return true;
	} else {
		return false;
	}
}

//------------------------------------------------------------------------------
bool IRBuffer::readFloat(double & v) {

	if (this->available() >= sizeof(v)) {
		v = IRFloatingPoint::toDouble(true, this->roPosBuffer());
		this->_position += sizeof(v);
		return true;
	} else {
		return false;
	}
}

//------------------------------------------------------------------------------
bool IRBuffer::copy(const IRBuffer & other) {

	if (this->readOnly()) {
		return false;
	}
	if (this == &other) {
		return true;
	}
	if (this->set(other.roBuffer(), other.size())) {
		this->setPosition(other.position());
		return true;
	} else {
		return false;
	}
}

//------------------------------------------------------------------------------
