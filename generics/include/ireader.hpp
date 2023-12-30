#ifndef	IREADER_HPP
#define	IREADER_HPP

namespace generics {
	template <class Tdata>
	class IReader {
	public:
		virtual Tdata read() = 0;
		virtual ~IReader() noexcept = 0;
	};

	template <class Tdata>
	IReader<Tdata>::~IReader() noexcept {
		
	}
}

#endif // IREADER_HPP