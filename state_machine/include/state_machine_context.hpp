#ifndef	__STATE_MACHINE_CONTEXT_HPP__
#define	__STATE_MACHINE_CONTEXT_HPP__

namespace state_machine {
	template <class Tstate_id, class Tcontext_data>
	class StateMachineContext {
	public:
		StateMachineContext(const Tstate_id& initial_state_id, const Tcontext_data& initial_data);
		StateMachineContext(const StateMachineContext& other) = default;
		StateMachineContext& operator=(const StateMachineContext& other) = default;
		virtual ~StateMachineContext() noexcept = default;

		inline Tstate_id state_id() const;
		inline void update_state(const Tstate_id& state);
		inline Tcontext_data data() const;
		inline void update_data(const Tcontext_data& data);
	private:
		Tstate_id m_state_id;
		Tcontext_data m_data;
	}; // StateMachineContext

	template <class Tstate_id, class Tcontext_data>
	StateMachineContext<Tstate_id, Tcontext_data>::StateMachineContext(const Tstate_id& initial_state_id, const Tcontext_data& initial_data): m_state_id(initial_state_id), m_data(initial_data) {

	}

	template <class Tstate_id, class Tcontext_data>
	inline Tstate_id StateMachineContext<Tstate_id, Tcontext_data>::state_id() const {
		return m_state_id;
	}

	template <class Tstate_id, class Tcontext_data>
	inline void StateMachineContext<Tstate_id, Tcontext_data>::update_state(const Tstate_id& state) {
		m_state_id = state;
	}

	template <class Tstate_id, class Tcontext_data>
	inline Tcontext_data StateMachineContext<Tstate_id, Tcontext_data>::data() const {
		return m_data;
	}

	template <class Tstate_id, class Tcontext_data>
	inline void StateMachineContext<Tstate_id, Tcontext_data>::update_data(const Tcontext_data& data) {
		m_data = data;
	}

} // namespace state_machine
#endif // __STATE_MACHINE_EVENT_HPP__