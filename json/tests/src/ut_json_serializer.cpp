#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <memory>

#include "gtest/gtest.h"
#include "gtest/gtest-matchers.h"
#include "gmock/gmock-more-matchers.h"

#include "json_serializer.hpp"
#include "idata.hpp"
#include "string.hpp"
#include "array.hpp"
#include "object.hpp"

using namespace testing;
using namespace data;
using namespace json;

TEST(ut_json_serializer, JsonSerializer_serialize_sanity) {
	// GIVEN
	Array test_array;
	test_array.push_back(std::shared_ptr<IData>(new String("value1")));
	test_array.push_back(std::shared_ptr<IData>(new String("value2")));

	Object test_object;
	test_object["key1"] = std::shared_ptr<IData>(new Array(test_array));
	test_object["key2"] = std::shared_ptr<IData>(new String("value3"));

	std::string expected_result("{\"key1\": [\"value1\", \"value2\"], \"key2\": \"value3\"}");

	// WHEN
	std::string result("");
	JsonSerializer serializer;

	// THEN
	ASSERT_NO_THROW(result = serializer.serialize(test_object));
	ASSERT_EQ(result, expected_result);
}
