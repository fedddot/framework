#ifndef	__IBYTES_READER_HPP__
#define	__IBYTES_READER_HPP__

#include <vector>
#include <cstddef>

#include "ireader.hpp"

namespace io {
	class IBytesReader: public IReader<std::vector<char>> {
	public:
		virtual std::vector<char> read(std::size_t size) = 0;
		virtual std::vector<char> peek(std::size_t size) const = 0;
		virtual std::size_t size() const = 0;
	}; // IBytesReader
} // namespace io
#endif // __IBYTES_READER_HPP__