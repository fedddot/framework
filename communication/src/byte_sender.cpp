#include <stdexcept>
#include <vector>
#include <memory>
#include <algorithm>

#include "isender.hpp"
#include "idata.hpp"
#include "iserializer.hpp"
#include "byte_sender.hpp"

using namespace communication;
using namespace data;

ByteSender::ByteSender(const std::vector<char>& header, const std::size_t& length_field_size, const SerializerSmartPtr& serializer_ptr): 
	m_header(header), 
	m_length_field_size(init_length_field_size(length_field_size)), 
	m_serializer_ptr(init_serializer(serializer_ptr)) {

}

std::vector<char> ByteSender::prepare_data(const IData& data) const {
	std::vector<char> wrapped_data;
	wrapped_data.insert(wrapped_data.end(), m_header.begin(), m_header.end());
	auto serial_data = m_serializer_ptr->serialize(data);
	auto serial_data_size = serialize_data_size(serial_data.size());
	wrapped_data.insert(wrapped_data.end(), serial_data_size.begin(), serial_data_size.end());
	wrapped_data.insert(wrapped_data.end(), serial_data.begin(), serial_data.end());	
	return wrapped_data;
}

std::size_t ByteSender::init_length_field_size(const std::size_t& length_field_size) {
	if ((sizeof(std::size_t) < length_field_size) || (0 == length_field_size)) {
		throw std::invalid_argument("received invalid length_field_size");
	}
	return length_field_size;
}

ByteSender::SerializerSmartPtr ByteSender::init_serializer(const SerializerSmartPtr& serializer_ptr) {
	if (!serializer_ptr) {
		throw std::invalid_argument("received invalid serializer");
	}
	return serializer_ptr;
}

std::vector<char> ByteSender::serialize_data_size(const std::size_t& data_size) const {
	enum {BITS_IN_BYTE = 8, BYTE_MASK = 0xFF};
	std::vector<char> serial_data_size;
	for (int i = 0; i < m_length_field_size; ++i) {
		const int bits_to_shift = BITS_IN_BYTE * (m_length_field_size - i - 1);
		char placeholder_value = static_cast<char>((data_size >> bits_to_shift) & BYTE_MASK);
		serial_data_size.push_back(placeholder_value);
	}
	return serial_data_size;
}