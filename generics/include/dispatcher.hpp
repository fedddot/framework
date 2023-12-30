#ifndef	__DISPATCHER_HPP__
#define	__DISPATCHER_HPP__

#include <stdexcept>
#include <algorithm>
#include <map>
#include "ilistener.hpp"
#include "isubscribable.hpp"

namespace generics {
	template <class Tid, class Tevent>
	class Dispatcher: public ISubscribable<Tid, IListener<Tevent>&> {
	public:
		Dispatcher() = default;
		Dispatcher(const Dispatcher<Tid, Tevent>& other) = default;
		Dispatcher& operator=(const Dispatcher<Tid, Tevent>& other) = default;

		virtual inline void subscribe(const Tid& id, IListener<Tevent>& subscriber) override;
		virtual inline void unsubscribe(const Tid& id) override;
		virtual inline bool is_subscribed(const Tid& id) const override;
		inline void dispatch(const Tevent& event);
	private:
		std::map<Tid, IListener<Tevent>&> m_listeners;
	};

	template <class Tid, class Tevent>
	inline void Dispatcher<Tid, Tevent>::subscribe(const Tid& id, IListener<Tevent>& subscriber) {
		if (m_listeners.end() != m_listeners.find(id)) {
			throw std::invalid_argument("received id is already subscribed");
		}
		m_listeners.insert({id, subscriber});
	}

	template <class Tid, class Tevent>
	inline void Dispatcher<Tid, Tevent>::unsubscribe(const Tid& id) {
		auto iter = m_listeners.find(id);
		if (m_listeners.end() == iter) {
			throw std::invalid_argument("received id is not subscribed");
		}
		m_listeners.erase(iter);
	}

	template <class Tid, class Tevent>
	inline bool Dispatcher<Tid, Tevent>::is_subscribed(const Tid& id) const {
		return m_listeners.end() != m_listeners.find(id);
	}

	template <class Tid, class Tevent>
	inline void Dispatcher<Tid, Tevent>::dispatch(const Tevent& event) {
		std::for_each(m_listeners.begin(), m_listeners.end(),
			[&](const auto& iter) {
				iter.second.on_event(event);
			}
		);
	}
}

#endif // __DISPATCHER_HPP__