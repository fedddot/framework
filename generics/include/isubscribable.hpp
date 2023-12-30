#ifndef	ISUBSCRIBABLE_HPP
#define	ISUBSCRIBABLE_HPP

namespace generics {
	template <class Tid, class Tsubscriber>
	class ISubscribable {
	public:
		virtual ~ISubscribable() noexcept = 0;
		virtual void subscribe(const Tid& id, Tsubscriber subscriber) = 0;
		virtual void unsubscribe(const Tid& id) = 0;
		virtual bool is_subscribed(const Tid& id) const = 0;
	};

	template <class Tid, class Tsubscriber>
	ISubscribable<Tid, Tsubscriber>::~ISubscribable() noexcept {

	}
}

#endif // ISUBSCRIBABLE_HPP