#ifndef	__ICOMMUNICATION_MANAGER_HPP__
#define	__ICOMMUNICATION_MANAGER_HPP__

#include "ireceiver.hpp"
#include "isender.hpp"

namespace communication {
	template <class Trawdata, class Tdata>
	class ICommunicationManager: public IReceiver<Trawdata, Tdata>, public ISender<Tdata> {
	public:

	}; // ICommunicationManager
} // namespace communication
#endif // __ICOMMUNICATION_MANAGER_HPP__