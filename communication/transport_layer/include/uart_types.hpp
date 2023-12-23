#ifndef	__UART_TYPES_HPP__
#define	__UART_TYPES_HPP__

namespace uart {
	enum class BaudRate: unsigned int {
		BR9600 = 9600U,
		BR115200 = 115200U
	};

	enum class Parity: int {
		NONE,
		EVEN,
		ODD
	};

	enum class StopBits: unsigned int {
		ONE = 1,
		TWO = 2
	};

	enum class BitsNumber: unsigned int {
		BN5 = 5U,
		BN6 = 6U,
		BN7 = 7U,
		BN8 = 8U
	};
} // namespace uart
#endif // __UART_TYPES_HPP__