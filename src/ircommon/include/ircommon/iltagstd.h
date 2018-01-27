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
#ifndef _IRCOMMON_ILTAGSTD_H_
#define _IRCOMMON_ILTAGSTD_H_

#include <ircommon/iltag.h>
#include <ircommon/irutils.h>
#include <ircommon/irfp.h>
#include <cstring>

namespace ircommon {
namespace iltags {

/**
 * This class implements the ILTag null.
 *
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
 * @since 2018.01.24
 */
class ILNullTag : public ILTag {
protected:
	virtual bool serializeValue(ircommon::IRBuffer & out) const;
public:
	ILNullTag() : ILTag(ILTag::TAG_NULL){}

	virtual ~ILNullTag() = default;

	virtual std::uint64_t size() const {
		return 0;
	}

	virtual bool deserializeValue(const ILTagFactory & factory,
			const void * buff, std::uint64_t size);
};

/**
 * This class implements the ILTag boolean.
 *
 * @since 2018.01.24
 * @note This type is a specialization of ILBasicTag.
 */
class ILBoolTag : public ILTag {
protected:
	bool _value;

	virtual bool serializeValue(ircommon::IRBuffer & out) const;
public:
	ILBoolTag() : ILTag(ILTag::TAG_BOOL), _value(false){}

	virtual ~ILBoolTag() = default;

	virtual std::uint64_t size() const;

	virtual bool deserializeValue(const ILTagFactory & factory,
			const void * buff, std::uint64_t size);

	/**
	 * Returns the value of this tag.
	 *
	 * @return The value of the tag.
	 */
	bool value() const {
		return this->_value;
	}

	/**
	 * Sets the value of this tag.
	 *
	 * @param[in] v The value.
	 */
	void setValue(bool v) {
		this->_value = v;
	}
};

/**
 * This class template implements the generic ILTag that handles integer values.
 *
 * <p>It is important to notice that the methods serializeValue() and
 * deserializeValue() must be implemented by the specializations. Furthermore,
 * some types may also replace the default implementation of size().</p>
 *
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
 * @since 2018.01.24
 * @tparam ValueType The value type. It must be one of the standard integer
 * types.
 * @tparam TagID The tag id.
 */
template <class ValueType, std::uint64_t TagID>
class ILBasicIntTag : public ILTag {
protected:
	ValueType _value;

	virtual bool serializeValue(ircommon::IRBuffer & out) const {
		return out.writeInt(this->_value);
	}
public:
	ILBasicIntTag() : ILTag(TagID), _value(0) {}
	virtual ~ILBasicIntTag() = default;

	virtual std::uint64_t size() const {
		return sizeof(ValueType);
	}

	virtual bool deserializeValue(const ILTagFactory & factory,
			const void * buff, std::uint64_t size) {

		if (size != sizeof(ValueType)) {
			return false;
		}
		IRUtils::BE2Int(buff, this->_value);
		return true;
	}

	/**
	 * Returns the value of this tag.
	 *
	 * @return The value of the tag.
	 */
	inline const ValueType & value() const {
		return this->_value;
	}

