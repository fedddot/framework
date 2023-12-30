#include <stdexcept>
#include <vector>
#include <map>
#include <algorithm>
#include <memory>
#include <iostream>

#include "gtest/gtest.h"
#include "gtest/gtest-matchers.h"
#include "gmock/gmock-more-matchers.h"

#include "ilistener.hpp"

#include "package_receiver.hpp"

using namespace testing;
using namespace communication;
using namespace generics;

class TestListener: public IListener<std::vector<char>> {
public:
	TestListener(const std::vector<char>& payload_data, bool *test_listener_invoked_ptr);
	virtual inline void on_event(const std::vector<char>& event) override;
private:
	std::vector<char> m_payload_data;
	bool *m_test_listener_invoked_ptr;
};

TestListener::TestListener(const std::vector<char>& payload_data, bool *test_listener_invoked_ptr): m_payload_data(payload_data), m_test_listener_invoked_ptr(test_listener_invoked_ptr) {
	*m_test_listener_invoked_ptr = false;
}

inline void TestListener::on_event(const std::vector<char>& event) {
	ASSERT_EQ(m_payload_data, event);
	*m_test_listener_invoked_ptr = true;
}

class ut_package_receiver: public Test {
public:
	ut_package_receiver();
	virtual inline void SetUp() override;
	virtual inline void TearDown() override;
	inline PackageReceiver& test_instance();
	inline PackageDescriptor& package_descriptor();
	inline Dispatcher<char>& char_dispatcher();
private:
	PackageDescriptor m_package_descriptor;
	std::shared_ptr<PackageReceiver> m_test_instance;
	Dispatcher<char> m_char_dispatcher;
};

ut_package_receiver::ut_package_receiver(): m_package_descriptor({'a', 'b', 'c', 'd'}, 4UL), m_test_instance(nullptr) {

}

inline void ut_package_receiver::SetUp() {
	m_test_instance = std::shared_ptr<PackageReceiver>(new PackageReceiver(m_package_descriptor, m_char_dispatcher));
}

inline void ut_package_receiver::TearDown() {
	m_test_instance = nullptr;
}

inline PackageReceiver& ut_package_receiver::test_instance() {
	return std::ref(*m_test_instance);
}

inline PackageDescriptor& ut_package_receiver::package_descriptor() {
	return std::ref(m_package_descriptor);
}

inline Dispatcher<char>& ut_package_receiver::char_dispatcher() {
	return std::ref(m_char_dispatcher);
}

TEST_F(ut_package_receiver, PackageReceiver_on_event_sanity) {
	// GIVEN
	const std::vector<std::vector<char>> test_cases(
		{
			{'a', 'b', 'c', 'd'},
			{'a', 'b', 'c', 'd', 'e', 'f'}
		}
	);
	
	std::for_each(test_cases.begin(), test_cases.end(),
		[&](const std::vector<char>& test_case) {
			// WHEN
			bool test_listener_invoked = false;
			TestListener test_listener(test_case, &test_listener_invoked);
			test_instance().subscribe(&test_listener);
			const std::vector<char> packed_test_cases = package_descriptor().pack(test_case);

			// THEN
			std::for_each(packed_test_cases.begin(), packed_test_cases.end(),
				[&](const char& ch) {
					ASSERT_NO_THROW(char_dispatcher().dispatch(ch));
				}
			);
			ASSERT_TRUE(test_listener_invoked);
			test_instance().unsubscribe(&test_listener);
		}
	);
}