#ifndef	__STATE_MACHINE_STATE_HPP__
#define	__STATE_MACHINE_STATE_HPP__

#include <functional>
#include "state_machine_context.hpp"

namespace state_machine {
	template <class Tstate_id, class Tcontext_data, class Tevent>
	class StateBase {
	public:
		typedef StateMachineContext<Tstate_id, Tcontext_data> Context;
		typedef std::function<void(Context *, const Tevent&)> StateHandler;

		StateBase(const Tstate_id& id, const StateHandler& state_handler);
		StateBase(const StateBase& other) = default;
		StateBase& operator=(const StateBase& other) = default;
		virtual ~StateBase() noexcept = default;

		inline Tstate_id id() const;
		inline void handle_event(Context *context_ptr, const Tevent& event) const;
	private:
		Tstate_id m_id;
		StateHandler m_handler;
	};

	template <class Tstate_id, class Tcontext, class Tevent>
	StateBase<Tstate_id, Tcontext, Tevent>::StateBase(const Tstate_id& id, const StateHandler& state_handler): m_id(id), m_handler(state_handler) {

	}

	template <class Tstate_id, class Tcontext, class Tevent>
	inline Tstate_id StateBase<Tstate_id, Tcontext, Tevent>::id() const {
		return m_id;
	}

	template <class Tstate_id, class Tcontext, class Tevent>
	inline void StateBase<Tstate_id, Tcontext, Tevent>::handle_event(Context *context_ptr, const Tevent& event) const {
		m_handler(context_ptr, event);
	}

} // namespace state_machine
#endif // __STATE_MACHINE_STATE_HPP__