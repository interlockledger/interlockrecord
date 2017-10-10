/*
 * iltag.h
 *
 *  Created on: 10 de out de 2017
 *      Author: fchino
 */

#ifndef _IRCOMMON_ILTAG_H_
#define _IRCOMMON_ILTAG_H_

#include <stdint.h>
#include <vector>

class ILTag {
private:
	uint64_t _tagID;
public:
	ILTag(uint64_t id);

	virtual ~ILTag();

	uint64_t getID() const {
		return this->_tagID;
	}

	virtual uint64_t getSize() const = 0;

	virtual uint64_t getSerializedSize() const;

	uint64_t serialize(std::vector<uint8_t> & out) const;
};

class ILRawTag: public ILTag {
protected:
	uint64_t _size;

	uint8_t * _data;

	bool _secure;
public:
	ILRawTag(uint64_t id, uint64_t size, bool secure);

	virtual ~ILRawTag();

	virtual uint64_t getSize() const;

	uint64_t serialize(std::vector<uint8_t> & out) const;

	bool resize(uint64_t newSize);

	const uint8_t * data() const {
		return this->_data;
	}

	uint8_t * data() {
		return this->_data;
	}
};


#endif /* _IRCOMMON_ILTAG_H_ */
