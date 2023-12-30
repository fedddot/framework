#ifndef	__STATE_MACHINE_HPP__
#define	__STATE_MACHINE_HPP__

#include <stdexcept>
#include <functional>
#include <string>
#include <map>

namespace state_machine {
	template <class Tstate_id, class Tcontext, class Tevent>
	class StateMachine {
	public:
		typedef std::function<Tstate_id(Tcontext *context, const Tstate_id& calling_state, const Tevent& event)> StateHandler;
		typedef std::map<Tstate_id, StateHandler> States;

		StateMachine(const std::string& name, const States& states, const Tstate_id& initial_state);
		StateMachine(const StateMachine& other) = default;
		StateMachine& operator=(const StateMachine& other) = default;
		virtual ~StateMachine() noexcept = default;

		inline void step(const Tevent& event);
		inline Tstate_id state() const;
		inline std::string name() const;
	private:
		typedef typename States::iterator StatesIterator;
		std::string m_name;
		Tcontext m_context;
		States m_states;
		StatesIterator m_state;
	}; // StateMachine

	template <class Tstate_id, class Tcontext, class Tevent>
	StateMachine<Tstate_id, Tcontext, Tevent>::StateMachine(const std::string& name, const States& states, const Tstate_id& initial_state): m_name(name), m_context(), m_states(states), m_state(m_states.end()) {
		auto iter = m_states.find(initial_state);
		if (m_states.end() == iter) {
			throw std::invalid_argument("initial state is not in received states");
		}
		m_state = iter;
	}

	template <class Tstate_id, class Tcontext, class Tevent>
	inline void StateMachine<Tstate_id, Tcontext, Tevent>::step(const Tevent& event) {
		auto next_state_id = (m_state->second)(&m_context, m_state->first, event);
		auto next_state_iter = m_states.find(next_state_id);
		if (m_states.end() == next_state_iter) {
			throw std::runtime_error("next state returned by state handler is not in received states");
		}
		m_state = next_state_iter;
	}

	template <class Tstate_id, class Tcontext, class Tevent>
	inline Tstate_id StateMachine<Tstate_id, Tcontext, Tevent>::state() const {
		return m_state->first;
	}

	template <class Tstate_id, class Tcontext, class Tevent>
	inline std::string StateMachine<Tstate_id, Tcontext, Tevent>::name() const {
		return m_name;
	}

} // namespace state_machine
#endif // __STATE_MACHINE_HPP__