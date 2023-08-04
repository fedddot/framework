#include <sstream>
#include <memory>
#include <algorithm>

#include "idata.hpp"
#include "string.hpp"
#include "array.hpp"
#include "object.hpp"

#include "json_common.hpp"
#include "json_serializer.hpp"

using namespace json;
using namespace data;

std::string JsonSerializer::serialize(const IData& data) {
	switch (data.getDataType()) {
	case IData::DataType::COMPOSITE:
		return serializeComposite(data);
	case IData::DataType::VALUE:
		return serializeValue(data);
	default:
		break;
	}
	throw UnexpectedDataType("JsonSerializer::serialize", "");
}

std::string JsonSerializer::serializeComposite(const IData& data) {
	const Composite& composite_data = dynamic_cast<const Composite&>(data);
	switch (composite_data.getCompositeType()) {
	case Composite::CompositeType::ARRAY:
		return serializeArray(data);
	case Composite::CompositeType::OBJECT:
		return serializeObject(data);
	default:
		break;
	}
	throw UnexpectedDataType("JsonSerializer::serializeComposite", "");
}

std::string JsonSerializer::serializeArray(const IData& data) {
	auto array = dynamic_cast<const Array&>(data);
	std::stringstream serial_data;
	serial_data << static_cast<char>(JsonSpecialChar::ARRAY_START);
	auto iter = array.begin();
	while (array.end() != iter) {
		auto member_ptr = *iter;
		if (nullptr == member_ptr) {
			throw BadMember("JsonSerializer::serializeArray", "nullptr");
		}
		serial_data << serialize(*member_ptr);
		++iter;
		if (array.end() != iter) {
			serial_data << static_cast<char>(JsonSpecialChar::DELIMITER) << static_cast<char>(JsonSpecialChar::SPACE);
		}
	}
	serial_data << static_cast<char>(JsonSpecialChar::ARRAY_END);
	return serial_data.str();
}

std::string JsonSerializer::serializeObject(const IData& data) {
	auto object = dynamic_cast<const Object&>(data);
	std::stringstream serial_data;
	serial_data << static_cast<char>(JsonSpecialChar::OBJECT_START);
	auto iter = object.begin();
	while (object.end() != iter) {
		auto member_ptr = iter->second;
		if (nullptr == member_ptr) {
			throw BadMember("JsonSerializer::serializeObject", "nullptr");
		}
		serial_data << static_cast<char>(JsonSpecialChar::STRING_START) << iter->first << static_cast<char>(JsonSpecialChar::STRING_END) << static_cast<char>(JsonSpecialChar::SEMICOLON) << static_cast<char>(JsonSpecialChar::SPACE) << serialize(*member_ptr);
		++iter;
		if (object.end() != iter) {
			serial_data << static_cast<char>(JsonSpecialChar::DELIMITER) << static_cast<char>(JsonSpecialChar::SPACE);
		}
	}
	serial_data << static_cast<char>(JsonSpecialChar::OBJECT_END);
	return serial_data.str();
}

std::string JsonSerializer::serializeValue(const IData& data) {
	const Value& data_value = dynamic_cast<const Value&>(data);
	switch (data_value.getDataValueType()) {
	case Value::DataValueType::STRING:
		return serializeString(data);
	default:
		break;
	}
	throw UnexpectedDataType("JsonSerializer::serializeValue", "");
}

std::string JsonSerializer::serializeString(const IData& data) {
	auto str = dynamic_cast<const String&>(data);
	std::stringstream serial_data;
	serial_data << static_cast<char>(JsonSpecialChar::STRING_START) << str << static_cast<char>(JsonSpecialChar::STRING_END);
	return serial_data.str();
}

JsonSerializer::UnexpectedDataType::UnexpectedDataType(const std::string& where, const std::string& note): m_msg("") {
	std::stringstream msg_stream;
	msg_stream << "Data of unexpected type received at " << where;
	if (!note.empty()) {
		msg_stream << " (note: " << note << ")";
	}
	m_msg = msg_stream.str();
}

const char *JsonSerializer::UnexpectedDataType::what() const noexcept {
	return m_msg.c_str();
}

JsonSerializer::BadMember::BadMember(const std::string& where, const std::string& note): m_msg("") {
	std::stringstream msg_stream;
	msg_stream << "Bad member pointer received at " << where;
	if (!note.empty()) {
		msg_stream << " (note: " << note << ")";
	}
	m_msg = msg_stream.str();
}

const char *JsonSerializer::BadMember::what() const noexcept {
	return m_msg.c_str();
}