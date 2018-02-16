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
	/**
	 * IDs of all known standard tags.
	 */
	typedef enum {
		/**
		 * The NULL tag. It contains no payload.
		 */
		TAG_NULL = 0,
		/**
		 * The boolean tag. It contains a single byte that represents true (1)
		 * or false (0).
		 */
		TAG_BOOL = 1,
		/**
		 * The signed 8-bit integer tag. It contains a single byte that
		 * represents the value.
		 */
		TAG_INT8 = 2,
		/**
		 * The unsigned 8-bit integer tag. It contains a single byte that
		 * represents the value.
		 */
		TAG_UINT8 = 3,
		/**
		 * The signed 16-bit integer tag. It contains 2 bytes that represents
		 * the value in Big Endian.
		 */
		TAG_INT16 = 4,
		/**
		 * The unsigned 16-bit integer tag. It contains 2 bytes that represents
		 * the value in Big Endian.
		 */
		TAG_UINT16 = 5,
		/**
		 * The signed 32-bit integer tag. It contains 4 bytes that represents
		 * the value in Big Endian.
		 */
		TAG_INT32 = 6,
		/**
		 * The unsigned 32-bit integer tag. It contains 4 bytes that represents
		 * the value in Big Endian.
		 */
		TAG_UINT32 = 7,
		/**
		 * The signed 64-bit integer tag. It contains 8 bytes that represents
		 * the value in Big Endian.
		 */
		TAG_INT64 = 8,
		/**
		 * The unsigned 64-bit integer tag. It contains 8 bytes that
		 * represents the value in Big Endian.
		 */
		TAG_UINT64 = 9,
		/**
		 * The ILInt64 tag. It contains 1 to 9 bytes that represents a 64-bit
		 * integer encoded as an ILInt.
		 */
		TAG_ILINT64 = 10,
		/**
		 * The single precision floating point tag. It contains a 4 bytes that
		 * represents the value encoded as IEEE-754 in Big Endian.
		 */
		TAG_BINARY32 = 11,
		/**
		 * The double precision floating point tag. It contains a 8 bytes that
		 * represents the value encoded as IEEE-754 in Big Endian.
		 */
		TAG_BINARY64 = 12,
		/**
		 * The quadruple precision floating point tag. It contains a 16 bytes
		 * that represents the value encoded as IEEE-754 in Big Endian. The
		 * support for this tag is optional.
		 */
		TAG_BINARY128 = 13,
		/**
		 * The byte array tag. It contains a byte array with 0 or more bytes.
		 */
		TAG_BYTE_ARRAY = 16,
		/**
		 * The string tag. It contains a UTF-8 string with 0 or more caracters.
		 */
		TAG_STRING = 17,
		/**
		 * The big integer tag. It contains the value encoded as
		 * two's complement big endian value.
		 */
		TAG_BINT = 18,
		/**
		 * The big decimal tag. It contains an arbitrary precision decimal
		 * encoded as an ILInt64 for the precision and the integral part as
		 * encoded as two's complement big endian value.
		 */
		TAG_BDEC = 19,
		/**
		 * The ILnt64 array tag. It contains an array of 64-bit integers encoded
		 * as ILInt64 values. It is composed by an ILInt64 that encodes the
		 * number of entries followed by the entries themselves.
		 */
		TAG_ILINT64_ARRAY = 20,
		/**
		 * The ILTag array tag. It contains an ILInt64 value that encodes the
		 * number of objects followed by the serialization of the tags.
		 */
		TAG_ILTAG_ARRAY = 21,
        /**
		 * The ILTag sequence tag. It contains the serialization of a sequence of tags.
		 */
		TAG_ILTAG_SEQ = 22
	} KnownStandardTagID;
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
	uint64_t id() const {
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

	/**
	 * Returns the size of the values for all implicit tags that have a fixed
	 * size. This means that the size of TAG_ILINT64 is not covered by this
	 * method.
	 *
	 * @param[in] tagId The tag Id.
	 * @return The implicit tag size.
	 */
	static std::uint64_t getImplicitValueSize(std::uint64_t tagId);
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
	/**
	 * Creates a new instance of this class.
	 *
	 * @param[in] id The tag ID.
	 * @param[in] secure If true, uses an internal secure buffer.
	 * @param[in] inc The increment of the internal buffer.
	 */
	ILRawTag(std::uint64_t id, bool secure = false,
			std::uint64_t inc = ircommon::IRBuffer::DEFAULT_INCREMENT) :
			ILTag(id), _value(0, secure, inc) {}

	/**
	 * Disposes this instance and releases all associated resources.
	 */
	virtual ~ILRawTag() = default;

	virtual std::uint64_t size() const {
		return this->value().size();
	}

	virtual bool deserializeValue(const ILTagFactory & factory,
			const void * buff, std::uint64_t size);

	/**
	 * Grants read-only access to the internal buffer.
	 *
	 * @return The instance of the internal buffer.
	 */
	inline const ircommon::IRBuffer & value() const {
		return this->_value;
	}

	/**
	 * Grants read/write access to the internal buffer.
	 *
	 * @return The instance of the internal buffer.
	 */
	inline ircommon::IRBuffer & value() {
		return this->_value;
	}

	/**
	 * Verifies if this instance is secure.
	 *
	 * @return true if the instance is secure or false otherwise.
	 * @since 2018.01.23
	 */
	inline bool secure() const {
		return this->_value.secure();
	}
};

