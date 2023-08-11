#ifndef	__ICOMMUNICATION_MANAGER_HPP__
#define	__ICOMMUNICATION_MANAGER_HPP__

#include "ireceiver.hpp"
#include "isender.hpp"

namespace communication {
	template <class Trawdata, class Tdata>
	class ICommunicationManager: public IReceiver<Trawdata, Tdata>, public ISender<Tdata> {
	public:
		virtual void start() = 0;
		virtual void stop() = 0;
		virtual bool isRunning() const = 0;
	}; // ICommunicationManager
} // namespace communication
#endif // __ICOMMUNICATION_MANAGER_HPP__