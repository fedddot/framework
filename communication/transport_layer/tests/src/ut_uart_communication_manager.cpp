#include "gtest/gtest.h"
#include "gtest/gtest-matchers.h"
#include "gmock/gmock-more-matchers.h"
#include <iostream>
#include <functional>
#include <ostream>
#include <string>

#include "ilistener.hpp"
#include "uart_communication_manager.hpp"

using namespace uart;
using namespace generics;

class TestListener: public IListener<std::string> {
private:
	std::function<void(const std::string&)> m_on_event_cb;
public:
	TestListener(const std::function<void(const std::string&)>& on_event_cb): m_on_event_cb(on_event_cb) {

	}
	virtual void on_event(const std::string& event) override {
		m_on_event_cb(event);
	}
};

TEST(ut_uart_communication_manager, sanity) {
	// GIVEN
	const std::string test_data("test_data");
	auto data_sender = [&](const std::string& data)-> void {
		std::cout << data << std::endl;
	};

	auto event_action = [&](const std::string& data)-> void {
		ASSERT_EQ(test_data, data);
	};
	
	// WHEN
	UartCommunicationManager<std::string> manager();
	TestListener listener(event_action);

	// THEN
	// ASSERT_NO_THROW(manager.subscribe("test_subscriber", listener));
	// ASSERT_TRUE(manager.is_subscribed("test_subscriber"));
	// ASSERT_NO_THROW(manager.dispatch(test_data));
	// ASSERT_NO_THROW(manager.unsubscribe("test_subscriber"));
}