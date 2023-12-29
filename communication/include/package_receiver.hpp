#ifndef	__PACKAGE_RECEIVER_HPP__
#define	__PACKAGE_RECEIVER_HPP__

#include <vector>
#include <functional>
#include <cstddef>

namespace communication {
	/// @brief Responsible to receive packed data byte-by-byte, validate header, calculate payload size and receive corresponding number of bytes as a payload. Once the payload is received and processed a callback specified on construction step will be called
	class PackageReceiver {
	public:
		typedef typename std::vector<char> Package;
		typedef typename std::function<void(const Package&)> OnPackageReceived;

		PackageReceiver(const std::size_t& package_length_field_size, const OnPackageReceived& on_pkg_received_callback);

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