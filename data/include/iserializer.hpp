#ifndef	__ISERIALIZER_HPP__
#define	__ISERIALIZER_HPP__

namespace data {
	/// @brief declares a generic interface for data serializer
	/// @tparam Tinput type of data to be serialized
	/// @tparam Toutput type of serialized data
	template <class Tinput, class Toutput>
	class ISerializer {
	public:
		/// @brief serializes received structured data
		/// @param data const reference to data
		/// @return instance of valid serialized data
		/// @exception std::invalid_argument if received data can not be validly serialized
		virtual Toutput serialize(const Tinput& data) = 0;
		virtual ~ISerializer() noexcept = 0;
	}; // ISerializer

	template <class Tinput, class Toutput>
	ISerializer<Tinput, Toutput>::~ISerializer() noexcept {
		
	}
} // namespace data

#endif // __ISERIALIZER_HPP__