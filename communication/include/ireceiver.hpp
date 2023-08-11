#ifndef	__IRECEIVER_HPP__
#define	__IRECEIVER_HPP__

#include "ilistener.hpp"

namespace communication {
	template <class Trawdata, class Tdata>
	class IReceiver: public common::IListener<Trawdata> {
	public:
		virtual void set_data_listener(common::IListener<Tdata> *data_listener_ptr) = 0;
		virtual common::IListener<Tdata> *get_data_listener() = 0;
	}; // IReceiver
} // namespace communication
#endif // __IRECEIVER_HPP__