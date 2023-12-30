#ifndef	UART_COMMUNICATION_MANAGER_HPP
#define	UART_COMMUNICATION_MANAGER_HPP

#include "communication_manager.hpp"
#include "uart_types.hpp"

namespace uart {
	template <class Tid>
	class UartCommunicationManager: public communication::CommunicationManager<Tid, char> {
	public:
		typedef typename communication::CommunicationManager<Tid, char>::SendAction SendAction;
		inline UartCommunicationManager(const SendAction& send_action, const UartConfig& config);
		UartCommunicationManager(const UartCommunicationManager& other) = default;
		UartCommunicationManager& operator=(const UartCommunicationManager& other) = default;

		inline UartConfig config() const;
	private:
		UartConfig m_config;
	};

	template <class Tid>
	inline UartCommunicationManager<Tid>::UartCommunicationManager(const SendAction& send_action, const UartConfig& config): communication::CommunicationManager<Tid, char>(send_action), m_config(config) {

	}

	template <class Tid>
	inline UartConfig UartCommunicationManager<Tid>::config() const {
		return m_config;
	}
}
#endif // UART_COMMUNICATION_MANAGER_HPP