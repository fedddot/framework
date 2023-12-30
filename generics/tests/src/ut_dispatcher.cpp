#include "gtest/gtest.h"
#include <iostream>
#include <string>

#include "dispatcher.hpp"
#include "test_listener.hpp"

using namespace generics;
using namespace generics_tests;

TEST(ut_dispatcher, sanity) {
	// GIVEN:
	auto on_event = [&](const std::string& event)-> void {
		std::cout << event << std::endl;
	};
	TestListener<std::string> lis1(on_event);
	TestListener<std::string> lis2(on_event);
	Dispatcher<int, std::string> dispatcher;

	// THEN:
	ASSERT_NO_THROW(dispatcher.subscribe(1, lis1));
	ASSERT_THROW(dispatcher.subscribe(1, lis1), std::invalid_argument);
	ASSERT_NO_THROW(dispatcher.subscribe(2, lis2));
	ASSERT_THROW(dispatcher.subscribe(2, lis2), std::invalid_argument);
	ASSERT_NO_THROW(dispatcher.dispatch("test string"));
	ASSERT_NO_THROW(dispatcher.unsubscribe(2));
	ASSERT_NO_THROW(dispatcher.dispatch("another test string"));
}
