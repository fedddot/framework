#ifndef __JSON_SERIALIZER_HPP__
#define __JSON_SERIALIZER_HPP__

#include <stdexcept>
#include <string>
#include <vector>

#include "idata.hpp"
#include "iserializer.hpp"

namespace json {
	class JsonSerializer : public data::ISerializer<data::IData, std::vector<char>> {
	public:
		virtual std::vector<char> serialize(const data::IData& data) override;
	private:
		class Exception: public std::exception {
		public:
			Exception(const std::string& msg);
			virtual inline const char *what() const noexcept override;
		private:
			std::string m_msg;
		};

		class UnexpectedDataType: public Exception {
		public:
			UnexpectedDataType(const std::string& where);
		};

		class BadMemberPointer: public Exception {
		public:
			BadMemberPointer(const std::string& where);
		};


		std::vector<char> serializeComposite(const data::IData& data);
		std::vector<char> serializeArray(const data::IData& data);
		std::vector<char> serializeObject(const data::IData& data);

		std::vector<char> serializeValue(const data::IData& data);
		std::vector<char> serializeString(const data::IData& data);
	}; // JsonSerializer


	inline const char *JsonSerializer::Exception::what() const noexcept {
		return m_msg.c_str();
	}
} // namespace json

#endif // __JSON_SERIALIZER_HPP__