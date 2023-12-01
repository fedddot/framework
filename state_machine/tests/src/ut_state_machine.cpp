#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <vector>

#include "gtest/gtest.h"

#include "state_machine.hpp"

using namespace testing;
using namespace state_machine;

enum class EventId: int {
	START_EVENT,
	END_EVENT,
	PROCESS_EVENT
};
typedef std::string EventData;
typedef std::vector<EventData> Context;

enum class StateId: int {
	IDLE,
	WAIT_PROCESS_EVENT,
	WAIT_END_EVENT,
};

typedef StateMachine<StateId, Context, EventId, EventData> TestStateMachine;

static std::string state_id_to_str(const StateId& state_id) {
	switch (state_id) {
	case StateId::IDLE:
		return "IDLE";
	case StateId::WAIT_PROCESS_EVENT:
		return "WAIT_PROCESS_EVENT";
	case StateId::WAIT_END_EVENT:
		return "WAIT_END_EVENT";
	default:
		break;
	}
	throw std::invalid_argument("unsupported state_id received");
}

static std::string event_id_to_str(const EventId& event_id) {
	switch (event_id) {
	case EventId::START_EVENT:
		return "START_EVENT";
	case EventId::PROCESS_EVENT:
		return "PROCESS_EVENT";
	case EventId::END_EVENT:
		return "END_EVENT";
	default:
		break;
	}
	throw std::invalid_argument("unsupported event_id received");
}

static void report_state(const StateId& state_id, const TestStateMachine::Event& event) {
	std::cout << "[" << state_id_to_str(state_id) << "]: event received: " << event_id_to_str(event.id()) << std::endl;
}

const TestStateMachine::States test_states {
	TestStateMachine::State(
		StateId::IDLE,
		[](Context *context, const StateId& current_state, const TestStateMachine::Event& event)-> StateId {
			report_state(current_state, event);
			context->push_back(event.data());
			if (EventId::START_EVENT == event.id()) {
				const StateId next_state_id(StateId::WAIT_PROCESS_EVENT);
				std::cout << "go to " << state_id_to_str(next_state_id) << std::endl;
				return next_state_id;
			}
			std::cout << "ignored" << std::endl;
			return current_state;
		}
	),
	TestStateMachine::State(
		StateId::WAIT_PROCESS_EVENT,
		[](Context *context, const StateId& current_state, const TestStateMachine::Event& event)-> StateId {
			report_state(current_state, event);
			context->push_back(event.data());
			if (EventId::PROCESS_EVENT == event.id()) {
				const StateId next_state_id(StateId::WAIT_END_EVENT);
				std::cout << "go to " << state_id_to_str(next_state_id) << std::endl;
				return next_state_id;
			}
			std::cout << "ignored" << std::endl;
			return current_state;
		}
	),
	TestStateMachine::State(
		StateId::WAIT_END_EVENT,
		[](Context *context, const StateId& current_state, const TestStateMachine::Event& event)-> StateId {
			report_state(current_state, event);
			context->push_back(event.data());
			if (EventId::END_EVENT == event.id()) {
				const StateId next_state_id(StateId::IDLE);
				std::cout << "go to " << state_id_to_str(next_state_id) << std::endl;
				return next_state_id;
			}
			std::cout << "ignored" << std::endl;
			return current_state;
		}
	)
};

TEST(ut_state_machine, Ctor_Dtor_getters_sanity) {
	// GIVEN:
	const std::string test_sm_name("test_sm");
	const StateId initial_state(StateId::IDLE);
	// WHEN:
	TestStateMachine *instance_ptr(nullptr);
	// THEN:
	ASSERT_NO_THROW(instance_ptr = new TestStateMachine(test_sm_name, Context(), test_states, initial_state));
	ASSERT_EQ(test_sm_name, instance_ptr->name());
	ASSERT_EQ(initial_state, instance_ptr->curr_state());
	ASSERT_NO_THROW(delete instance_ptr);
	instance_ptr = nullptr;
}

TEST(ut_state_machine, step_sanity) {
	// GIVEN:
	const std::string test_sm_name("test_sm");
	const StateId initial_state(StateId::IDLE);
	struct TestCase {
		std::string description;
		StateId initial_state;
		EventId ignored_event;
		EventId handled_event;
		StateId expected_state;
	};
	const std::vector<TestCase> test_cases {
		{
			.description = "Receiving events from IDLE state",
			.initial_state = StateId::IDLE,
			.ignored_event = EventId::PROCESS_EVENT,
			.handled_event = EventId::START_EVENT,
			.expected_state = StateId::WAIT_PROCESS_EVENT
		},
		{
			.description = "Receiving events from WAIT_PROCESS_EVENT state",
			.initial_state = StateId::WAIT_PROCESS_EVENT,
			.ignored_event = EventId::END_EVENT,
			.handled_event = EventId::PROCESS_EVENT,
			.expected_state = StateId::WAIT_END_EVENT
		},
		{
			.description = "Receiving events from WAIT_END_EVENT state",
			.initial_state = StateId::WAIT_END_EVENT,
			.ignored_event = EventId::PROCESS_EVENT,
			.handled_event = EventId::END_EVENT,
			.expected_state = StateId::IDLE
		}
	};

	// WHEN:
	TestStateMachine instance(test_sm_name, Context(), test_states, initial_state);

	std::for_each(
		test_cases.begin(),
		test_cases.end(),
		[&](const auto& test_case) {
			std::cout << "Running test case: " << test_case.description << std::endl;
			// WHEN:
			TestStateMachine::Event ignored_event(test_case.ignored_event, test_case.description);
			TestStateMachine::Event handled_event(test_case.handled_event, test_case.description);

			// THEN:
			ASSERT_EQ(test_case.initial_state, instance.curr_state());
			ASSERT_NO_THROW(instance.step(ignored_event));
			ASSERT_EQ(test_case.initial_state, instance.curr_state());
			ASSERT_NO_THROW(instance.step(handled_event));
			ASSERT_EQ(test_case.expected_state, instance.curr_state());
		}
	);
}