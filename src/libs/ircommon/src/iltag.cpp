
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

