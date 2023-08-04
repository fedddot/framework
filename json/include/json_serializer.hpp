#ifndef __JSON_SERIALIZER_HPP__
#define __JSON_SERIALIZER_HPP__

#include <string>
#include <stdexcept>

#include "idata.hpp"
#include "idata_serializer.hpp"

namespace json {
	class JsonSerializer : public data::IDataSerializer {
	public:
		virtual std::string serialize(const data::IData& data) override;
	private:
		class UnexpectedDataType: public std::exception {
		public:
			UnexpectedDataType(const std::string& where, const std::string& note);
			virtual const char *what() const noexcept override;
		private:
			std::string m_msg;
		};
		class BadMember: public std::exception {
		public:
			BadMember(const std::string& where, const std::string& note);
			virtual const char *what() const noexcept override;
		private:
			std::string m_msg;
		};
		std::string serializeComposite(const data::IData& data);
		std::string serializeArray(const data::IData& data);
		std::string serializeObject(const data::IData& data);

		std::string serializeValue(const data::IData& data);
		std::string serializeString(const data::IData& data);
	}; // JsonSerializer
} // namespace json

#endif // __JSON_SERIALIZER_HPP__