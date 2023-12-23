#ifndef	__IWRITER_HPP__
#define	__IWRITER_HPP__

namespace io {
	template <class Tdata>
	class IWriter {
	public:
		virtual ~IWriter() noexcept = 0;
		virtual void write(const Tdata& data) = 0;
	}; // IWriter

	template<class Tdata>
	IWriter<Tdata>::~IWriter() noexcept {
		
	}
} // namespace io
#endif // __IWRITER_HPP__