#include "gtest/gtest.h"
#include "gtest/gtest-matchers.h"
#include "gmock/gmock-more-matchers.h"
#include <iostream>
#include <string>

#include "dispatcher.hpp"
#include "ilistener.hpp"

using namespace generics;

class TestListener: public IListener<std::string> {
public:
	virtual void on_event(const std::string& event) {
		std::cout << event << std::endl;
	}
};

TEST(ut_dispatcher, sanity) {
	// GIVEN:
	TestListener lis1;
	TestListener lis2;
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
