#ifndef	__STATE_MACHINE_STATE_HPP__
#define	__STATE_MACHINE_STATE_HPP__

#include <functional>

namespace state_machine {
	template <class Tstate_id, class Tcontext, class Tevent>
	class StateBase {
	public:
		typedef std::function<Tstate_id(Tcontext *, const Tstate_id& current_state, const Tevent&)> TransitionFunction;

		StateBase(const Tstate_id& id, const TransitionFunction& trans_function);
		StateBase(const StateBase& other) = default;
		StateBase& operator=(const StateBase& other) = default;
		virtual ~StateBase() noexcept = default;

		inline Tstate_id id() const;
		inline TransitionFunction trans_function() const;
	private:
		Tstate_id m_id;
		TransitionFunction m_trans_function;
	};

	template <class Tstate_id, class Tcontext, class Tevent>
	StateBase<Tstate_id, Tcontext, Tevent>::StateBase(const Tstate_id& id, const TransitionFunction& trans_function): m_id(id), m_trans_function(trans_function) {

	}

	template <class Tstate_id, class Tcontext, class Tevent>
	inline Tstate_id StateBase<Tstate_id, Tcontext, Tevent>::id() const {
		return m_id;
	}

	template <class Tstate_id, class Tcontext, class Tevent>
	inline typename StateBase<Tstate_id, Tcontext, Tevent>::TransitionFunction StateBase<Tstate_id, Tcontext, Tevent>::trans_function() const {
		return m_trans_function;
	}

} // namespace state_machine
#endif // __STATE_MACHINE_STATE_HPP__