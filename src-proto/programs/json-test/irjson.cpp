#include "irjson.h"

#include <stdexcept>

using namespace  ircommon::json;

void IRJsonObject::set(const std::string & name, std::shared_ptr<IRJsonBase> & value) {
	this->_map[name] = value;
}

bool IRJsonObject::contains(const std::string & name) const {
	return (this->_map.find(name) != this->_map.end());
}

std::shared_ptr<IRJsonBase> & IRJsonObject::operator[](const std::string & name) {

	auto found = this->_map.find(name);
	if (found != this->_map.end()) {
		return found->second;
	} else {
		throw std::invalid_argument("Not found.");
	}
}

const std::shared_ptr<IRJsonBase> & IRJsonObject::operator[](const std::string & name) const {

	auto found = this->_map.find(name);
	if (found != this->_map.end()) {
		return found->second;
	} else {
		throw std::invalid_argument("Not found.");
	}
}

void IRJsonObject::remove(const std::string & name) {
	this->_map.erase(name);
}

void IRJsonObject::getAttributeNames(std::vector<std::string> & attr) const {
	for (auto pair = this->_map.begin(); pair != this->_map.end(); pair++) {
		attr.push_back(pair->first);
	}
}

std::shared_ptr<IRJsonBase> & IRJsonArray::operator[](int idx) {
	return this->_values[idx];
}

const std::shared_ptr<IRJsonBase> & IRJsonArray::operator[](int idx) const {
	return this->_values[idx];
}


void IRJsonArray::remove(int idx) {
	this->_values.erase(this->_values.begin() + idx);
}

void IRJsonArray::insert(int idx, const std::shared_ptr<IRJsonBase> & value) {
	this->_values.insert(this->_values.begin() + idx, value);
}

void IRJsonArray::append(const std::shared_ptr<IRJsonBase> & value) {
	this->_values.push_back(value);
}

void IRJsonSerializer::levelUp() {
	this->_level++;
}

void IRJsonSerializer::levelDown() {
	this->_level--;
}

void IRJsonSerializer::beginLine(std::string & out) {
	if (this->_indent) {
		out.append(this->_level, '\t');
	}
}

void IRJsonSerializer::endLine(std::string & out) {
	if (this->_indent) {
		out.append(1, '\n');
	}
}

void IRJsonSerializer::serialize(std::string & out, const IRJsonBase & v) {

	switch(v.type()) {
	case IRJsonBase::ARRAY:
		this->serializeArray(out, static_cast<const IRJsonArray &>(v));
		break;
	case IRJsonBase::BOOLEAN:
		this->serializeBoolean(out, static_cast<const IRJsonBoolean &>(v));
		break;
	case IRJsonBase::DECIMAL:
		this->serializeDecimal(out, static_cast<const IRJsonDecimal &>(v));
		break;
	case IRJsonBase::INTEGER:
		this->serializeInteger(out, static_cast<const IRJsonInteger &>(v));
		break;
	case IRJsonBase::NULL_VALUE:
		this->serializeNull(out);
		break;
	case IRJsonBase::OBJECT:
		this->serializeObject(out, static_cast<const IRJsonObject &>(v));
		break;
	case IRJsonBase::STRING:
		this->serializeString(out, static_cast<const IRJsonString &>(v));
		break;
	}
}

void IRJsonSerializer::serializeNull(std::string & out) {
	out.append("null");
}

void IRJsonSerializer::serializeString(std::string & out, const IRJsonString & v) {
	this->serializeString(out, v.get());
}

void IRJsonSerializer::serializeString(std::string & out, const std::string & v) {

	out.append(1, '\"');
	// TODO Create the escaped string later.
	out.append(v);
	out.append(1, '\"');
}


void IRJsonSerializer::serializeInteger(std::string & out, const IRJsonInteger & v) {
	out.append(std::to_string(v.get()));
}

void IRJsonSerializer::serializeDecimal(std::string & out, const IRJsonDecimal & v) {
	out.append(std::to_string(v.get()));
}

void IRJsonSerializer::serializeBoolean(std::string & out, const IRJsonBoolean & v) {
	if (v.get()) {
		out.append("true");
	} else {
		out.append("false");
	}
}

void IRJsonSerializer::serializeObject(std::string & out, const IRJsonObject & v) {
	std::vector<std::string> attr;

	v.getAttributeNames(attr);
	this->beginLine(out);
	out.append(1, '{');
	this->endLine(out);
	this->levelUp();
	for (int i = 0; i < attr.size(); i++) {
		this->beginLine(out);
		this->serializeString(out, attr[i]);
		out.append(1, ':');
		this->serialize(out, *v[attr[i]]);
		if (i < (attr.size() - 1)) {
			out.append(1, ',');
		}
		this->endLine(out);
	}
	this->levelDown();
	this->beginLine(out);
	out.append(1, '}');
	this->endLine(out);
}

void IRJsonSerializer::serializeArray(std::string & out, const IRJsonArray & v) {

	this->beginLine(out);
	out.append(1, '[');
	this->endLine(out);
	this->levelUp();
	for (int i = 0; i < v.size(); i++) {
		this->beginLine(out);
		this->serialize(out, *(v[i]));
		if (i < (v.size() - 1)) {
			out.append(1, ',');
		}
		this->endLine(out);
	}
	this->levelDown();
	this->beginLine(out);
	out.append(1, ']');
	this->endLine(out);
}
