#include <stdexcept>
#include <vector>
#include <map>
#include <algorithm>
#include <memory>
#include <iostream>

#include "gtest/gtest.h"
#include "gtest/gtest-matchers.h"
#include "gmock/gmock-more-matchers.h"

#include "package_descriptor.hpp"

using namespace testing;
using namespace communication;

TEST(ut_package_descriptor, PackageDescriptor_ctor_dtor_sanity) {
	// GIVEN
	const std::vector<char> test_header({'a', 'b', 'c', 'd'});
	const std::size_t test_payload_length_fiels_size(4UL);

	// WHEN
	std::shared_ptr<PackageDescriptor> test_instance(nullptr);

	// THEN
	ASSERT_NO_THROW(test_instance = std::shared_ptr<PackageDescriptor>(new PackageDescriptor(test_header, test_payload_length_fiels_size)));
	ASSERT_NO_THROW(test_instance = nullptr);
}

TEST(ut_package_descriptor, PackageDescriptor_ctor_dtor_negative) {
	// GIVEN
	const std::vector<char> test_header_valid({'a', 'b', 'c', 'd'});
	const std::size_t test_payload_length_fiels_size_valid(4UL);

	const std::vector<char> test_header_too_short({'a', 'b', 'c'});
	const std::size_t test_payload_length_fiels_size_too_small(0UL);
	const std::size_t test_payload_length_fiels_size_too_large(sizeof(std::size_t) + 1UL);

	// WHEN
	std::shared_ptr<PackageDescriptor> test_instance(nullptr);

	// THEN
	ASSERT_THROW(test_instance = std::shared_ptr<PackageDescriptor>(new PackageDescriptor(test_header_too_short, test_payload_length_fiels_size_valid)), std::invalid_argument);
	ASSERT_EQ(test_instance, nullptr);

	ASSERT_THROW(test_instance = std::shared_ptr<PackageDescriptor>(new PackageDescriptor(test_header_valid, test_payload_length_fiels_size_too_small)), std::invalid_argument);
	ASSERT_EQ(test_instance, nullptr);

	ASSERT_THROW(test_instance = std::shared_ptr<PackageDescriptor>(new PackageDescriptor(test_header_valid, test_payload_length_fiels_size_too_large)), std::invalid_argument);
	ASSERT_EQ(test_instance, nullptr);
}

TEST(ut_package_descriptor, PackageDescriptor_pack_payload_length_sanity) {
	// GIVEN
	const std::vector<char> test_header({'a', 'b', 'c', 'd'});
	const std::size_t test_payload_length_fiels_size(4UL);
	PackageDescriptor test_instance(test_header, test_payload_length_fiels_size);
	typedef std::pair<std::size_t, PackageDescriptor::PackageData> InputOutputPair;
	const std::map<std::size_t, PackageDescriptor::PackageData> test_cases(
		{
			InputOutputPair(0xFF, 		{0x00, 0x00, 0x00, static_cast<char>(0xFF)}),
			InputOutputPair(0xFF00, 	{0x00, 0x00, static_cast<char>(0xFF), 0x00}),
			InputOutputPair(0xFF0000, 	{0x00, static_cast<char>(0xFF), 0x00, 0x00}),
			InputOutputPair(0xFF000000, {static_cast<char>(0xFF), 0x00, 0x00, 0x00}),
		}
	);
	
	std::for_each(test_cases.begin(), test_cases.end(),
		[&](const auto& iter) {
			// WHEN
			PackageDescriptor::PackageData packed_data;

			// THEN
			ASSERT_NO_THROW(packed_data = test_instance.pack_payload_length(iter.first));
			ASSERT_EQ(packed_data, iter.second);
		}
	);
}

TEST(ut_package_descriptor, PackageDescriptor_unpack_payload_length_sanity) {
	// GIVEN
	const std::vector<char> test_header({'a', 'b', 'c', 'd'});
	const std::size_t test_payload_length_fiels_size(4UL);
	PackageDescriptor test_instance(test_header, test_payload_length_fiels_size);
	typedef std::pair<PackageDescriptor::PackageData, std::size_t> InputOutputPair;
	const std::map<PackageDescriptor::PackageData, std::size_t> test_cases(
		{
			InputOutputPair({static_cast<char>(0xAA), static_cast<char>(0xBC), static_cast<char>(0xCC), static_cast<char>(0xD1)}, 0xAABCCCD1),
			InputOutputPair({static_cast<char>(0x00), static_cast<char>(0xB0), static_cast<char>(0x12), static_cast<char>(0x45)}, 0x00B01245)
		}
	);
	
	std::for_each(test_cases.begin(), test_cases.end(),
		[&](const auto& iter) {
			// WHEN
			std::size_t decoded_length(0UL);

			// THEN
			ASSERT_NO_THROW(decoded_length = test_instance.unpack_payload_length(iter.first));
			ASSERT_EQ(decoded_length, iter.second);
		}
	);
}

TEST(ut_package_descriptor, PackageDescriptor_pack_sanity) {
	// GIVEN
	const std::vector<char> test_header({'a', 'b', 'c', 'd'});
	const std::size_t test_payload_length_fiels_size(4UL);
	PackageDescriptor test_instance(test_header, test_payload_length_fiels_size);
	const std::vector<std::vector<char>> test_cases(
		{
			{'a', 'b', 'c', 'd'},
			{'a', 'b', 'c', 'd', 'e', 'f'},
			{}
		}
	);
	
	std::for_each(test_cases.begin(), test_cases.end(),
		[&](const std::vector<char>& test_case) {
			// WHEN
			std::vector<char> packed_data;

			// THEN
			ASSERT_NO_THROW(packed_data = test_instance.pack(test_case));
			
			// Check header
			auto iter_start = packed_data.begin();
			auto iter_end = iter_start + test_header.size();
			std::vector<char> packed_header(iter_start, iter_end);
			ASSERT_EQ(test_header, packed_header);

			// Check size
			iter_start = iter_end;
			iter_end = iter_start + test_payload_length_fiels_size;
			std::vector<char> packed_size(iter_start, iter_end);
			ASSERT_EQ(test_case.size(), test_instance.unpack_payload_length(packed_size));

			// Check payload
			iter_start = iter_end;
			iter_end = iter_start + test_case.size();
			std::vector<char> packed_payload(iter_start, iter_end);
			ASSERT_EQ(packed_data.end(), iter_end);
			ASSERT_EQ(test_case, packed_payload);
		}
	);
}