#include <stdexcept>
#include <vector>
#include <cstddef>

#include "bytes_reader.hpp"

using namespace io;

std::vector<char> BytesReader::read() {
	std::vector<char> result(m_data);
	m_data.clear();
	return result;
}

std::vector<char> BytesReader::peek() const {
	return m_data;
}

std::vector<char> BytesReader::read(std::size_t size) {
	if (size > m_data.size()) {
		throw std::invalid_argument("invalid reading size - reading buffer is not long enough");
	}
	auto begin = m_data.begin();
	auto end = begin + size;
	std::vector<char> result(begin, end);
	m_data.erase(begin, end);
	return result;
}

std::vector<char> BytesReader::peek(std::size_t size) const {
	if (size > m_data.size()) {
		throw std::invalid_argument("invalid reading size - reading buffer is not long enough");
	}
	auto begin = m_data.begin();
	auto end = begin + size;
	return std::vector<char>(begin, end);
}

std::size_t BytesReader::size() const {
	return m_data.size();
}

void BytesReader::feed(char data) {
	m_data.push_back(data);
}