#ifndef	ICOMMUNICATION_MANAGER_HPP
#define	ICOMMUNICATION_MANAGER_HPP

#include "isubscribable.hpp"
#include "ilistener.hpp"

namespace communication {
	template <class Tid, class Tdata>
	class ICommunicationManager: public generics::ISubscribable<Tid, generics::IListener<Tdata>&> {
	public:
		virtual void send(const Tdata& data) = 0;
	};
} // namespace communication
#endif // ICOMMUNICATION_MANAGER_HPP