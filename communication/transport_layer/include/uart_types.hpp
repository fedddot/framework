#ifndef	UART_TYPES_HPP
#define	UART_TYPES_HPP

namespace uart {
	struct UartConfig {
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
		
		BaudRate baud_rate;
		Parity parity;
		StopBits stop_bits;
		BitsNumber bits_number;
		
		inline UartConfig(BaudRate baud_rate = BaudRate::BR115200, Parity parity = Parity::NONE, StopBits stop_bits = StopBits::ONE, BitsNumber bits_number = BitsNumber::BN8);
		
		UartConfig(const UartConfig& other) = default;
		UartConfig& operator=(const UartConfig& other) = default;
		virtual ~UartConfig() noexcept = default;
	};

	inline UartConfig::UartConfig(BaudRate baud_rate, Parity parity, StopBits stop_bits, BitsNumber bits_number): baud_rate(baud_rate), parity(parity), stop_bits(stop_bits), bits_number(bits_number) {

	}
}
#endif // UART_TYPES_HPP