#ifndef	ILISTENER_HPP
#define	ILISTENER_HPP

namespace generics {
	template <class Tevent>
	class IListener {
	public:
		virtual ~IListener() noexcept = 0;
		virtual void on_event(const Tevent& event) = 0;
	};

	template <class Tevent>
	IListener<Tevent>::~IListener() noexcept {

	}
}
#endif // ILISTENER_HPP