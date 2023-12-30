#ifndef	COMMUNICATION_MANAGER_HPP
#define	COMMUNICATION_MANAGER_HPP

#include <functional>
#include "dispatcher.hpp"
#include "icommunication_manager.hpp"

namespace communication {
	template <class Tid, class Tdata>
	class CommunicationManager: public ICommunicationManager<Tid, Tdata> {
	public:
		using SendAction = std::function<void(const Tdata&)>;
		CommunicationManager(const SendAction& send_action);
		virtual inline void subscribe(const Tid& id, generics::IListener<Tdata>& subscriber) override;
		virtual inline void unsubscribe(const Tid& id) override;
		virtual inline bool is_subscribed(const Tid& id) const override;
		virtual inline void send(const Tdata& data) override;
		inline void feed(const Tdata& data);
	private:
		SendAction m_send_action;
		generics::Dispatcher<Tid, Tdata> m_dispatcher;
	};

	template <class Tid, class Tdata>
	CommunicationManager<Tid, Tdata>::CommunicationManager(const SendAction& send_action): m_send_action(send_action) {

	}

	template <class Tid, class Tdata>
	inline void CommunicationManager<Tid, Tdata>::subscribe(const Tid& id, generics::IListener<Tdata>& subscriber) {
		m_dispatcher.subscribe(id, subscriber);
	}

	template <class Tid, class Tdata>
	inline void CommunicationManager<Tid, Tdata>::unsubscribe(const Tid& id) {
		m_dispatcher.unsubscribe(id);
	}

	template <class Tid, class Tdata>
	inline bool CommunicationManager<Tid, Tdata>::is_subscribed(const Tid& id) const {
		return m_dispatcher.is_subscribed(id);
	}


	template <class Tid, class Tdata>
	inline void CommunicationManager<Tid, Tdata>::send(const Tdata& data) {
		m_send_action(data);
	}

	template <class Tid, class Tdata>
	inline void CommunicationManager<Tid, Tdata>::feed(const Tdata& data) {
		m_dispatcher.dispatch(data);
	}

} // namespace communication
#endif // COMMUNICATION_MANAGER_HPP