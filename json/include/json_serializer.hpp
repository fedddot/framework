#ifndef __JSON_SERIALIZER_HPP__
#define __JSON_SERIALIZER_HPP__

#include <vector>
#include <stdexcept>

#include "idata.hpp"
#include "idata_serializer.hpp"

namespace json {
	class JsonSerializer : public data::ISerializer<data::IData, std::vector<char>> {
	public:
		virtual std::vector<char> serialize(const data::IData& data) override;
	private:
		std::vector<char> serializeComposite(const data::IData& data);
		std::vector<char> serializeArray(const data::IData& data);
		std::vector<char> serializeObject(const data::IData& data);

		std::vector<char> serializeValue(const data::IData& data);
		std::vector<char> serializeString(const data::IData& data);
	}; // JsonSerializer
} // namespace json

#endif // __JSON_SERIALIZER_HPP__