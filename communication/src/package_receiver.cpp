#include <stdexcept>
#include <algorithm>
#include <vector>
#include <cstddef>
#include <memory>

#include "ilistener.hpp"
#include "ireceiver.hpp"

#include "package_receiver.hpp"

using namespace communication;
using namespace common;

PackageReceiver::PackageReceiver(const Header& header, const std::size_t& payload_length_field_size, const std::size_t& max_payload_length): m_header(header), m_payload_length_field_size(payload_length_field_size), m_max_payload_length(max_payload_length), m_data_listener_ptr(nullptr) {
	if (MIN_HEADER_LENGTH > m_header.size()) {
		throw std::invalid_argument("received header is too short");
	}
	if ((MIN_PAYLOAD_LENGTH_FIELD_SIZE > m_payload_length_field_size) || (MAX_PAYLOAD_LENGTH_FIELD_SIZE < m_payload_length_field_size)) {
		throw std::invalid_argument("wrong payload_length_field_size received");
	}
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

common::IListener<Payload> *PackageReceiver::data_listener() {
	return m_data_listener_ptr;
}

void PackageReceiver::receive_header(const char& event) {
	m_data_buff.push_back(event);
	if (m_data_buff.size() < m_header.size()) {
		return;
	}
	if (m_header != m_data_buff) {
		m_data_buff.erase(m_data_buff.begin());
		return;
	}
	m_data_buff.clear();
	m_state = ReceiverState::RECEIVING_SIZE;
}

void PackageReceiver::receive_size(const char& event) {
	m_data_buff.push_back(event);
	if (m_data_buff.size() < m_payload_length_field_size) {
		return;
	}
	m_data_size = deserialize_data_length(m_data_buff);
	if ((m_data_size == 0) || (m_data_size > m_max_payload_length)) {
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

std::size_t PackageReceiver::deserialize_data_length(const std::vector<char>& data) {
	enum { BITS_IN_BITE = 8 };
	std::size_t data_length(0UL);
	std::for_each(
		data.begin(),
		data.end(),
		[&](const auto& iter) {
			data_length <<= BITS_IN_BITE;
			data_length |= static_cast<std::size_t>(iter);
		}
	);
	return data_length;
}