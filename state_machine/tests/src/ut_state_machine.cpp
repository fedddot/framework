#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <vector>

#include "gtest/gtest.h"

#include "state_machine.hpp"

using namespace testing;
using namespace state_machine;

enum class Event: int {
	START_EVENT,
	END_EVENT,
	PROCESS_EVENT
};
typedef std::vector<Event> Context;

enum class State: int {
	IDLE,
	WAIT_PROCESS_EVENT,
	WAIT_END_EVENT,
};

typedef StateMachine<State, Context, Event> TestStateMachine;

static std::string state_id_to_str(const State& state_id) {
	switch (state_id) {
	case State::IDLE:
		return "IDLE";
	case State::WAIT_PROCESS_EVENT:
		return "WAIT_PROCESS_EVENT";
	case State::WAIT_END_EVENT:
		return "WAIT_END_EVENT";
	default:
		break;
	}
	throw std::invalid_argument("unsupported state_id received");
}

static std::string event_id_to_str(const Event& event_id) {
	switch (event_id) {
	case Event::START_EVENT:
		return "START_EVENT";
	case Event::PROCESS_EVENT:
		return "PROCESS_EVENT";
	case Event::END_EVENT:
		return "END_EVENT";
	default:
		break;
	}
	throw std::invalid_argument("unsupported event_id received");
}

static void report_state(const State& state_id, const Event& event) {
	std::cout << "[" << state_id_to_str(state_id) << "]: event received: " << event_id_to_str(event) << std::endl;
}

const TestStateMachine::States test_states {
	{
		State::IDLE,
		[](Context *context, const State& current_state, const Event& event)-> State {
			report_state(current_state, event);
			context->push_back(event);
			if (Event::START_EVENT == event) {
				const State next_state_id(State::WAIT_PROCESS_EVENT);
				std::cout << "go to " << state_id_to_str(next_state_id) << std::endl;
				return next_state_id;
			}
			std::cout << "ignored" << std::endl;
			return current_state;
		}
	},
	{
		State::WAIT_PROCESS_EVENT,
		[](Context *context, const State& current_state, const Event& event)-> State {
			report_state(current_state, event);
			context->push_back(event);
			if (Event::PROCESS_EVENT == event) {
				const State next_state_id(State::WAIT_END_EVENT);
				std::cout << "go to " << state_id_to_str(next_state_id) << std::endl;
				return next_state_id;
			}
			std::cout << "ignored" << std::endl;
			return current_state;
		}
	},
	{
		State::WAIT_END_EVENT,
		[](Context *context, const State& current_state, const Event& event)-> State {
			report_state(current_state, event);
			context->push_back(event);
			if (Event::END_EVENT == event) {
				const State next_state_id(State::IDLE);
				std::cout << "go to " << state_id_to_str(next_state_id) << std::endl;
				return next_state_id;
			}
			std::cout << "ignored" << std::endl;
			return current_state;
		}
	}
};

TEST(ut_state_machine, Ctor_Dtor_getters_sanity) {
	// GIVEN:
	const std::string test_sm_name("test_sm");
	const State initial_state(State::IDLE);
	// WHEN:
	TestStateMachine *instance_ptr(nullptr);
	// THEN:
	ASSERT_NO_THROW(instance_ptr = new TestStateMachine(test_sm_name, test_states, initial_state));
	ASSERT_EQ(test_sm_name, instance_ptr->name());
	ASSERT_EQ(initial_state, instance_ptr->state());
	ASSERT_NO_THROW(delete instance_ptr);
	instance_ptr = nullptr;
}

TEST(ut_state_machine, Ctor_invalid_states_empty_negative) {
	// GIVEN:
	const std::string test_sm_name("test_sm");
	const State initial_state(State::IDLE);
	
	// WHEN:
	TestStateMachine *instance_ptr(nullptr);
	// THEN:
	ASSERT_THROW(instance_ptr = new TestStateMachine(test_sm_name, TestStateMachine::States(), initial_state), std::invalid_argument);
	ASSERT_EQ(nullptr, instance_ptr);
}

TEST(ut_state_machine, Ctor_invalid_states_initial_state_is_not_in_states_negative) {
	// GIVEN:
	const std::string test_sm_name("test_sm");
	const State initial_state(State::IDLE);
	TestStateMachine::States invalid_states(test_states);
	
	// WHEN:
	TestStateMachine *instance_ptr(nullptr);
	invalid_states.erase(invalid_states.find(initial_state));

	// THEN:
	ASSERT_THROW(instance_ptr = new TestStateMachine(test_sm_name, invalid_states, initial_state), std::invalid_argument);
	ASSERT_EQ(nullptr, instance_ptr);
}

TEST(ut_state_machine, step_sanity) {
	// GIVEN:
	const std::string test_sm_name("test_sm");
	const State initial_state(State::IDLE);
	struct TestCase {
		std::string description;
		State initial_state;
		Event ignored_event;
		Event handled_event;
		State expected_state;
	};
	const std::vector<TestCase> test_cases {
		{
			.description = "Receiving events from IDLE state",
			.initial_state = State::IDLE,
			.ignored_event = Event::PROCESS_EVENT,
			.handled_event = Event::START_EVENT,
			.expected_state = State::WAIT_PROCESS_EVENT
		},
		{
			.description = "Receiving events from WAIT_PROCESS_EVENT state",
			.initial_state = State::WAIT_PROCESS_EVENT,
			.ignored_event = Event::END_EVENT,
			.handled_event = Event::PROCESS_EVENT,
			.expected_state = State::WAIT_END_EVENT
		},
		{
			.description = "Receiving events from WAIT_END_EVENT state",
			.initial_state = State::WAIT_END_EVENT,
			.ignored_event = Event::PROCESS_EVENT,
			.handled_event = Event::END_EVENT,
			.expected_state = State::IDLE
		}
	};

	// WHEN:
	TestStateMachine instance(test_sm_name, test_states, initial_state);

	std::for_each(
		test_cases.begin(),
		test_cases.end(),
		[&](const auto& test_case) {
			std::cout << "Running test case: " << test_case.description << std::endl;
			// WHEN:
			Event ignored_event(test_case.ignored_event);
			Event handled_event(test_case.handled_event);

			// THEN:
			ASSERT_EQ(test_case.initial_state, instance.state());
			ASSERT_NO_THROW(instance.step(ignored_event));
			ASSERT_EQ(test_case.initial_state, instance.state());
			ASSERT_NO_THROW(instance.step(handled_event));
			ASSERT_EQ(test_case.expected_state, instance.state());
		}
	);
}

TEST(ut_state_machine, step_negative_handler_returned_non_existing_state) {
	// GIVEN:
	const std::string test_sm_name("test_sm");
	const State initial_state(State::IDLE);
	const State deleted_state(State::WAIT_END_EVENT);
	TestStateMachine::States states(test_states);
	
	// WHEN:
	states.erase(states.find(deleted_state));
	TestStateMachine instance(test_sm_name, states, initial_state);

	// THEN:
	ASSERT_NO_THROW(instance.step(Event::START_EVENT));
	ASSERT_THROW(instance.step(Event::PROCESS_EVENT), std::runtime_error);
}