#include "uart_types.hpp"
#include "uart.hpp"

using namespace uart;

Uart::Uart(BaudRate baud_rate, Parity parity, StopBits stop_bits, BitsNumber bits_number): m_baud_rate(baud_rate), m_parity(parity), m_stop_bits(stop_bits), m_bits_number(bits_number) {

}