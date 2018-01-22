/*
 * Copyright (c) 2017-2018, Open Communications Security
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
#include <memory>
#include <ircommon/irbuffer.h>

namespace ircommon {
namespace iltags {

// Pre-declaration of ILTagFactory
class ILTagFactory;

/**
 * This abstract class is the base class for all ILTags implemented by this
 * library.
 *
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
 * @since 2017.12.27
 */
class ILTag {
public:
	// TODO Add documentation to those constants
	enum {
		TAG_NULL = 0,
		TAG_BOOL = 1,
		TAG_INT8 = 2,
		TAG_UINT8 = 3,
		TAG_INT16 = 4,
		TAG_UINT16 = 5,
		TAG_INT32 = 6,
		TAG_UINT32 = 7,
		TAG_INT64 = 8,
		TAG_UINT64 = 9,
		TAG_LINT64 = 10,
		TAG_BINARY32 = 11,
		TAG_BINARY64 = 12,
		TAG_BINARY128 = 13,
		TAG_BYTE_ARRAY = 16,
		TAG_STRING = 17,
		TAG_BINT = 18,
		TAG_BDEC = 19,
		TAG_ILINT64_ARRAY = 20,
		TAG_ILTAG_ARRAY = 21
	};
private:
	/**
	 * The tag ID.
	 */
	std::uint64_t _tagID;
protected:
	/**
	 * Serializes the value of this tag.  The serialization must be written to
	 * the current position of the buffer out.
	 *
	 * @param[in] out The buffer that will receive the value.
	 * @return true for success or false otherwise.
	 * @note This method must be implemented by all subclasses of this class.
	 * @note It is called by serialize() in order to serialize the value of the
	 * tag.
	 */
	virtual bool serializeValue(ircommon::IRBuffer & out) const = 0;
public:
	/**
	 * Creates a new instance of this class.
	 *
	 * @param[in] id The tag id.
	 */
	ILTag(std::uint64_t id);

	/**
	 * Disposes this instance and releases all associated resources.
	 */
	virtual ~ILTag() = default;

	/**
	 * Returns the ID of this tag.
	 *
	 * @return The tag ID.
	 */
	uint64_t getID() const {
		return this->_tagID;
	}

	/**
	 * Returns the size of the serialized value in bytes.
	 *
	 * @return The size of the value.
	 */
	virtual std::uint64_t size() const = 0;

	/**
	 * Returns the total size of the serialized tag, including the Id, the size
	 * (if required) and the size of the value.
	 *
	 * @return The total size of the tag in bytes.
	 */
	std::uint64_t tagSize() const;

	/**
	 * Serializes this tag. The serialization must be written to the current
	 * position of the buffer out.
	 *
	 * @param[out]
	 */
	bool serialize(ircommon::IRBuffer & out) const;

	/**
	 * Deserializes the value of the tag.
	 *
	 * @param[in] factory The ILTagFactory if required.
	 * @param[in] buff The buffer that contains the tag value.
	 * @param[in] size The size of the buff in bytes.
	 * @return true for success or false otherwise.
	 */
	virtual bool deserializeValue(const ILTagFactory & factory,
			const void * buff, std::uint64_t size) = 0;

	/**
	 * Verifies if this tag is implicit or not.
	 * @return true if this tag is implicit or false otherwise.
	 */
	bool isImplicit() const {
		return ILTag::isImplicit(this->_tagID);
	}

	/**
	 * Verifies if this tag is standard or not.
	 *
	 * @return true if this tag is standard or false otherwise.
	 */
	bool isStandard() const {
		return ILTag::isStandard(this->_tagID);
	}

	/**
	 * Verifies if a given tag id denotes an implicit or explicit tag.
	 *
	 * @param[in] tagID the tagId.
	 * @return true if the tag is implicit or false otherwise.
	 */
	static bool isImplicit(std::uint64_t tagId) {
		return (tagId < 16);
	}