	/**
	 * Sets the value of this tag.
	 *
	 * @param[in] v The value.
	 */
	inline void setValue(ValueType v) {
		this->_value = v;
	}
};

/**
 * This class implements the ILTag 8-bit integer.
 *
 * @since 2018.01.24
 * @note This type is a specialization of ILBasicTag.
 */
typedef ILBasicIntTag<std::int8_t, ILTag::TAG_INT8> ILInt8Tag;

/**
 * This class implements the ILTag 8-bit unsigned integer.
 *
 * @since 2018.01.24
 * @note This type is a specialization of ILBasicTag.
 */
typedef ILBasicIntTag<std::uint8_t, ILTag::TAG_UINT8> ILUInt8Tag;

/**
 * This class implements the ILTag 16-bit integer.
 *
 * @since 2018.01.24
 * @note This type is a specialization of ILBasicTag.
 */
typedef ILBasicIntTag<std::int16_t, ILTag::TAG_INT16> ILInt16Tag;

/**
 * This class implements the ILTag 16-bit unsigned integer.
 *
 * @since 2018.01.24
 * @note This type is a specialization of ILBasicTag.
 */
typedef ILBasicIntTag<std::uint16_t, ILTag::TAG_UINT16> ILUInt16Tag;

/**
 * This class implements the ILTag 32-bit integer.
 *
 * @since 2018.01.24
 * @note This type is a specialization of ILBasicTag.
 */
typedef ILBasicIntTag<std::int32_t, ILTag::TAG_INT32> ILInt32Tag;

/**
 * This class implements the ILTag 32-bit unsigned integer.
 *
 * @since 2018.01.24
 * @note This type is a specialization of ILBasicTag.
 */
typedef ILBasicIntTag<std::uint32_t, ILTag::TAG_UINT32> ILUInt32Tag;

/**
 * This class implements the ILTag 64-bit integer.
 *
 * @since 2018.01.24
 * @note This type is a specialization of ILBasicTag.
 */
typedef ILBasicIntTag<std::int64_t, ILTag::TAG_INT64> ILInt64Tag;

/**
 * This class implements the ILTag 64-bit unsigned integer.
 *
 * @since 2018.01.24
 * @note This type is a specialization of ILBasicTag.
 */
typedef ILBasicIntTag<std::uint64_t, ILTag::TAG_UINT64> ILUInt64Tag;

/**
 * This class implements the ILTag ILInt64.
 *
 * @since 2018.01.24
 * @note This type is a specialization of ILBasicTag.
 */
class ILILIntTag : public ILTag {
protected:
	std::uint64_t _value;

	virtual bool serializeValue(ircommon::IRBuffer & out) const;
public:
	ILILIntTag() : ILTag(ILTag::TAG_ILINT64), _value(false){}

	virtual ~ILILIntTag() = default;

	virtual std::uint64_t size() const;

	virtual bool deserializeValue(const ILTagFactory & factory,
			const void * buff, std::uint64_t size);

	/**
	 * Returns the value of this tag.
	 *
	 * @return The value of the tag.
	 */
	std::uint64_t value() const {
		return this->_value;
	}

	/**
	 * Sets the value of this tag.
	 *
	 * @param[in] v The value.
	 */
	void setValue(std::uint64_t v) {
		this->_value = v;
	}
};

/**
 * This class template implements the generic ILTag that handles floating point
 * values.
 *
 * <p>It is important to notice that the methods serializeValue() and
 * deserializeValue() must be implemented by the specializations. Furthermore,
 * some types may also replace the default implementation of size().</p>
 *
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
 * @since 2018.01.24
 * @tparam ValueType The value type. It must be one of the floating point types.
 * @tparam TagID The tag id.
 */
template <class ValueType, std::uint64_t TagID>
class ILBasicFloatTag : public ILTag {
protected:
	ValueType _value;

	virtual bool serializeValue(ircommon::IRBuffer & out) const {
		return out.writeFloat(this->_value);
	}
public:
	ILBasicFloatTag() : ILTag(TagID),_value(0){}
	virtual ~ILBasicFloatTag() = default;

	virtual std::uint64_t size() const {
		return sizeof(ValueType);
	}

	virtual bool deserializeValue(const ILTagFactory & factory,
			const void * buff, std::uint64_t size) {

		if (size != sizeof(ValueType)) {
			return false;
		}
		IRFloatingPoint::toFloat(true, buff, this->_value);
		return true;
	}

	/**
	 * Returns the value of this tag.
	 *
	 * @return The value of the tag.
	 */
	inline const ValueType & value() const {
		return this->_value;
	}

	/**
	 * Sets the value of this tag.
	 *
	 * @param[in] v The value.
	 */
	inline void setValue(ValueType v) {
		this->_value = v;
	}
};

/**
 * This class implements the ILTag single precision floating point.
 *
 * @since 2018.01.24
 * @note This type is a specialization of ILBasicTag.
 */
typedef ILBasicFloatTag<float, ILTag::TAG_BINARY32> ILBinary32Tag;

/**
 * This class implements the ILTag double precision floating point.
 *
 * @since 2018.01.24
 * @note This type is a specialization of ILBasicTag.
 */
typedef ILBasicFloatTag<double, ILTag::TAG_BINARY64> ILBinary64Tag;

/**
 * This class implements the ILTag string.
 *
 * @since 2018.01.24
 * @note This type is a specialization of ILBasicTag.
 */
class ILStringTag : public ILTag {
protected:
	std::string _value;

