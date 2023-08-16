#ifndef	__RAW_DATA_RECEIVER_HPP__
#define	__RAW_DATA_RECEIVER_HPP__

#include <cstddef>
#include <vector>
#include <memory>

#include "idata.hpp"
#include "iparser.hpp"
#include "ilistener.hpp"
#include "ireceiver.hpp"

namespace communication {
	class ByteReceiver: public IReceiver<char, std::shared_ptr<data::IData>> {
	public:
		typedef std::shared_ptr<data::IParser<std::vector<char>, std::shared_ptr<data::IData>>> ParserSmartPointer;
		ByteReceiver(const std::vector<char>& header, const std::size_t& length_field_size, const std::size_t& max_data_size, const ParserSmartPointer& parser_ptr);
		ByteReceiver(const ByteReceiver& other) = delete;
		ByteReceiver& operator=(const ByteReceiver& other) = delete;

		virtual void onEvent(const char& event) override;
		virtual inline void set_data_listener(common::IListener<std::shared_ptr<data::IData>> *data_listener_ptr) override;
		virtual inline common::IListener<std::shared_ptr<data::IData>> *get_data_listener() override;

		void reset_receiver();
	private:
		std::vector<char> m_header;
		std::size_t m_length_field_size;
		std::size_t m_max_data_size;
		ParserSmartPointer m_parser_ptr;

		common::IListener<std::shared_ptr<data::IData>> *m_data_listener_ptr;

		enum class ReceiverState: int {
			RECEIVING_HEADER,
			RECEIVING_SIZE,
			RECEIVING_DATA
		};

		ReceiverState m_state;
		std::size_t m_data_size;
		std::vector<char> m_data_buff;

		void receive_header(const char& event);
		void receive_size(const char& event);
		void receive_data(const char& event);

		static std::size_t deserialize_data_length(const std::vector<char>& data);
		static std::size_t init_length_field_size(const std::size_t& length_field_size);
		static ParserSmartPointer init_parser_ptr(const ParserSmartPointer& parser_ptr);
		
	}; // ByteReceiver

	inline void ByteReceiver::set_data_listener(common::IListener<std::shared_ptr<data::IData>> *data_listener_ptr) {
		m_data_listener_ptr = data_listener_ptr;
	}

	inline common::IListener<std::shared_ptr<data::IData>> *ByteReceiver::get_data_listener() {
		return m_data_listener_ptr;
	}
} // namespace data
#endif // __RAW_DATA_RECEIVER_HPP__