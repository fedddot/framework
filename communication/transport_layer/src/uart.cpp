#include "uart.hpp"

using namespace communication;

Uart::Uart(BaudRate baud_rate, Parity parity, StopBits stop_bits): m_baud_rate(baud_rate), m_parity(parity), m_stop_bits(stop_bits) {

}