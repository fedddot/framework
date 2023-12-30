#ifndef	__UART_HPP__
#define	__UART_HPP__

#include <vector>

#include "ilistener.hpp"
#include "dispatcher.hpp"
#include "isender.hpp"

namespace communication {
	class Uart: public ISender<std::vector<char>>, public common::Dispatcher<char> {
	public:
		enum class BaudRate: int {
			BR9600,
			BR115200
		};

		enum class Parity: int {
			NONE,
			EVEN,
			ODD
		};

		enum class StopBits: int {
			ONE,
			TWO
		};

		enum class BitsNumber: int {
			BN5,
			BN6,
			BN7,
			BN8
		};

		Uart(BaudRate baud_rate = BaudRate::BR115200, Parity parity = Parity::NONE, StopBits stop_bits = StopBits::ONE, BitsNumber bits_number = BitsNumber::BN8);

		Uart(const Uart& other) = delete;
		Uart& operator=(const Uart& other) = delete;

		inline BaudRate baud_rate() const;
		inline Parity parity() const;
		inline StopBits stop_bits() const;
		inline BitsNumber bits_number() const;
	private:
		BaudRate m_baud_rate;
		Parity m_parity;
		StopBits m_stop_bits;
		BitsNumber m_bits_number;
	}; // Uart

	inline Uart::BaudRate Uart::baud_rate() const {
		return m_baud_rate;
	}

	inline Uart::Parity Uart::parity() const {
		return m_parity;
	}

	inline Uart::StopBits Uart::stop_bits() const {
		return m_stop_bits;
	}

	inline Uart::BitsNumber Uart::bits_number() const {
		return m_bits_number;
	}
} // namespace communication
#endif // __UART_HPP__