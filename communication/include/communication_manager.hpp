#ifndef	COMMUNICATION_MANAGER_HPP
#define	COMMUNICATION_MANAGER_HPP

#include <functional>
#include "dispatcher.hpp"

namespace communication {
	template <class Tid, class Tdata>
	class CommunicationManager: public generics::Dispatcher<Tid, Tdata> {
	public:
		CommunicationManager(const std::function<void(const Tdata&)>& send_action);
		inline void send(const Tdata& data);
	private:
		std::function<void(const Tdata&)> m_send_action;
	};

	template <class Tid, class Tdata>
	CommunicationManager<Tid, Tdata>::CommunicationManager(const std::function<void(const Tdata&)>& send_action): m_send_action(send_action) {

	}

	template <class Tid, class Tdata>
	inline void CommunicationManager<Tid, Tdata>::send(const Tdata& data) {
		m_send_action(data);
	}
} // namespace communication
#endif // COMMUNICATION_MANAGER_HPP