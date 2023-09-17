#ifndef	__IRECEIVER_HPP__
#define	__IRECEIVER_HPP__

#include "ilistener.hpp"

namespace communication {
	/// @brief Defines an interface of a class responsible to receive data byte-by-byte, compose it into a Tdata instance representing received data and notify data listener
	/// @tparam Tdata class representing composed received data
	template <class Tdata>
	class IReceiver: public common::IListener<char> {
	public:
		/// @brief New character received callback. Should be invoked by the underlying layer each time a new character received. Responsible for proper storing, processing the incomming data, and dispatching the composed data to the listener
		/// @param event new character received
		virtual void onEvent(const char& event) = 0;

		/// @brief Sets data listener. When a new data received, IReceiver instance dispatches it to the listener by calling to its onEvent method with corresponding data
		/// @param data_listener_ptr a valid pointer to the data listener instance
		/// @exception std::invalid_argument if invalid listener pointer received
		virtual void set_data_listener(common::IListener<Tdata> *data_listener_ptr) = 0;

		/// @brief Gets previously set by set_data_listener pointer to data listener.
		/// @return pointer to data listener. nullptr if not set or if set to nullptr
		virtual common::IListener<Tdata> *data_listener() = 0;
	}; // IReceiver
} // namespace communication
#endif // __IRECEIVER_HPP__