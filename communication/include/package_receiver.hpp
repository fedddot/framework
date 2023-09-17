#ifndef	__PACKAGE_RECEIVER_HPP__
#define	__PACKAGE_RECEIVER_HPP__

#include <vector>
#include <cstddef>

#include "ilistener.hpp"
#include "ireceiver.hpp"
#include "package_descriptor.hpp"

namespace communication {
	class PackageReceiver: public IReceiver<std::vector<char>> {
	public:
		typedef std::vector<char> Payload;
		PackageReceiver(const PackageDescriptor& package_descriptor);
		PackageReceiver(const PackageReceiver& other) = delete;
		PackageReceiver& operator=(const PackageReceiver& other) = delete;

		/// @brief New character received callback. Should be invoked by the underlying layer each time a new character received. Responsible for proper storing, processing the incomming data, and dispatching the composed data to the listener
		/// @param event new character received
		virtual void onEvent(const char& event) = 0;

		/// @brief Sets data listener. When a new data received, IReceiver instance dispatches it to the listener by calling to its onEvent method with corresponding data
		/// @param data_listener_ptr a valid pointer to the data listener instance
		/// @exception std::invalid_argument if invalid listener pointer received
		virtual void set_data_listener(common::IListener<Payload> *data_listener_ptr) = 0;

		/// @brief Gets previously set by set_data_listener pointer to data listener.
		/// @return pointer to data listener. nullptr if not set or if set to nullptr
		virtual common::IListener<Payload> *data_listener() = 0;

		/// @brief Flushes input buffer and sets the receiver statie to be RECEIVING_HEADER
		void reset_receiver();
	private:
		PackageDescriptor m_package_descriptor;
		common::IListener<Payload> *m_data_listener_ptr;		

		// Receiver state variables
		enum class ReceiverState: int {
			RECEIVING_HEADER,
			RECEIVING_SIZE,
			RECEIVING_PAYLOAD
		};
		ReceiverState m_state;
		std::size_t m_data_size;
		std::vector<char> m_data_buff;

		// Receiver state handlers
		void receive_header(const char& event);
		void receive_size(const char& event);
		void receive_data(const char& event);
	}; // PackageReceiver
} // namespace data
#endif // __PACKAGE_RECEIVER_HPP__