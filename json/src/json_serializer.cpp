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

std::vector<char> JsonSerializer::serialize(const IData& data) {
	switch (data.getDataType()) {
	case IData::DataType::COMPOSITE:
		return serializeComposite(data);
	case IData::DataType::VALUE:
		return serializeValue(data);
	default:
		break;
	}
	throw UnexpectedDataType("serialize");
}

std::vector<char> JsonSerializer::serializeComposite(const IData& data) {
	const Composite& composite_data = dynamic_cast<const Composite&>(data);
	switch (composite_data.getCompositeType()) {
	case Composite::CompositeType::ARRAY:
		return serializeArray(data);
	case Composite::CompositeType::OBJECT:
		return serializeObject(data);
	default:
		break;
	}
	throw UnexpectedDataType("serializeComposite");
}

std::vector<char> JsonSerializer::serializeArray(const IData& data) {
	auto array = dynamic_cast<const Array&>(data);
	std::vector<char> serial_data;
	serial_data.push_back(static_cast<char>(JsonSpecialChar::ARRAY_START));
	auto iter = array.begin();
	while (array.end() != iter) {
		auto member_ptr = *iter;
		if (nullptr == member_ptr) {
			throw BadMemberPointer("serializeArray");
		}
		auto serial_member = serialize(*member_ptr);
		serial_data.insert(serial_data.end(), serial_member.begin(), serial_member.end());
		++iter;
		if (array.end() != iter) {
			serial_data.push_back(static_cast<char>(JsonSpecialChar::DELIMITER));
			serial_data.push_back(static_cast<char>(JsonSpecialChar::SPACE));
		}
	}
	serial_data.push_back(static_cast<char>(JsonSpecialChar::ARRAY_END));
	return serial_data;
}

std::vector<char> JsonSerializer::serializeObject(const IData& data) {
	auto object = dynamic_cast<const Object&>(data);
	std::vector<char> serial_data;
	serial_data.push_back(static_cast<char>(JsonSpecialChar::OBJECT_START));
	auto iter = object.begin();
	while (object.end() != iter) {
		auto member_ptr = iter->second;
		if (nullptr == member_ptr) {
			throw BadMemberPointer("serializeObject");
		}
		auto serial_member = serialize(*member_ptr);
		auto field_name = serialize(String(iter->first));
		
		serial_data.insert(serial_data.end(), field_name.begin(), field_name.end());
		serial_data.push_back(static_cast<char>(JsonSpecialChar::SEMICOLON));
		serial_data.push_back(static_cast<char>(JsonSpecialChar::SPACE));
		serial_data.insert(serial_data.end(), serial_member.begin(), serial_member.end());
		++iter;
		if (object.end() != iter) {
			serial_data.push_back(static_cast<char>(JsonSpecialChar::DELIMITER));
			serial_data.push_back(static_cast<char>(JsonSpecialChar::SPACE));
		}
	}
	serial_data.push_back(static_cast<char>(JsonSpecialChar::OBJECT_END));
	return serial_data;
}

std::vector<char> JsonSerializer::serializeValue(const IData& data) {
	const Value& data_value = dynamic_cast<const Value&>(data);
	switch (data_value.getDataValueType()) {
	case Value::DataValueType::STRING:
		return serializeString(data);
	default:
		break;
	}
	throw UnexpectedDataType("serializeValue");
}

std::vector<char> JsonSerializer::serializeString(const IData& data) {
	auto str = dynamic_cast<const String&>(data);
	std::vector<char> serial_str;
	serial_str.push_back(static_cast<char>(JsonSpecialChar::STRING_START));
	serial_str.insert(serial_str.end(), str.begin(), str.end());
	serial_str.push_back(static_cast<char>(JsonSpecialChar::STRING_END));
	return serial_str;
}

JsonSerializer::Exception::Exception(const std::string& msg): m_msg(msg) {

}

JsonSerializer::UnexpectedDataType::UnexpectedDataType(const std::string& where): Exception("in JsonSerializer::" + where + ": unexpected data type") {

}

JsonSerializer::BadMemberPointer::BadMemberPointer(const std::string& where): Exception("in JsonSerializer::" + where + ": bad member pointer value") {

}
