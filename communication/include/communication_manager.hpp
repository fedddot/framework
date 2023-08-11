#ifndef	__COMMUNICATION_MANAGER_HPP__
#define	__COMMUNICATION_MANAGER_HPP__

#include <stdexcept>
#include <memory>

#include "ireceiver.hpp"
#include "isender.hpp"
#include "icommunication_manager.hpp"

namespace communication {
	template <class Trawdata, class Tdata>
	class CommunicationManager: public ICommunicationManager<Trawdata, Tdata> {
	public:
		CommunicationManager(const std::shared_ptr<IReceiver<Trawdata, Tdata>>& receiver, const std::shared_ptr<ISender<Tdata>>& sender);

		virtual void onEvent(Trawdata event) override;
		virtual void set_data_listener(common::IListener<Tdata> *data_listener_ptr) override;
		virtual common::IListener<Tdata> *get_data_listener() override;
		virtual void send(Tdata data) override;
	private:
		std::shared_ptr<IReceiver<Trawdata, Tdata>> m_receiver;
		std::shared_ptr<ISender<Tdata>> m_sender;

		template <class Tinit>
		static inline std::shared_ptr<Tinit> init_pointer(const std::shared_ptr<Tinit>& ptr);
	}; // CommunicationManager

	template <class Trawdata, class Tdata>
	CommunicationManager<Trawdata, Tdata>::CommunicationManager(const std::shared_ptr<IReceiver<Trawdata, Tdata>>& receiver, const std::shared_ptr<ISender<Tdata>>& sender): m_receiver(init_pointer<IReceiver<Trawdata, Tdata>>(receiver)), m_sender(init_pointer<ISender<Tdata>>(sender)) {

	}

	template <class Trawdata, class Tdata>
	void CommunicationManager<Trawdata, Tdata>::onEvent(Trawdata event) {
		m_receiver->onEvent(event);
	}

	template <class Trawdata, class Tdata>
	void CommunicationManager<Trawdata, Tdata>::set_data_listener(common::IListener<Tdata> *data_listener_ptr) {
		m_receiver->set_data_listener(data_listener_ptr);
	}

	template <class Trawdata, class Tdata>
	common::IListener<Tdata> *CommunicationManager<Trawdata, Tdata>::get_data_listener() {
		return m_receiver->get_data_listener();
	}

	template <class Trawdata, class Tdata>
	void CommunicationManager<Trawdata, Tdata>::send(Tdata data) {
		m_sender->send(data);
	}

	template <class Trawdata, class Tdata>
	template <class Tinit>
	inline std::shared_ptr<Tinit> CommunicationManager<Trawdata, Tdata>::init_pointer(const std::shared_ptr<Tinit>& ptr) {
		if (nullptr == ptr) {
			throw std::invalid_argument("invalid pointer received");
		}
		return ptr;
	}
} // namespace communication
#endif // __ICOMMUNICATION_MANAGER_HPP__