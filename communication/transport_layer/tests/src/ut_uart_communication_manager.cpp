#include "gtest/gtest.h"
#include <iostream>
#include <functional>
#include <ostream>
#include <string>

#include "test_listener.hpp"
#include "uart_communication_manager.hpp"
#include "uart_types.hpp"

using namespace uart;
using namespace generics;
using namespace generics_tests;

TEST(ut_uart_communication_manager, sanity) {
	// GIVEN
	const std::string test_data = "ut_uart_communication_manager";
	auto data_sender = [&](const char& data)-> void {
		std::cout << "in data_sender: sending data \'" << data << "\'" << std::endl;	
	};

	// WHEN
	UartCommunicationManager<std::string> manager(data_sender, UartConfig());

	for (char ch: test_data) {
		// WHEN
		std::string test_listener_id("test_listener_" + std::to_string(ch));
		TestListener<char> test_listener(
			[&](const char& data)-> void {
				std::cout << "[" << test_listener_id << "]: in event_action: received data \'" << data << "\'" << std::endl;	
				ASSERT_EQ(ch, data);
			}
		);

		// THEN
		ASSERT_NO_THROW(manager.subscribe(test_listener_id, test_listener));
		ASSERT_TRUE(manager.is_subscribed(test_listener_id));
		ASSERT_NO_THROW(manager.feed(ch));
		ASSERT_NO_THROW(manager.unsubscribe(test_listener_id));
		ASSERT_FALSE(manager.is_subscribed(test_listener_id));
		ASSERT_NO_THROW(manager.send(ch));
	}
}