/**
 * This class implements the base class for all tag-list tags.
 * If <b>noCounter</b> is false, it follows the syntax of the
 * TAG_ILTAG_ARRAY, otherwise it follows the syntax of TAG_ILTAG_SEQ.
 *
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
 * @since 2018.01.22
 * @note As a safeguard, entries set to nullptr will be encoded as TAG_NULL.
 */
class ILTagListTag: public ILTag {
public:
	typedef std::shared_ptr<ILTag> SharedPointer;
protected:
	std::vector<SharedPointer> _list;

	virtual bool serializeValue(ircommon::IRBuffer & out) const;

	/**
	 * Determines it the serialization adds or not the tag counter
	 * in the serialization.
     * @since 2018.02.15
	 */
	bool _noCounter;
public:
	/**
	 * Creates a new instance of this class.
	 *
	 * @param[in] id The tag ID.
	 * @param[in] noCounter If true, removes the number of tags from the beginning of
	 * the serialization.
	 */
	ILTagListTag(std::uint64_t id, bool noCounter = false);

	/**
	 * Disposes this instance and releases all associated resources.
	 */
	virtual ~ILTagListTag() = default;

	/**
	 * Returns the number of tags.
	 *
	 * @return The number of tags.
	 */
	int count() const {
		return this->_list.size();
	}

	virtual std::uint64_t size() const;

	virtual bool deserializeValue(const ILTagFactory & factory,
			const void * buff, std::uint64_t size);

	/**
	 * Adds a new tag to the end of the array.
	 *
	 * @param[in] obj The tag to be added.
	 * @return true for success or false otherwise.
	 */
	bool add(SharedPointer obj);

	/**
	 * Adds a new tag to the end of the array.
	 *
	 * @param[in] obj The tag to be added. This method will claim the ownership
	 * of this instance.
	 * @return true for success or false otherwise.
	 */
	bool add(ILTag * obj) {
		return this->add(SharedPointer(obj));
	}

	/**
	 * Inserts a new tag in a given position.
	 *
	 * @param[in] idx The insert position.
	 * @param[in] obj The tag to be added.
	 * @return true for success or false otherwise.
	 */
	bool insert(int idx, SharedPointer obj);

	/**
	 * Inserts a new tag in a given position.
	 *
	 * @param[in] idx The insert position.
	 * @param[in] obj The tag to be added. This method will claim the ownership
	 * of this instance.
	 * @return true for success or false otherwise.
	 */
	bool insert(int idx, ILTag * obj) {
		return this->insert(idx, SharedPointer(obj));
	}

	/**
	 * Removes the tag at a given index.
	 *
	 * @param[in] idx The position.
	 * @return true for success or false otherwise.
	 */
	bool remove(int idx);

	/**
	 * Removes all tags.
	 *
	 * @return true for success or false otherwise.
	 */
	void clear() {
		this->_list.clear();
	}

	/**
	 * Grants read/write access to the tag a given postion.
	 *
	 * @param[in] idx The position.
	 * @return A reference to the SharedPointer that holds the tag.
	 */
	SharedPointer & operator [](int idx);

	/**
	 * Grants read-only access to the tag a given postion.
	 *
	 * @param[in] idx The position.
	 * @return A reference to the SharedPointer that holds the tag.
	 */
	const SharedPointer & operator [](int idx) const;
};

/**
 * This class implements a factory that creates ILTag instances based on their
 * IDs. Furthermore it can be used to deserialize tags from their byte
 * representation.
 *
 * <p>This class has two distinct operation modes, one that controls the
 * security of the newly created instances and other that controls how unknown
 * tags are handled.</p>
 *
 * <p>When secure mode is enabled, all inner classes, whenever possible, are
 * created in secure mode when available (defaults to false).</p>
 *
 * <p>When strict mode is enabled, all unknown classes are treated as errors
 * during the deserialization. Otherwise, all unknown IDs are deserialized to
 * an instance of ILRawTag.</p>
 *
 * <p>This default implementation knows no specialized classes. This means that
 * the method ILTagFactory::create() will always return null when strict mode
 * is true or an instance of ILRawTag otherwise. Subclasses of the this class
 * must override the ILTagFactory::create() method to handle specialized classes
 * and call the super class create() implementation for all unknown IDs.</p>
 *
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
 * @since 2018.01.20
 */
