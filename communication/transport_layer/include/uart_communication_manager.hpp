#ifndef	UART_COMMUNICATION_MANAGER_HPP
#define	UART_COMMUNICATION_MANAGER_HPP

#include "communication_manager.hpp"
#include "uart_types.hpp"

namespace uart {
	template <class Tid>
	class UartCommunicationManager: public communication::CommunicationManager<Tid, char> {
	public:
		using BaudRate = uart_types::BaudRate;
		using Parity = uart_types::Parity;
		using StopBits = uart_types::StopBits;
		using BitsNumber = uart_types::BitsNumber;

		UartCommunicationManager();

		UartCommunicationManager(const UartCommunicationManager& other) = delete;
		UartCommunicationManager& operator=(const UartCommunicationManager& other) = delete;

		inline BaudRate baud_rate() const;
		inline Parity parity() const;
		inline StopBits stop_bits() const;
		inline BitsNumber bits_number() const;
	private:
		BaudRate m_baud_rate;
		Parity m_parity;
		StopBits m_stop_bits;
		BitsNumber m_bits_number;
	};

	inline UartCommunicationManager::BaudRate UartCommunicationManager::baud_rate() const {
		return m_baud_rate;
	}

	inline UartCommunicationManager::Parity UartCommunicationManager::parity() const {
		return m_parity;
	}

	inline UartCommunicationManager::StopBits UartCommunicationManager::stop_bits() const {
		return m_stop_bits;
	}

	inline UartCommunicationManager::BitsNumber UartCommunicationManager::bits_number() const {
		return m_bits_number;
	}
}
#endif // UART_COMMUNICATION_MANAGER_HPP