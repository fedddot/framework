#ifndef	__PACKAGE_RECEIVER_HPP__
#define	__PACKAGE_RECEIVER_HPP__

#include <vector>
#include <cstddef>

#include "ilistener.hpp"
#include "dispatcher.hpp"
#include "package_descriptor.hpp"

namespace communication {
	/// @brief Responsible to receive packed data byte-by-byte, validate header, calculate payload size and receive corresponding number of bytes as a payload. After the payload is received and processed notifies data listener (if set up)
	class PackageReceiver: public common::IListener<char>, public common::Dispatcher<std::vector<char>> {
	public:
		typedef std::vector<char> Payload;

		/// @brief Ctor, creates a new instance of class. The layout of receiving messages is configured and maintained by received PackageDescriptor instance
		/// @param package_descriptor a const reference to PackageDescriptor instance describing the layout of receiving data
		/// @param char_dispatcher <<TODO>>: describe
		PackageReceiver(const PackageDescriptor& package_descriptor, common::Dispatcher<char>& char_dispatcher);

		PackageReceiver(const PackageReceiver& other) = delete;
		PackageReceiver& operator=(const PackageReceiver& other) = delete;
		virtual ~PackageReceiver() noexcept override;

		/// @brief New character received callback. Should be invoked by the underlying layer each time a new character received. Responsible for proper storing, processing the incomming data, and dispatching the composed data to the listener
		/// @param event new character received
		virtual void on_event(const char& event) override;

		/// @brief Flushes input buffer and sets the receiver state to be RECEIVING_HEADER
		void reset_receiver();
	private:
		PackageDescriptor m_package_descriptor;
		common::Dispatcher<char>& m_char_dispatcher;

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
} // namespace communication
#endif // __PACKAGE_RECEIVER_HPP__