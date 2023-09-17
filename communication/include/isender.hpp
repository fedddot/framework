#ifndef	__ISENDER_HPP__
#define	__ISENDER_HPP__

namespace communication {
	/// @brief Defines an interface of a class responsible to send data of type Tdata
	/// @tparam Tdata class representing data to be sent
	template <class Tdata>
	class ISender {
	public:
		virtual ~ISender() noexcept = 0;

		/// @brief Sends data through underlying protocol
		/// @param data a const reference to instance of data object
		virtual void send(const Tdata& data) = 0;
	}; // ISender

	template <class Tdata>
	ISender<Tdata>::~ISender() noexcept {
		
	}
} // namespace communication
#endif // __ISENDER_HPP__