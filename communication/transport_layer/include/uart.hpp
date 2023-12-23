#ifndef	__UART_HPP__
#define	__UART_HPP__

#include "uart_types.hpp"
#include "ibytes_reader.hpp"
#include "ibytes_writer.hpp"

namespace uart {
	class Uart {
	public:
		Uart(BaudRate baud_rate, Parity parity, StopBits stop_bits, BitsNumber bits_number);

		Uart(const Uart& other) = delete;
		Uart& operator=(const Uart& other) = delete;
		virtual ~Uart() noexcept = default;

		inline BaudRate baud_rate() const;
		inline Parity parity() const;
		inline StopBits stop_bits() const;
		inline BitsNumber bits_number() const;

		virtual io::IBytesReader& reader() = 0;
		virtual io::IBytesWriter& writer() = 0;
	private:
		BaudRate m_baud_rate;
		Parity m_parity;
		StopBits m_stop_bits;
		BitsNumber m_bits_number;
	}; // Uart

	inline BaudRate Uart::baud_rate() const {
		return m_baud_rate;
	}

	inline Parity Uart::parity() const {
		return m_parity;
	}

	inline StopBits Uart::stop_bits() const {
		return m_stop_bits;
	}

	inline BitsNumber Uart::bits_number() const {
		return m_bits_number;
	}
} // namespace communication
#endif // __UART_HPP__