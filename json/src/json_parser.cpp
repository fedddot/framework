#include <algorithm>
#include <memory>
#include <vector>

#include "idata.hpp"
#include "iparser.hpp"

#include "string.hpp"
#include "array.hpp"
#include "object.hpp"

#include "json_common.hpp"
#include "json_parser.hpp"

using namespace json;
using namespace data;

const std::vector<char> json::JsonParser::m_bulk_chars {
	static_cast<char>(JsonSpecialChar::SPACE),
	static_cast<char>(JsonSpecialChar::TAB),
	static_cast<char>(JsonSpecialChar::NEW_LINE)
};

std::shared_ptr<data::IData> JsonParser::parse(const std::vector<char>& data) {
	return parse(data.cbegin(), data.cend()).get_parsed_data();
}

JsonParser::ParsingResult JsonParser::parse(const const_iter& start_iter, const const_iter& end_iter) {
	auto parsing_start_iter = skipBulks(start_iter, end_iter);
	if (end_iter == parsing_start_iter) {
		throw UnexpectedEndOfData("parse");
	}
	switch (*parsing_start_iter) {
	case static_cast<char>(JsonSpecialChar::STRING_START):
		return parseString(parsing_start_iter, end_iter);
	case static_cast<char>(JsonSpecialChar::OBJECT_START):
		return parseObject(parsing_start_iter, end_iter);
	case static_cast<char>(JsonSpecialChar::ARRAY_START):
		return parseArray(parsing_start_iter, end_iter);
	default:
		break;
	}
	throw UnexpectedCharacter("parse", "either STRING_START, OBJECT_START or ARRAY_START", std::string(parsing_start_iter, parsing_start_iter + 1));
}

JsonParser::ParsingResult JsonParser::parseString(const const_iter& start_iter, const const_iter& end_iter) {
	auto iter = start_iter;
	const char expected_first_char = static_cast<char>(JsonSpecialChar::STRING_START);
	if (expected_first_char != *iter) {
		throw UnexpectedCharacter("parse", "STRING_START", std::string(start_iter, start_iter + 1));
	}
	++iter;
	String parsed_string("");
	while (end_iter != iter) {
		if (static_cast<char>(JsonSpecialChar::STRING_END) == *iter) {
			++iter;
			return ParsingResult(std::shared_ptr<IData>(new String(parsed_string)), iter);
		}
		parsed_string += *iter;
		++iter;
	}
	throw UnexpectedEndOfData("parseString");
}

JsonParser::ParsingResult JsonParser::parseObject(const const_iter& start_iter, const const_iter& end_iter) {
	auto iter = start_iter;
	const char expected_first_char = static_cast<char>(JsonSpecialChar::OBJECT_START);
	if (expected_first_char != *iter) {
		throw UnexpectedCharacter("parseObject", "OBJECT_START", std::string(start_iter, start_iter + 1));
	}
	++iter;
	iter = skipBulks(iter, end_iter);
	Object parsed_object;
	while (end_iter != iter) {
		if (static_cast<char>(JsonSpecialChar::OBJECT_END) == *iter) {
			++iter;
			return ParsingResult(std::shared_ptr<IData>(new Object(parsed_object)), iter);
		}
		auto field_name_parsed = parseString(iter, end_iter);
		iter = field_name_parsed.get_parsing_end_iter();
		String field_name(*(field_name_parsed.get_parsed_data()));
		iter = skipBetweenFieldNameAndMember(iter, end_iter);

		auto member_parsed = parse(iter, end_iter);
		iter = member_parsed.get_parsing_end_iter();
		parsed_object.insert({field_name, member_parsed.get_parsed_data()});
		iter = skipAfterMember(iter, end_iter, static_cast<char>(JsonSpecialChar::OBJECT_END));
	}
	throw UnexpectedEndOfData("parseObject");
}