	virtual bool serializeValue(ircommon::IRBuffer & out) const;
public:
	ILStringTag() : ILTag(ILTag::TAG_STRING), _value(){}

	virtual ~ILStringTag() = default;

	virtual std::uint64_t size() const;

	virtual bool deserializeValue(const ILTagFactory & factory,
			const void * buff, std::uint64_t size);

	/**
	 * Returns the value of this tag.
	 *
	 * @return The value of the tag.
	 */
	inline const std::string & value() const {
		return this->_value;
	}

	/**
	 * Sets the value of this tag.
	 *
	 * @param[in] v The value.
	 */
	inline void setValue(const std::string & v) {
		this->_value = v;
	}

	/**
	 * Sets the value of this tag.
	 *
	 * @param[in] s The value as a null terminated string.
	 * @return true on success or false otherwise.
	 */
	inline void setValue(const char * s) {
		this->_value = s;
	}

	/**
	 * Sets the value of this tag.
	 *
	 * @param[in] s The value.
	 * @param[in] lenght The number of characters.
	 * @return true on success or false otherwise.
	 */
	inline void setValue(const char * s, std::uint64_t length) {
		this->_value.assign(s, length);
	}
};

/**
 * This class template implements a ILTag that holds a fixed size opaque value.
 * It is similar to the class ILRawTag but it does not allow the resize of the
 * value.
 *
 * <p>Due to optimization reasons, the constructor will not initialize the the
 * contents of the value.</p>
 *
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
 * @since 2018.01.24
 * @tparam TagID The tag ID.
 * @tparam ValueSize The size of the value in bytes.
 */
template <std::uint64_t TagID, std::uint64_t ValueSize>
class ILBasicFixedOpaqueTag : public ILTag {
protected:
	std::uint8_t _value[ValueSize];

	virtual bool serializeValue(ircommon::IRBuffer & out) const {
		return out.write(this->_value, ValueSize);
	}
public:
	ILBasicFixedOpaqueTag() : ILTag(TagID){}

	virtual ~ILBasicFixedOpaqueTag() = default;

	virtual std::uint64_t size() const {
		return ValueSize;
	}

	virtual bool deserializeValue(const ILTagFactory & factory,
			const void * buff, std::uint64_t size) {
		return this->setValue(buff, size);
	}

	/**
	 * Returns the value of this tag. It always have size() bytes in length.
	 *
	 * @return The value of the tag.
	 */
	const void * value() const {
		return this->_value;
	}

	/**
	 * Sets the value of this tag.
	 *
	 * @param[in] v The value.
	 * @param[in] size The size of the value. It must have exact size() bytes or
	 * else this method will fail.
	 * @return true on success or false otherwise.
	 */
	bool setValue(const void * v, std::uint64_t size) {
		if (size != ValueSize) {
			return false;
		} else {
			std::memcpy(this->_value, v,ValueSize);
			return true;
		}
	}
};

/**
 * This class implements the ILTag quadruple precision floating point.
 *
 * <p>Since most C++ compilers doesn't implement the quadruple precision
 * floating point, this class does not provide methods to handle this type
 * directly.</p>
 *
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
 * @since 2018.01.24
 * @note This type is a specialization of ILBasicFixedOpaqueTag.
 */
typedef ILBasicFixedOpaqueTag<ILTag::TAG_BINARY128, 16> ILBinary128Tag;

/**
 * This class implements the ILTag byte array.
 *
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
 * @since 2018.01.24
 */
class ILByteArrayTag: public ILRawTag {
public:
	ILByteArrayTag(bool secure = false) : ILRawTag(ILTag::TAG_BYTE_ARRAY, secure){}
	virtual ~ILByteArrayTag() = default;
};

/**
 * This class implements the ILTag big integer.
 *
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
 * @since 2018.01.24
 */
class ILBigIntTag: public ILRawTag {
public:
	ILBigIntTag(bool secureMode = true): ILRawTag(ILTag::TAG_BINT, secureMode){}
	virtual ~ILBigIntTag() = default;
};

/**
 * This class implements the ILTag big decimal.
 *
 * <p>The big decimal is represented as an integer part multiplied by
 * 10^(-scale).</p>
 *
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
 * @since 2018.01.24
 */
class ILBigDecimalTag: public ILTag {
private:
	IRBuffer _integral;

