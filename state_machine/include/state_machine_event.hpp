#ifndef	__STATE_MACHINE_EVENT_HPP__
#define	__STATE_MACHINE_EVENT_HPP__

namespace state_machine {
	template <class Tevent_id, class Tevent_data>
	class StateMachineEvent {
	public:
		StateMachineEvent(const Tevent_id& id, const Tevent_data& data);
		StateMachineEvent(const StateMachineEvent& other) = default;
		StateMachineEvent& operator=(const StateMachineEvent& other) = default;
		virtual ~StateMachineEvent() noexcept = default;
		inline Tevent_id id() const;
		inline Tevent_data data() const;
	private:
		Tevent_id m_id;
		Tevent_data m_data;
	}; // Event

	template <class Tevent_id, class Tevent_data>
	StateMachineEvent<Tevent_id, Tevent_data>::StateMachineEvent(const Tevent_id& id, const Tevent_data& data): m_id(id), m_data(data) {

	}

	template <class Tevent_id, class Tevent_data>
	inline Tevent_id StateMachineEvent<Tevent_id, Tevent_data>::id() const {
		return m_id;
	}

	template <class Tevent_id, class Tevent_data>
	inline Tevent_data StateMachineEvent<Tevent_id, Tevent_data>::data() const {
		return m_data;
	}

} // namespace state_machine
#endif // __STATE_MACHINE_EVENT_HPP__