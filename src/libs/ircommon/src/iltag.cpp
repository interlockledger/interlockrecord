
#include <ircommon/iltag.h>
#include <ircommon/ilint.h>

//==============================================================================
// Class ILTag
//------------------------------------------------------------------------------
ILTag::ILTag(uint64_t id): _tagID(id) {
}

//------------------------------------------------------------------------------
ILTag::~ILTag() {
}

//------------------------------------------------------------------------------
uint64_t ILTag::getSerializedSize() const {

	// ILInt + ILInt + Payload
	return ILIntSize(this->getID()) +
			ILIntSize(this->getSize()) +
			this->getSize();
}

//==============================================================================
// Class ILRawTag
//------------------------------------------------------------------------------
ILRawTag::ILRawTag(uint64_t id, uint64_t size, bool secure): ILTag(id) {
	this->_data = new uint8_t[size];
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
uint64_t ILRawTag::serialize(std::vector<uint8_t> & out) const {
	uint8_t tmp[9];



}

//------------------------------------------------------------------------------
bool ILRawTag::resize(uint64_t newSize) {
}