	std::int32_t _scale;
protected:
	virtual bool serializeValue(ircommon::IRBuffer & out) const;
public:
	ILBigDecimalTag(bool secureMode = false) : ILTag(ILTag::TAG_BDEC),
			_integral(0, secureMode), _scale(0) {}

	virtual ~ILBigDecimalTag() = default;

	virtual std::uint64_t size() const;

	virtual bool deserializeValue(const ILTagFactory & factory,
			const void * buff, std::uint64_t size);

	/**
	 * Returns the scale of this big decimal.
	 *
	 * @return The scale.
	 */
	std::int32_t scale() const {
		return this->_scale;
	}

	/**
	 * Sets the scale of this big decimal.
	 *
	 * @param[in] v The scale.
	 */
	void setScale(std::int32_t v){
		this->_scale = v;
	}

	/**
	 * Sets the
	 */
	bool setIntegral(const void * value, std::uint64_t size) {
		return this->_integral.set(value, size);
	}

	const IRBuffer & integral() const {
		return this->_integral;
	}
};

/**
 * This class implements the ILTag array of ILInt64.
 *
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
 * @since 2018.01.24
 */
class ILILIntArrayTag: public ILTag{
private:
	std::vector<std::uint64_t> _values;
protected:
	virtual bool serializeValue(ircommon::IRBuffer & out) const;
public:
	ILILIntArrayTag() : ILTag(ILTag::TAG_ILINT64_ARRAY) {}

	virtual ~ILILIntArrayTag() = default;

	virtual std::uint64_t size() const;

	virtual bool deserializeValue(const ILTagFactory & factory,
			const void * buff, std::uint64_t size);

	/**
	 * Number of elements.
	 */
	std::uint64_t count() const {
		return this->_values.size();
	}

	bool add(std::uint64_t v);

	bool insert(std::uint64_t idx, std::uint64_t v);

	bool remove(std::uint64_t idx);

	std::uint64_t get(std::uint64_t idx) const {
		return this->_values[idx];
	}

	void set(std::uint64_t idx, std::uint64_t v){
		this->_values[idx], v;
	}

	std::uint64_t & operator [](std::uint64_t idx) {
		return this->_values[idx];
	}

	std::uint64_t operator [](std::uint64_t idx) const {
		return this->_values[idx];
	}
};

/**
 * This class implements the ILTag array of tags.
 *
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
 * @since 2018.01.24
 */
class ILTagArrayTag: public ILTagListTag {
public:
	ILTagArrayTag(): ILTagListTag(ILTag::TAG_ILTAG_ARRAY) {}

	virtual ~ILTagArrayTag() = default;
};

/**
 * This class implements a factory that handles all standard tag types.
 *
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
 * @since 2018.01.22
 */
class ILStandardTagFactory: public ILTagFactory {
public:
	/**
	 * Creates a new instance of this class.
	 *
	 * @param[in] secureMode The secure mode state.
	 * @param[in] strictMode The strict mode state.
	 */
	ILStandardTagFactory(bool secureMode = false, bool strictMode = false):
			ILTagFactory(secureMode, strictMode) {};

	/**
	 * Disposes this instance and releases all associated resources.
	 */
	virtual ~ILStandardTagFactory() = default;

	virtual ILTag * create(std::uint64_t tagId) const;
};

} // namespace iltags
} // namespace ircommon

#endif /* _IRCOMMON_ILTAGSTD_H_ */
