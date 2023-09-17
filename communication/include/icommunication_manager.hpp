#ifndef	__ICOMMUNICATION_MANAGER_HPP__
#define	__ICOMMUNICATION_MANAGER_HPP__

#include "ilistener.hpp"

namespace communication {
	template <class Tmsg>
	class ICommunicationManager: public common::IListener<char> {
	public:
		virtual ~ICommunicationManager() noexcept = 0;

		/// @brief Sends received message through underlying protocol
		/// @param msg a const reference to a valid Tmsg instance to be sent
		virtual void send(const Tmsg& msg) = 0;

		/// @brief New character received callback. Should be invoked by the underlying layer each time a new character received 
		/// @param event new character received
		virtual void onEvent(const char& event) = 0;

		/// @brief Sets message listener. When a new message received, a communication manager dispatches it to the listener by calling to its onEvent method with corresponding message
		/// @param listener_ptr a valid pointer to message listener instance
		/// @exception std::invalid_argument if invalid listener pointer received
		virtual void set_message_listener(common::IListener<Tmsg> *listener_ptr) = 0;

		/// @brief Gets previously set by set_message_listener pointer to message listener.
		/// @return pointer to message listener. nullptr if not set or if set to nullptr.
		virtual common::IListener<Tmsg> *message_listener() = 0;
	}; // ICommunicationManager

	template <class Tmsg>
	ICommunicationManager<Tmsg>::~ICommunicationManager() noexcept {
		
	}
} // namespace communication
#endif // __ICOMMUNICATION_MANAGER_HPP__