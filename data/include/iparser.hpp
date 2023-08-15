#ifndef	__IPARSER_HPP__
#define	__IPARSER_HPP__

namespace data {
	template <class Tinput, class Toutput>
	class IParser {
	public:
		virtual Toutput parse(const Tinput& data) = 0;
		virtual ~IParser() noexcept = 0;
	}; // IParser

	template <class Tinput, class Toutput>
	IParser<Tinput, Toutput>::~IParser() noexcept {

	}
	
} // namespace data

#endif // __IPARSER_HPP__