/*
 * irbuffer.h
 *
 *  Created on: 13 de out de 2017
 *      Author: fchino
 */

#ifndef INCLUDE_IRCOMMON_IRBUFFER_H_
#define INCLUDE_IRCOMMON_IRBUFFER_H_

#include <cstdint>

namespace ircommon {

/**
 * This class implements a simple memory buffer.
 *
 *
 */
class IRBuffer {
private:
	std::uint8_t * _buff;

	const std::uint8_t * _robuff;

	std::uint64_t _size;

	std::uint64_t _actualSize;

	std::uint64_t _position;

	std::uint64_t _inc;

	bool _secure;
public:
	IRBuffer(std::uint64_t buffSize, const void * buff);

	IRBuffer(std::uint64_t initialSize, bool secure = false, std::uint64_t inc = 512);

	virtual ~IRBuffer();

	std::uint64_t size() const {
		return _size;
	}

	std::uint64_t position() const {
		return _position;
	}

	std::uint64_t available() const {
		return size() - position();
	}

	std::uint8_t * buffer() {
		return this->_buff;
	}

	const std::uint8_t * buffer() const {
		return this->_robuff;
	}

	void setSize(std::uint64_t size);

	void setPosition(std::uint64_t position);

	bool movePosition(std::int64_t delta);

	bool reserve(std::uint64_t newSize);

	bool write(std::uint64_t buffSize, const void * buff);

	std::uint64_t read(std::uint64_t buffSize, void * buff);
};

} //namespace ircommon

#endif /* INCLUDE_IRCOMMON_IRBUFFER_H_ */
