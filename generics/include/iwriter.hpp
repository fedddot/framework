#ifndef	IWRITER_HPP
#define	IWRITER_HPP

namespace generics {
	template <class Tdata>
	class IWriter {
	public:
		virtual void write(const Tdata& data) = 0;
		virtual ~IWriter() noexcept = 0;
	};

	template <class Tdata>
	IWriter<Tdata>::~IWriter() noexcept {
		
	}
}

#endif // IWRITER_HPP