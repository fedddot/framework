#ifndef	__IREADER_HPP__
#define	__IREADER_HPP__

namespace io {
	template <class Tdata>
	class IReader {
	public:
		virtual ~IReader() noexcept = 0;
		virtual Tdata read() = 0;
		virtual Tdata peek() const = 0;
	}; // IReader
	
	template<class Tdata>
	IReader<Tdata>::~IReader() noexcept {
		
	}
} // namespace io

#endif // __IREADER_HPP__