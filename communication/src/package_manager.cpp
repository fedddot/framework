#include <vector>
#include <cstddef>

#include "isender.hpp"
#include "dispatcher.hpp"
#include "package_descriptor.hpp"
#include "package_receiver.hpp"
#include "package_sender.hpp"

#include "package_manager.hpp"

using namespace communication;
using namespace generics;

PackageManager::PackageManager(const PackageDescriptor& package_descriptor, ISender<std::vector<char>>& packed_data_sender, Dispatcher<char>& char_dispatcher): m_receiver(package_descriptor, char_dispatcher), m_sender(package_descriptor, packed_data_sender) {

}