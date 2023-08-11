#ifndef	__IDATA_RECEIVER_HPP__
#define	__IDATA_RECEIVER_HPP__

#include "ilistener.hpp"

namespace data {
	template <class Tindata, class Toutdata>
	class IDataReceiver: public common::IListener<Tindata> {
	public:
		virtual void set_data_listener(common::IListener<Toutdata> *data_listener_ptr) = 0;
		virtual common::IListener<Toutdata> *get_data_listener() = 0;
	}; // IDataReceiver
} // namespace data
#endif // __IDATA_RECEIVER_HPP__