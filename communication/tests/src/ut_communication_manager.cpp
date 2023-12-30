#include "gtest/gtest.h"
#include <iostream>
#include <functional>
#include <ostream>
#include <string>

#include "test_listener.hpp"
#include "communication_manager.hpp"

using namespace communication;
using namespace generics;
using namespace generics_tests;

TEST(ut_communication_manager, sanity) {
	// GIVEN
	const std::string test_data("test_data");
	auto data_sender = [&](const std::string& data)-> void {
		std::cout << data << std::endl;
	};

	auto event_action = [&](const std::string& data)-> void {
		ASSERT_EQ(test_data, data);
	};
	
	// WHEN
	CommunicationManager<std::string, std::string> manager(data_sender);
	TestListener<std::string> listener(event_action);

	// THEN
	ASSERT_NO_THROW(manager.subscribe("test_subscriber", listener));
	ASSERT_TRUE(manager.is_subscribed("test_subscriber"));
	ASSERT_NO_THROW(manager.feed(test_data));
	ASSERT_NO_THROW(manager.unsubscribe("test_subscriber"));
}