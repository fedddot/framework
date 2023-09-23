#ifndef	__ILISTENER_HPP__
#define	__ILISTENER_HPP__

namespace common {
	template <class Event>
	class IListener {
	public:
		virtual ~IListener() noexcept = 0;
		virtual void on_event(const Event& event) = 0;
	}; // IListener

	template <class Event>
	IListener<Event>::~IListener() noexcept {

	}
} // namespace common

#endif // __ILISTENER_HPP__