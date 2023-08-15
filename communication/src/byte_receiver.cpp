#include <stdexcept>
#include <algorithm>
#include <cstddef>
#include <vector>
#include <memory>

#include "idata.hpp"
#include "iparser.hpp"
#include "ilistener.hpp"
#include "ireceiver.hpp"
#include "byte_receiver.hpp"

using namespace communication;
using namespace common;
using namespace data;

ByteReceiver::ByteReceiver(const std::vector<char>& header, const std::size_t& length_field_size, const std::size_t& max_data_size, const std::shared_ptr<IParser<std::vector<char>, std::shared_ptr<IData>>>& parser_ptr): 
	m_header(header), 
	m_length_field_size(init_length_field_size(length_field_size)), 
	m_max_data_size(max_data_size), 
	m_parser_ptr(init_parser_ptr(parser_ptr)), 
	m_data_listener_ptr(nullptr) {
	reset_receiver();
}

void ByteReceiver::onEvent(const char& event) {
	switch (m_state) {
	case ReceiverState::RECEIVING_HEADER:
		receive_header(event);
		break;
	case ReceiverState::RECEIVING_SIZE:
		receive_size(event);
		break;
	case ReceiverState::RECEIVING_DATA:
		receive_data(event);
		break;
	default:
		throw std::runtime_error("ByteReceiver::onEvent: unsupported ReceiverState");
	}
}

void ByteReceiver::receive_header(const char& event) {
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

void ByteReceiver::receive_size(const char& event) {
	m_data_buff.push_back(event);
	if (m_data_buff.size() < m_length_field_size) {
		return;
	}
	m_data_size = deserialize_data_length(m_data_buff);
	if ((m_data_size == 0) || (m_data_size > m_max_data_size)) {
		reset_receiver();
		return;
	}
	m_data_buff.clear();
	m_state = ReceiverState::RECEIVING_DATA;
}

void ByteReceiver::receive_data(const char& event) {
	m_data_buff.push_back(event);
	if (m_data_buff.size() < m_data_size) {
		return;
	}
	std::vector<char> data(m_data_buff);
	reset_receiver();
	if (m_data_listener_ptr) {
		m_data_listener_ptr->onEvent(m_parser_ptr->parse(data));
	}
}

void ByteReceiver::reset_receiver() {
	m_state = ReceiverState::RECEIVING_HEADER;
	m_data_size = 0;
	m_data_buff.clear();
}

std::size_t ByteReceiver::init_length_field_size(const std::size_t& length_field_size) {
	if (length_field_size > sizeof(std::size_t)) {
		throw std::invalid_argument("received length_field_size is too large");
	}
	return length_field_size;
}

std::size_t ByteReceiver::deserialize_data_length(const std::vector<char>& data) {
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