	/**
	 * Verifies if a given tag id standard or not. All tags with IDs lower than
	 * 32 are considered part of the standard and should not be redefined by
	 * applications.
	 *
	 * @param[in] tagID the tagId.
	 * @return true if the tag is standard or false otherwise.
	 */
	static bool isStandard(std::uint64_t tagId) {
		return (tagId < 32);
	}
};

/**
 * This class implements the base class for all raw tags. The tag
 * information will be stored inside a IRBuffer to allow manipulation.
 *
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
 * @since 2017.12.27
 */
class ILRawTag: public ILTag {
protected:
	ircommon::IRBuffer _value;

	virtual bool serializeValue(ircommon::IRBuffer & out) const;
public:
	ILRawTag(std::uint64_t id, bool secure = false);

	virtual ~ILRawTag() = default;

	virtual std::uint64_t size() const;

	virtual bool deserializeValue(const ILTagFactory & factory,
			const void * buff, std::uint64_t size);

	/**
	 * Grants read-only access to the internal buffer.
	 *
	 * @return The instance of the internal buffer.
	 */
	const ircommon::IRBuffer & value() const {
		return this->_value;
	}

	/**
	 * Grants read/write access to the internal buffer.
	 *
	 * @return The instance of the internal buffer.
	 */
	ircommon::IRBuffer & value() {
		return this->_value;
	}
};

/**
 * This class implements the base class for all tag-list tags.
 *
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
 * @since 2018.01.22
 */
class ILTagListTag: public ILTag {
public:
	typedef std::shared_ptr<ILTag> SharedPointer;
protected:
	std::vector<SharedPointer> _list;

	virtual bool serializeValue(ircommon::IRBuffer & out) const;
public:
	ILTagListTag(std::uint64_t id);

	virtual ~ILTagListTag() = default;

	int count() const {
		return this->_list.size();
	}

	virtual std::uint64_t size() const;

	virtual bool deserializeValue(const ILTagFactory & factory,
			const void * buff, std::uint64_t size);

	bool add(SharedPointer obj);

	bool add(ILTag * obj) {
		return this->add(SharedPointer(obj));
	}

	bool insert(int idx, SharedPointer obj);

	bool insert(int idx, ILTag * obj) {
		return this->insert(idx, SharedPointer(obj));
	}

	bool remove(int idx);

	void clear() {
		this->_list.clear();
	}

	SharedPointer & operator [](int idx);

	const SharedPointer & operator [](int idx) const;
};

/**
 * This abstract class implements a factory that creates ILTag instances
 * based on their IDs.
 *
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
 * @since 2018.01.20
 */
class ILTagFactory {
public:
	/**
	 * Creates a new instance of this class.
	 */
	ILTagFactory() = default;

	/**
	 * Disposes this instance and releases all associated resources.
	 */
	virtual ~ILTagFactory() = default;

	/**
	 * Creates a new instance of the tag based on the ID.
	 *
	 * @param[in] tagId The tag id.
	 * @return The instance of ILTag that implements this ID or NULL if the ID
	 * is unsupported.
	 * @note Custom factories must overwrite this method.
	 */
	virtual ILTag * create(std::uint64_t tagId) const;

	/**
	 * Deserializes the first ILTag found inside the input.
	 *
	 * @param[in] The input buffer.
	 * @return The extracted tag or NULL otherwise.
	 */
	ILTag * deserialize(IRBuffer & inp) const;
};

/**
 * This class implements a factory that creates ILTag instances
 * based on their IDs.
 *
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
 * @since 2018.01.20
 */
class ILRawTagFactory: public ILTagFactory {
public:
	/**
	 * Creates a new instance of this class.
	 */
	ILRawTagFactory();

	/**
	 * Disposes this instance and releases all associated resources.
	 */
	virtual ~ILRawTagFactory() = default;

	virtual ILTag * create(std::uint64_t tagId) const;
};

} //namespace iltags
} //namespace ircommon

#endif /* _IRCOMMON_ILTAG_H_ */
