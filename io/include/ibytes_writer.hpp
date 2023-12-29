#ifndef	__IBYTES_WRITER_HPP__
#define	__IBYTES_WRITER_HPP__

#include <vector>
#include "iwriter.hpp"

namespace io {
	using IBytesWriter = IWriter<std::vector<char>>;
} // namespace io
#endif // __IBYTES_WRITER_HPP__