#ifndef	__BYTES_READER_HPP__
#define	__BYTES_READER_HPP__

#include <vector>
#include <cstddef>

#include "ibytes_reader.hpp"

namespace io {
	class BytesReader: public IBytesReader {
	public:
		BytesReader() = default;
		BytesReader(const BytesReader& other) = default;
		BytesReader& operator=(const BytesReader& other) = default;

		virtual std::vector<char> read() override;
		virtual std::vector<char> peek() const override;
		virtual std::vector<char> read(std::size_t size) override;
		virtual std::vector<char> peek(std::size_t size) const override;
		virtual std::size_t size() const override;
		void feed(char data);
	private:
		std::vector<char> m_data;
	}; // BytesReader
} // namespace io
#endif // __BYTES_READER_HPP__