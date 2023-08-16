#ifndef __JSON_PARSER_HPP__
#define __JSON_PARSER_HPP__

#include <stdexcept>
#include <string>
#include <memory>
#include <vector>

#include "idata.hpp"
#include "iparser.hpp"

namespace json {
	class JsonParser : public data::IParser<std::vector<char>, std::shared_ptr<data::IData>> {
	public:
		virtual std::shared_ptr<data::IData> parse(const std::vector<char>& data) override;
	private:
		typedef std::vector<char>::const_iterator const_iter;
		class ParsingResult {
		public:
			ParsingResult(const std::shared_ptr<data::IData>& parsed_data, const const_iter& parsing_end_iter);
			inline const std::shared_ptr<data::IData> get_parsed_data() const;
			inline const const_iter get_parsing_end_iter() const;
		private:
			const std::shared_ptr<data::IData> m_parsed_data;
			const const_iter m_parsing_end_iter;
			static std::shared_ptr<data::IData> init_parsed_data(const std::shared_ptr<data::IData>& parsed_data);
		};

		class Exception: public std::exception {
		public:
			Exception(const std::string& msg);
			virtual inline const char *what() const noexcept override;
		private:
			std::string m_msg;
		};

		class UnexpectedEndOfData: public Exception {
		public:
			UnexpectedEndOfData(const std::string& where);
		};

		class UnexpectedCharacter: public Exception {
		public:
			UnexpectedCharacter(const std::string& where, const std::string& expected, const std::string& received);
		};

		ParsingResult parse(const const_iter& start_iter, const const_iter& end_iter);
		ParsingResult parseString(const const_iter& start_iter, const const_iter& end_iter);
		ParsingResult parseObject(const const_iter& start_iter, const const_iter& end_iter);
		ParsingResult parseArray(const const_iter& start_iter, const const_iter& end_iter);

		static const const_iter skipChars(const const_iter& start_iter, const const_iter& end_iter, const std::vector<char>& chars);
		static const const_iter skipBulks(const const_iter& start_iter, const const_iter& end_iter);
		static const const_iter skipBetweenFieldNameAndMember(const const_iter& start_iter, const const_iter& end_iter);
		static const const_iter skipAfterMember(const const_iter& start_iter, const const_iter& end_iter, char expected_closing_bracket);

		static const std::vector<char> m_bulk_chars;
	}; // JsonParser

	inline const std::shared_ptr<data::IData> JsonParser::ParsingResult::get_parsed_data() const {
		return m_parsed_data;
	}

	inline const JsonParser::const_iter JsonParser::ParsingResult::get_parsing_end_iter() const {
		return m_parsing_end_iter;
	}

	inline const char *JsonParser::Exception::what() const noexcept {
		return m_msg.c_str();
	}
} // namespace json

#endif // __JSON_PARSER_HPP__