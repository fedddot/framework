#ifndef	__IBYTES_WRITER_HPP__
#define	__IBYTES_WRITER_HPP__

#include <vector>
#include "iwriter.hpp"

namespace io {
	typedef IWriter<std::vector<char>> IBytesWriter;
} // namespace io
#endif // __IBYTES_WRITER_HPP__