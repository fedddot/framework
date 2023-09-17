#ifndef	__RAW_DATA_SENDER_HPP__
#define	__RAW_DATA_SENDER_HPP__

#include <vector>
#include <cstddef>
#include <memory>

#include "isender.hpp"
#include "idata.hpp"
#include "iserializer.hpp"

namespace communication {
	class ByteSender: public ISender<data::IData> {
	public:
		typedef std::shared_ptr<data::ISerializer<data::IData, std::vector<char>>> SerializerSmartPtr;
		ByteSender(const std::vector<char>& header, const std::size_t& length_field_size, const SerializerSmartPtr& serializer_ptr);
		std::vector<char> prepare_data(const data::IData& data) const;
	private:
		const std::vector<char> m_header;
		const std::size_t m_length_field_size;
		SerializerSmartPtr m_serializer_ptr;
		
		static std::size_t init_length_field_size(const std::size_t& length_field_size);
		static SerializerSmartPtr init_serializer(const SerializerSmartPtr& serializer_ptr);
		std::vector<char> serialize_data_size(const std::size_t& data_size) const;
	}; // ByteSender
} // namespace communication
#endif // __RAW_DATA_SENDER_HPP__