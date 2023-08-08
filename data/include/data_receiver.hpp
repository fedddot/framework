#ifndef	__DATA_RECEIVER_HPP__
#define	__DATA_RECEIVER_HPP__

#include <stdexcept>
#include <string>
#include <cstddef>
#include <vector>
#include "ilistener.hpp"
#include "idata_receiver.hpp"

namespace data {
	class DataReceiver: public IDataReceiver<char, const std::vector<char>&> {
	public:
		class DataReceiverException: public std::exception {
		public:
			DataReceiverException(const std::string& where, const std::string& what, DataReceiver& receiver);
			DataReceiverException(const DataReceiverException& other) = default;
			DataReceiverException& operator=(const DataReceiverException& other) = default;
			virtual const char* what() const noexcept override;
		private:
			std::string m_msg;
		};

		DataReceiver(const std::vector<char>& header, const std::size_t& length_field_size, const std::size_t& max_data_size);

		virtual void onEvent(char event) override;
		virtual inline void set_data_listener(common::IListener<const std::vector<char>&> *data_listener_ptr) override;
		virtual inline common::IListener<const std::vector<char>&> *get_data_listener() override;
		void reset_receiver();
	private:
		const std::vector<char> m_header;
		const std::size_t m_length_field_size;
		const std::size_t m_max_data_size;

		common::IListener<const std::vector<char>&> *m_data_listener_ptr;

		enum class ReceiverState: int {
			RECEIVING_HEADER,
			RECEIVING_SIZE,
			RECEIVING_DATA
		};

		ReceiverState m_state;
		std::size_t m_data_size;
		std::vector<char> m_data_buff;

		void receive_header(char event);
		void receive_size(char event);
		void receive_data(char event);

		static std::size_t deserialize_data_length(const std::vector<char>& data);
		static std::size_t init_length_field_size(const std::size_t& length_field_size);
		
	}; // DataReceiver

	inline void DataReceiver::set_data_listener(common::IListener<const std::vector<char>&> *data_listener_ptr) {
		m_data_listener_ptr = data_listener_ptr;
	}

	inline common::IListener<const std::vector<char>&> *DataReceiver::get_data_listener() {
		return m_data_listener_ptr;
	}

	inline const char *DataReceiver::DataReceiverException::what() const noexcept {
		return m_msg.c_str();
	}
} // namespace data
#endif // __DATA_RECEIVER_HPP__