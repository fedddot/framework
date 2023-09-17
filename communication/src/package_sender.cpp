#include <vector>
#include <cstddef>

#include "isender.hpp"
#include "package_descriptor.hpp"

#include "package_sender.hpp"

using namespace communication;

PackageSender::PackageSender(const PackageDescriptor& package_descriptor, ISender<std::vector<char>>& packed_data_sender): m_package_descriptor(package_descriptor), m_packed_data_sender(packed_data_sender) {

}

void PackageSender::send(const Payload& data) {
	m_packed_data_sender.send(m_package_descriptor.pack(data));
}