JsonParser::ParsingResult JsonParser::parseArray(const const_iter& start_iter, const const_iter& end_iter) {
	auto iter = start_iter;
	const char expected_first_char = static_cast<char>(JsonSpecialChar::ARRAY_START);
	if (expected_first_char != *iter) {
		throw UnexpectedCharacter("parseArray", "ARRAY_START", std::string(start_iter, start_iter + 1));
	}
	++iter;
	iter = skipBulks(iter, end_iter);
	Array parsed_array;
	while (end_iter != iter) {
		if (static_cast<char>(JsonSpecialChar::ARRAY_END) == *iter) {
			++iter;
			return ParsingResult(std::shared_ptr<IData>(new Array(parsed_array)), iter);
		}
		auto member_parsed = parse(iter, end_iter);
		iter = member_parsed.get_parsing_end_iter();
		parsed_array.push_back(member_parsed.get_parsed_data());
		iter = skipAfterMember(iter, end_iter, static_cast<char>(JsonSpecialChar::ARRAY_END));
	}
	throw UnexpectedEndOfData("parseArray");
}

const JsonParser::const_iter JsonParser::skipChars(const const_iter& start_iter, const const_iter& end_iter, const std::vector<char>& chars) {
	auto iter = start_iter;
	while (end_iter != iter) {
		auto chars_iter = std::find(chars.begin(), chars.end(), *iter);
		if (chars.end() == chars_iter) {
			break;
		}
		++iter;
	}
	return iter;
}

const JsonParser::const_iter JsonParser::skipBulks(const const_iter& start_iter, const const_iter& end_iter) {
	return skipChars(start_iter, end_iter, m_bulk_chars);
}

const JsonParser::const_iter JsonParser::skipBetweenFieldNameAndMember(const const_iter& start_iter, const const_iter& end_iter) {
	auto iter = start_iter;
	iter = skipBulks(iter, end_iter);
	if (end_iter == iter) {
		UnexpectedEndOfData("skipBetweenFieldNameAndMember");
	}
	const char expected_token = static_cast<char>(JsonSpecialChar::SEMICOLON);
	if (expected_token != *iter) {
		UnexpectedCharacter("skipBetweenFieldNameAndMember", std::string(&expected_token, 1), std::string(iter, iter + 1));
	}
	++iter;
	iter = skipBulks(iter, end_iter);
	if (end_iter == iter) {
		UnexpectedEndOfData("skipBetweenFieldNameAndMember");
	}
	return iter;
}

const JsonParser::const_iter JsonParser::skipAfterMember(const const_iter& start_iter, const const_iter& end_iter, char expected_closing_bracket) {
	auto iter = start_iter;
	iter = skipBulks(iter, end_iter);
	if (end_iter == iter) {
		UnexpectedEndOfData("skipAfterMember");
	}
	const char expected_token = static_cast<char>(JsonSpecialChar::DELIMITER);
	if (expected_token == *iter) {
		++iter;
		iter = skipBulks(iter, end_iter);
		if (end_iter == iter) {
			UnexpectedEndOfData("skipBetweenFieldNameAndMember");
		}
		return iter;
	}
	if (expected_closing_bracket != *iter) {
		UnexpectedCharacter("skipAfterMember", std::string(&expected_closing_bracket, 1), std::string(iter, iter + 1));
	}
	return iter;
}

JsonParser::ParsingResult::ParsingResult(const std::shared_ptr<IData>& parsed_data, const const_iter& parsing_end_iter): m_parsed_data(init_parsed_data(parsed_data)), m_parsing_end_iter(parsing_end_iter) {

}

std::shared_ptr<IData> JsonParser::ParsingResult::init_parsed_data(const std::shared_ptr<IData>& parsed_data) {
	if (!parsed_data) {
		throw std::invalid_argument("invalid data received");
	}
	return parsed_data;
}

JsonParser::Exception::Exception(const std::string& msg): m_msg(msg) {

}

JsonParser::UnexpectedEndOfData::UnexpectedEndOfData(const std::string& where): Exception("in JsonParser::" + where + ": unexpected end of file") {
	
}

JsonParser::UnexpectedCharacter::UnexpectedCharacter(const std::string& where, const std::string& expected, const std::string& received): Exception("in JsonParser::" + where + ": unexpected token reveived (expected: \"" + expected + "\"; received: \"" + received + "\")") {
	
}