class ILTagFactory {
private:
	/**
	 * Secure flag.
	 */
	bool _secure;
	/**
	 * Flag that indicates the state of the strict mode.
	 */
	bool _strictMode;
public:
	/**
	 * Creates a new instance of this class.
	 *
	 * @param[in] secureMode The secure mode state.
	 * @param[in] strictMode The strict mode state.
	 */
	ILTagFactory(bool secureMode = false, bool strictMode = false):
		_secure(secureMode),_strictMode(strictMode) {};

	/**
	 * Disposes this instance and releases all associated resources.
	 */
	virtual ~ILTagFactory() = default;

	/**
	 * Creates a new instance of the tag based on the ID.
	 *
	 * @param[in] tagId The tag id.
	 * @return The instance of ILTag that implements this ID or NULL if it is
	 * unknown.
	 * @note Custom factories must overwrite this method in order to provide
	 * additional or custom implementations of a given ID.
	 */
	virtual ILTag * create(std::uint64_t tagId) const;

	/**
	 * Deserializes the first ILTag found inside the input.
	 *
	 * @param[in] The input buffer.
	 * @return The extracted tag or NULL otherwise.
	 */
	ILTag * deserialize(IRBuffer & inp) const;

	/**
	 * Verifies if this instance is working in secure mode.
	 *
	 * @return true if it is in secure mode or false otherwise.
	 */
	bool secure() const{
		return this->_secure;
	}

	/**
	 * Sets the state of secure mode.
	 *
	 * @param[in] v true to enable it or false otherwise.
	 * @since 2018.01.25
	 */
	void setSecure(bool v) {
		this->_secure = v;
	}

	/**
	 * Returns the strict mode status. If true, all unknown tags will be treated
	 * as errors during the deserialization process. Otherwise, unknown tags
	 * will be deserialized as instances of ILRawTag.
	 *
	 * <p>The strict mode is disabled by default.</p>
	 *
	 * @return The value of flag strict.
	 * @since 2018.01.25
	 */
	bool strictMode() const {
		return this->_strictMode;
	}

	/**
	 * Sets the state of the strict mode.
	 *
	 * @param[in] v Use true to enable it or false otherwise.
	 * @since 2018.01.25
	 */
	void setStrictMode(bool v) {
		this->_strictMode = v;
	}

	/**
	 * This method extracts the tag header from an IRBuffer. The header will
	 * be read from the input buffer current position. On success, the position
	 * will of the buffer will be pointing to the end of the tag header.
	 *
	 * @param[in] inp The input buffer.
	 * @param[out] tagId The ID of the tag.
	 * @param[out] tagSize The size of the tag.
	 * @return true for success or false otherwise.
	 * @since 2018.01.24
	 */
	static bool extractTagHeader(IRBuffer & inp,
			std::uint64_t & tagId, std::uint64_t & tagSize);

	/**
	 * Deserializes the first ILTag found inside the input and
	 * fills the tag instance properly.
	 *
	 * <p>This method will succeed if and only if the serialized
	 * tag type matches the expected tag type defined by the tag
	 * instance.</p>
	 *
	 * @param[in] inp The input buffer.
	 * @param[out] tag The tag.
	 * @return true on success or false otherwise.
	 * @since 2018.02.01
	 */
	bool deserialize(IRBuffer & inp, ILTag & tag) const;
};

/**
 * This class defines methods that can be used to perform
 * some common operations with tags.
 *
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
 * @since 2018.02.01
 */
class ILTagUtil {
public:
	/**
	 * Verifies if two ILTag instances have the same ID.
	 *
	 * @param[in] a An ILTag.
	 * @param[in] b Another ILTag.
	 * @return true if they share the same ID or false otherwise.
	 */
	static bool sameID(const ILTag & a, const ILTag & b);

	/**
	 * Verifies if two ILTag instances have the same class.
	 *
	 * @param[in] a An ILTag.
	 * @param[in] b Another ILTag.
	 * @return true if they share the class ID or false otherwise.
	 */
	static bool sameClass(const ILTag & a, const ILTag & b);

	/**
	 * Verifies if two ILTag instances are equal.
	 *
	 * <p>This is achieved by comparing their serializations. Because
	 * of that, the use of this method should be avoided whenever
	 * possible. The main motivation to this method is to ease
	 * the creation of unit-tests regarding the tags.</p>
	 *
	 * @param[in] a An ILTag.
	 * @param[in] b Another ILTag.
	 * @return true if they are equal or false otherwise.
	 */
	static bool equals(const ILTag & a, const ILTag & b);
};

} //namespace iltags
} //namespace ircommon

#endif /* _IRCOMMON_ILTAG_H_ */
