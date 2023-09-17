#include <stdexcept>
#include <algorithm>
#include <vector>
#include <cstddef>

#include "package_descriptor.hpp"

using namespace communication;

PackageDescriptor::PackageDescriptor(const Header& header, const std::size_t& payload_length_field_size): m_header(header), m_payload_length_field_size(payload_length_field_size) {
	if (MIN_HEADER_LENGTH > m_header.size()) {
		throw std::invalid_argument("received header is too short");
	}
	if ((MIN_PAYLOAD_LENGTH_FIELD_SIZE > m_payload_length_field_size) || (MAX_PAYLOAD_LENGTH_FIELD_SIZE < m_payload_length_field_size)) {
		throw std::invalid_argument("wrong payload_length_field_size received");
	}
}

PackageDescriptor::PackageData PackageDescriptor::pack(const Payload& payload) const {
	PackageData packed_data;
	auto append_vector_with_other = [](std::vector<char> *one, const std::vector<char>& other) {
		std::for_each(other.begin(), other.end(),
			[&](const auto& ch) {
				one->push_back(ch);
			}
		);
	};

	append_vector_with_other(&packed_data, m_header);
	append_vector_with_other(&packed_data, pack_payload_length(payload.size()));
	append_vector_with_other(&packed_data, payload);

	return packed_data;
}

PackageDescriptor::PackageData PackageDescriptor::pack_payload_length(const std::size_t& payload_length) const {
	PackageData packed_payload_length;
	for (int i = 0; i < m_payload_length_field_size; ++i) {
		const int bits_to_shift = BITS_IN_BYTE * (m_payload_length_field_size - i - 1);
		char placeholder_value = static_cast<char>((payload_length >> bits_to_shift) & BYTE_MASK);
		packed_payload_length.push_back(placeholder_value);
	}
	return packed_payload_length;
}

std::size_t PackageDescriptor::unpack_payload_length(const PackageData& packed_payload_length) const {
	if (m_payload_length_field_size != packed_payload_length.size()) {
		throw std::invalid_argument("received packed data has wrong size");
	}
	std::size_t data_length(0UL);
	std::for_each(
		packed_payload_length.begin(),
		packed_payload_length.end(),
		[&](const auto& length_ch) {
			data_length <<= BITS_IN_BYTE;
			data_length |= static_cast<std::size_t>(length_ch);
		}
	);
	return data_length;
}