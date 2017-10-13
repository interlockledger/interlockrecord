/*
 * iltag.h
 *
 *  Created on: 10 de out de 2017
 *      Author: fchino
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
