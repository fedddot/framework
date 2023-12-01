#ifndef	__STATE_MACHINE_HPP__
#define	__STATE_MACHINE_HPP__

#include <stdexcept>
#include <string>
#include <functional>
#include <vector>

#include "state_machine_state.hpp"
#include "state_machine_event.hpp"

namespace state_machine {
	template <class Tstate_id, class Tcontext, class Tevent_id, class Tevent_data>
	class StateMachine {
	public:
		typedef EventBase<Tevent_id, Tevent_data> Event;
		typedef StateBase<Tstate_id, Tcontext, Event> State;
		typedef std::vector<State> States;

		StateMachine(const std::string& name, const Tcontext& initial_context, const States& states, const Tstate_id& init_state_id);

		inline void step(const Event& event);
		inline Tstate_id curr_state() const;
		inline std::string name() const;
	private:
		typedef typename States::const_iterator StatesIterator;
		std::string m_name;
		Tcontext m_context;
		States m_states;
		StatesIterator m_curr_state;
		static inline StatesIterator find_state(const States& states, const Tstate_id& id);
	}; // StateMachine

	template <class Tstate_id, class Tcontext, class Tevent_id, class Tevent_data>
	StateMachine<Tstate_id, Tcontext, Tevent_id, Tevent_data>::StateMachine(const std::string& name, const Tcontext& initial_context, const States& states, const Tstate_id& init_state_id): m_name(name), m_context(initial_context), m_states(states), m_curr_state(find_state(m_states, init_state_id)) {

	}

	template <class Tstate_id, class Tcontext, class Tevent_id, class Tevent_data>
	inline void StateMachine<Tstate_id, Tcontext, Tevent_id, Tevent_data>::step(const Event& event) {
		auto next_state_id = m_curr_state->trans_function()(&m_context, m_curr_state->id(), event);
		auto next_state_iter = find_state(m_states, next_state_id);
		m_curr_state = next_state_iter;
	}

	template <class Tstate_id, class Tcontext, class Tevent_id, class Tevent_data>
	inline Tstate_id StateMachine<Tstate_id, Tcontext, Tevent_id, Tevent_data>::curr_state() const {
		return m_curr_state->id();
	}

	template <class Tstate_id, class Tcontext, class Tevent_id, class Tevent_data>
	inline std::string StateMachine<Tstate_id, Tcontext, Tevent_id, Tevent_data>::name() const {
		return m_name;
	}

	template <class Tstate_id, class Tcontext, class Tevent_id, class Tevent_data>
	inline typename StateMachine<Tstate_id, Tcontext, Tevent_id, Tevent_data>::StatesIterator StateMachine<Tstate_id, Tcontext, Tevent_id, Tevent_data>::find_state(const States& states, const Tstate_id& id) {
		StatesIterator iter(states.begin());
		StatesIterator iter_end(states.end());
		while (iter_end != iter) {
			if (id == iter->id()) {
				return iter;
			}
			++iter;
		}
		throw std::invalid_argument("state with specified ID not found");
	}

} // namespace state_machine
#endif // __STATE_MACHINE_HPP__