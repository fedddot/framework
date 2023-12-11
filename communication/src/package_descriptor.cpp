#include <stdexcept>
#include <algorithm>
#include <vector>
#include <cstddef>

#include "package_descriptor.hpp"

using namespace communication;

PackageDescriptor::PackageDescriptor(const Data& signature): m_signature(signature) {
}

bool PackageDescriptor::validate(const Data& desc_data) const {
	if (desc_data.size() != desc_size()) {
		return false;
	}
	const Data signature(desc_data.begin(), desc_data.begin() + m_signature.size());
	return signature == m_signature;
}

PackageDescriptor::DataSize PackageDescriptor::data_size(const Data& desc_data) const {
	DataSize result(0UL);
	std::for_each(
		desc_data.begin() + m_signature.size(),
		desc_data.end(),
		[&](const auto& ch) {
			result <<= sizeof(char) * BITS_IN_BYTE;
			result |= static_cast<DataSize>(ch);
		}
	);
	return result;
}

PackageDescriptor::Data PackageDescriptor::pack(const Data& raw_data) const {
	const Data packed_data_size(pack_data_size(raw_data.size()));
	Data packed_data(m_signature);
	packed_data.insert(packed_data.end(), packed_data_size.begin(), packed_data_size.end());
	packed_data.insert(packed_data.end(), raw_data.begin(), raw_data.end());
	return packed_data;
}

PackageDescriptor::Data PackageDescriptor::pack_data_size(const DataSize& data_size) {
	Data packed_data_size;
	int shift = (sizeof(DataSize) - 1) * BITS_IN_BYTE;
	while (shift >= 0) {
		const char ch = static_cast<const char>((data_size >> shift) & 0xFF);
		packed_data_size.push_back(ch);
		shift -= BITS_IN_BYTE;
	}
	return packed_data_size;
}