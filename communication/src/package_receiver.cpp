#include <stdexcept>
#include <algorithm>
#include <vector>
#include <cstddef>

#include "ilistener.hpp"
#include "dispatcher.hpp"
#include "package_descriptor.hpp"

#include "package_receiver.hpp"

using namespace communication;
using namespace generics;

PackageReceiver::PackageReceiver(const PackageDescriptor& package_descriptor, common::Dispatcher<char>& char_dispatcher): m_package_descriptor(package_descriptor), m_char_dispatcher(char_dispatcher) {
	reset_receiver();
	m_char_dispatcher.subscribe(this);
}

PackageReceiver::~PackageReceiver() noexcept {
	m_char_dispatcher.unsubscribe(this);
}

void PackageReceiver::on_event(const char& event) {
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
		throw std::runtime_error("PackageReceiver::on_event: unsupported ReceiverState");
	}
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
	dispatch(data);
}

void PackageReceiver::reset_receiver() {
	m_state = ReceiverState::RECEIVING_HEADER;
	m_data_size = 0;
	m_data_buff.clear();
}