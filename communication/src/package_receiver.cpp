#include <stdexcept>
#include <algorithm>
#include <vector>
#include <cstddef>

#include "ilistener.hpp"
#include "ireceiver.hpp"
#include "package_descriptor.hpp"

#include "package_receiver.hpp"

using namespace communication;
using namespace common;

PackageReceiver::PackageReceiver(const PackageDescriptor& package_descriptor): m_package_descriptor(package_descriptor), m_data_listener_ptr(nullptr) {
	reset_receiver();
}

void PackageReceiver::onEvent(const char& event) {
	switch (m_state) {
	case ReceiverState::RECEIVING_HEADER:
		receive_header(event);
		break;
	case ReceiverState::RECEIVING_SIZE:
		receive_size(event);
		break;
	case ReceiverState::RECEIVING_PAYLOAD:
		receive_data(event);
		break;
	default:
		throw std::runtime_error("PackageReceiver::onEvent: unsupported ReceiverState");
	}
}

void PackageReceiver::set_data_listener(common::IListener<Payload> *data_listener_ptr) {
	m_data_listener_ptr = data_listener_ptr;
}

common::IListener<PackageReceiver::Payload> *PackageReceiver::data_listener() {
	return m_data_listener_ptr;
}

void PackageReceiver::receive_header(const char& event) {
	m_data_buff.push_back(event);
	if (m_data_buff.size() < m_package_descriptor.header().size()) {
		return;
	}
	if (!m_package_descriptor.match_header(m_data_buff)) {
		m_data_buff.erase(m_data_buff.begin());
		return;
	}
	m_data_buff.clear();
	m_state = ReceiverState::RECEIVING_SIZE;
}

void PackageReceiver::receive_size(const char& event) {
	m_data_buff.push_back(event);
	if (m_data_buff.size() < m_package_descriptor.payload_length_field_size()) {
		return;
	}
	m_data_size = m_package_descriptor.unpack_payload_length(m_data_buff);
	if (m_data_size == 0) {
		reset_receiver();
		return;
	}
	m_data_buff.clear();
	m_state = ReceiverState::RECEIVING_PAYLOAD;
}

void PackageReceiver::receive_data(const char& event) {
	m_data_buff.push_back(event);
	if (m_data_buff.size() < m_data_size) {
		return;
	}
	std::vector<char> data(m_data_buff);
	reset_receiver();
	if (m_data_listener_ptr) {
		m_data_listener_ptr->onEvent(data);
	}
}

void PackageReceiver::reset_receiver() {
	m_state = ReceiverState::RECEIVING_HEADER;
	m_data_size = 0;
	m_data_buff.clear();
}